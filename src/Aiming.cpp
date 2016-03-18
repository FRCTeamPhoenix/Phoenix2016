/*
 * Aiming.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Brin Harper
 *
 * The Aiming class takes in the vision data received from the Raspberry Pi, by way
 * of the UDP client.  This data is passed to the Aiming class in the form
 * of an integer array, which represents the coordinates of the target's four corners.
 * Aiming implements the received vision data in order to align and rotate the robot,
 * until the the shooter is positioned correctly to shoot at the desired high target.
 *
 */

#include "Aiming.h"

Aiming::Aiming(Client* client, DriveTrainController* driveTrainController,
      DriveStation* driveStation,LidarHandler* lidar,ShooterController* shooter,
      Encoder* encoder1,Encoder* encoder2) :
   m_client(client),
   m_driveTrainController(driveTrainController),
   m_driveStation(driveStation),
   m_lidar(lidar),
   m_shooter(shooter),
   m_encoder1(encoder1),
   m_encoder2(encoder2)
{
   sendcount=0;
   sameCenterCount=0;
   // Nothing is happening
   setCurrentState(IDLE);
   centered=false;

   // We have not yet approached
   hasApproached=false;
   // By default, we will only be performing a specified part of the aiming process
   // In order to perform the ENTIRE process (including shooting), START should be pressed
   fullProcess=false;

   // "Clean slate" for the target coordinate array!
   memset(m_currentTargetCoordinates,0,8);
   memset(m_centeredEncoders,0,4);
}

// Call this method to begin aiming process - same as manually setting state to first phase of aiming process
void Aiming::beginAiming() {
   setCurrentState(CENTERING);
}

// Gives Aiming class access to image data sent over to client from Raspberry Pi
void Aiming::getNewImageData() {

   if (m_client->checkPacketState()){
   // Updates array of current coordinates with data received by client
      newCenter=true;
      for(int i = 0; i < AimingConstants::numTargetVals; i++) {
         m_currentTargetCoordinates[i] = m_client->getTargetData(i+1);
      }
   }
}
// Turns robot to line up with target, once target is within field of vision
void Aiming::centering() {

   if ((m_driveTrainController->getCurrentState()==DriveTrainController::IDLE
         || m_driveTrainController->getCurrentState()==DriveTrainController::TELEOP )){
      driveIdle=true;
   }

   if (deviation > -AimingConstants::distanceVariance && deviation < AimingConstants::distanceVariance){
      centered=true;

      for (int i =0;i<4;i++){
         m_centeredEncoders[i]=m_currentTargetCoordinates[i+2];
      }
   }
   else {
      centered=false;
   }



   //only move if the drivetrain is idle and we have received the most recent packet
   if (driveIdle && (m_targetCenter_x != 0) && !centered){
//      dataRequested=false;
//      requestedDataReceived=false;
      rotate();

   }
   if (centered){
      setCurrentState(ENCODERCENTER);
   }
}
void Aiming::rotate(){


   if(deviation< -AimingConstants::rotationVariance){
      m_driveTrainController->aimRobotCounterclockwise(fabs(deviation/20), 0.6f);

   }
   //move robot cw if target is left of desired
   else if (deviation > AimingConstants::rotationVariance){
      m_driveTrainController->aimRobotClockwise(fabs(deviation/20), 0.6f);

   }
}

void Aiming::approachTarget() {


   // Decide if we need to move forward or backwards
   if (m_lidar->getFastAverage() < AimingConstants::aimedDistance - AimingConstants::distanceVariance){
      m_driveTrainController->moveRobotStraight(-6,0.5f);
   }
   else if (m_lidar->getFastAverage() > AimingConstants::aimedDistance + AimingConstants::distanceVariance){
         m_driveTrainController->moveRobotStraight(6,0.5f);
   }

   // We're done approaching and can move to the next phase we need!
   else {
      hasApproached=true;
      if (fullProcess){
         setCurrentState(CENTERING);

      }
      else {
         setCurrentState(IDLE);
      }

   }
}
void Aiming::encoderCenter(){

   int centerEncoder1=m_currentTargetCoordinates[2] ;
   int centerEncoder2=m_currentTargetCoordinates[3];
   int degreeDifference;
   bool hasMoved=false;

   if ((m_driveTrainController->getCurrentState()==DriveTrainController::IDLE
         || m_driveTrainController->getCurrentState()==DriveTrainController::TELEOP )){
      driveIdle=true;
   }

   if (!hasMoved){

      degreeDifference=encoderDistanceToDegrees(m_encoder1->GetDistance(),m_encoder2->GetDistance())
            -encoderDistanceToDegrees(centerEncoder1,centerEncoder2);

      cout << degreeDifference;
      m_driveTrainController->aimRobotClockwise(degreeDifference,0.6f);
      hasMoved=true;
   }
   else if (hasMoved && driveIdle){
      setCurrentState(IDLE);
   }
}


int Aiming::encoderDistanceToDegrees(int encoder1, int encoder2){

   int degrees;
   int encoderTickDifference;
   double fractionOfCircumference;

   encoderTickDifference = encoder1 - encoder2;
   encoderTickDifference /=2;
   fractionOfCircumference = (double) (encoderTickDifference / AimingConstants::circumferenceOfRotation);
   degrees = fractionOfCircumference * 360;

   return degrees;
}

void Aiming::sendEncoderData(){
   sendcount++;
   memset(sendData,0,2);
   memset(byteData,0,8);
   sendData[0] = m_encoder1->GetDistance();
   sendData[1] = m_encoder2->GetDistance();

   if (sendcount%2000 ==0){
      cout <<"sending packet number "<<sendcount<<endl;
      for (int i =0;i<9;i++){
         cout << sendData[i] << " ";
      }
   }

   for (int i =0; i<2;i++){
      char * intbytes= m_client->intToBytes(sendData[0]);
      for (int j =0;j <4 ;j++){
         byteData[i*4+j]=intbytes[j];
      }
   }
   m_client->sendPacket(byteData);
}
void Aiming::setTargetCoordinateValue(AimingConstants::targetPositionData position, int newValue) {
   m_currentTargetCoordinates[position] = newValue;
}

Aiming::STATE Aiming::getCurrentState() {
   return m_currentState;
}

void Aiming::setFullProcess(bool processVariant) {
   fullProcess = processVariant;
}

void Aiming::setCurrentState(Aiming::STATE newState) {
   m_currentState = newState;
}

// Outputs current coordinate values of target corners, in the following format:
// "(xUpperLeft, yUpperLeft), (xUpperRight, yUpperRight), (xLowerLeft, yLowerLeft),
// (xLowerRight, yLowerRight)"
void Aiming::printCurrentCoordinates() {
   cout << "(" << m_currentTargetCoordinates[AimingConstants::xUL] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yUL] << "), (" <<
         m_currentTargetCoordinates[AimingConstants::xUR] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yUR] << "), (" <<
         m_currentTargetCoordinates[AimingConstants::xLL] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yLL] << "), (" <<
         m_currentTargetCoordinates[AimingConstants::xLR] << ", " <<
         m_currentTargetCoordinates[AimingConstants::yLR] << ")" << endl;
}
int Aiming::getCenter(){
   return m_targetCenter_x;
}
int Aiming::getDeviation(){
   return deviation;
}
// Called to implement all aiming mechanisms
void Aiming::run() {

   if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonA)) {
         setCurrentState(IDLE);
   }

   getNewImageData();
   sendEncoderData();
      //previousTargetCenter=m_targetCenter_x;

   m_targetCenter_x=m_currentTargetCoordinates[0];

   deviation = (m_targetCenter_x - AimingConstants::desiredCenter);

   switch(m_currentState) {
   case IDLE:
      m_driveTrainController->setGoalState(m_driveTrainController->TELEOP);
      fullProcess=false;
      hasApproached=false;
      previousTargetCenter=-1;


      //SmartDashboard::PutString("DB/String 0", "State: IDLE" );

      if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonStart)) {
            fullProcess=true;
            setCurrentState(CENTERING);
      }
      else if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonB)) {
         setCurrentState(APPROACHING);
      }
      else if(m_driveStation->getGamepadButton(DriveStationConstants::buttonNames::buttonY)) {
         setCurrentState(CENTERING);
      }

      break;
   case CENTERING:
      //SmartDashboard::PutString("DB/String 0", "State: Centering" );
      getNewImageData();
      centering();
      break;
   case APPROACHING:
      //SmartDashboard::PutString("DB/String 0", "State: Approaching" );
      getNewImageData();
      approachTarget();
      break;
   case ENCODERCENTER:
      getNewImageData();
      encoderCenter();
      break;
   default:
      break;
   }
   newCenter=false;

}

Aiming::~Aiming() {
}

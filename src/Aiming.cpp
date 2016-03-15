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

   sameCenterCount=0;
   // Nothing is happening
   setCurrentState(IDLE);
   centered=false;

   dataRequested=false;
   requestedDataReceived=false;
   // We have not yet approached
   hasApproached=false;

   // By default, we will only be performing a specified part of the aiming process
   // In order to perform the ENTIRE process (including shooting), START should be pressed
   fullProcess=false;

   // "Clean slate" for the target coordinate array!
   memset(m_currentTargetCoordinates,0,8);
   memset(requestArray,3,9);
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
void Aiming::getRequestedData(){

   if(m_client->m_unreadResponseData){
      requestedDataReceived=true;
      for(int i = 0; i < AimingConstants::numTargetVals; i++) {
          m_currentTargetCoordinates[i] = m_client->getResponseData(i+1);
       }

      m_targetCenter_x=((m_currentTargetCoordinates[AimingConstants::xUL]
                               +m_currentTargetCoordinates[AimingConstants::xLR])/2);
      deviation = (m_targetCenter_x - AimingConstants::desiredCenter);

   }
}
// Turns robot to line up with target, once target is within field of vision
void Aiming::centering() {

//   if(!dataRequested){
//      m_client->sendPacket(m_client->intToByte(requestArray));
//      dataRequested=true;
//   }
//
//   if (!requestedDataReceived){
//      getRequestedData();
//   }


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
      moveDirection="ccw";
      m_driveTrainController->aimRobotCounterclockwise(fabs(deviation/20), 0.6f);

   }
   //move robot cw if target is left of desired
   else if (deviation > AimingConstants::rotationVariance){
      moveDirection="cw";
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

   int centerEncoder1;
   int centerEncoder2;
   int degreeDifference;
   if (m_centeredEncoders[0]==0){
      centerEncoder1=(-1*m_centeredEncoders[1]);
   }
   else {
      centerEncoder1=m_centeredEncoders[1];
   }
   if (m_centeredEncoders[2]==0){
      centerEncoder2=(-1*m_centeredEncoders[3]);
   }
   else {
      centerEncoder2=m_centeredEncoders[3];
   }
   degreeDifference=encoderDistanceToDegrees(m_encoder1->Get(),m_encoder2->Get())
         -encoderDistanceToDegrees(centerEncoder1,centerEncoder2);

   m_driveTrainController->aimRobotClockwise(degreeDifference,0.6f);
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
   int sendData[9];
   char byteData[18];
   memset(sendData,0,18);
   memset(sendData,0,9);
   int encoder1Ticks = m_encoder1->Get();
   int encoder2Ticks = m_encoder2->Get();
   //zero means negative 1 is positive

   if(encoder1Ticks<0){
      sendData[0]=0;
      sendData[1]=(-1*encoder1Ticks);
   }
   else {
      sendData[0]=1;
      sendData[1]=encoder1Ticks;
   }
   if (encoder2Ticks<0){
      sendData[2]=0;
      sendData[3]=encoder2Ticks;
   }
   else {
      sendData[2]=0;
      sendData[3]=encoder2Ticks;
   }

   m_client->copyArray(*m_client->byteToInt(byteData,sendData),byteData);
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
int Aiming::getSameCenter(){
   return sameCenterCount;
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

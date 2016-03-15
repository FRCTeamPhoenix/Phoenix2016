/*
 * Aiming.h
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

#ifndef SRC_AIMING_H_
#define SRC_AIMING_H_
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))
#include <cmath>
#include "Client.h"
#include "DriveTrainController.h"
#include "ShooterController.h"
#include "constants.h"
#include <cmath>

class Aiming {
public:

   enum STATE {
         IDLE,
         CENTERING,
         APPROACHING,
         REVERTING,
         SHOOTING,
         ENCODERCENTER
      };

   Aiming(Client*, DriveTrainController*, DriveStation*,LidarHandler*,
         ShooterController*,Encoder*encoder1, Encoder*encoder2);
   void getNewImageData();
   void getRequestedData();
   void beginAiming();
   void centering();
   void approachTarget();
   void revert();
   void shoot();
   void rotate();
   void encoderCenter();
   STATE getCurrentState();
   void setTargetCoordinateValue(AimingConstants::targetPositionData, int);
   void setCurrentState(STATE);
   void setFullProcess(bool);
   void printCurrentCoordinates();
   void run();
   void encoderGet();
   int getCenter();
   int getDeviation();
   int getSameCenter();
   void sendEncoderData();
   int encoderDistanceToDegrees(int, int);
   virtual ~Aiming();

private:

   Client* m_client;
   DriveTrainController* m_driveTrainController;
   DriveStation* m_driveStation;
   LidarHandler * m_lidar;
   ShooterController *m_shooter;
   Timer m_timer;
   Encoder* m_encoder1;
   Encoder* m_encoder2;
   int m_currentTargetCoordinates[8];
   STATE m_currentState;
   bool lastArrayWasNull;
   bool hasApproached;
   bool hasRotated;
   bool fullProcess;
   bool centered;
   double previousTargetCenter;
   double m_targetCenter_x;
   double deviation;
   bool driveIdle;
   bool newCenter;
   bool dataRequested;
   bool requestedDataReceived;
   int sameCenterCount;
   int packetCount;
   string moveDirection;
   int  moveCount;
   int requestArray[9];
   int m_centeredEncoders[4];
};

#endif /* SRC_AIMING_H_ */

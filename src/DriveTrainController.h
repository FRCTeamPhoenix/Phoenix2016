/*
 * DriveTrainController.h
 *
 *  Created on: Jan 14, 2016
 *      Author: Ian
 */

#ifndef SRC_DRIVETRAINCONTROLLER_H_
#define SRC_DRIVETRAINCONTROLLER_H_

#include "BaseController.h"
#include "WPILib.h"
#include "constants.h"
#include "DriveStation.h"

class DriveTrainController: public BaseController {
public:
   enum STATE {
      IDLE,
      NORMAL,
      AUTOTEST,
      AIMING_TARGET,
      AIMING_OBSTACLE,
      OBSTACLE,
      TEST,
      AUTO
   };
   DriveTrainController(RobotDrive* m_driveTrain,
         DriveStation* m_driveStation,
         Encoder* leftWheelEncoder,
         Encoder* rightWheelEncoder);
   virtual ~DriveTrainController();
   void run();
   void autoDrive(void);
   void manualDrive(float throttleRatio);
   void aimRobotClockwise(float degree, float motorSpeed);
   void aimRobotCounterclockwise(float degree, float motorSpeed);
   void stopRobot();

   STATE getCurrentState();
   void setCurrentState(STATE currentState);
   void setDriveConstants(float, float);

private:
   RobotDrive* m_driveTrain;
   DriveStation * m_driveStation;
   Encoder* m_leftWheelEncoder;
   Encoder* m_rightWheelEncoder;
   STATE m_goalState;
   int32_t m_initalEncoderValueLeft;
   int32_t m_initalEncoderValueRight;
   int32_t m_targetTickRight;
   int32_t m_targetTickLeft;
   STATE m_currentState;
   float m_power, m_twist;
};

#endif /* SRC_DRIVETRAINCONTROLLER_H_ */

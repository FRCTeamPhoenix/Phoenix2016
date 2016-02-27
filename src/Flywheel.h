/*
 * Flywheel.h
 *
 *  Created on: Jan 19, 2016
 *      Author: ben
 */

#ifndef SRC_FLYWHEEL_H_
#define SRC_FLYWHEEL_H_
#include "WPILib.h"
#include "BaseController.h"
#include "WheelSpeedController.h"
#include "LidarHandler.h"

class Flywheel : BaseController {
private:
   Talon* m_leftFlywheelMotor;
   Talon* m_rightFlywheelMotor;
   Encoder* m_leftFlywheelEncoder;
   Encoder* m_rightFlywheelEncoder;
   LidarHandler* m_lidar;

   WheelSpeedController m_leftFlywheelController;
   WheelSpeedController m_rightFlywheelController;

   bool m_spinning;
   float m_maxDistance;
   float m_maxDistanceRate;

   float m_minDistance;
   float m_minDistanceRate;



   void setRate(float rate);
   float calculateSpeed();

public:
   Flywheel(Talon* leftFlywheelMotor, Talon* rightFlywheelMotor, Encoder* leftFlywheelEncoder, Encoder* rigtFlywheelEncoder, LidarHandler* lidar);
   virtual ~Flywheel();

   enum STATE{
      OFF,
      NOTREADY,
      READY

   };

   void run();
   STATE getCurrentState();
   void start();
   void stop();
   bool upToSpeed(float tolerance);



};
#endif /* SRC_FLYWHEEL_H_ */

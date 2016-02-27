#pragma once

#include "BaseController.h"

#include <queue>

class DriveStation;
class DriveTrainController;
class ShooterController;
class LoaderController;
class Flywheel;
class ConfigEditor;
class Arm;

class AutoController : public BaseController
{
 public:
   AutoController(DriveStation*, DriveTrainController*, ShooterController*, LoaderController*, Flywheel*, ConfigEditor*, Arm*);

   void run(void);
   void cancel(void);
 private:
   void performAction(void);

   std::queue<Action*> m_queue;

   DriveStation* m_driveStation;
   DriveTrainController* m_driveTrain;
   ShooterController* m_shooterController;
   LoaderController* m_loaderController;
   Flywheel* m_flywheel;
   ConfigEditor* m_configEditor;
   Arm* m_arm;
};

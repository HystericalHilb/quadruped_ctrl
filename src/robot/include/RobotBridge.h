/*!
 * @file RobotBridge.h
 * @brief Interface between robot code and robot hardware
 *
 * This class initializes the hardware of both robots and allows the robot
 * controller to access it
 */

#ifndef PROJECT_ROBOTBRIDGE_H
#define PROJECT_ROBOTBRIDGE_H

#include <string>

#include "RobotRunner.h"
#include "Utilities/PeriodicTask.h"

/*!
 * Interface between robot and hardware
 */
class RobotBridge {
 public:
  RobotBridge(RobotController* robot_ctrl) : statusTask(&taskManager, 0.5f) {
    _controller = robot_ctrl;
    _userControlParameters = robot_ctrl->getUserControlParameters();
  }
  ~RobotBridge() { delete _robotRunner; }

 protected:
  PeriodicTaskManager taskManager;
  PrintTaskStatus statusTask;
  GamepadCommand _gamepadCommand;

  bool _firstRun = true;
  RobotRunner* _robotRunner = nullptr;
  RobotControlParameters _robotParams;
  RobotController* _controller = nullptr;
  ControlParameters* _userControlParameters = nullptr;
};

/*!
 * Interface between robot and hardware/simulator specialized for Mini Cheetah
 */
class MiniCheetahRobotBridge : public RobotBridge {
 public:
  MiniCheetahRobotBridge(RobotController* rc, std::string runningType);
  void initRobot();
  void run();

 private:
  VectorNavData _vectorNavData;
  std::string _runningType = "sim";
};

#endif
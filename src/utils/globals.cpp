#include "main.h"

#include "main.h"
#include "pros/adi.hpp"


//DRIVETRAIN MOTORS


pros::Motor driveleftfront(3, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driverightfront(16, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor leftmid(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rightmid(8, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveleftback(18, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driverightback(14, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);



pros::MotorGroup leftdrive({driveleftfront,leftmid, driveleftback});
pros::MotorGroup rightdrive({driverightfront,rightmid, driverightback});
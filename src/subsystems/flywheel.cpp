#include "main.h"


//--------------------------------------------------------------------------------------------CONSTANTS--------------------------------------------------------------------------------------------
#define FLYWHEEL_GEARSET pros::E_MOTOR_GEARSET_06
#define FLYWHEEL_PORT 19



bool maintainSpeed = true;
double targetspeed = 600;
double kp = 0.5;
double ki = 0.10;
double kd = 0.05;
double preverror = 0.0;
double error = 0.0;
double totalError = 0.0; // += error
double derivative = 0.0; // = error-preverror
double flyspeed;
double Power = 0;
bool ReadyShoot = false;
double final_velocity;
#define FLYWHEEL_GEARSET pros::E_MOTOR_GEARSET_06
#define INTAKE_GEARSET pros::E_MOTOR_GEARSET_18

pros::Controller master(pros::E_CONTROLLER_MASTER);
//--------------------------------------------------------------------------------------------FLYWHEEL--------------------------------------------------------------------------------------------
namespace flywheel{
    okapi::Motor motor(5);
    
    int targetSpeed = 0;
    double actualSpeed = 0;
    auto flywheel_read = okapi::DemaFilter(0.1,0.1);
    int voltageUpdate() {
        if (targetSpeed == 0)  {motor.moveVoltage(0); return 0; }
        actualSpeed = flywheel_read.filter(motor.getActualVelocity());
        int currentVoltage = actualSpeed * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
        int convertedTarget = targetSpeed * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
        int error = (convertedTarget - currentVoltage) * 0.3;
        int finalVoltage = convertedTarget + error;
        motor.moveVoltage(finalVoltage);
        return finalVoltage;
    };

    void setTargetSpeed(double pwr) {
        targetSpeed = TECHNICAL_FLYWHEEL_RPM * pwr;
        voltageUpdate();
    };
    
}


#include "main.h"


//--------------------------------------------------------------------------------------------CONSTANTS--------------------------------------------------------------------------------------------
#define FLYWHEEL_GEARSET pros::E_MOTOR_GEARSET_06
#define FLYWHEEL_PORT 19




double flywheelRatio = 15;


velPID flywheelPID(0.35, 0.05, 0.045, 0.9);
emaFilter rpmFilter(0.15);



double motorSlew = 0.7;

double targetRPM = 0;
double currentRPM = 0;
double lastPower = 0;
double motorPower = 0;

//--------------------------------------------------------------------------------------------FLYWHEEL--------------------------------------------------------------------------------------------
namespace flywheel{

    double targetSpeed;
    pros::Motor motor(FLYWHEEL_PORT, true);

    //FUNCTIONS
    
    
    void loop(double target_speed){
        targetRPM = target_speed;
        while(true) {
  
        currentRPM = rpmFilter.filter((motor.get_actual_velocity()) * flywheelRatio);
  
        motorPower = flywheelPID.calculate(targetRPM, currentRPM);
  
        if(motorPower <= 0) motorPower = 0; //Prevent motor from spinning backward
  
        //Give the motor a bit of a starting boost
        if(motorPower > lastPower && lastPower < 10 && motorPower > 10) lastPower = 10;
  
        //This slews the motor by limiting the rate of change of the motor speed
        double increment = motorPower - lastPower;
        if(std::abs(increment) > motorSlew) motorPower = lastPower + (motorSlew * sgn(increment));
            lastPower = motorPower;
  
        motor.move(motorPower);
  
        std::cout << "RPM: " << currentRPM << " Power: "<< motorPower << " Error: "<< flywheelPID.getError() << "\n";
        pros::delay(20);
}
    }
    //--------------------------------------------------------------------------------------------SET TARGET SPEED--------------------------------------------------------------------------------------------
    void setTargetSpeed(double speed){
        targetSpeed = speed;
        loop(targetSpeed);
    }
    
    
}

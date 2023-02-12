#include "main.h"


//CONSTANTS
#define FLYWHEEL_GEARSET pros::E_MOTOR_GEARSET_18
#define FLYWHEEL_PORT 15

namespace flywheel{
    
    //CONSTANTS
    int targetSpeed = 0;
    double actualSpeed = 0;
    bool maintainSpeed = true;
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


    //FLYWHEEL MOTOR
    pros::Motor motor(FLYWHEEL_PORT, FLYWHEEL_GEARSET, true);

    //FUNCTIONS
    
    
    void loop(double target_speed){
        motor.set_brake_mode(MOTOR_BRAKE_COAST);
        
        while(true){
            
            flyspeed = motor.get_actual_velocity();
            error = target_speed - flyspeed;
            
            
            Power += (error*kp + totalError * ki + (error - preverror) * kd)/12;
            motor.move_voltage(Power);
            
            preverror = error;
            totalError += error;

            pros::delay(20);

        }
    }

    void setTargetSpeed(double speed){
        targetSpeed = speed;
        loop(targetSpeed);
    }
    
    
}

#include "main.h"


//CONSTANTS
#define FLYWHEEL_GEARSET pros::E_MOTOR_GEARSET_18
#define FLYWHEEL_PORT 19




PID flywheel_PID{1 , 0.003, 4, 100, "flywheel"}; //tune

namespace flywheel{

    double targetSpeed;
    pros::Motor motor(FLYWHEEL_PORT, FLYWHEEL_GEARSET, true);

    //FUNCTIONS
    
    
    void loop(double target_speed){
        motor.set_brake_mode(MOTOR_BRAKE_COAST);
        
        while(true){
            flywheel_PID.set_target(target_speed);
            motor = flywheel_PID.compute(motor.get_position());

        }
    }

    void setTargetSpeed(double speed){
        targetSpeed = speed;
        loop(targetSpeed);
    }
    
    
}

#include "main.h"


//CONSTANTS
#define INTAKE_GEARSET pros::E_MOTOR_GEARSET_18
#define INTAKE_PORT 15

namespace intake{
    //FLYWHEEL MOTOR
    pros::Motor motoruwu(INTAKE_PORT, INTAKE_GEARSET);

    void intakefordrive(){
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
            motoruwu.move_voltage(1200);
        }else{
            motoruwu.move_voltage(0);
        }
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
            motoruwu.move_voltage(-1200);
        }else{
            motoruwu.move_voltage(0);
        }
    };

    void intake_for_time(bool mode, int time){
        if(mode == true){
            motoruwu.move_voltage(12000);
            pros::delay(time);
            motoruwu.move_voltage(0);

        }else{
            motoruwu.move_voltage(-12000);
            pros::delay(time);
            motoruwu.move_velocity(0);
        }
    }
    
}

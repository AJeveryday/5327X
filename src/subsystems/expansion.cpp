#include "main.h"

namespace expansion{
    //CONFIG
    bool isTriggered = false;
    pros::ADIDigitalOut expansion1('A', isTriggered);
    

    void fire(){
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
            isTriggered = true;
        }
    }
}
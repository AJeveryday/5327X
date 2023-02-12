#include "main.h"


//------------------------------------------------------------CHASSIS PID CONFIGURATIONS----------------------------------------------------------------

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;




// PID constants


void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

//---------------------------------------------------LEFT-AUTONOMOUS-------------------------------------------------------------------------
void autonomous_left(){
    chassis.set_drive_pid(27, 90, false, true);
}



//---------------------------------------------------RIGHT-AUTONOMOUS-------------------------------------------------------------------------
void autonomous_right(){
    //flywheel.move_velocity(600);
    chassis.set_drive_pid(-23.4, DRIVE_SPEED, true);  // Move 23.4 inches backward
    chassis.wait_drive(); 
    chassis.set_turn_pid(90, TURN_SPEED);             // Turn 90 degrees clockwise
    chassis.wait_drive();
    chassis.set_drive_pid(-6, DRIVE_SPEED, true);     // Move 5 inches backward
    chassis.wait_drive();
    //autonroller();                                    // Claim Roller
    chassis.wait_drive();
    chassis.set_drive_pid(10, DRIVE_SPEED, true);     // Move 10 inches forward
    chassis.wait_drive();
  
  //outtakeon();
  pros::delay(3000);
  //intakeoff();
}







//---------------------------------------------------SOLO-AWP-------------------------------------------------------------------------
void soloawp(){
    chassis.set_drive_pid(27, 90, false, true);
}





//---------------------------------------------------SKILLS-AUTONOMOUS-------------------------------------------------------------------------
void skills_autonomous(){
    chassis.set_drive_pid(27, 90, false, true);
}
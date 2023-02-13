#include "main.h"


//------------------------------------------------------------CHASSIS PID CONFIGURATIONS----------------------------------------------------------------

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;
const int INTAKE_SPEED = 45;




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
    
    flywheel::setTargetSpeed(3600);                                             // start flywheel
    intake::intake_for_time(false,2000);                                      //hit rollers
    chassis.set_drive_pid(0.5, DRIVE_SPEED, false, true);                    // forward by a little
    intake::intake_for_time(false, 1500);                                   //index first disk
    pros::delay(200);
    intake::intake_for_time(false, 1500);                                 //index second disk
    pros::delay(200);

    chassis.set_drive_pid(-2.5, 45, false, true);                       //move back slightly after shooting
    chassis.wait_drive();
    chassis.set_turn_pid(44.5, TURN_SPEED);                           //turn bot
    chassis.wait_drive();
    intake::intake_for_time(true, 7000);                            //start intake
    chassis.wait_drive();
    chassis.set_drive_pid(60.5, 45, false, true);                     //drive forward to intake disks till halfway of the field
    chassis.wait_drive();
    chassis.set_turn_pid(-45, 80);                                      // turn towards goal
    chassis.wait_drive();
    chassis.set_drive_pid(2.5, 45, false, true);                          //go forward slightly
    chassis.wait_drive();
    intake::intake_for_time(false, 1500);                                     //index first disk
    pros::delay(200);
    intake::intake_for_time(false, 1500);                                         //index second disk
    pros::delay(200);
    intake::intake_for_time(false, 1500);                                             //index third disk

    


}



//---------------------------------------------------RIGHT-AUTONOMOUS-------------------------------------------------------------------------
void autonomous_right(){
    flywheel::setTargetSpeed(3600);
    chassis.set_drive_pid(-23.4, DRIVE_SPEED, true);                                                // Move 23.4 inches backward
    chassis.wait_drive(); 
    chassis.set_turn_pid(90, TURN_SPEED);                                                         // Turn 90 degrees clockwise
    chassis.wait_drive();
    chassis.set_drive_pid(-6, DRIVE_SPEED, true);                                               // Move 5 inches backward
    chassis.wait_drive();
    intake::intake_for_time(false, 4000);                                                     // Claim Roller
    chassis.wait_drive();
    chassis.set_drive_pid(4.5, DRIVE_SPEED, false, true);                                   // forward by a little
    //shoot
    intake::intake_for_time(false, 1500);                                                 //index first disk
    pros::delay(200);
    intake::intake_for_time(false, 1500);                                               //index second disk
    pros::delay(200);
    chassis.set_turn_pid(-45, 90);                                                   // turn 45 degrees to intake disks
    chassis.wait_drive();
    intake::intake_for_time(true, 7000);                                                 //start intake

    chassis.set_drive_pid(60.5, 45, false, true);                                           //drive forward to intake disks till halfway of the field
    chassis.wait_drive();
    chassis.set_turn_pid(-45, 80);                                                              // turn towards goal
    chassis.wait_drive();
    chassis.set_drive_pid(2.5, 45, false, true);                                                    //go forward to auton line by a little
    chassis.wait_drive();
    intake::intake_for_time(false, 1500);                                                               //index first disk
    pros::delay(200);
    intake::intake_for_time(false, 1500);                                                                   //index second disk
    pros::delay(200);
    intake::intake_for_time(false, 1500);                                                                       //index third disk


  
}







//---------------------------------------------------SOLO-AWP-------------------------------------------------------------------------
void soloawp(){
    chassis.set_drive_pid(27, 90, false, true);
}





//---------------------------------------------------SKILLS-AUTONOMOUS-------------------------------------------------------------------------
void skills_autonomous(){
    chassis.set_drive_pid(27, 90, false, true);
}
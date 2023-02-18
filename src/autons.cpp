#include "main.h"

//------------------------------------------------------------CHASSIS PID CONFIGURATIONS----------------------------------------------------------------

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED = 100;
const int SWING_SPEED = 90;
const int INTAKE_SPEED = 45;

// PID constants

void default_constants()
{
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults()
{
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition()
{
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}
pros::Motor intake0(15, pros::E_MOTOR_GEARSET_18);

//---------------------------------------------------LEFT-AUTONOMOUS-------------------------------------------------------------------------
void autonomous_left()
{

  chassis.set_drive_pid(-2, 20, false, true);
  intake::intake_for_time(false, 400); // roller
  flywheel::setTargetSpeed(3400);      // flywheel on

  // after roller
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, false, true); // forward 10
  chassis.wait_drive();
  chassis.set_turn_pid(45, TURN_SPEED); // turn 45
  chassis.wait_drive();
  // intake0.();                      // intake 3 secs
  chassis.set_drive_pid(28, DRIVE_SPEED, false, true); // forward 28
  chassis.wait_drive();
  chassis.set_turn_pid(-33, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(9, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  intake::intake_for_time(false, 1500); //
  pros::delay(400);
  intake::intake_for_time(false, 1500); //
  pros::delay(400);
  /*
  chassis.set_drive_pid(-10, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  intake0.move_voltage(12000);
  chassis.set_turn_pid(45,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(20, DRIVE_SPEED, false, true);      // drive forward to intake disks till halfway of the field
  chassis.wait_drive();
  chassis.set_turn_pid(-33, TURN_SPEED);                    // turn towards goal
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, false, true);      // go forward slightly
  chassis.wait_drive();
  intake::intake_for_time(false, 1000);                     // index first disk
  pros::delay(200);                                         // wait 0.2
  intake::intake_for_time(false, 1500);                     // index second disk
  pros::delay(200);                                         // wait 0.2
  chassis.set_drive_pid(-15, DRIVE_SPEED, false,true);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-85.5, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  intake::intake_for_time(false, 400);
  flywheel::setTargetSpeed(0);



  //*/
}

//---------------------------------------------------RIGHT-AUTONOMOUS-------------------------------------------------------------------------
void autonomous_right()
{
  /*
    chassis.reset_gyro();
    chassis.reset_drive_sensor();
    flywheel::setTargetSpeed(0.64);
    chassis.set_drive_pid(22, 120, false, true);
    chassis.wait_drive();
    chassis.set_turn_pid(27, TURN_SPEED);

    chassis.wait_drive();
    pros::delay(2000);
    intake::intake_for_time(false, 300);                     //
    pros::delay(700);
    intake::intake_for_time(false, 2000);                     //
    pros::delay(400);
    chassis.set_turn_pid(-51, 127);
    chassis.wait_drive();
    intake0.move_voltage(12000);
    chassis.set_drive_pid(30, 120, false, true);
    chassis.wait_drive();
    chassis.set_drive_pid(-30, 120, false, true);
    chassis.wait_drive();
    chassis.set_turn_pid(27, TURN_SPEED);
    pros::delay(2000);
    intake::intake_for_time(false, 300);                     //
    pros::delay(700);
    intake::intake_for_time(false, 2000);
    chassis.set_turn_pid(-67.5, 90);
    chassis.wait_drive();
    chassis.set_drive_pid(-30, DRIVE_SPEED, false, true);
    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();
    intake::intake_for_time(false, 400);
  */
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_angle(-90);
  
  flywheel::setTargetSpeed(0.93333);
  chassis.set_drive_pid(-20, DRIVE_SPEED, true); // Move 23.4 inches backward
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED); // Turn 90 degrees clockwise
  chassis.wait_drive();
  chassis.set_drive_pid(-8, DRIVE_SPEED, true); // Move 5 inches backward
  chassis.wait_drive();

  intake::intake_for_time(true, 500); // Claim Roller

  chassis.set_drive_pid(18, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  
  chassis.set_turn_pid(14, TURN_SPEED); // Turn  degrees clockwise
  chassis.wait_drive();
  intake::intake_for_time(false, 300); //
  pros::delay(2000);
  intake::intake_for_time(false, 3000);
  chassis.set_swing_pid(LEFT_SWING, -50, 90);
  chassis.wait_drive();
  intake0.move_voltage(12000);
  chassis.set_drive_pid(35, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  
  flywheel::setTargetSpeed(0.8);
  pros::delay(2000);
  //chassis.set_turn_pid(31, TURN_SPEED);
  
  chassis.wait_drive();
  pros::delay(2000);
  chassis.set_drive_pid(8, DRIVE_SPEED, false, true);
  intake::intake_for_time(false, 300); //
  pros::delay(900);
  intake::intake_for_time(false, 2000);
  flywheel::setTargetSpeed(0);
}

//---------------------------------------------------SOLO-AWP-------------------------------------------------------------------------
void soloawp()
{
  chassis.set_drive_pid(-2, 20, false, true);
  intake::intake_for_time(false, 400); // roller
  flywheel::setTargetSpeed(3400);      // flywheel on

  // after roller
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, false, true); // forward 10 from roller
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED); // turn 45 ready for first dash to middle
  chassis.wait_drive();
  chassis.set_drive_pid((-132.4/2), DRIVE_SPEED, false, true); // first dash
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED); // angles towards high goal for shooting
  chassis.wait_drive();
  
  flywheel::setTargetSpeed(0.8); //shoots
  pros::delay(2000);
  chassis.set_turn_pid(31, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-45, TURN_SPEED); // turn 45 prepares for dash to second roller
  chassis.wait_drive();
  chassis.set_drive_pid((-133.4/2), DRIVE_SPEED, false, true); //dash to second roller after shooting (needs tunign)
  chassis.wait_drive();
  chassis.set_drive_pid(-5, DRIVE_SPEED, false, true);
  chassis.wait_drive();
  intake::intake_for_time(true, 500); // Claim Roller
  
}

//---------------------------------------------------SKILLS-AUTONOMOUS-------------------------------------------------------------------------
void skills_autonomous()
{
  soloawp();
  chassis.set_drive_pid(25, DRIVE_SPEED, false, true); // forward 10 from roller
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED); // turn 45 ready for first dash to middle
  chassis.wait_drive();
  chassis.set_drive_pid(-25, DRIVE_SPEED, false, true); // forward 10 from roller
  chassis.wait_drive();
  soloawp();
  chassis.set_drive_pid(25, DRIVE_SPEED, false, true); // forward 10 from roller
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED); // turn 45 ready for first dash to middle
  chassis.wait_drive();
  chassis.set_drive_pid(15, DRIVE_SPEED, false, true); // forward 10 from roller
  chassis.wait_drive();
  chassis.set_turn_pid(45, TURN_SPEED); // turn 45 ready for first dash to middle
  chassis.wait_drive();

  




}
#include "main.h"

/******************************************************************************/
/**                              Welcome to 5327X                            **/
/**                                                                          **/
/**                                    Wauw   								 **/
/******************************************************************************/
//-------------------------------------------CHASSIS-CONSTRUCTOR------------------------------------------------------------------------------------
Drive chassis(
	{-18, -9, -11},

	// Right Chassis Ports (negative port will reverse it!)
	{14, 13, 3}

	,
	21 // imu sensor
	,
	4.125 // Wheel Diameter
	,
	600 // Cartridge RPM
	,
	2.333 // External Gear Ratio (MUST BE DECIMAL)
		  // rotational ports if neccesary
);
pros::Motor flywheel1(5, pros::E_MOTOR_GEARSET_18);
// FLYWHEEL OBJECT--------------------
void screen_task(){
	pros::lcd::print(5,"flywheel speed", flywheel1.get_actual_velocity());
}
void wait(int waitTime) {
    int t = 0;
    while (t < waitTime) {
        t += 2;
        flywheel::voltageUpdate();
        pros::delay(20);
    };
};
//-------------------------------------------PROGRAM-INITIALIZE---------------------------------------------------------------------------------
void initialize()
{

	// Chassis Configurations
	pros::Task screentask(screen_task);
	chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
	chassis.set_active_brake(0.2);					   // Sets the active brake kP. We recommend 0.1.
	chassis.set_curve_default(0, 0);				   // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
	default_constants();							   // sets chassis PID values
	exit_condition_defaults();						   // sets chassis PID values
	chassis.set_joystick_threshold(5);
	// autonomous selector

	ez::as::initialize();
	ez::as::auton_selector.add_autons({
		//Auton("Left autonomous", autonomous_left),			   // left auton
		//Auton("Right autonomous", autonomous_right),		   // right auton
		Auton("Soloawp autonomous juicy lookin ahh", soloawp), // soloawp auton
		// Auton("Skills autonomous", autonomous_skills) //skills
	});
	ez::as::auton_selector.print_selected_auton();

	// IMU calibration
	chassis.imu_calibrate();
	// chassis initialization
	chassis.initialize();
}

//-------------------------------------------COMPETITION-DISABLED---------------------------------------------------------------------------------
void disabled()
{
	// autonomous selector for competition
	ez::as::auton_selector.add_autons({
		//Auton("Right autonomous", autonomous_right),		   // right auton
		//Auton("Left autonomous", autonomous_left),			   // left auton
		Auton("Soloawp autonomous juicy lookin ahh", soloawp), // soloawp auton
	});
}

void enabled()
{
	ez::as::auton_selector.call_selected_auton();
}


//-------------------------------------------COMPETITION-INITIALIZE---------------------------------------------------------------------------------
void competition_initialize()
{
	// autonomous selector for competition
	ez::as::auton_selector.call_selected_auton();
}

//-------------------------------------------COMPETITION-AUTONOMOUS---------------------------------------------------------------------------------
void autonomous()
{
	// reset chassis configuration info
	chassis.reset_gyro();
	chassis.reset_drive_sensor();
	chassis.set_drive_brake(MOTOR_BRAKE_HOLD);

	// Autonomous selector
	// ez::as::auton_selector.call_selected_auton();
	//ez::as::auton_selector.call_selected_auton();
	autonomous_right();
	
}

bool isTriggered = false;

pros::Motor intake01(12, pros::E_MOTOR_GEARSET_18);
pros::ADIDigitalOut expansion1('A', isTriggered);



//-----------------------------------------------DRIVER-CONTROL---------------------------------------------------------------------------------
void opcontrol()
{
	int intake01_mode = 0;
	flywheel::setTargetSpeed(0);
	//---------------------------------odometry-------------------------------------------
	// positionTracking();
	while (true)
	{
		chassis.joy_thresh_opcontrol(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
		chassis.tank(); // tank drive
		//pros::Task screentask(screen_task);
		// flywheel
		if ((master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)))  
		{ // When L1 pressed,
    	  	flywheel::setTargetSpeed(LONG_RANGE_POWER);
    	  	wait(3);
    	}

    	if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))    
		{ // When L2 pressed,
    	  	flywheel::setTargetSpeed(SHORT_RANGE_POWER);
    	  	wait(3);
    	}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
		{
			flywheel::setTargetSpeed(-0.3333333);
			pros::delay(3000);
		}
		
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
		{
			flywheel::setTargetSpeed(0);
			pros::delay(20);
		}

		// intake01/Outtake
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
		{ // When R1 pressed,
			if (intake01_mode != 1)
			{								 			// If intake not running,
				intake01.move_voltage(12000); 			// Run intake
				intake01_mode = 1;
			}
			else {										// If intake already running,
				intake01.move_voltage(0); 				// Turn off intake motor
				intake01_mode = 0;
			}
		}
		// Outtake
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) 
		{ // When R2 pressed,
			if (intake01_mode != -1)
			{								 			// If outtake not running,
				intake01.move_voltage(-12000); 			// Run outtake
				intake01_mode = -1;
			}
			else {										// If outtake already running,
				intake01.move_voltage(0); 				// Turn off intake motor
				intake01_mode = 0;
			}
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
			intake01.move_voltage(0);
		}
		// Expansion

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
			isTriggered = true;

		}
	}
}
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
	{14, 13, 1}

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

// FLYWHEEL OBJECT--------------------

//-------------------------------------------PROGRAM-INITIALIZE---------------------------------------------------------------------------------
void initialize()
{

	// Chassis Configurations
	chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
	chassis.set_active_brake(0.2);					   // Sets the active brake kP. We recommend 0.1.
	chassis.set_curve_default(0, 0);				   // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
	default_constants();							   // sets chassis PID values
	exit_condition_defaults();						   // sets chassis PID values

	// autonomous selector

	ez::as::initialize();
	ez::as::auton_selector.add_autons({
		Auton("Left autonomous", autonomous_left),			   // left auton
		Auton("Right autonomous", autonomous_right),		   // right auton
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
		Auton("Right autonomous", autonomous_right),		   // right auton
		Auton("Left autonomous", autonomous_left),			   // left auton
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
	ez::as::auton_selector.call_selected_auton();
}

bool isTriggered = false;

pros::Motor intake01(15, pros::E_MOTOR_GEARSET_18);
pros::ADIDigitalOut expansion1('A', isTriggered);
//-----------------------------------------------DRIVER-CONTROL---------------------------------------------------------------------------------
void opcontrol()
{
	int intake01_mode = 0;
	//---------------------------------odometry-------------------------------------------
	// positionTracking();
	while (true)
	{
		chassis.tank(); // tank drive

		// flywheel
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
		{
			flywheel::setTargetSpeed(3600);
			pros::delay(3000);
		}
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
		{
			flywheel::setTargetSpeed(2000);
			pros::delay(3000);
		}
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
		{
			flywheel::setTargetSpeed(-0.3333333);
			pros::delay(3000);
		}
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			flywheel::setTargetSpeed(0);
			pros::delay(20);
		}

		// intake011/Outtake
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
		{ // When R1 pressed,
			if (intake01_mode == 0)
			{								 // If intake01 not running,
				intake01.move_voltage(1200); // Run intake01
				intake01_mode = 1;
			}
			else
			{							  // If intake01 already running,
				intake01.move_voltage(0); // Turn off intake01 motor
				intake01_mode = 0;
			}
		}
		// Outtake
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
		{ // When R2 pressed,
			if (intake01_mode == 0)
			{								   // If outtake not running,
				intake01.move_voltage(-12000); // Run Outtake
				intake01_mode = -1;
			}
			else
			{							  // If outtake already running,
				intake01.move_voltage(0); // Turn off intake01 motor
				intake01_mode = 0;
			}
		}

		// Expansion

		// if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
		// isTriggered = true;
		//}
	}
}
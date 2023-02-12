#include "main.h"

//-------------------------------------------CHASSIS-CONSTRUCTOR------------------------------------------------------------------------------------
Drive chassis (
  {1, -2, 3} //left chassis ports
  ,{-4, 5, -6} //right chassis ports
  ,21 //imu sensor
  ,4.125 // Wheel Diameter
  ,600 // Cartridge RPM
  ,2.333 // External Gear Ratio (MUST BE DECIMAL)
);

//-------------------------------------------PROGRAM-INITIALIZE---------------------------------------------------------------------------------
void initialize() {

	//Chassis Configurations
	chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  	chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  	chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  	default_constants(); //sets chassis PID values
  	exit_condition_defaults(); //sets chassis PID values 
	
	
	//autonomous selector
	ez::as::initialize();
	ez::as::auton_selector.add_autons({
		Auton("Left autonomous", autonomous_left), // left auton
		Auton("Right autonomous", autonomous_right), //right auton
		Auton("Soloawp autonomous juicy lookin ahh", soloawp), //soloawp auton
		Auton("Skills autonomous", autonomous_skills) //skills
  	});

}






//-------------------------------------------COMPETITION-DISABLED---------------------------------------------------------------------------------
void disabled() {

}







//-------------------------------------------COMPETITION-INITIALIZE---------------------------------------------------------------------------------
void competition_initialize() {

}




//-------------------------------------------COMPETITION-AUTONOMOUS---------------------------------------------------------------------------------
void autonomous() {
	//reset chassis configuration info
	chassis.reset_gyro(); 
  	chassis.reset_drive_sensor(); 
  	chassis.set_drive_brake(MOTOR_BRAKE_HOLD); 

  
	//Autonomous selector
	ez::as::auton_selector.call_selected_auton(); 
}








//-----------------------------------------------DRIVER-CONTROL---------------------------------------------------------------------------------
void opcontrol() {
	while(true){
		chassis.tank(); //tank drive


		//flywheel -- TUNE ASAP
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
			flywheel::setTargetSpeed(3600);
		}
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
			flywheel::setTargetSpeed(2000);
		}

		//Intake/Outtake
		intake::intakefordrive();

		//Expansion
		expansion::fire();
	}
}
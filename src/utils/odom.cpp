#include "main.h"
//CONSTANTS / Hard-Coded Values
//Radius of tracking wheels in inches

pros::Imu Inertial6(21);
pros::Rotation left_encoder(3);
pros::Rotation right_encoder(4);
pros::Rotation y_encoder(5);

double WHEEL_RADIUS = 4.125; //was 1.379 //1.43

//Starting angle (relative to field) (RADIANS)
auto heading = Inertial6.get_heading();
double THETA_START = heading; //imagine the field is a unit circle

//The starting x and y coordinates of the bot (INCHES)  //EDIT
  //These distances are relative to some point (0,0) on the field
  //Relative to: BOTTOM LEFT CORNER
double X_START = 56.5; //19.1
double Y_START = 8.5; //8.5

//Distances of tracking wheels from tracking center (INCHES) //EDIT
double LTrackRadius = 6.8335; //was 6.87
double RTrackRadius = 6.8335; //6.8335
double STrackRadius = 5.85;

//Calculated Values (every loop)
//Angles (DEGREES) *NEEDS TO BE CONVERTED TO RADIANS FOR MATH*
double LPos = 0;
double RPos = 0;
double SPos = 0;

double LPrevPos = 0;
double RPrevPos = 0;
double SPrevPos = 0;

//Distances traveled by tracking wheels each loop (INCHES)
double deltaDistL = 0;
double deltaDistR = 0;
double deltaDistS = 0;

//Distance summations (since last reset)
double totalDeltaDistL = 0;
double totalDeltaDistR = 0;

//The current angle of the bot (RADIANS)
double currentAbsoluteOrientation = THETA_START;
//The previous angle of the bot (RADIANS)
double previousTheta = THETA_START;

//The change in Theta each loop (RADIANS)
double deltaTheta = 0;

//The Average angle Theta (In RADIANS) throughout the arc
  //currentAbsoluteOrientation + (deltaTheta / 2)
double avgThetaForArc = currentAbsoluteOrientation + (deltaTheta / 2);

//The changes in the X and Y positions (INCHES)
/*These are calculated on a local basis each loop,
then converted to global position changes */
double deltaXLocal = 0;
double deltaYLocal = 0;

//The X and Y offsets converted from their local forms (INCHES)
double deltaXGlobal = 0;
double deltaYGlobal = 0;

//The global position of the bot (INCHES)
double xPosGlobal = X_START;
double yPosGlobal = Y_START;


int positionTracking() {
  while(1) {
    //Get encoder values (DEGREES)
    
    LPos = left_encoder.get_position();
    RPos = right_encoder.get_position();
    SPos = y_encoder.get_position();

    //Calculate distance traveled by tracking each wheel (INCHES)
      //Converts degrees to radians
    deltaDistL = ((LPos - LPrevPos) * heading / 180) * WHEEL_RADIUS;
    deltaDistR = ((RPos - RPrevPos) * heading / 180) * WHEEL_RADIUS;
    deltaDistS = ((SPos - SPrevPos) * heading / 180) * WHEEL_RADIUS;

    //Update previous values to be used next loop (DEGREES)
    LPrevPos = LPos;
    RPrevPos = RPos;
    SPrevPos = SPos;

    //Total change in each of the L and R encoders since last reset (INCHES)
    //These are used to calculate the absolute orientation of the bot
    totalDeltaDistL += deltaDistL;
    totalDeltaDistR += deltaDistR;

    //Calculate the current absolute orientation (RADIANS)
    //currentAbsoluteOrientation = THETA_START - ( (totalDeltaDistL - totalDeltaDistR) / (LTrackRadius + RTrackRadius) );
    currentAbsoluteOrientation = ((360 - Inertial6.get_heading())) * heading / 180.0;

    //Calculate the change in the angle of the bot (RADIANS)
    deltaTheta = currentAbsoluteOrientation - previousTheta;

    //Update the previous Theta value (RADIANS)  
    previousTheta = currentAbsoluteOrientation;

    //If we didn't turn, then we only translated
    if(deltaTheta == 0) {
      deltaXLocal = deltaDistS;
      // could be either L or R, since if deltaTheta == 0 we assume they're =
      deltaYLocal = deltaDistL;
    }
    //Else, caluclate the new local position
    else {
      //Calculate the changes in the X and Y values (INCHES)
      //General equation is:
        //Distance = 2 * Radius * sin(deltaTheta / 2)
      deltaXLocal = 2 * sin(deltaTheta / 2.0) * ((deltaDistS / deltaTheta) + STrackRadius);
      deltaYLocal = 2 * sin(deltaTheta / 2.0) * ((deltaDistR / deltaTheta) - RTrackRadius);

    }

    //The average angle of the robot during it's arc (RADIANS)
    avgThetaForArc = currentAbsoluteOrientation - (deltaTheta / 2);

    deltaXGlobal = (deltaYLocal * cos(avgThetaForArc)) - (deltaXLocal * sin(avgThetaForArc));
    deltaYGlobal = (deltaYLocal * sin(avgThetaForArc)) + (deltaXLocal * cos(avgThetaForArc));

    //Wraps angles back around if they ever go under 0 or over 2 pi
    while(currentAbsoluteOrientation >= 2 * heading) {
      currentAbsoluteOrientation -= 2 * heading;
    }
    
    while(currentAbsoluteOrientation < 0) {
      currentAbsoluteOrientation += 2 * heading;
    }

    //Update global positions
    xPosGlobal += deltaXGlobal;
    yPosGlobal += deltaYGlobal;

    //print values to screen
    pros::c::screen_print(TEXT_MEDIUM, 1, "xPosGlobal/yPosGlobal: ",xPosGlobal, yPosGlobal);
    pros::delay(10);

  }
  return xPosGlobal, yPosGlobal;
}
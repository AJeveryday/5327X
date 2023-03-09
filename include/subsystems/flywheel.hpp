namespace flywheel {

    #define LONG_RANGE_POWER 1
    #define SHORT_RANGE_POWER 0.75
    #define MAXIMUM_VOLTAGE 12000
    #define TECHNICAL_FLYWHEEL_RPM 600

    

    extern int targetSpeed;
    extern double actualSpeed;

    int voltageUpdate();
    void setTargetSpeed(double pwr);
  

}
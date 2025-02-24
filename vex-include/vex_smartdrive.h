/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2019, All rights reserved.               */
/*                                                                            */
/*    Module:     vex_smartdrive.h                                            */
/*    Author:     James Pearman                                               */
/*    Created:    7 April 2019                                                */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_DRIVETRAIN_EXT_CLASS_H
#define   VEX_DRIVETRAIN_EXT_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_smartdrive.h
  * @brief   Drivetrain class header
*//*---------------------------------------------------------------------------*/

namespace vex {

  class smartdrive : public drivetrain  {
    public:  
      smartdrive( motor_group &l, motor_group &r, vex::gyro &g, double wheelTravel=320, double trackWidth=320, double wheelBase=130, distanceUnits unit=distanceUnits::mm, double externalGearRatio = 1.0 );
      smartdrive( vex::motor &l, vex::motor &r, vex::gyro &g, double wheelTravel=320, double trackWidth=320, double wheelBase=130, distanceUnits unit=distanceUnits::mm, double externalGearRatio = 1.0 );

      ~smartdrive();

      /**
       * @brief Turn on the motors and rotate to an angle at the default velocity.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param angle Sets the angle to turn.
       * @param units The measurement unit for the angle value.
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool turnToHeading( double angle, rotationUnits units,  bool waitForCompletion=true );
      
      /**
       * @brief Turn on the motors and rotate to an angle at a specified velocity.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param angle Sets the angle to turn.
       * @param units The measurement unit for the angle value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool turnToHeading( double angle, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      /**
       * @brief Turn on the motors and rotate an angle at the default velocity.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param dir Sets the direction to turn.
       * @param angle Sets the angle to turn.
       * @param units The measurement unit for the angle value.
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      virtual bool turnFor( turnType dir, double angle, rotationUnits units,  bool waitForCompletion=true );

      virtual bool turnFor( double angle, rotationUnits units, bool waitForCompletion=true );
      
      /**
       * @brief Turn on the motors and rotate an angle at a specified velocity.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param dir Sets the direction to turn.
       * @param angle Sets the angle to turn.
       * @param units The measurement unit for the angle value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      virtual bool turnFor( turnType dir, double angle, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      virtual bool turnFor( double angle, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      /**
       * @brief reset the gyro sensor angle to angle
       * @param value The new absolute angle for the gyro
       * @param units The rotation unit for the angle
       */
      void setHeading(  double value, rotationUnits units );
      
      /**
       * @brief Gets the heading (angle) of the gyro sensor.
       * @return Returns a double that represents the unit value specified by the parameter of the gyro sensor.
       * @param units The measurement unit for the gyro device.
       */
      double heading( rotationUnits units = rotationUnits::deg );
      
      /** 
       * @brief Checks to see if the gyroTurnFor function is still running.
       * @return Returns a true Boolean if the motor is on and is rotating to a target. Returns a false Boolean if the motor is done rotating to a target.
       */
      bool isTurning();

    private:
      vex::gyro   *g;
      double      _targetAngle;
      turnType    _targetDir;
      int32_t     _timeout;
      bool        _turning;
      bool        _slow;
      int32_t     _gyroTaskId;
            
      static int  _gyrotask( void *arg );
      void        _initevents();
      bool        _testForCompletionGyro();
      bool        _waitForCompletionGyro();

      enum class tEventType {
        EVENT_GYRO_POLL = 4
      };
  };
}

#endif // VEX_DRIVETRAIN_EXT_CLASS_H
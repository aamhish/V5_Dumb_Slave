/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017-2019, All rights reserved.          */
/*                                                                            */
/*    Module:     vex_competition.h                                           */
/*    Author:     James Pearman                                               */
/*    Created:    6 Nov 2017                                                  */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_COMPETITION_CLASS_H
#define   VEX_COMPETITION_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_competition.h
  * @brief   V5 competition control class header
*//*---------------------------------------------------------------------------*/

namespace vex {
  /**
    * @prog_lang{block|cpp|pro} 
    * @brief Use this class to set up your program for competitions.
  */
  class competition {
    private:
      int32_t _index;
      static bool    _auton_pending;
      static bool    _driver_pending;
      
      static void (* _initialize_callback)(void);
      static void (* _autonomous_callback)(void);
      static void (* _drivercontrol_callback)(void);

      static  void  _disable( void *arg );
      static  void  _autonomous( void );
      static  void  _drivercontrol( void );
      
      bool _globalInstance;
      
    protected:
      int32_t _getIndex();

    public:
    /**
      * @prog_lang{pro} 
      * @drawer_cat{constructor}
      * @block_sig{vex::competition Competition = vex::competition();}
      * @brief Creates a competition object that has access to competition methods.      
    */
      competition();
      ~competition();

      enum class tEventType {
        EVENT_INITIALIZE     = 8,
        EVENT_AUTONOMOUS     = 9,
        EVENT_DRIVER_CTL     = 10,
        EVENT_DISABLE        = 11
      };

      // callbacks for C++ code
      // pre-auton makes no sense here

      /** 
        * @prog_lang{cpp|pro}
        * @drawer_cat{setting}
        * @block_sig{Competition.autonomous(autonFunction);}
        * @brief Calls back a function when the autonomous period starts.
        * @param callback A reference to a function.
      */
      void     autonomous( void (* callback)(void) );

      /** 
        * @prog_lang{cpp|pro}
        * @drawer_cat{setting}
        * @block_sig{Competition.drivercontrol(driverFunction);}
        * @brief Calls back a function when the driver control period starts.
        * @param callback A reference to a function.
      */
      void     drivercontrol( void (* callback)(void) );  
      
      // check competition states
      /** 
        * @prog_lang{block|cpp|pro}
        * @drawer_cat{sensing}
        * @block_sig{Competition.isEnabled()}
        * @brief Gets the status of your robot when under competition control.
        * @return Returns a Boolean based on if the autonomous or driver control periods is active. If either one is active, the Boolean will return true.
      */
      bool     isEnabled();

      /** 
        * @prog_lang{block|cpp|pro}
        * @drawer_cat{sensing}
        * @block_sig{Competition.isDriverControl()}
        * @brief Gets the status of the Driver Control period.
        * @return Returns a Boolean based on if the Driver Control Period is active. If the Driver Control period is active, the Boolean will return true.
      */
      bool     isDriverControl();

      /** 
        * @prog_lang{block|cpp|pro}
        * @drawer_cat{sensing}
        * @block_sig{Competition.isAutonomous()}
        * @brief Gets the status of the Autonomous period.
        * @return Returns a Boolean based on if the Autonomous Period is active. If the Autonomous Period is active, the Boolean will return true.
      */
      bool     isAutonomous();

      /** 
        * @prog_lang{block|cpp|pro}
        * @drawer_cat{sensing}
        * @block_sig{Competition.isCompetitionSwitch()}
        * @brief Gets the status of the Competition Control Switch being plugged into the robot.
        * @return Returns a Boolean based on if the V5 is connected to the Competition Control Switch. If the Brain is connected, the Boolean will return true.
      */
      bool     isCompetitionSwitch();

      /** 
        * @prog_lang{block|cpp|pro}
        * @drawer_cat{sensing}
        * @block_sig{Competition.isFieldControl()}
        * @brief Gets the status of the Field Control System being plugged into the robot.
        * @return Returns a Boolean based on if the V5 is connected to the Field Control System. If the Brain is connected, the Boolean will return true.
      */
      bool     isFieldControl();



      // may be useful for testing without controller            
      void     test_auton(void);
      void     test_driver(void);
      void     test_disable(void);

      // competition is part of brain device
      // simple events for everything
      mevent   PRE_AUTONOMOUS = {(uint32_t)brain::_getIndex(), (int32_t)tEventType::EVENT_INITIALIZE   };
      mevent   AUTONOMOUS     = {(uint32_t)brain::_getIndex(), (int32_t)tEventType::EVENT_AUTONOMOUS   };
      mevent   DRIVER_CONTROL = {(uint32_t)brain::_getIndex(), (int32_t)tEventType::EVENT_DRIVER_CTL   };
      mevent   DISABLED       = {(uint32_t)brain::_getIndex(), (int32_t)tEventType::EVENT_DISABLE      };
      
      /** 
        * @prog_lang{cpp|pro}
        * @drawer_cat{setting|none}
        * @brief Sets whether or not your program will stop tasks between modes. 
        * @return Gets whether or not your program will stop tasks between modes.
      */
      static bool     bStopTasksBetweenModes;   

      static bool     bStopAllTasksBetweenModes;   
  };
};

#endif // VEX_COMPETITION_CLASS_H
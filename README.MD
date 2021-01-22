# DFRobot_IIS2DLPC
The IIS2DLPC is an ultra-low-power high-performance 
three-axis linear accelerometer with digital I²C/SPI 
output interface which leverages on the robust and 
mature manufacturing processes already used for the 
production of micromachined accelerometers.
The IIS2DLPC has user-selectable full scales of 
±2g/±4g/±8g/±16g and is capable of measuring 
accelerations with output data rates from 1.6 Hz to 
1600 Hz.
The IIS2DLPC has one high-performance mode and 4 
low-power modes which can be changed on the fly, 
providing outstanding versatility and adaptability to the 
requirements of the application. 
The IIS2DLPC has an integrated 32-level first-in, first-out 
(FIFO) buffer allowing the user to store data in order to 
limit intervention by the host processor.
The embedded self-test capability allows the user to 
check the functioning of the sensor in the final 
application.
The IIS2DLPC has a dedicated internal engine to 
process motion and acceleration detection including 
free-fall, wakeup, highly configurable single/double-tap 
recognition, activity/inactivity, stationary/motion 
detection, portrait/landscape detection and 6D/4D 
orientation.
The IIS2DLPC is available in a small thin plastic land 
grid array package (LGA) and it is guaranteed to operate 
over an extended temperature range from -40 °C to 
+85 °C.


## DFRobot_IIS2DLPC Library for Arduino
---------------------------------------------------------

Provide an Arduino library to get Three-axis acceleration by reading data from IIS2DLPC.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary


Provide an Arduino library to get Three-axis acceleration by reading data from IIS2DLPC.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++

#include <DFRobot_IIS2DLPC.h>

    DFRobot_IIS2DLPC();
  
  /**
   * @brief Initialize the function
   * @return Return 0 indicates a successful initialization, while other values indicates failure and return to error code.
   */
  int begin(void);
 
  /**
   * @brief Get chip id
   * @return Returns the eight-digit serial number
   */
  uint8_t getID();
 
  /**
   * @brief Software reset to restore the value of all registers to the default value
   */
  void softReset();
  
  /**
   * @brief Choose whether to continuously let the chip collect data
   * @param enable: true/false
   */
  void continRefresh(bool enable);
  
  /**
   * @brief Set the filter processing mode
   * @param fds: Three modes of filtering
   */
  void setFilterPath(eIIS2DLPC_fds_t fds);

  /**
   * @brief Set the  bandwidth of the data
   * @param bw:  bandwidth
   */
  void setFilterBandwidth(eBWfilter_t bw);
  
  /**
   * @brief Set power mode
   * @param mode: 16 power modes to choose from
   */
  void setPowerMode(ePowerMode_t mode);
  
  /**
   * @brief Chip data collection rate setting
   * @param mode: 0-1600hz selection
   */
  void setDataRate(eOdr_t odr);
  
  /**
   * @brief Duration setting of free fall
   * @param dur: Free fall duration (0~31), the larger the value, the longer the free fall time is needed to be detected
      @n 1 LSB = 1 * 1/ODR (measurement frequency)
   */
  void setFrDur(uint8_t dur);
  
  /**
   * @brief Is it ready to acquire acceleration data in three directions?
   * @return ture\false
   */
  bool getDataReadyFlag();
  
  /**
   * @brief Set the interrupt source of the int1 pin
   * @param event: Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int1 pin
   */
  void setPinInt1Route(eInteEvent_t event);
  
  /**
   * @brief Set interrupt source of int2 pin
   * @param event: Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int2 pin
   */
  void setPinInt2Route(eInt2Event_t event);
  
  /**
   * @brief Latch interrupt
   * @param enable: Latched Interrupt. Switches between latched ('1'-logic) and pulsed ('0'-logic) mode for 
      function source signals and interrupts routed to pins (wakeup, single/double-tap).
   */
  void latchInterrupt(bool enable);
  
  /**
   * @brief Get the status of all events of the chip
   * @return  A structure that stores event information
   */
  sAllSources_t getAllSources();
  
  /**
   * @brief Set the wake-up duration
   * @param dur:Wakeup duration (0~3), a total of three levels
   */
  void setWakeupDur(uint8_t dur);

  /**
   * @brief Set the wake-up Threshold
   * @param th:Wake-up threshold,(0~31)1 LSB = 1/64 of g FS.
   */
  void setWakeupThreshold(uint8_t th);
  
  /**
   * @brief Sets the mode of motion detection
   * @param th:    eNoDetection     
                   eDetectActInact  
                   eDetectStatMotion
   */
  void setActMode(eSleepOn_t mode);
  
  /**
   * @brief Set the range
   * @param range:     eIIS2DLPC_2g     
                       eIIS2DLPC_4g     
                       eIIS2DLPC_8g     
                       eIIS2DLPC_16g 
   */
  void setRange(eRange_t range);
  
  /**
   * @brief Set to detect click events in the Z direction
   * @param enable:ture\false
   */
  void enableTapDetectionOnZ(bool enable);
  
  /**
   * @brief Set to detect click events in the Y direction
   * @param enable:ture\false
   */
  void enableTapDetectionOnY(bool enable);

  /**
   * @brief Set to detect click events in the X direction
   * @param enable:ture\false
   */
  void enableTapDetectionOnX(bool enable);

  /**
   * @brief Set the click threshold in the X direction
   * @param th:Threshold(0~31)
   */
  void setTapThresholdOnX(uint8_t th);
  
  /**
   * @brief Set the click threshold in the Y direction
   * @param th:Threshold(0~31)
   */
  void setTapThresholdOnY(uint8_t th);

  /**
   * @brief Set the click threshold in the Z direction
   * @param th:Threshold(0~31)
   */
  void setTapThresholdOnZ(uint8_t th);
  
  /**
   * @brief Sets the interval between double-clicks
   * @param th:1 LSB = 32 * 1/ODR(0~15)
     @n ODR:Data acquisition frequency
   */
  void setTapDur(uint8_t dur);
  
  /**
   * @brief Set the click detection mode
   * @param mode:     eOnlySingle
                      eBothSingleDouble
   */
  void setTapMode(sTapMode_t mode);

  /**
   * @brief Set Thresholds for 4D/6D
   * @param degree:         eDegrees80
                            eDegrees70
                            eDegrees60
                            eDegrees50
   */
  void set6dThreshold(s6dTH_t degree);

  /**
   * @brief Read the acceleration in the x direction
   * @return Acceleration data(g)
   */
  float readACCFromX();
  
  /**
   * @brief Read the acceleration in the y direction
   * @return  Acceleration data(g)
   */
  float readACCFromY();
  
  /**
   * @brief Read the acceleration in the z direction
   * @return Acceleration data(g)
   */
  float readACCFromZ();



```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
掌控板        |      √       |              |             | 
树莓派        |      √       |              |             | 
microbit        |      √       |              |             | 



## History

- data 2020-12-31
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))

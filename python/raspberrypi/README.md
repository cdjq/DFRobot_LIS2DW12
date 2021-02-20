# DFRobot_LIS2DW12
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



## DFRobot_IIS2DLPC Library for RaspberryPi
---------------------------------------------------------

Provide an RaspberryPi library to get Three-axis acceleration by reading data from LIS2DW12 and IIS2DLPC.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

Provide an RaspberryPi library to get Three-axis acceleration by reading data from LIS2DW12 and IIS2DLPC.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```python

  '''
    @brief Initialize the function
    @return Return 0 indicates a successful initialization, while other values indicates failure and return to error code.
  '''
   begin(self):
      
  '''
    @brief Get chip id
    @return Returns the eight-digit serial number
  '''
  get_ID(self):

  '''
    @brief Software reset to restore the value of all registers to the default value
  '''
  soft_reset(self):
    
    
  '''
    @brief Set the measurement range
    @param range:Range(g)
                 RANGE_2G     #/**<±2g>*/
                 RANGE_4G     #/**<±4g>*/
                 RANGE_8G     #/**<±8g>*/
                 RANGE_16G    #/**< ±16g>*/
  '''
  set_range(self,range_r):
    
  '''
    @brief Choose whether to continuously let the chip collect data
    @param enable  True(持续采集数据)/False(单次采集数据)
  '''
  contin_refresh(self,enable):
  
  '''
    @brief Set the filter processing mode
    @param fds  Three modes of filtering
                LPF_ON_OUT        = 0x00,/<Low pass filter>/
                USER_OFFSET_ON_OUT = 0x01,
                HIGH_PASS_ON_OUT   = 0x10,/<High pass filter>/
  '''
  set_filter_path(self,fds):

  '''
    @brief Set the  bandwidth of the data
    @param bw   ODR_DIV_2     = 0,/<ODR/2 (up to ODR = 800 Hz, 400 Hz when ODR = 1600 Hz)>/
                ODR_DIV_4     = 1,/<ODR/4 (High Power/Low power)>*
                ODR_DIV_10    = 2,/<ODR/10 (HP/LP)>/
                ODR_DIV_20    = 3,/< ODR/20 (HP/LP)>/
  '''
  set_filter_bandwidth(self,bw):
    
  '''
    @brief Set power mode
    @param mode 16 power modes to choose from
                   HIGH_PERFORMANCE                   = 0X04 #High-Performance Mode
                   CONT_LOWPWR_4                      = 0X03#Continuous measurement,Low-Power Mode 4(14-bit resolution)
                   CONT_LOWPWR_3                      = 0X02#Continuous measurement,Low-Power Mode 3(14-bit resolution)
                   CONT_LOWPWR_2                      = 0X01#Continuous measurement,Low-Power Mode 2(14-bit resolution)
                   CONT_LOWPWR_12BIT                  = 0X00#Continuous measurement,Low-Power Mode 1(12-bit resolution)
                   SING_LELOWPWR_4                    = 0X0B#Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)
                   SING_LELOWPWR_3                    = 0X0A#Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution
                   SING_LELOWPWR_2                    = 0X09#Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)
                   SING_LELOWPWR_12BIT                = 0X08#Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)
                   HIGHP_ERFORMANCELOW_NOISE           = 0X14#High-Performance Mode,Low-noise enabled
                   CONT_LOWPWRLOWNOISE_4              = 0X13#Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)
                   CONT_LOWPWRLOWNOISE_3              = 0X12#Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)
                   CONT_LOWPWRLOWNOISE_2              = 0X11#Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)
                   CONT_LOWPWRLOWNOISE_12BIT          = 0X10#Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)
                   SINGLE_LOWPWRLOWNOISE_4            = 0X1B#Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled
                   SINGLE_LOWPWRLOWNOISE_3            = 0X1A#Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled
                   SINGLE_LOWPWRLOWNOISE_2            = 0X19#Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled
                   SINGLE_LOWLOWNOISEPWR_12BIT        = 0X18#Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled
  '''
  set_power_mode(self,mode):
    
  '''
    @brief Set data measurement rate
    @param range rate(g)
                 ODR_OFF            = 0X00
                 ODR_1HZ6_LP_ONLY   = 0X01
                 ODR_12HZ5          = 0X02
                 ODR_25HZ           = 0X03
                 ODR_50HZ           = 0X04
                 ODR_100HZ          = 0X05
                 ODR_200HZ          = 0X06
                 ODR_400HZ          = 0X07
                 ODR_800HZ          = 0X08
                 ODR_1K6HZ          = 0X09
                 SETSWTRIG          = 0X12
                 SETPINTRIG         = 0X22
  '''
  set_data_rate(self, odr):
    
  '''
    @brief 自由落体时间
    @param dur  Free fall duration (0~31), the larger the value, the longer the free fall time is needed to be detected
    @n 1 LSB = 1 * 1/ODR (measurement frequency)
    @n example
    |                           High-pass filter cut-off frequency configuration                             |
    |--------------------------------------------------------------------------------------------------------|
    |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
    |   dur          |Data rate = 25 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 800 Hz  |
    |--------------------------------------------------------------------------------------------------------|
    |  n             |n*(1s/25)= n*40ms|  n*(1s/100)= n*10ms  |  n*(1s/400)= 2.5*nms |  n*(1s/800)= n*1.25ms |
    |--------------------------------------------------------------------------------------------------------|
  '''
  set_ff_Dur(self,dur):
  
  '''
  @brief Set the interrupt source of the int1 pin
  @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int1 pin
              DOUBLE_TAP = 0x08 #/**< Double-tap recognition is routed to INT1 pad>*/
              FF_EVENT = 0x10 #/**< Free-fall recognition is routed to INT1 pad>*/
              WAKEUP_EVENT = 0x20 #/**<Wakeup recognition is routed to INT1 pad>*/
              SINGLE_TAP = 0x40  #/**<Single-tap recognition is routed to INT1 pad.>*/
              TNT_16D  = 0x80  #/**<6D recognition is routed to INT1 pad>*/

  '''
  set_int1_route(self,event):
    
  '''
    @brief Set the wake-up duration
    @param dur Wakeup duration (0~3)
    @n 1 LSB = 1 * 1/ODR (measurement frequency)
    @n example
    |                           High-pass filter cut-off frequency configuration                             |
    |--------------------------------------------------------------------------------------------------------|
    |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
    |   dur          |Data rate = 25 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 800 Hz  |
    |--------------------------------------------------------------------------------------------------------|
    |  n             |n*(1s/25)= n*40ms|  n*(1s/100)= n*10ms  |  n*(1s/400)= 2.5*nms |  n*(1s/800)= n*1.25ms |
    |--------------------------------------------------------------------------------------------------------|
  '''
  set_wakeup_dur(self,dur):
  
  '''
    @brief Sets the mode of motion detection
    @param th:     NO_DETECTION        = 0 #/**<No detection>*/
                   DETECT_ACTINACT     = 1 #/**<Detect movement>*/
                   DETECT_STATMOTION   = 3 #/**<Detect Motion>*/
  '''
  set_act_mode(self,mode):

  '''
    @brief Set the wake-up Threshold
    @param th:unit(g),数值是在量程之内
  '''
  set_wakeup_threshold(self,th):

  '''
    @brief Latch interrupt
    @param enable  Latched Interrupt. Switches between latched ('1'-logic) and pulsed ('0'-logic) mode for 
     function source signals and interrupts routed to pins (wakeup, single/double-tap).
  '''
  latch_interrupt(self,enable):
    
  '''
    @brief Set to detect click events in the Z direction
    @param enable:Ture(使能点击检测\False(禁用点击检测)
  '''
  enable_tap_detection_on_z(self, enable):
  
  '''
    @brief Set to detect click events in the Y direction
    @param enable:Ture(使能点击检测\False(禁用点击检测)
  '''
  enable_tap_detection_on_y(self, enable):
    
  '''
    @brief Set to detect click events in the X direction
    @param enable:Ture(使能点击检)\False(禁用点击检)
  '''
  enable_tap_detection_on_x(self, enable):

  '''
    @brief Set the click threshold in the X direction
    @param th:Threshold(g),Can only be used in the range of ±2g
  '''
  set_tap_threshold_on_x(self,th):
  
  '''
    @brief Set the click threshold in the Y direction
    @param th:Threshold(g),Can only be used in the range of ±2g
  '''
  set_tap_threshold_on_y(self,th):
    
  '''
    @brief Set the click threshold in the Z direction
    @param th:Threshold(g),Can only be used in the range of ±2g
  '''
  set_tap_threshold_on_z(self,th):
    
  '''
    @brief 双击的两次点击之间的间隔时间
    @param th 1 LSB = 32 * 1/ODR(0~15)
    @n ODR:Data acquisition frequency
    @n example
    |                           High-pass filter cut-off frequency configuration                             |
    |--------------------------------------------------------------------------------------------------------|
    |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
    |   dur          |Data rate = 25 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 800 Hz  |
    |--------------------------------------------------------------------------------------------------------|
    |  n             |n*(1s/25)= n*40ms|  n*(1s/100)= n*10ms  |  n*(1s/400)= 2.5*nms |  n*(1s/800)= n*1.25ms |
    |--------------------------------------------------------------------------------------------------------|
  '''
  set_tap_dur(self,dur):

  '''
    @brief Set the click detection mode
    @param mode      ONLY_SINGLE   //检测单击
                     BOTH_SINGLE_DOUBLE //检测单击和双击
  '''
  set_tap_mode(self,mode):

  '''
    @brief Set Thresholds for 4D/6D，当转动的阈值大于指定角度时,就发生方向转变的事件
    @param degree:  DEGREES_80   80°
                    DEGREES_70   70°
                    DEGREES_60   60°
                    DEGREES_50   50°
  '''
  set_6d_threshold(self,degree):
    
  '''
    @brief Set interrupt source of int2 pin
    @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int2 pin
                  BOOT = 0x20,/< Boot state routed to INT2 pad.>/
                  SLEEP_CHANGE = 0x40,/<Enable routing of SLEEP_STATE on INT2 pad>/
                  SLEEP_STATE  = 0x80,/<Sleep change status routed to INT2 pad>/
  '''
  set_int2_route(self,event):
    
  '''
    @brief Read the acceleration in the x direction
    @return Acceleration data(g)
  '''
  read_acc_x(self):


  '''
    @brief Read the acceleration in the y direction
    @return  Acceleration data(g)
  '''
  read_acc_y(self):

  '''
    @brief Read the acceleration in the z direction
    @return Acceleration data(g)
  '''
  read_acc_z(self):
  
  '''
    @brief 检测是否有运动产生
    @return True(产生运动)/False(传感器未运动)
  '''
  act_detect(self):
      
  '''
    @brief 自由落体运动检测
    @return True(检测到自由落体运动)/False(未检测到自由落体运动)
  '''
  free_fall_detect(self):

  '''
    @brief Source of change in position portrait/landscape/face-up/face-down.
    @return True( no event detected)/False(a change in position is detected)
  '''
  ia6d_detect(self):
      
  '''
  @brief 获取传感器现在的位置
  @return      X_DOWN = 0 #/**<X is now down>*/
               X_UP  = 1 #/**<X is now up>*/
               Y_DOWN = 2 #/**<Y is now down>*/
               Y_UP = 3  #/**<Y is now up>*/
               Z_DOWN = 4  #/**<Z is now down>*/
               Z_UP = 5  #/**<Z is now up>*/
  '''
  get_orient(self):

  '''
    @brief 点击检测
    @return   SINGLE_CLICK  = 0 ,/<click>/
              DOUBLE_CLICK   ,/<double click>/
              NO_CLICK,      //没有点击产生
  '''
  tap_detect(self):


  '''
    @brief 点击方向的源头检测
    @return     DIR_X_UP = 0#在X 正方向发生的点击事件
                DIR_X_DOWN = 1#在X 负方向发生的点击事件
                DIR_Y_UP = 2#在Y 正方向发生的点击事件
                DIR_Y_DOWN = 3#在Y 负方向发生的点击事件
                DIR_Z_UP = 4#在Z 正方向发生的点击事件
                DIR_Z_DOWN = 5#在Z 负方向发生的点击事件
  '''
  get_tap_direction(self):

  '''
    @brief 点击检测
    @return    DIR_X = 0#X方向的运动唤醒芯片
               DIR_Y = 1#Y方向的运动唤醒芯片
               DIR_Z = 2#Z方向的运动唤醒芯片
               eDirError,
  '''
  get_wake_up_dir(self):



```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
raspberry pi 3             |      √         |            |             | 




## History

- data 2021-1-26
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

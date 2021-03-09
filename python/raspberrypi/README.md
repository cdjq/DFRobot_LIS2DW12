# DFRobot_LIS2DW12
The IIS2DLPC is an ultra-low-power high-performance 
three-axis linear accelerometer with digital I²C/SPI 
output interface which leverages on the robust and 
mature manufacturing processes already used for the 
production of micromachined accelerometers.<br>
The IIS2DLPC has user-selectable full scales of 
±2g/±4g/±8g/±16g and is capable of measuring 
accelerations with output data rates from 1.6 Hz to 
1600 Hz.<br>

The LIS2DW12 is an ultra-low-power high-performance three-axis linear
accelerometer belonging to the “femto” family which leverages on the robust and
mature manufacturing processes already used for the production of micromachined
accelerometers.
The LIS2DW12 has user-selectable full scales of ±2g/±4g/±8g/±16g and is capable of
measuring accelerations with output data rates from 1.6 Hz to 1600 Hz.

CHIP                | Work Well    | Work Wrong  | Remarks
------------------ | :----------: | :----------| -----
LIS2DW12       |      √       |              |             
IIS2DLPC      |      √       |              |       

## DFRobot_LIS2DW12 Library for RaspberryPi
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

下载DFRobot_LIS2DW12文件到树莓派文件目录下,然后运行下面两行命令行，使用此传感器:
```
cd DFRobot_LIS2DW12/python/raspberry/examples/LIS2DW12/get_acceleration
python get_acceleration.py
```

## Methods

```python

  '''
    @brief Initialize the function
    @return True(初始化成功)/Fasle(初始化失败)
  '''
  begin(self):
  
  '''
    @brief Get chip id
    @return 8 bit serial number
  '''
  get_id(self):

  '''
    @brief Software reset to restore the value of all registers to the default value
  '''
  soft_reset(self):
    
  '''
    @brief Set the measurement range
    @param range Range(g)
                 RANGE_2G     #±2g
                 RANGE_4G     #±4g
                 RANGE_8G     #±8g
                 RANGE_16G    #±16g
  '''
  set_range(self,range_r):
    
  '''
    @brief Choose whether to continuously let the chip collect data
    @param enable  true(continuous update)/false( output registers not updated until MSB and LSB read)
  '''
  contin_refresh(self,enable):
  
  '''
    @brief Set the filter processing mode
    @param path path of filtering
                LPF          #Low pass filter
                HPF          #High pass filter
  '''
  set_filter_path(self,path):

  '''
    @brief Set the  bandwidth of the data
    @param bw bandwidth
                RATE_DIV_2   #RATE/2 (up to RATE = 800 Hz, 400 Hz when RATE = 1600 Hz)
                RATE_DIV_4   #RATE/4 (High Power/Low power)
                RATE_DIV_10  #RATE/10 (HP/LP)
                RATE_DIV_20  #RATE/20 (HP/LP)
  '''
  set_filter_bandwidth(self,bw):
    
  '''
    @brief Set power mode
    @param mode 16 power modes to choose from
               HIGH_PERFORMANCE_14BIT          #High-Performance Mode
               CONT_LOWPWR4_14BIT              #Continuous measurement,Low-Power Mode 4(14-bit resolution)
               CONT_LOWPWR3_14BIT              #Continuous measurement,Low-Power Mode 3(14-bit resolution)
               CONT_LOWPWR2_14BIT              #Continuous measurement,Low-Power Mode 2(14-bit resolution)
               CONT_LOWPWR1_12BIT              #Continuous measurement,Low-Power Mode 1(12-bit resolution)
               SING_LELOWPWR4_14BIT            #Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)
               SING_LELOWPWR3_14BIT            #Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution
               SING_LELOWPWR2_14BIT            #Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)
               SING_LELOWPWR1_12BIT            #Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)
               HIGHP_ERFORMANCELOW_NOISE_14BIT #High-Performance Mode,Low-noise enabled
               CONT_LOWPWRLOWNOISE4_14BIT      #Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)
               CONT_LOWPWRLOWNOISE3_14BIT      #Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)
               CONT_LOWPWRLOWNOISE2_14BIT      #Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)
               CONT_LOWPWRLOWNOISE1_12BIT      #Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)
               SINGLE_LOWPWRLOWNOISE4_14BIT    #Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled
               SINGLE_LOWPWRLOWNOISE3_14BIT    #Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled
               SINGLE_LOWPWRLOWNOISE2_14BIT    #Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled
               SINGLE_LOWPWRLOWNOISE1_12BIT    #Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled
  '''
  set_power_mode(self,mode):
    
  '''
    @brief Set data measurement rate
    @param rate rate
                 RATE_OFF          #测量关闭
                 RATE_1HZ6         #1.6hz,仅在低功耗模式下使用
                 RATE_12HZ5        #12.5hz
                 RATE_25HZ         
                 RATE_50HZ         
                 RATE_100HZ        
                 RATE_200HZ        
                 RATE_400HZ        
                 RATE_800HZ          
                 RATE_1K6HZ          
  '''
  set_data_rate(self, rate):
    
  '''
     @brief 设置自由落体时间,也可以称作自由落体样本个数，只有产生足够多的自由落体样本，才会产生自由落体事件
     @param dur duration,范围:0~31
     @n time = dur * (1/rate)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
  '''
  set_free_fall_Dur(self,dur):

  
  '''
    @brief Set the interrupt source of the int1 pin
    @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int1 pin
              DOUBLE_TAP    #双击事件
              FREEFALL      #自由落体事件
              WAKEUP        #唤醒事件
              SINGLE_TAP    #单击事件
              IA6D          #在正面朝上/朝下/朝左/朝右/朝前/朝后 的状态发生改变的事件
    
  '''
  set_int1_event(self,event):
    
  '''
     @brief Set the wake-up duration
     @param dur duration,范围:0~3
     @n time = dur * (1/rate)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
  '''
  set_wakeup_dur(self,dur):
  
  '''
    @brief Sets the mode of motion detection
    @param mode  mode of motion detection
                   NO_DETECTION       #No detection
                   DETECT_ACT         #Detect movement
                   DETECT_STATMOTION  #Detect Motion
  '''
  set_act_mode(self,mode):

  '''
    @brief Set the wake-up Threshold
    @param th threshold unit:g,数值是在量程之内
  '''
  set_wakeup_threshold(self,th):
    
  '''
    @brief Set to detect click events in the Z direction
    @param enable Ture(使能点击检测\False(禁用点击检测)
  '''
  enable_tap_detection_on_z(self, enable):
  
  '''
    @brief Set to detect click events in the Y direction
    @param enable Ture(使能点击检测\False(禁用点击检测)
  '''
  enable_tap_detection_on_y(self, enable):

    
  '''
    @brief Set to detect click events in the X direction
    @param enable Ture(使能点击检)\False(禁用点击检)
  '''
  enable_tap_detection_on_x(self, enable):

  '''
    @brief Set the click threshold in the X direction
    @param th Threshold(g),Can only be used in the range of ±2g
  '''
  set_tap_threshold_on_x(self,th):
  
  '''
    @brief Set the click threshold in the Y direction
    @param th Threshold(g),Can only be used in the range of ±2g
  '''
  set_tap_threshold_on_y(self,th):
    
  '''
    @brief Set the click threshold in the Z direction
    @param th Threshold(g),Can only be used in the range of ±2g
  '''
  set_tap_threshold_on_z(self,th):
    
  '''
   @brief Duration of maximum time gap for double-tap recognition. When double-tap 
   @n recognition is enabled, this register expresses the maximum time between two 
   @n successive detected taps to determine a double-tap event.
   @param dur  duration,范围:0~15
   @n time = dur * (1/rate)(unit:s)
   |                                  参数与时间之间的线性关系的示例                                                        |
   |------------------------------------------------------------------------------------------------------------------------|
   |                |                     |                          |                          |                           |
   |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
   |------------------------------------------------------------------------------------------------------------------------|
   |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
   |------------------------------------------------------------------------------------------------------------------------|
  '''
  set_tap_dur(self,dur):
  
  '''
    @brief Set the click detection mode
    @param mode  点击检测模式
                     ONLY_SINGLE   //检测单击
                     BOTH_SINGLE_DOUBLE //检测单击和双击
  '''
  set_tap_mode(self,mode):

  '''
    @brief Set Thresholds for 4D/6D，当转动的阈值大于指定角度时,就发生方向转变的事件
    @param degree   DEGREES_80   #80°
                    DEGREES_70   #70°
                    DEGREES_60   #60°
                    DEGREES_50   #50°
  '''
  set_6d_threshold(self,degree):
    
  '''
    @brief 选择在中断2引脚产生的中断事件
    @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int2 pin
                  SLEEP_CHANGE  #Enable routing of SLEEP_STATE on INT2 pad
                  SLEEP_STATE   #0x80 Sleep change status routed to INT2 pad
  '''
  set_int2_event(self,event):
  
  '''
    @brief Read the acceleration in the x direction
    @return Acceleration data from x(mg),测量的量程为±2g,±4g,±8g或±16g,通过set_range()函数设置
  '''
  read_acc_x(self):

  '''
    @brief Read the acceleration in the y direction
    @return  Acceleration data from y(mg),测量的量程为±2g,±4g,±8g或±16g,通过set_range()函数设置
  '''
  read_acc_y(self):

  '''
    @brief Read the acceleration in the z direction
    @return Acceleration data from z(mg),测量的量程为±2g,±4g,±8g或±16g,通过set_range()函数设置
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
    @return True(a change in position is detected)/False(no event detected)
  '''
  ia_6d_detect(self):
      
  '''
  @brief 获取传感器现在的位置
  @return      X_DOWN   #X is now down
               X_UP     #X is now up
               Y_DOWN   #Y is now down
               Y_UP     #Y is now up
               Z_DOWN   #Z is now down
               Z_UP     #Z is now up
  '''
  get_orient(self):
     
  '''
    @brief 点击检测
    @return   SINGLE_CLICK       #single click
              DOUBLE_CLICK       #double click
              NO_CLICK,          #没有点击产生
  '''
  tap_detect(self):

  '''
    @brief 点击方向的源头检测
    @return     DIR_X_UP   #在X 正方向发生的点击事件
                DIR_X_DOWN #在X 负方向发生的点击事件
                DIR_Y_UP   #在Y 正方向发生的点击事件
                DIR_Y_DOWN #在Y 负方向发生的点击事件
                DIR_Z_UP   #在Z 正方向发生的点击事件
                DIR_Z_DOWN #在Z 负方向发生的点击事件
  '''
  get_tap_direction(self):
   
  '''
    @brief 唤醒的运动方向检测
    @return    DIR_X  #X方向的运动唤醒芯片
               DIR_Y  #Y方向的运动唤醒芯片
               DIR_Z  #Z方向的运动唤醒芯片
               eDirError,
  '''
  get_wake_up_dir(self):

  '''
    @brief In Single data conversion on demand mode,请求测量一次数据
  '''
  demand_data(self):


```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Raspberry Pi             |      √         |            |             | 
       

## History

- data 2021-3-5
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

/*!
 * @file DFRobot_LIS2DW12.h
 * @brief Define the basic structure of class DFRobot_LIS2DW12
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-12-23
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_LIS2DW12
 */

#ifndef DFROBOT_LIS2DW12_H
#define DFROBOT_LIS2DW12_H
 #include "Arduino.h"

#include <Wire.h>
#include <SPI.h>
#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define LIS2DW12_I2C_ADDR  (0x19)  /*LIS2DW12 IIC address*/
#define IIS2DLPC_I2C_ADDR  (0x19)  /*IIS2DLPC IIC address*/

#define ERR_OK              0      //ok
#define ERR_DATA_BUS       -1      //error in data bus
#define ERR_IC_VERSION     -2      //chip version mismatch


class DFRobot_LIS2DW12
{
public:
  #define REG_CARD_ID      0x0F     /*The chip id*/
  #define REG_CTRL_REG1    0x20     /*Control register 1*/
  #define REG_CTRL_REG4    0x23     /*Control register 2*/
  #define REG_CTRL_REG2    0x21     /*Control register 3*/
  #define REG_CTRL_REG3    0x22     /*Control register 4*/
  #define REG_CTRL_REG5    0x24     /*Control register 5*/
  #define REG_CTRL_REG6    0x25     /*Control register 6*/
  #define REG_CTRL_REG7    0x3F     /*Control register 7*/
  #define REG_STATUS_REG   0x27     /*Status register*/
  #define REG_OUT_X_L      0x28     /*The low order of the X-axis acceleration register*/
  #define REG_OUT_X_H      0x29     /*The high point of the X-axis acceleration register*/
  #define REG_OUT_Y_L      0x2A     /*The low order of the Y-axis acceleration register*/
  #define REG_OUT_Y_H      0x2B     /*The high point of the Y-axis acceleration register*/
  #define REG_OUT_Z_L      0x2C     /*The low order of the Z-axis acceleration register*/
  #define REG_OUT_Z_H      0x2D     /*The high point of the Z-axis acceleration register*/
  #define REG_WAKE_UP_DUR  0x35   
  #define REG_FREE_FALL    0x36     /*Free fall event register*/
  #define REG_STATUS_DUP   0x37     /*Interrupt event status register*/
  #define REG_WAKE_UP_SRC  0x38     /*Wakeup source register*/
  #define REG_TAP_SRC      0x39     /*Tap source register*/
  #define REG_SIXD_SRC     0x3A     /*6D source register*/
  #define REG_ALL_INT_SRC  0x3B     /*Reading this register, all related interrupt function flags routed to the INT pads are reset simultaneously*/
  
  #define REG_TAP_THS_X    0x30     /*4D configuration enable and TAP threshold configuration .*/
  #define REG_TAP_THS_Y    0x31     /*Threshold for tap recognition @ FS = ±2 g on Y direction*/
  #define REG_TAP_THS_Z    0x32     /*Threshold for tap recognition @ FS = ±2 g on Z direction*/
  #define REG_INT_DUR      0x33     /*Interrupt duration register*/
  #define REG_WAKE_UP_THS  0x34     /*Wakeup threshold register*/
  #define SPI_READ_BIT     0X80     /* bit 0: RW bit. When 0, the data DI(7:0) is written into the device. When 1, the data DO(7:0) 
from the device is read.*/

public:


/**
   Power mode
*/
typedef enum{
  
  eHighPerformance_14bit                   = 0x04,/**<High-Performance Mode,14-bit resolution>*/
  eContLowPwr4_14bit                      = 0x03,/**<Continuous measurement,Low-Power Mode 4(14-bit resolution)>*/
  eContLowPwr3_14bit                      = 0x02,/**<Continuous measurement,Low-Power Mode 3(14-bit resolution)>*/
  eContLowPwr2_14bit                      = 0x01,/**<Continuous measurement,Low-Power Mode 2(14-bit resolution)>*/
  eContLowPwr1_12bit                  = 0x00,/**<Continuous measurement,Low-Power Mode 1(12-bit resolution)>*/
  eSingleLowPwr4_14bit                    = 0x0b,/**<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>*/
  eSingleLowPwr3_14bit                    = 0x0a,/**<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>*/
  eSingleLowPwr2_14bit                    = 0x09,/**<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>*/
  eSingleLowPwr1_12bit                = 0x08,/**<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>*/
  eHighPerformanceLowNoise_14bit           = 0x14,/**<High-Performance Mode,Low-noise enabled,14-bit resolution>*/
  eContLowPwrLowNoise4_14bit              = 0x13,/**<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>*/
  eContLowPwrLowNoise3_14bit              = 0x12,/**<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>*/
  eContLowPwrLowNoise2_14bit              = 0x11,/**<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>*/
  eContLowPwrLowNoise1_12bit          = 0x10,/**<Continuous measurement,Low-Power Mode 1(12-bit resolution,Low-noise enabled)>*/
  eSingleLowPwrLowNoise4_14bit            = 0x1b,/**<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>*/
  eSingleLowPwrLowNoise3_14bit            = 0x1a,/**<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>*/
  eSingleLowPwrLowNoise2_14bit            = 0x19,/**<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>*/
  eSingleLowLowNoisePwr1_12bit        = 0x18,/**<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>*/
}ePowerMode_t;

/**
  Sensor range
*/
typedef enum{
  e2_g     = 2, /**<±2g>*/
  e4_g     = 4, /**<±4g>*/
  e8_g     = 8, /**<±8g>*/
  e16_g    = 16, /**<±16g>*/
}eRange_t;

/**
  Filtering mode
*/
typedef enum {
  eLPF        = 0x00,/**< low-pass filter path selected>*/
  eHPF        = 0x10,/**<high-pass filter path selected>*/
} ePath_t;

/**
   Bandwidth selection
*/
typedef enum {
  eRateDiv_2     = 0,/**<Rate/2 (up to Rate = 800 Hz, 400 Hz when Rate = 1600 Hz)>*/
  eRateDiv_4     = 1,/**<Rate/4 (High Power/Low power)>*/
  eRateDiv_10    = 2,/**<Rate/10 (HP/LP)>*/
  eRateDiv_20    = 3,/**< Rate/20 (HP/LP)>*/
}eBWfilter_t;

/**
  Data collection rate
*/
typedef enum {
  eRate_0hz            = 0x00,/**<测量关闭>*/
  eRate_1hz6_lp_only   = 0x01,/**<1.6hz>*/
  eRate_12hz5          = 0x02,/**<12.5hz>*/
  eRate_25hz           = 0x03,
  eRate_50hz           = 0x04,
  eRate_100hz          = 0x05,
  eRate_200hz          = 0x06,
  eRate_400hz          = 0x07,
  eRate_800hz          = 0x08,
  eRate_1k6hz          = 0x09,
} eRate_t;

/**
  Motion detection mode
*/
typedef enum {
  eNoDetection        = 0,/**<No detection>*/
  eDetectAct     = 1,/**<Detect movement,the chip automatically 
goes to 12.5 Hz rate in the low-power mode>*/
  eDetectStatMotion   = 3,/**<Detect Motion, the chip detects acceleration below a fixed threshold but 
does not change either rate or operating mode>*/
} eActDetect_t;

/**
  Interrupt source 1 trigger event setting
*/
typedef enum{
  eDoubleTap   = 0x08,/**< Double-tap recognition is routed to INT1 pad>*/
  eFreeFall     = 0x10,/**< Free-fall recognition is routed to INT1 pad>*/
  eWakeUp = 0x20,/**<Wakeup recognition is routed to INT1 pad>*/
  eSingleTap   = 0x40,/**<Single-tap recognition is routed to INT1 pad.>*/
  e6D      = 0x80,/**<6D recognition is routed to INT1 pad>*/
}eInt1Event_t;

/**
  Interrupt source 2 trigger event setting
*/
typedef enum{
  eSleepChange = 0x40,/**<Sleep change status routed to INT2 pad>*/
  eSleepState  = 0x80,/**<Enable routing of SLEEP_STATE on INT2 pad>*/
}eInt2Event_t;

/**
  Click detection mode
*/
typedef enum {
  eOnlySingle          = 0,/**<Only detect click events.>*/
  eBothSingleDouble    = 1,/**<Both single-click and double-click events are detected.>*/
} sTapMode_t;

/**
  位置检测角度转变阈值
*/
typedef enum {
  eDegrees80  ,/**<80 degrees.>*/
  eDegrees70  ,/**<70 degrees.>*/
  eDegrees60  ,/**<60 degrees.>*/
  eDegrees50  ,/**<50 degrees.>*/
} e6DTh_t;

/**
  Click or double click
*/
typedef enum {
  eSingleClick  = 0 ,/**<single click>*/
  eDoubleClick      ,/**<double click>*/
  eNoClick,
} eTap_t;

/**
  which direction is tap event detected
*/
typedef enum {
  eDirXUp = 0,  /**<从 X 正方向发生的点击事件>*/
  eDirXDown = 1,/**<从 X 负方向发生的点击事件>*/
  eDirYUp = 2,/**<从 Y 正方向发生的点击事件>*/
  eDirYDown = 3,/**<从 Y 负方向发生的点击事件>*/
  eDirZUp = 4,/**<从 Z 正方向发生的点击事件>*/
  eDirZDown = 5,/**<从 Z 负方向发生的点击事件>*/
  eDirNone = 6,
}eTapDir_t;

/**
  which direction is wake up event detected
*/
typedef enum {
  eDirX = 0,/**<X方向的运动唤醒芯片>*/
  eDirY = 1,/**<Y方向的运动唤醒芯片>*/
  eDirZ = 2,/**<Z方向的运动唤醒芯片>*/
  eDirError =4,
}eWakeUpDir_t;

/**
  orientation
*/
typedef enum {
  eXDown = 0,/**<X is now down>*/
  eXUp  = 1 ,/**<X is now up>*/
  eYDown = 2 ,/**<Y is now down>*/
  eYUp = 3 , /**<Y is now up>*/
  eZDown = 4 , /**<Z is now down>*/
  eZUp = 5 , /**<Z is now up>*/
} eOrient_t;
public:
  DFRobot_LIS2DW12();
  
  /**
   * @brief Initialize the function
   * @return true(初始化成功)/fasle(初始化失败)
   */
  bool begin(void);
 
  /**
   * @brief Get chip id
   * @return 8 bit serial number
   */
  uint8_t getID();
 
  /**
   * @brief Software reset to restore the value of all registers to the default value
   */
  void softReset();
  
  /**
   * @brief 使芯片持续采集数据
   * @param enable  true(continuous update)/false( output registers not updated until MSB and LSB read)
   */
  void continRefresh(bool enable);
  
  /**
   * @brief Set the filter processing mode
   * @param path path of filtering
                 eLPF   = 0x00,/< low-pass filter path selected>/
                 eHPF   = 0x10,/<high-pass filter path selected>/
   */
  void setFilterPath(ePath_t path);

  /**
   * @brief Set the  bandwidth of the data
   * @param bw   eRateDiv_2     = 0,/<Rate/2 (up to Rate = 800 Hz, 400 Hz when Rate = 1600 Hz)>/
                 eRateDiv_4     = 1,/<Rate/4 (High Power/Low power)>*
                 eRateDiv_10    = 2,/<Rate/10 (HP/LP)>/
                 eRateDiv_20    = 3,/< Rate/20 (HP/LP)>/
   */
  void setFilterBandwidth(eBWfilter_t bw);
  
  /**
   * @brief Set power mode
   * @param mode  16 power modes to choose from
                 eHighPerformance_14bit                   = 0x04,/<High-Performance Mode,14-bit resolution>/
                 eContLowPwr4_14bit                      = 0x03,/<Continuous measurement,Low-Power Mode 4(14-bit resolution)>/
                 eContLowPwr3_14bit                      = 0x02,/<Continuous measurement,Low-Power Mode 3(14-bit resolution)>/
                 eContLowPwr2_14bit                      = 0x01,/<Continuous measurement,Low-Power Mode 2(14-bit resolution)/
                 eContLowPwr1_12bit                  = 0x00,/<Continuous measurement,Low-Power Mode 1(12-bit resolution)>/
                 eSingleLowPwr4_14bit                    = 0x0b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>/
                 eSingleLowPwr3_14bit                    = 0x0a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>/
                 eSingleLowPwr2_14bit                    = 0x09,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>/
                 eSingleLowPwr1_12bit                = 0x08,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>/
                 eHighPerformanceLowNoise_14bit           = 0x14,/<High-Performance Mode,Low-noise enabled,14-bit resolution>/
                 eContLowPwrLowNoise4_14bit              = 0x13,/<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise3_14bit              = 0x12,/<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise2_14bit              = 0x11,/<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise1_12bit          = 0x10,/<Continuous measurement,Low-Power Mode 1(12-bit resolution,Low-noise enabled)>/
                 eSingleLowPwrLowNoise4_14bit            = 0x1b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>/
                 eSingleLowPwrLowNoise3_14bit            = 0x1a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>/
                 eSingleLowPwrLowNoise2_14bit            = 0x19,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>/
                 eSingleLowLowNoisePwr1_12bit        = 0x18,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>/
                  */
  void setPowerMode(ePowerMode_t mode);
  
  /**
   * @brief Chip data collection rate setting
   * @param rate  0-1600hz selection
                  eRate_0hz            <测量关闭>
                  eRate_1hz6_lp_only   <1.6hz>
                  eRate_12hz5          <12.5hz>
                  eRate_25hz        
                  eRate_50hz        
                  eRate_100hz       
                  eRate_200hz       
                  eRate_400hz       
                  eRate_800hz       
                  eRate_1k6hz       
   */
  void setDataRate(eRate_t rate);
  
  /**
   * @brief 设置自由落体时间,也可以称作自由落体样本个数，只有产生足够多的自由落体样本，才会产生自由落体事件
   * @param dur duration(0 ~ 3)
   * @n time = dur * (1/rate)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
   */
  void setFreeFallDur(uint8_t dur);
  
  /**
   * @brief 选择在中断1引脚产生的中断事件
   * @param event  中断事件,当此事件产生会在中断1引脚产生电平跳变
               eDoubleTap   = 0x08,/< Double-tap recognition is routed to INT1 pad>/
               eFreeFall     = 0x10,/< Free-fall recognition is routed to INT1 pad>/
               eWakeUp = 0x20,/<Wakeup recognition is routed to INT1 pad>/
               eSingleTap   = 0x40,/<Single-tap recognition is routed to INT1 pad.>/
               e6D      = 0x80,/<6D recognition is routed to INT1 pad>/
   */
  void setInt1Event(eInt1Event_t event);
  
  /**
   * @brief 选择在中断2引脚产生的中断事件
   * @param event 中断事件,当此事件产生会在中断2引脚产生电平跳变
                 eSleepChange = 0x40,/<Sleep change status routed to INT2 pad>/
                 eSleepState  = 0x80,/<Enable routing of SLEEP_STATE on INT2 pad>/
   */
  void setInt2Event(eInt2Event_t event);
  
  /**
   * @brief lock interrupt Switches between latched ('1'-logic) and pulsed ('0'-logic) mode for 
     @n function source signals and interrupts routed to pins (wakeup, single/double-tap).
   * @param enable  true lock interrupt.
                    false pulsed interrupt
   */
  void lockInterrupt(bool enable);
  
  /**
   * @brief Set the wake-up duration
   * @param dur duration(0 ~ 3)
     @n time = dur * (1/rate)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
   */
  void setWakeUpDur(uint8_t dur);

  /**
   * @brief Set the wake-up Threshold
   * @param th unit(mg),数值是在量程之内
   */
  void setWakeUpThreshold(float th);
  
  /**
   * @brief Sets the mode of motion detection
   * @param mode 运动检测模式
                eNoDetection        = 0,/<No detection>/
                eDetectAct     = 1,/<Detect movement,the chip automatically goes to 12.5 Hz rate in the low-power mode>/
                eDetectStatMotion   = 3,/<Detect Motion, the chip detects acceleration below a fixed threshold but does not change either rate or operating mode>/
   */
  void setActMode(eActDetect_t mode);
  
  /**
   * @brief Set the range
   * @param range  e2_g     = 2, /<±2g>/
                   e4_g     = 4, /<±4g>/
                   e8_g     = 8, /<±8g>/
                   e16_g    = 16, /< ±16g>/
   */
  void setRange(eRange_t range);
  
  /**
   * @brief enable detect click events in the Z direction
   * @param enable ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnZ(bool enable);
  
  /**
   * @brief enable detect click events in the Y direction
   * @param enable ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnY(bool enable);

  /**
   * @brief enable detect click events in the X direction
   * @param enable ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnX(bool enable);

  /**
   * @brief Set the click threshold in the X direction
   * @param th Threshold(mg),Can only be used in the range of 0~2g
   */
  void setTapThresholdOnX(float th);
  
  /**
   * @brief Set the click threshold in the Y direction
   * @param th Threshold(mg),Can only be used in the range of 0~2g
   */
  void setTapThresholdOnY(float th);

  /**
   * @brief Set the click threshold in the Z direction
   * @param th Threshold(mg),Can only be used in the range of 0~2g
   */
  void setTapThresholdOnZ(float th);
  
  /**
   * @brief Duration of maximum time gap for double-tap recognition. When double-tap 
   * @n recognition is enabled, this register expresses the maximum time between two 
   * @n successive detected taps to determine a double-tap event.
   * @param dur duration(0 ~ 3)
   * @n time = dur * (1/rate)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
   */
  void setTapDur(uint8_t dur);
  
  /**
   * @brief Set the click detection mode
   * @param mode     eOnlySingle   //检测单击
                     eBothSingleDouble //检测单击和双击
   */
  void setTapMode(sTapMode_t mode);

  /**
   * @brief Set Thresholds for 4D/6D，当转动的阈值大于指定角度时,就发生方向转变的事件
   * @param degree   eDegrees80   (80°)
                     eDegrees70   (70°)
                     eDegrees60   (60°)
                     eDegrees50   (50°)
   */
  void set6DThreshold(e6DTh_t degree);

  /**
   * @brief Read the acceleration in the x direction
   * @return  Acceleration data from x(mg),测量的量程为±2g,±4g,±8g或±16g,通过setRange()函数设置
   */
  int32_t readAccX();
  
  /**
   * @brief Read the acceleration in the y direction
   * @return  Acceleration data from y(mg),测量的量程为±2g,±4g,±8g或±16g,通过setRange()函数设置
   */
  int32_t readAccY();
  
  /**
   * @brief Read the acceleration in the z direction
   * @return  Acceleration data from z(mg),测量的量程为±2g,±4g,±8g或±16g,通过setRange()函数设置
   */
  int32_t readAccZ();
  
  /**
   * @brief 检测是否有运动产生
   * @return true(产生运动)/false(传感器未运动)
   */
  bool actDetect();
  
  /**
   * @brief 自由落体运动检测
   * @return true(检测到自由落体运动)/false(未检测到自由落体运动)
   */
  bool freeFallDetect();
  
  /**
   * @brief Source of change in position portrait/landscape/face-up/face-down.
   * @return true(a change in position is detected)/false(no event detected)
   */
  bool ia6DDetect();
  
  /**
   * @brief 获取传感器现在的位置
   * @return    eXDown  /<X is now down>/
                eXUp    /<X is now up>/
                eYDown  /<Y is now down>/
                eYUp    /<Y is now up>/
                eZDown  /<Z is now down>/
                eZUp    /<Z is now up>/
   */
  eOrient_t getOrient();
  
  /**
   * @brief 点击检测
   * @return   eSingleClick       /<Single click>/
               eDoubleClick       /<double click>/
               eNoClick,          //没有点击产生
                */
  eTap_t tapDetect();
  
  /**
   * @brief 点击方向的源头检测
   * @return   eDirXUp   /<从 X 正方向发生的点击事件>/
               eDirXDown /<从 X 负方向发生的点击事件>/
               eDirYUp   /<从 Y 正方向发生的点击事件>/
               eDirYDown /<从 Y 负方向发生的点击事件>/
               eDirZUp   /<从 Z 正方向发生的点击事件>/
               eDirZDown /<从 Z 负方向发生的点击事件>/
   */
  eTapDir_t getTapDirection();
  
  /**
   * @brief 唤醒的运动方向检测
   * @return   eDirX    /<X方向的运动唤醒芯片>/
               eDirY    /<Y方向的运动唤醒芯片>/
               eDirZ    /<Z方向的运动唤醒芯片>/
               eDirError,
   */
  eWakeUpDir_t getWakeUpDir();

protected:

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  virtual uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size) = 0;
  
  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  virtual uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size)= 0; 
  float   _range     = e2_g;
  int32_t _range1    = 0;
private:

  /**
   * @brief set quiet time after a tap detection: this register represents
     @n the time after the first detected tap in which there must not be any overthreshold event.
   * @param quiet quiet time
   */
  void setTapQuiet(uint8_t quiet);
  
  /**
   * @brief Set the maximum time of an over-threshold signal detection to be recognized as a tap event.
   * @param shock  shock time
   */
  void setTapShock(uint8_t shock);
  
  /**
   * @brief Set 6d filtered data source
   * @param data 0: rate/2 low pass filtered data sent to 6D interrupt function (default)
                 1: LPF2 output data sent to 6D interrupt function)
   */
  void set6dFeedData(uint8_t data);
  
  /**
   * @brief Set Free-fall threshold
   * @param th threshold
   */
  void setFfThreshold(uint8_t th);
  
  /**
   * @brief Set duration to go in sleep mode.
   * @param dur  duration
   */
  void setActSleepDur(uint8_t dur);
};

class DFRobot_IIS2DLPC_I2C : public DFRobot_LIS2DW12{
public:
  /*!
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x19/0x18)
   */
  DFRobot_IIS2DLPC_I2C(TwoWire * pWire = &Wire,uint8_t addr = IIS2DLPC_I2C_ADDR);
  /**
   * @brief init function
   * @return true(初始化成功)/fasle(初始化失败)
   */
  bool begin(void);

protected:

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
  
  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    uint8_t _deviceAddr;
    TwoWire *_pWire;
};

class DFRobot_IIS2DLPC_SPI : public DFRobot_LIS2DW12{

public:
  /*!
   * @brief Constructor 
   * @param cs : Chip selection pinChip selection pin
   * @param spi :SPI controller
   */
  DFRobot_IIS2DLPC_SPI(uint8_t cs = 3,SPIClass *spi=&SPI);
  
  /**
   * @brief init function
   * @return true(初始化成功)/fasle(初始化失败)
   */
  bool begin(void);
protected:

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
  
  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    SPIClass *_pSpi;
    uint8_t _cs = 0;
};

class DFRobot_LIS2DW12_I2C : public DFRobot_LIS2DW12{
public:
  /*!
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x19/0x18)
   */
  DFRobot_LIS2DW12_I2C(TwoWire * pWire = &Wire,uint8_t addr = LIS2DW12_I2C_ADDR);
  
  /**
   * @brief init function
   * @return true(初始化成功)/fasle(初始化失败)
   */
  bool begin(void);

protected:
  
  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);

  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    uint8_t _deviceAddr;
    TwoWire *_pWire;
};

class DFRobot_LIS2DW12_SPI : public DFRobot_LIS2DW12{

public:
  /*!
   * @brief Constructor 
   * @param cs : Chip selection pinChip selection pin
   * @param spi :SPI controller
   */
  DFRobot_LIS2DW12_SPI(uint8_t cs = 3,SPIClass *spi=&SPI);
  
  /**
   * @brief init function
   * @return true(初始化成功)/fasle(初始化失败)
   */
  bool begin(void);
protected:

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
  
  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    SPIClass *_pSpi;
    uint8_t _cs = 0;
};
#endif
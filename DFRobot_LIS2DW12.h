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
//#define ENABLE_DBG

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
  
  eHighPerformance                   = 0x04,/**<High-Performance Mode>*/
  eContLowPwr_4                      = 0x03,/**<Continuous measurement,Low-Power Mode 4(14-bit resolution)>*/
  eContLowPwr_3                      = 0x02,/**<Continuous measurement,Low-Power Mode 3(14-bit resolution)>*/
  eContLowPwr_2                      = 0x01,/**<Continuous measurement,Low-Power Mode 2(14-bit resolution)>*/
  eContLowPwr_12bit                  = 0x00,/**<Continuous measurement,Low-Power Mode 1(12-bit resolution)>*/
  eSingleLowPwr_4                    = 0x0b,/**<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>*/
  eSingleLowPwr_3                    = 0x0a,/**<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>*/
  eSingleLowPwr_2                    = 0x09,/**<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>*/
  eSingleLowPwr_12bit                = 0x08,/**<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>*/
  eHighPerformanceLowNoise           = 0x14,/**<High-Performance Mode,Low-noise enabled>*/
  eContLowPwrLowNoise_4              = 0x13,/**<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>*/
  eContLowPwrLowNoise_3              = 0x12,/**<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>*/
  eContLowPwrLowNoise_2              = 0x11,/**<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>*/
  eContLowPwrLowNoise_12bit          = 0x10,/**<Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)>*/
  eSingleLowPwrLowNoise_4            = 0x1b,/**<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>*/
  eSingleLowPwrLowNoise_3            = 0x1a,/**<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>*/
  eSingleLowPwrLowNoise_2            = 0x19,/**<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>*/
  eSingleLowLowNoisePwr_12bit        = 0x18,/**<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>*/
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
  eLpfOnOut        = 0x00,/**< low-pass filter path selected>*/
  eHpfOnOut   = 0x10,/**<high-pass filter path selected>*/
} eFds_t;

/**
   Bandwidth selection
*/
typedef enum {
  eOdrDiv_2     = 0,/**<ODR/2 (up to ODR = 800 Hz, 400 Hz when ODR = 1600 Hz)>*/
  eOdrDiv_4     = 1,/**<ODR/4 (High Power/Low power)>*/
  eOdrDiv_10    = 2,/**<ODR/10 (HP/LP)>*/
  eOdrDiv_20    = 3,/**< ODR/20 (HP/LP)>*/
}eBWfilter_t;

/**
  Data collection rate
*/
typedef enum {
  eOdr_0hz            = 0x00,/**<测量关闭>*/
  eOdr_1hz6_lp_only   = 0x01,/**<1.6hz>*/
  eOdr_12hz5          = 0x02,/**<12.5hz>*/
  eOdr_25hz           = 0x03,
  eOdr_50hz           = 0x04,
  eOdr_100hz          = 0x05,
  eOdr_200hz          = 0x06,
  eOdr_400hz          = 0x07,
  eOdr_800hz          = 0x08,
  eOdr_1k6hz          = 0x09,
} eFreq_t;

/**
  Free fall threshold@ ±2 g FS
*/
typedef enum {
  eFfTsh5LSbFS2g  = 0, /**<5 LSB>*/
  eFfTsh7LSbFS2g  = 1, /**<7 LSB>*/
  eFfTsh8LSbFS2g  = 2, /**<8 LSB>*/
  eFfTsh10LSbFS2g = 3, /**<10 LSB>*/
  eFfTsh11LSbFS2g = 4, /**<11 LSB>*/
  eFfTsh13LSbFS2g = 5, /**<13 LSB>*/
  eFfTsh15LSbFS2g = 6, /**<15 LSB>*/
  eFfTsh16LSbFS2g = 7, /**<16 LSB>*/
} eFfThs_t;

/**
  Motion detection mode
*/
typedef enum {
  eNoDetection        = 0,/**<No detection>*/
  eDetectActInact     = 1,/**<Detect movement,the chip automatically 
goes to 12.5 Hz ODR in the low-power mode>*/
  eDetectStatMotion   = 3,/**<Detect Motion, the chip detects acceleration below a fixed threshold but 
does not change either ODR or operating mode>*/
} eSleepOn_t;

/**
  Interrupt source 1 trigger event setting
*/
typedef enum{
  eDoubleTap   = 0x08,/**< Double-tap recognition is routed to INT1 pad>*/
  eFfEvent     = 0x10,/**< Free-fall recognition is routed to INT1 pad>*/
  eWakeupEvent = 0x20,/**<Wakeup recognition is routed to INT1 pad>*/
  eSingleTap   = 0x40,/**<Single-tap recognition is routed to INT1 pad.>*/
  eTnt16d      = 0x80,/**<6D recognition is routed to INT1 pad>*/
}eInt1Event_t;

/**
  Interrupt source 2 trigger event setting
*/
typedef enum{
  eBoot        = 0x20,/**< Boot state routed to INT2 pad.>*/
  eSleepChange = 0x40,/**<Enable routing of SLEEP_STATE on INT2 pad>*/
  eSleepState  = 0x80,/**<Sleep change status routed to INT2 pad>*/
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
  eDegrees80          = 0,/**<80 degrees.>*/
  eDegrees70             ,/**<70 degrees.>*/
  eDegrees60             ,/**<60 degrees.>*/
  eDegrees50             ,/**<50 degrees.>*/
} s6dTH_t;

/**
  Click or double click
*/
typedef enum {
  eSingleClick  = 0 ,/**<click>*/
  eDoubleClick      ,/**<double click>*/
  eNoClick,
} eTap_t;

/**
  which direction is tap event detected
*/
typedef enum {
  eDirXup = 0,  /**<从 X 正方向发生的点击事件>*/
  eDirXdown = 1,/**<从 X 负方向发生的点击事件>*/
  eDirYup = 2,/**<从 Y 正方向发生的点击事件>*/
  eDirYdown = 3,/**<从 Y 负方向发生的点击事件>*/
  eDirZup = 4,/**<从 Z 正方向发生的点击事件>*/
  eDirZdown = 5,/**<从 Z 负方向发生的点击事件>*/
  eDirNone,
}eTapDir_t;

/**
  which direction is wake up event detected
*/
typedef enum {
  eDirX = 0,/**<X方向的运动唤醒芯片>*/
  eDirY = 1,/**<Y方向的运动唤醒芯片>*/
  eDirZ = 2,/**<Z方向的运动唤醒芯片>*/
  eDirError,
}eWakeupDir_t;

/**
  orientation
*/
typedef enum {
  eXdown = 0,/**<X is now down>*/
  eXup  = 1 ,/**<X is now up>*/
  eYdown = 2 ,/**<Y is now down>*/
  eYup = 3 , /**<Y is now up>*/
  eZdown = 4 , /**<Z is now down>*/
  eZup = 5 , /**<Z is now up>*/
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
                 eLpfOnOut   = 0x00,/< low-pass filter path selected>/
                 eHpfOnOut   = 0x10,/<high-pass filter path selected>/
   */
  void setFilterPath(eFds_t path);

  /**
   * @brief Set the  bandwidth of the data
   * @param bw   eOdrDiv_2     = 0,/<ODR/2 (up to ODR = 800 Hz, 400 Hz when ODR = 1600 Hz)>/
                 eOdrDiv_4     = 1,/<ODR/4 (High Power/Low power)>*
                 eOdrDiv_10    = 2,/<ODR/10 (HP/LP)>/
                 eOdrDiv_20    = 3,/< ODR/20 (HP/LP)>/
   */
  void setFilterBandwidth(eBWfilter_t bw);
  
  /**
   * @brief Set power mode
   * @param mode  16 power modes to choose from
                 eHighPerformance                   = 0x04, /<High-Performance Mode>/
                 eContLowPwr_4                      = 0x03,/<Continuous measurement,Low-Power Mode 4(14-bit resolution)>/
                 eContLowPwr_3                      = 0x02,/<Continuous measurement,Low-Power Mode 3(14-bit resolution)>/
                 eContLowPwr_2                      = 0x01,/<Continuous measurement,Low-Power Mode 2(14-bit resolution)>/
                 eContLowPwr_12bit                  = 0x00,/<Continuous measurement,Low-Power Mode 1(12-bit resolution)>/
                 eSingleLowPwr_4                    = 0x0b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>/
                 eSingleLowPwr_3                    = 0x0a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>/
                 eSingleLowPwr_2                    = 0x09,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>/
                 eSingleLowPwr_12bit                = 0x08,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>/
                 eHighPerformanceLowNoise           = 0x14,/<High-Performance Mode,Low-noise enabled>/
                 eContLowPwrLowNoise_4              = 0x13,/<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise_3              = 0x12,/<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise_2              = 0x11,/<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise_12bit          = 0x10,/<Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)>/
                 eSingleLowPwrLowNoise_4           = 0x1b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>/
                 eSingleLowPwrLowNoise_3           = 0x1a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>/
                 eSingleLowPwrLowNoise_2           = 0x19,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>/
                 eSingleLowLowNoisePwr_12bit       = 0x18,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>/
   */
  void setPowerMode(ePowerMode_t mode);
  
  /**
   * @brief Chip data collection rate setting
   * @param freq  0-1600hz selection
                  eOdr_0hz            <测量关闭>
                  eOdr_1hz6_lp_only   <1.6hz>
                  eOdr_12hz5          <12.5hz>
                  eOdr_25hz        
                  eOdr_50hz        
                  eOdr_100hz       
                  eOdr_200hz       
                  eOdr_400hz       
                  eOdr_800hz       
                  eOdr_1k6hz       
   */
  void setDataRate(eFreq_t freq);
  
  /**
   * @brief 设置自由落体时间(或可以称作自由落体样本个数，只有产生足够多的自由落体样本，才会产生自由落体事件)
   * @param dur (0 ~ 31)
   * @n time = dur * (1/ODR)(unit:s)
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
                   eDoubleTap = 0x08,/< Double-tap recognition is routed to INT1 pad>/
                   eFfEvent = 0x10,/< Free-fall recognition is routed to INT1 pad>/
                   eWakeupEvent = 0x20,/<Wakeup recognition is routed to INT1 pad>/
                   eSingleTap = 0x40,/<Single-tap recognition is routed to INT1 pad.>/
                   eTnt16d  = 0x80,/<6D recognition is routed to INT1 pad>/
   */
  void setPinInt1Route(eInt1Event_t event);
  
  /**
   * @brief 选择在中断2引脚产生的中断事件
   * @param event 中断事件,当此事件产生会在中断2引脚产生电平跳变
                   eBoot = 0x20,/< Boot state routed to INT2 pad.>/
                   eSleepChange = 0x40,/<Enable routing of SLEEP_STATE on INT2 pad>/
                   eSleepState  = 0x80,/<Sleep change status routed to INT2 pad>/
   */
  void setPinInt2Route(eInt2Event_t event);
  
  /**
   * @brief Latch interrupt Switches between latched ('1'-logic) and pulsed ('0'-logic) mode for 
     @n function source signals and interrupts routed to pins (wakeup, single/double-tap).
   * @param enable  true latched interrupt.
                    false pulsed interrupt
   */
  void latchInterrupt(bool enable);
  
  /**
   * @brief Set the wake-up duration
   * @param dur (0 ~ 3)
     @n time = dur * (1/ODR)(unit:s)
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
   * @param th:unit(g),数值是在量程之内
   */
  void setWakeUpThreshold(float th);
  
  /**
   * @brief Sets the mode of motion detection
   * @param mode 运动检测模式
                eNoDetection        = 0,/<No detection>/
                eDetectActInact     = 1,/<Detect movement,the chip automatically goes to 12.5 Hz ODR in the low-power mode>/
                eDetectStatMotion   = 3,/<Detect Motion, the chip detects acceleration below a fixed threshold but does not change either ODR or operating mode>/
   */
  void setActMode(eSleepOn_t mode);
  
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
   * @param enable:ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnY(bool enable);

  /**
   * @brief enable detect click events in the X direction
   * @param enable ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnX(bool enable);

  /**
   * @brief Set the click threshold in the X direction
   * @param th Threshold(g),Can only be used in the range of ±2g
   */
  void setTapThresholdOnX(int32_t th);
  
  /**
   * @brief Set the click threshold in the Y direction
   * @param th Threshold(g),Can only be used in the range of ±2g
   */
  void setTapThresholdOnY(int32_t th);

  /**
   * @brief Set the click threshold in the Z direction
   * @param th Threshold(g),Can only be used in the range of ±2g
   */
  void setTapThresholdOnZ(int32_t th);
  
  /**
   * @brief Duration of maximum time gap for double-tap recognition. When double-tap 
   * @n recognition is enabled, this register expresses the maximum time between two 
   * @n successive detected taps to determine a double-tap event.
   * @param dur (0 ~ 15)
   * @n time = dur * (1/ODR)(unit:s)
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
   * @param degree   eDegrees80   80°
                     eDegrees70   70°
                     eDegrees60   60°
                     eDegrees50   50°
   */
  void set6dThreshold(s6dTH_t degree);

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
   * @return true( no event detected)/false(a change in position is detected)
   */
  bool ia6dDetect();
  
  /**
   * @brief 获取传感器现在的位置
   * @return    eXdown = 0 ,/<X is now down>/
                eXup   = 1 ,/<X is now up>/
                eYdown = 2 ,/<Y is now down>/
                eYup   = 3 ,/<Y is now up>/
                eZdown = 4 ,/<Z is now down>/
                eZup   = 5 ,/<Z is now up>/
   */
  eOrient_t getOrient();
  
  /**
   * @brief 点击检测
   * @return   eSingleClick  = 0 ,/<click>/
               eDoubleClick      ,/<double click>/
               eNoClick,          //没有点击产生
                */
  eTap_t tapDetect();
  
  /**
   * @brief 点击方向的源头检测
   * @return   eDirXup   = 0,/<从 X 正方向发生的点击事件>/
               eDirXdown = 1,/<从 X 负方向发生的点击事件>/
               eDirYup   = 2,/<从 Y 正方向发生的点击事件>/
               eDirYdown = 3,/<从 Y 负方向发生的点击事件>/
               eDirZup   = 4,/<从 Z 正方向发生的点击事件>/
               eDirZdown = 5,/<从 Z 负方向发生的点击事件>/
   */
  eTapDir_t getTapDirection();
  
  /**
   * @brief 唤醒的运动方向检测
   * @return   eDirX = 0,/<X方向的运动唤醒芯片>/
               eDirY = 1,/<Y方向的运动唤醒芯片>/
               eDirZ = 2,/<Z方向的运动唤醒芯片>/
               eDirError,
   */
  eWakeupDir_t getWakeUpDir();

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
  uint8_t _range1    = 0;
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
   * @param data 0: ODR/2 low pass filtered data sent to 6D interrupt function (default)
                 1: LPF2 output data sent to 6D interrupt function)
   */
  void set6dFeedData(uint8_t data);
  
  /**
   * @brief Set Free-fall threshold
   * @param th threshold
   */
  void setFfThreshold(eFfThs_t th);
  
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
/*!
 * @file DFRobot_IIS2DLPC.h
 * @brief Define the basic structure of class DFRobot_IIS2DLPC 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-12-23
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_IIS2DLPC
 */

#ifndef DFROBOT_IIS2DLPC_H
#define DFROBOT_IIS2DLPC_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>
#include <SPI.h>
//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define IIS2DLPC_I2C_ADDR  (0x19)  /*sensor IIC address*/

//#define ERR_OK             0      //ok
//#define ERR_DATA_BUS      -1      //error in data bus
//#define ERR_IC_VERSION    -2      //chip version mismatch


class DFRobot_IIS2DLPC
{
public:
  #define IIS2DLPC_REG_CARD_ID    0x0F     /*The chip id*/
  #define IIS2DLPC_REG_CTRL_REG1  0x20     /*Control register 1*/
  #define IIS2DLPC_REG_CTRL_REG4  0x23     /*Control register 2*/
  #define IIS2DLPC_REG_CTRL_REG2  0x21     /*Control register 3*/
  #define IIS2DLPC_REG_CTRL_REG3  0x22     /*Control register 4*/
  #define IIS2DLPC_REG_CTRL_REG5  0x24     /*Control register 5*/
  #define IIS2DLPC_REG_CTRL_REG6  0x25     /*Control register 6*/
  #define IIS2DLPC_REG_CTRL_REG7  0x3F     /*Control register 7*/
  #define IIS2DLPC_REG_STATUS_REG 0x27     /*Status register*/
  #define IIS2DLPC_REG_OUT_X_L      0x28     /*The low order of the X-axis acceleration register*/
  #define IIS2DLPC_REG_OUT_X_H      0x29     /*The high point of the X-axis acceleration register*/
  #define IIS2DLPC_REG_OUT_Y_L      0x2A     /*The low order of the Y-axis acceleration register*/
  #define IIS2DLPC_REG_OUT_Y_H      0x2B     /*The high point of the Y-axis acceleration register*/
  #define IIS2DLPC_REG_OUT_Z_L      0x2C     /*The low order of the Z-axis acceleration register*/
  #define IIS2DLPC_REG_OUT_Z_H      0x2D     /*The high point of the Z-axis acceleration register*/
  #define IIS2DLPC_REG_WAKE_UP_DUR  0x35   
  #define IIS2DLPC_REG_FREE_FALL    0x36    /*Free fall event register*/
  #define IIS2DLPC_REG_STATUS_DUP    0x37  /*Interrupt event status register*/
  
  
  #define IIS2DLPC_REG_TAP_THS_X    0x30
  #define IIS2DLPC_REG_TAP_THS_Y    0x31
  #define IIS2DLPC_REG_TAP_THS_Z    0x32
  #define IIS2DLPC_REG_INT_DUR      0x33
  #define IIS2DLPC_REG_WAKE_UP_THS  0x34
/**
  Event detection status register
*/
typedef struct {
  uint8_t drdy                       : 1;
  uint8_t ffIa                      : 1;
  uint8_t ia6d                     : 1;
  uint8_t singleTap                 : 1;
  uint8_t doubleTap                 : 1;
  uint8_t sleepStateIa             : 1;
  uint8_t drdyt  : 1;
  uint8_t ovr                        : 1;

} sStatusDup_t;

/**
Wakeup source register
*/
typedef struct {
  uint8_t zwu                       : 1;
  uint8_t ywu                       : 1;
  uint8_t xwu                       : 1;
  uint8_t wuIa                      : 1;
  uint8_t sleepStateIa             : 1;
  uint8_t ffIa                      : 1;
  uint8_t notUse                : 2;

} sWakeUpSrc_t;

/**
  Tap source register
*/
typedef struct {

  uint8_t ztap                      : 1;
  uint8_t ytap                      : 1;
  uint8_t xtap                      : 1;
  uint8_t tapSign                   : 1;
  uint8_t doubleTap                 : 1;
  uint8_t singleTap                 : 1;
  uint8_t tapIa                     : 1;
  uint8_t notUse                : 1;

} sTapSrc_t;

/**
  6D source register
*/
typedef struct {
  uint8_t xl                         : 1;
  uint8_t xh                         : 1;
  uint8_t yl                         : 1;
  uint8_t yh                         : 1;
  uint8_t zl                         : 1;
  uint8_t zh                         : 1;
  uint8_t ia6d                     : 1;
  uint8_t notUse                : 1;
} sSixdSrc_t;

/**
    all related interrupt function flags routed to the INT pads are reset 
  simultaneously
*/
typedef struct {
  uint8_t ffIa                      : 1;
  uint8_t wuIa                      : 1;
  uint8_t singleTap                 : 1;
  uint8_t doubleTap                 : 1;
  uint8_t ia6d                     : 1;
  uint8_t sleepChangeIa            : 1;
  uint8_t notUse                : 2;

} sAllIntSrc_t;
/**
    all related interrupt function flags routed to the INT pads are reset 
  simultaneously
*/
typedef struct {
  sStatusDup_t   status;
  sWakeUpSrc_t  wakeUp;
  sTapSrc_t      tapSrc;
  sSixdSrc_t     sixdSrc;
  sAllIntSrc_t  allIntSrc;
}sAllSources_t;


public:


/**
   Power mode
*/
typedef enum{
  
  eHighPerformance                   = 0x04, 
  eContLowPwr_4                      = 0x03,
  eContLowPwr_3                      = 0x02,
  eContLowPwr_2                      = 0x01,
  eContLowPwr_12bit                  = 0x00,
  eSingleLowPwr_4                    = 0x0b,
  eSingleLowPwr_3                    = 0x0a,
  eSingleLowPwr_2                    = 0x09,
  eSingleLowPwr_12bit                = 0x08,
  eHighPerformanceLowNoise           = 0x14,
  eContLowPwrLowNoise_4              = 0x13,
  eContLowPwrLowNoise_3              = 0x12,
  eContLowPwrLowNoise_2              = 0x11,
  eContLowPwrLowNoise_12bit          = 0x10,
  eSingleLowPwrLowNoise_4            = 0x1b,
  eSingleLowPwrLowNoise_3            = 0x1a,
  eSingleLowPwrLowNoise_2            = 0x19,
  eSingleLowLowNoisePwr_12bit        = 0x18,
}ePowerMode_t;

/**
  Sensor range
*/
typedef enum{
  eIIS2DLPC_2g     = 0, /**<±2g>*/
  eIIS2DLPC_4g     = 1, /**<±4g>*/
  eIIS2DLPC_8g     = 2, /**<±8g>*/
  eIIS2DLPC_16g    = 3, /**< ±16g>*/
}eRange_t;

/**
  Filtering mode
*/
typedef enum {
  eIIS2DLPC_LPF_ON_OUT         = 0x00,/**<Low pass filter>*/
  eIIS2DLPC_USER_OFFSET_ON_OUT  = 0x01,
  eIIS2DLPC_HIGH_PASS_ON_OUT    = 0x10,/**<High pass filter>*/
} eIIS2DLPC_fds_t;




/**
   bandwidth of collected data
*/
typedef enum {
  eIIS2DLPC_ODR_DIV_2     = 0,/**<ODR/2 (up to ODR = 800 Hz, 400 Hz when ODR = 1600 Hz)>*/
  eIIS2DLPC_ODR_DIV_4     = 1,/**<ODR/4 (HP/LP)>*/
  eIIS2DLPC_ODR_DIV_10    = 2,/**<ODR/10 (HP/LP)>*/
  eIIS2DLPC_ODR_DIV_20    = 3,/**< ODR/20 (HP/LP)>*/
}eBWfilter_t;

/**
  Data collection rate
*/
typedef enum {
  eOdr_off            = 0x00,
  eOdr_1hz6_lp_only   = 0x01,
  eOdr_12hz5          = 0x02,
  eOdr_25hz           = 0x03,
  eOdr_50hz           = 0x04,
  eOdr_100hz          = 0x05,
  eOdr_200hz          = 0x06,
  eOdr_400hz          = 0x07,
  eOdr_800hz          = 0x08,
  eOdr_1k6hz          = 0x09,
  eSetSwTrig          = 0x12,
  eSetPinTrig         = 0x22,
} eOdr_t;

/**
  Free fall threshold@ ±2 g FS
*/
typedef enum {
  eFfTsh_5LSb_FS2g  = 0,/**<5 LSB>*/
  eFfTsh_7LSb_FS2g  = 1,/**<7 LSB>*/
  eFfTsh_8LSb_FS2g  = 2,/**<8 LSB>*/
  eFfTsh_10LSb_FS2g = 3,/**<10 LSB>*/
  eFfTsh_11LSb_FS2g = 4,/**<11 LSB>*/
  eFfTsh_13LSb_FS2g = 5,/**<13 LSB>*/
  eFfTsh_15LSb_FS2g = 6,/**<15 LSB>*/
  eFfTsh_16LSb_FS2g = 7,/**<16 LSB>*/
} eFfThs_t;

/**
  Motion detection mode
*/
typedef enum {
  eNoDetection        = 0,/**<No detection>*/
  eDetectActInact     = 1,/**<Detect movement>*/
  eDetectStatMotion   = 3,/**<Detect Motion>*/
} eSleepOn_t;

/**
  Interrupt source 1 trigger event setting
*/
typedef enum{
  eDoubleTap = 0x08,/**< Double-tap recognition is routed to INT1 pad>*/
  eFfEvent = 0x10,/**< Free-fall recognition is routed to INT1 pad>*/
  eWakeupEvent = 0x20,/**<Wakeup recognition is routed to INT1 pad>*/
  eSingleTap = 0x40,/**<Single-tap recognition is routed to INT1 pad.>*/
  eTnt16d  = 0x80,/**<6D recognition is routed to INT1 pad>*/
}eInteEvent_t;

/**
  Interrupt source 2 trigger event setting
*/
typedef enum{
  eBoot = 0x20,/**< Boot state routed to INT2 pad.>*/
  eSleepChange = 0x40,/**<Enable routing of SLEEP_STATE on INT2 pad>*/
  eSleepState  = 0x80,/**<Sleep change status routed to INT2 pad>*/
}eInt2Event_t;

/**
  Click detection mode
*/
typedef enum {
  eOnlySingle          = 0,/**<Only detect click events.>*/
  eBothSingleDouble   = 1,/**<Both single-click and double-click events are detected.>*/
} sTapMode_t;

/**
  位置检测
*/
typedef enum {
  eDegrees80          = 0,/**<80 degrees.>*/
  eDegrees70          = 0,/**<.>*/
  eDegrees60          = 0,/**<.>*/
  eDegrees50          = 0,/**<.>*/
} s6dTH_t;
public:
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

  
protected:
  void setTapQuiet(uint8_t quiet);
  void setTapShock(uint8_t shock);
  void set6dFeedData(uint8_t data);
  void setFfThreshold(eFfThs_t th);
  void setActSleepDur(uint8_t dur);
  virtual uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size) = 0;
  /**
   * @brief Write command into sensor chip 
   * @param reg  
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
  virtual uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size)= 0; 
  uint8_t _interface = 0;
  float _range = eIIS2DLPC_2g;
};



class DFRobot_IIS2DLPC_I2C : public DFRobot_IIS2DLPC{
public:
  /*!
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x64/0x65/0x660x67)
   */
  DFRobot_IIS2DLPC_I2C(TwoWire * pWire = &Wire,uint8_t addr = IIS2DLPC_I2C_ADDR);
  /**
   * @brief init function
   * @return Return 1 if initialization succeeds, otherwise return non-zero and error code.
   */
  int begin(void);
private:

  /**
   * @brief Write command into sensor chip 
   * @param 
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
  /**
   * @brief Write command into sensor chip 
   * @param reg  
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
    uint8_t _deviceAddr;
    TwoWire *_pWire;
};
class DFRobot_IIS2DLPC_SPI : public DFRobot_IIS2DLPC{

public:
  /*!
   * @brief Constructor 
   * @param cs : Chip selection pinChip selection pin
   * @param spi :SPI controller
   */
  DFRobot_IIS2DLPC_SPI(uint8_t cs = 3,SPIClass *spi=&SPI);
  
  /**
   * @brief init function
   * @return Return 1 if initialization succeeds, otherwise return non-zero and error code.
   */
  int begin(void);
protected:

  /**
   * @brief Write command into sensor chip 
   * @param 
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
  /**
   * @brief Write command into sensor chip 
   * @param reg  
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    SPIClass *_pSpi;
    uint8_t _cs = 0;
};

#endif
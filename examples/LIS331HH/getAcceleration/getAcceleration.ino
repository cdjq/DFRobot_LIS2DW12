/**！
 * @file getAcceleration.ino
 * @brief 获取x,y,z三个方向的加速度值,加速度的测量的量程可选择±6g,±12g或±24g
 * @n 在使用SPI时片选引脚可以通过 LIS331HH_CS 的值修改
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_LIS
 */

#include <DFRobot_LIS.h>

//当你使用I2C通信时,使用下面这段程序,使用DFRobot_LIS331HH_I2C构造对象
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
//DFRobot_LIS331HH_I2C acce(&Wire,0x19);
DFRobot_LIS331HH_I2C acce;

//当你使用SPI通信时,使用下面这段程序,使用DFRobot_LIS331HH_SPI构造对象
#if defined(ESP32) || defined(ESP8266)
#define LIS331HH_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define LIS331HH_CS 3
#elif (defined NRF5)
#define LIS331HH_CS P3
#endif
/*!
 * @brief Constructor 
 * @param cs : Chip selection pinChip selection pin
 * @param spi :SPI controller
 */
//DFRobot_LIS331HH_SPI acce(/*cs = */LIS331HH_CS,&SPI);
//DFRobot_LIS331HH_SPI acce(/*cs = */LIS331HH_CS);

void setup(void){

  Serial.begin(9600);
  //Chip initialization
  while(!acce.begin()){
     delay(1000);
     Serial.println("初始化失败，请检查连线或I2C地址设置");
  }
  //Get chip id
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  
  /**
    set range:Range(g)
              eLis331hh_6g = 6,/<±6g>/
              eLis331hh_12g = 12,/<±12g>/
              eLis331hh_24g = 24/<±24g>/
  */
  acce.setRange(/*range = */DFRobot_LIS::eLis331hh_6g);

  /**
    Set data measurement rate：
      ePowerDown_0HZ = 0,
      eLowPower_halfHZ,
      eLowPower_1HZ,
      eLowPower_2HZ,
      eLowPower_5HZ,
      eLowPower_10HZ,
      eNormal_50HZ,
      eNormal_100HZ,
      eNormal_400HZ,
      eNormal_1000HZ,
  */
  acce.setAcquireRate(/*rate = */DFRobot_LIS::eNormal_50HZ);
  delay(1000);
}

void loop(void){

    //Get the acceleration in the three directions of xyz
    //测量的量程为±6g,±12g或±24g,通过setRange()函数设置
    long ax,ay,az;
    ax = acce.readAccX();//Get the acceleration in the x direction
    ay = acce.readAccY();//Get the acceleration in the y direction
    az = acce.readAccZ();//Get the acceleration in the z direction
    //acce.getAcceFromXYZ(/*accx = */ax,/*accy = */ay,/*accz = */az);//第二种获取三方向加速度的方法
    Serial.print("Acceleration x: "); //print acceleration
    Serial.print(ax);
    Serial.print(" mg \ty: ");
    Serial.print(ay);
    Serial.print(" mg \tz: ");
    Serial.print(az);
    Serial.println(" mg");
    delay(300);
}

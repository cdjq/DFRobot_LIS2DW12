/**！
 * @file getAcceleration.ino
 * @brief 获取x,y,z三个方向的加速度值,三个方向加速度的量程可选择±100g或±200g
 * @n 在使用SPI时,片选引脚时可以通过改变宏H3LIS200DL_CS的值修改
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_H3LIS
 */

#include <DFRobot_LIS.h>

//当你使用I2C通信时,使用下面这段程序,使用DFRobot_H3LIS200DL_I2C构造对象
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
//DFRobot_H3LIS200DL_I2C acce(&Wire,0x19);
DFRobot_H3LIS200DL_I2C acce;

//当你使用SPI通信时,使用下面这段程序,使用DFRobot_H3LIS200DL_SPI构造对象
#if defined(ESP32) || defined(ESP8266)
#define H3LIS200DL_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define H3LIS200DL_CS 3
#elif (defined NRF5)
#define H3LIS200DL_CS P3
#endif
/*!
 * @brief Constructor 
 * @param cs  Chip selection pinChip selection pin
 * @param spi  SPI controller
 */
//DFRobot_H3LIS200DL_SPI acce(/*cs = */H3LIS200DL_CS);

void setup(void){

  Serial.begin(9600);
  //Chip initialization
  while(!acce.begin()){
     Serial.println("初始化失败，请检查连线与I2C地址设置");
     delay(1000);
  }
  //Get chip id
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  
  /**
    set range:Range(g)
              eH3lis200dl_100g,/< ±100g>/
              eH3lis200dl_200g,/< ±200g>/
  */
  acce.setRange(/*Range = */DFRobot_LIS::eH3lis200dl_100g);

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
  acce.setAcquireRate(/*Rate = */DFRobot_LIS::eNormal_50HZ);
  delay(1000);
}

void loop(void){

  //Get the acceleration in the three directions of xyz
  long ax,ay,az;
  //测量的量程为±100g或±200g,通过setRange()函数设置
  ax = acce.readAccX();//Get the acceleration in the x direction
  ay = acce.readAccY();//Get the acceleration in the y direction
  az = acce.readAccZ();//Get the acceleration in the z direction
  //acce.getAcceFromXYZ(/*accx = */ax,/*accy = */ay,/*accz = */az);//第二种获取三方向加速度的方法
  Serial.print("Acceleration x: "); //print acceleration
  Serial.print(ax);
  Serial.print(" g\t  y: ");
  Serial.print(ay);
  Serial.print(" g\t  z: ");
  Serial.print(az);
  Serial.println(" g");
  delay(300);

}
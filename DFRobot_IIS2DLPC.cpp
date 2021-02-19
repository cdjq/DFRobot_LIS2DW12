/*!
 * @file DFRobot_IIS2DLPC.cpp
 * @brief The realization of the class DFRobot_IIS2DLPC
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-12-23
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_IIS2DLPC
 */

#include <DFRobot_IIS2DLPC.h>


DFRobot_IIS2DLPC::DFRobot_IIS2DLPC(){
}

int DFRobot_IIS2DLPC::begin(void){
  uint8_t identifier = 0; 
  
  uint8_t regData = 0x02;
  //writeReg(IIS2DLPC_REG_CTRL_REG2,&regData,1);
  //delay(1000);
  uint8_t reg;
  if(_interface == 1){
    reg  = REG_CARD_ID | 0x80;
  }
  readReg(reg,&identifier,1);
  
  //Serial.println(reg,HEX);
  if(identifier == 0x44){
    return ERR_OK;
  } else if(identifier == 0 || identifier == 0xff){
    DBG("Communication failure");
    return ERR_DATA_BUS;
  } else {  
    DBG("the ic is not IIS2DLPC");
    return ERR_IC_VERSION;
  }

}

uint8_t DFRobot_IIS2DLPC::getID(){
  uint8_t identifier; 
  uint8_t reg;
  if(_interface == 1){
    reg  = REG_CARD_ID | 0x80;
  }
  readReg(reg,&identifier,1);
  return identifier;
}
void DFRobot_IIS2DLPC::softReset()
{
  uint8_t reg;
  
  uint8_t regester = REG_CTRL_REG2;
  if(_interface == 1){
    regester  = REG_CTRL_REG2 | 0x80;
  }
  readReg(regester,&reg, 1);
  
  
  reg =  reg | (1<<6);
  
  DBG(reg);
  writeReg(REG_CTRL_REG2,&reg,1);

}
void DFRobot_IIS2DLPC::continRefresh(bool enable){

  uint8_t reg;
  uint8_t regester = REG_CTRL_REG2;
  if(_interface == 1){
    regester  = REG_CTRL_REG2 | 0x80;
  }
  readReg(regester,&reg, 1);
  if(enable == true){
    reg = reg | (1<<3);
  } else {
    reg = reg &(~(1<<3));
  }
  DBG(reg);
  writeReg(REG_CTRL_REG2,&reg,1);

}
void DFRobot_IIS2DLPC::setFilterPath(eFds_t fds){


  uint8_t ret;
  uint8_t regester = REG_CTRL_REG6;
  if(_interface == 1){
    regester  = REG_CTRL_REG6 | 0x80;
  }
  readReg(regester,&ret, 1);
  uint8_t enable = (fds & 0x10U )?1 : 0;
  ret = ret &(~(3<<2));
  ret = ret | enable << 3;
  DBG(ret);
  writeReg(REG_CTRL_REG6,&ret, 1);
  
  uint8_t regester1 = REG_CTRL_REG7;
  if(_interface == 1){
    regester1  = REG_CTRL_REG7 | 0x80;
  }
  readReg(regester1,&ret,1);

  enable = (fds & 0x01U )?1 : 0;
  ret = ret &(~(1<<4));
  ret = ret | enable << 4;
  DBG(ret);
  writeReg(REG_CTRL_REG7,&ret, 1);
  return ;
}

void DFRobot_IIS2DLPC::setFilterBandwidth(eBWfilter_t bw){

  uint8_t ret;
  uint8_t regester1 = REG_CTRL_REG6;
  if(_interface == 1){
    regester1  = REG_CTRL_REG6 | 0x80;
  }
  readReg(regester1,&ret, 1);
  ret = ret & (~(3 << 6));
  ret = ret | (bw << 6);
  DBG(ret);
  writeReg(REG_CTRL_REG6,&ret, 1);
  return;
}

void DFRobot_IIS2DLPC::setPowerMode(ePowerMode_t mode){

  uint8_t ret;
  uint8_t regester = REG_CTRL_REG1;
  if(_interface == 1){
    regester  = REG_CTRL_REG1 | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret &(~0x0f);
  ret = ret | (mode & 0xF); 
  writeReg(REG_CTRL_REG1,&ret, 1);
  DBG(ret);
  
  uint8_t regester1 = REG_CTRL_REG6;
  if(_interface == 1){
    regester1  = REG_CTRL_REG6 | 0x80;
  }
  readReg(regester1,&ret,1);

  uint8_t enable = mode >> 4;
  ret = ret &(~(1<<2));
  ret = ret | enable << 2;
   DBG(ret);
  writeReg(REG_CTRL_REG6,&ret, 1);
  return ;

}
void DFRobot_IIS2DLPC::setDataRate(eOdr_t odr){

  uint8_t ret;
  
  uint8_t regester = REG_CTRL_REG1;
  if(_interface == 1){
    regester  = REG_CTRL_REG1 | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret &(~(0xf<<4));
  ret = ret | odr<<4; 
  DBG(ret);
  writeReg(REG_CTRL_REG1,&ret, 1);

  uint8_t regester1 = REG_CTRL_REG3;
  if(_interface == 1){
    regester1  = REG_CTRL_REG3 | 0x80;
  }
  readReg(regester1,&ret,1);

  uint8_t enable = (odr&0x30) >> 4;
  ret = ret & (~3);
  ret = ret | enable;
  DBG(ret);
  writeReg(REG_CTRL_REG3,&ret, 1);
  return ;


}
void DFRobot_IIS2DLPC::setRange(eRange_t range){
  uint8_t reg = 0;
  
  uint8_t regester = REG_CTRL_REG6;
  if(_interface == 1){
    regester  = REG_CTRL_REG6 | 0x80;
  }
  readReg(regester,&reg,1);
  //_range = range;
  switch(range){
    case e2_g:{
     _range = 0.061f;
     _range1 = 2;
     reg = reg &(~(3<<4));
     reg = reg | 0;
     break;
    }
    case e4_g:{
     _range = 0.122f;
     _range1 = 4;
     reg = reg &(~(3<<4));
     reg = reg | (1<<4);
     break;
    }
    case e8_g:{
     _range = 0.244f;
     _range1 = 8;
     reg = reg &(~(3<<4));
     reg = reg | (2<<4);
     break;
    }
    case e16_g:{
     _range = 0.488f;
     _range1 = 16;
     reg = reg &(~(3<<4));
     reg = reg | (3<<4);
     break;
    }
  }
  DBG(reg);
  writeReg(REG_CTRL_REG6,&reg,1);
  
}

bool DFRobot_IIS2DLPC::getDataReadyFlag(){
  uint8_t ret;
  
  uint8_t regester = REG_STATUS_REG;
  if(_interface == 1){
    regester  = REG_STATUS_REG | 0x80;
  }
  readReg(regester,&ret, 1);
  //Serial.println(ret);
  //DBG(ret);
  if(ret & 0x01){
    return true;
  } else {
    return false;
  }
}

void DFRobot_IIS2DLPC::setFrDur(uint8_t dur){
  uint8_t reg1 = 0;
  uint8_t reg2 = 0;
  
  uint8_t regester = REG_WAKE_UP_DUR;
  uint8_t regester1 = REG_FREE_FALL;
  if(_interface == 1){
    regester  = REG_WAKE_UP_DUR | 0x80;
    regester1 = REG_FREE_FALL   | 0x80;
  }
  readReg(regester,&reg1,1);
  readReg(regester1,&reg2,1);
  reg1 = reg1 & (~0x80);
  
  reg2 = reg2 & (~0xf8);
  reg2 = reg2 | (dur<<3);
  DBG(reg1);
  writeReg(REG_WAKE_UP_DUR,&reg1,1);
  //delay()
  DBG(reg2);
  writeReg(REG_FREE_FALL,&reg2,1);
  setFfThreshold(eFfTsh10LSbFS2g);
}

void DFRobot_IIS2DLPC::setFfThreshold(eFfThs_t th){

  uint8_t ret;
  
  uint8_t regester = REG_FREE_FALL;
  if(_interface == 1){
    regester  = REG_FREE_FALL | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~7);
  ret = ret | (th & 0x7);
  DBG(ret);
  writeReg(REG_FREE_FALL,&ret, 1);
  return;
}

void DFRobot_IIS2DLPC::setPinInt1Route(eInt1Event_t event){

  uint8_t reg1 = 0;
  uint8_t reg2 = 0;
  uint8_t reg3 = 0;
  
  uint8_t regester1 = REG_CTRL_REG4;
  uint8_t regester2 = REG_CTRL_REG5;
  uint8_t regester3 = REG_CTRL_REG7;
  if(_interface == 1){
    regester1  = REG_CTRL_REG4 | 0x80;
    regester2  = REG_CTRL_REG5 | 0x80;
    regester3  = REG_CTRL_REG7 | 0x80;
  }
  readReg(regester1,&reg1,1);
  readReg(regester2,&reg2,1);
  readReg(regester3,&reg3,1);
  
  reg3 = reg3 & (~0x20);
  if(((reg2&0x80) | (reg2&0x40) | (reg1&0x08)| (reg1&0x10)| (reg1&0x20)| (reg1&0x40)| (reg1&0x80)) != 0){
   reg3 = reg3 | 0x20;
  }
  reg3 = reg3 | 0x20;
  //reg1 = reg1 & (~0x10);
  
  reg1 = reg1 | event;
  DBG(reg1);
  DBG(reg3);
  writeReg(REG_CTRL_REG4,&reg1,1);
  writeReg(REG_CTRL_REG7,&reg3,1);


}
void DFRobot_IIS2DLPC::setWakeupDur(uint8_t dur){

  uint8_t ret;
  
  uint8_t regester = REG_WAKE_UP_DUR;
  if(_interface == 1){
    regester  = REG_WAKE_UP_DUR | 0x80;
  }
  
  readReg(regester,&ret, 1);
  ret = ret & (~ 0x60);
  ret = ret | ((dur <<5) & 0x60);
  
    DBG(ret);
  writeReg(REG_WAKE_UP_DUR,&ret, 1);
  return;
}

void DFRobot_IIS2DLPC::setActSleepDur(uint8_t dur)
{
  uint8_t ret;
  
  uint8_t regester = REG_WAKE_UP_DUR;
  if(_interface == 1){
    regester  = REG_WAKE_UP_DUR | 0x80;
  }
  
  readReg(regester,&ret, 1);
  dur = dur & 0X0F;
  ret = ret & (~0X0F);
  ret = ret | dur;
  
  DBG(ret);
  writeReg(REG_WAKE_UP_DUR,&ret, 1);
  return;
}

void DFRobot_IIS2DLPC::setActMode(eSleepOn_t mode)
{
  uint8_t reg1;
  uint8_t reg2;
  
  uint8_t regester1 = REG_WAKE_UP_THS;
  uint8_t regester2 = REG_WAKE_UP_DUR;
  if(_interface == 1){
    regester1  = REG_WAKE_UP_THS | 0x80;
    regester2  = REG_WAKE_UP_DUR | 0x80;
  }
  readReg(regester1,&reg1, 1);
  readReg(regester2,&reg2, 1);
  reg1 = reg1 & (~0x01);
  reg2 = reg2 & (~0x02);
  reg1 = reg1 | (mode & 0x01);
  reg2 = reg2 | (mode & 0x02);
  DBG(reg1);
  DBG(reg1);
  writeReg(REG_WAKE_UP_THS,&reg1, 1);
  writeReg(REG_WAKE_UP_DUR,&reg2, 1);
  return;
}


void DFRobot_IIS2DLPC::setWakeupThreshold(float th){
  uint8_t ret;
  uint8_t th1 = (th/_range1) * 64;
  DBG(th1);
  uint8_t regester = REG_WAKE_UP_THS;
  if(_interface == 1){
    regester  = REG_WAKE_UP_THS | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~ 0x3f);
  ret = ret | (th1 & 0x3f);
    DBG(ret);
  writeReg(REG_WAKE_UP_THS,&ret, 1);
  return;
}
DFRobot_IIS2DLPC::sAllSources_t DFRobot_IIS2DLPC::getAllSources()
{
  uint8_t ret[5];
  sAllSources_t source;
  uint8_t regester = REG_STATUS_DUP;
  if(_interface == 1){
    regester  = REG_STATUS_DUP | 0x80;
  }
  readReg(regester,(uint8_t*)&source, 5);
  
  
  //&source = (sAllSources_t *)ret;
  return source;
}
void DFRobot_IIS2DLPC::latchInterrupt(bool enable){

  uint8_t ret;
  uint8_t regester = REG_CTRL_REG3;
  if(_interface == 1){
    regester  = REG_CTRL_REG3 | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~ 0x10);
  ret = ret | (enable << 4);
  writeReg(REG_CTRL_REG3,&ret, 1);
  return;
}
void DFRobot_IIS2DLPC::enableTapDetectionOnZ(bool enable)
{
  uint8_t ret;
  uint8_t regester = REG_TAP_THS_Z;
  if(_interface == 1){
    regester  = REG_TAP_THS_Z | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~(1<<5));
  ret = ret | (enable << 5);
  DBG(ret);
  writeReg(REG_TAP_THS_Z,&ret, 1);
  return;
}
void DFRobot_IIS2DLPC::enableTapDetectionOnY(bool enable){
  uint8_t ret;
  
  uint8_t regester = REG_TAP_THS_Z;
  if(_interface == 1){
    regester  = REG_TAP_THS_Z | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~(1<<6));
  ret = ret | (enable << 6);
  DBG(ret);
  writeReg(REG_TAP_THS_Z,&ret, 1);
  return;

}
void DFRobot_IIS2DLPC::enableTapDetectionOnX(bool enable){

  uint8_t ret;
  uint8_t regester = REG_TAP_THS_Z;
  if(_interface == 1){
    regester  = REG_TAP_THS_Z | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~(1<<7));
  ret = ret | (enable << 7);
  DBG(ret);
  writeReg(REG_TAP_THS_Z,&ret, 1);
  return;

}

void DFRobot_IIS2DLPC::setTapThresholdOnX(float th)
{
  uint8_t ret;
  uint8_t th1 = (th/_range1) * 32;
  
  
  uint8_t regester = REG_TAP_THS_X;
  if(_interface == 1){
    regester  = REG_TAP_THS_X | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~0x1f);
  ret = ret | (th1 & 0x1f);
  DBG(ret);
  writeReg(REG_TAP_THS_X,&ret, 1);
  return;
}
void DFRobot_IIS2DLPC::setTapThresholdOnY(float th)
{
  uint8_t ret;
  uint8_t th1 = (th/_range1) * 32;
  uint8_t regester = REG_TAP_THS_Y;
  if(_interface == 1){
    regester  = REG_TAP_THS_Y | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~0x1f);
  ret = ret | (th1 & 0x1f);
  DBG(ret);
  writeReg(REG_TAP_THS_Y,&ret, 1);
  return;
}
void DFRobot_IIS2DLPC::setTapThresholdOnZ(float th)
{
  uint8_t ret;
  uint8_t th1 = (th/_range1) * 32;
  uint8_t regester = REG_TAP_THS_Z;
  if(_interface == 1){
    regester  = REG_TAP_THS_Z | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~0x1f);
  ret = ret | (th1 & 0x1f);
  DBG(ret);
  writeReg(REG_TAP_THS_Z,&ret, 1);
  return;
}

void DFRobot_IIS2DLPC::setTapDur(uint8_t dur)
{
  uint8_t ret;
  uint8_t regester = REG_INT_DUR;
  if(_interface == 1){
    regester  = REG_INT_DUR | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~0xf0);
  ret = ret | (dur << 4);
  DBG(ret);
  writeReg(REG_INT_DUR,&ret, 1);
 
  setTapQuiet(2);
  setTapShock(2);
  return;
}
void DFRobot_IIS2DLPC::setTapQuiet(uint8_t quiet)
{
  uint8_t ret;
  
  uint8_t regester = REG_INT_DUR;
  if(_interface == 1){
    regester  = REG_INT_DUR | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~0xC);
  quiet = quiet & 0x3;
  ret = ret | (quiet << 2 );
  DBG(ret);
  writeReg(REG_INT_DUR,&ret, 1);
  return;
}
void DFRobot_IIS2DLPC::setTapShock(uint8_t shock)
{
  uint8_t ret;
  
  uint8_t regester = REG_INT_DUR;
  if(_interface == 1){
    regester  = REG_INT_DUR | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~0x3);
  shock = shock & 0x3;
  ret = ret | (shock);
  DBG(ret);
  writeReg(REG_INT_DUR,&ret, 1);
  return;
}

void DFRobot_IIS2DLPC::setTapMode(sTapMode_t mode)
{

  uint8_t ret;
  
  uint8_t regester = REG_WAKE_UP_THS;
  if(_interface == 1){
    regester  = REG_WAKE_UP_THS | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~0x80);
  ret = ret | (mode << 7);
  DBG(ret);
  writeReg(REG_WAKE_UP_THS,&ret, 1);
  return;

}
void DFRobot_IIS2DLPC::set6dThreshold(s6dTH_t degree)
{

  uint8_t ret;
  
  uint8_t regester = REG_TAP_THS_X;
  if(_interface == 1){
    regester  = REG_TAP_THS_X | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~0x60);
  ret = ret | degree << 5;
  DBG(ret);
  writeReg(REG_TAP_THS_X,&ret, 1);
  set6dFeedData(1);
  return;
}


void DFRobot_IIS2DLPC::setPinInt2Route(eInt2Event_t event)
{


  uint8_t reg1 = 0;
  uint8_t reg2 = 0;
  uint8_t reg3 = 0;
  uint8_t regester1 = REG_CTRL_REG4;
  uint8_t regester2 = REG_CTRL_REG5;
  uint8_t regester3 = REG_CTRL_REG7;
  if(_interface == 1){
    regester1  = REG_CTRL_REG4 | 0x80;
    regester2  = REG_CTRL_REG5 | 0x80;
    regester3  = REG_CTRL_REG7 | 0x80;
  }
  readReg(regester1,&reg1,1);
  readReg(regester2,&reg2,1);
  readReg(regester3,&reg3,1);
  
  reg3 = reg3 & (~0x20);
  if(((reg2&0x80) | (reg2&0x40) | (reg1&0x08)| (reg1&0x10)| (reg1&0x20)| (reg1&0x40)| (reg1&0x80)) != 0){
   reg3 = reg3 | 0x20;
  }
  reg3 = reg3 | 0x20;
  //reg1 = reg1 & (~0x10);
  
  reg2 = reg2 | event;
  DBG(reg1);
  DBG(reg3);
  writeReg(REG_CTRL_REG5,&reg2,1);
  writeReg(REG_CTRL_REG7,&reg3,1);

}
/*LPF2 on 6D function selection. */
void DFRobot_IIS2DLPC::set6dFeedData(uint8_t data)
{
  uint8_t ret;
  uint8_t regester = REG_CTRL_REG7;
  if(_interface == 1){
    regester  = REG_CTRL_REG7 | 0x80;
  }
  readReg(regester,&ret, 1);
  ret = ret & (~1);
  ret = ret | data;
  DBG(ret);
  writeReg(REG_CTRL_REG7,&ret, 1);
  return;

}

float DFRobot_IIS2DLPC::readAccX(){
  //uint8_t reg = 0;
//  uint8_t ACCX = 0;
    uint8_t sensorData[2];
   
     uint8_t regester = REG_OUT_X_L;
     if(_interface == 1){
       regester  = REG_OUT_X_L | 0x80;
     }
     readReg(regester,sensorData,2);
     int16_t a = ((int16_t)sensorData[1])*256+(int16_t)sensorData[0];
     return a*_range;
  //} else{
    // return 0;
  //}

}
float DFRobot_IIS2DLPC::readAccY(){

  uint8_t sensorData[2];
  uint8_t regester = REG_OUT_Y_L;
  if(_interface == 1){
    regester  = REG_OUT_Y_L | 0x80;
  }
  readReg(regester,sensorData,2);
  int16_t a = ((int16_t)sensorData[1])*256+(int16_t)sensorData[0];
  return a*_range;
  
}

float DFRobot_IIS2DLPC::readAccZ(){
 // uint8_t reg = 0;
  //uint8_t ACCZ = 0;
  uint8_t sensorData[2];
  uint8_t regester = REG_OUT_Z_L;
  if(_interface == 1){
    regester  = REG_OUT_Z_L | 0x80;
  }
  readReg(regester,sensorData,2);
  int16_t a = ((int16_t)sensorData[1])*256+(int16_t)sensorData[0];
  // DBG(a);
  //a = (a * 1000 * (uint8_t)_range)/(256*128);
  DBG(_range);
  return a*_range;
 // } else{

  //}
}
bool DFRobot_IIS2DLPC::actDetect()
{

  uint8_t reg;
  uint8_t regester = REG_WAKE_UP_SRC;
  if(_interface == 1){
    regester  = REG_WAKE_UP_SRC | 0x80;
  }
  readReg(regester,&reg,1);
  if((reg & 0x08) > 0){
     return true;
  } else {
     return false;
  }
}

bool DFRobot_IIS2DLPC::freeFallDetect()
{
  uint8_t reg;
  uint8_t regester = REG_WAKE_UP_SRC;
  if(_interface == 1){
    regester  = REG_WAKE_UP_SRC | 0x80;
  }
  readReg(regester,&reg,1);
  if((reg & 0x20) > 0){
     return true;
  } else {
     return false;
  }
}

bool DFRobot_IIS2DLPC::ia6dDetect()
{
  uint8_t reg;
  uint8_t regester = REG_SIXD_SRC;
  if(_interface == 1){
    regester  = REG_SIXD_SRC | 0x80;
  }
  readReg(regester,&reg,1);
  if((reg & 0x40) > 0){
     return true;
  } else {
     return false;
  }
}

DFRobot_IIS2DLPC::eOrient_t DFRobot_IIS2DLPC::getOrient()
{
  uint8_t reg;
  uint8_t regester = REG_SIXD_SRC;
  if(_interface == 1){
    regester  = REG_SIXD_SRC | 0x80;
  }
  readReg(regester,&reg,1);
  if((reg & 0x01) > 0){
     return eXdown;
  } else if((reg & 0x2) > 0){
     return eXup;
  } else if((reg & 0x4) > 0){
     return eYdown;
  } else if((reg & 0x8) > 0){
     return eYup;
  } else if((reg & 0x10) > 0){
     return eZdown;
  } else if((reg & 0x20) > 0){
     return eZup;
  }
}
DFRobot_IIS2DLPC::eTap_t DFRobot_IIS2DLPC::tapDetect()
{
  uint8_t reg;
  uint8_t regester = REG_TAP_SRC;
  if(_interface == 1){
    regester  = REG_TAP_SRC | 0x80;
  }
  readReg(regester,&reg,1);
  if((reg & 0x20) > 0){
     return eSingleClick;
  } else if((reg & 0x10) > 0){
     return eDoubleClick;
  } else {
    return eNoClick;
  }
}
DFRobot_IIS2DLPC::eTapDir_t DFRobot_IIS2DLPC::getTapDirection()
{
  uint8_t reg;
  uint8_t regester = REG_TAP_SRC;
  if(_interface == 1){
    regester  = REG_TAP_SRC | 0x80;
  }
  readReg(regester,&reg,1);
  uint8_t positive = reg & 0x08;

  if(((reg & 0x04) != 0) && (positive > 0)){
     return eDirXup;
  }else if(((reg & 0x4) != 0) && (positive == 0)){
    return eDirXdown;
  }else if(((reg & 0x2) != 0) && (positive > 0)){
    return eDirYup;
  }else if(((reg & 0x2) != 0) && (positive == 0)){
    return eDirYdown;
  }else if(((reg & 0x1) != 0) && (positive > 0)){
    return eDirZup;
  }else if(((reg & 0x1) != 0) && (positive == 0)){
     return eDirZdown;
  }
  return eDirNone;
}
DFRobot_IIS2DLPC::eWakeupDir_t DFRobot_IIS2DLPC::getWakeupDir()
{
  uint8_t reg;
  uint8_t regester = REG_WAKE_UP_SRC;
  if(_interface == 1){
    regester  = REG_WAKE_UP_SRC | 0x80;
  }
  readReg(regester,&reg,1);
  
  if((reg & 0x1) > 0){
     return eDirZ;
  }else if((reg & 0x2) > 0){
     return eDirY;
  }else if((reg & 0x4) > 0){
     return eDirX;
  }else{
     return eDirError;
  }
}
/*
void DFRobot_IIS2DLPC::setHFilterMode(eHighPassFilter_t mode){

  uint8_t reg = 0;

  readReg(IIS2DLPC_REG_CTRL_REG1,&reg,1);
  if(mode == eShutDown){
    reg = reg & (~0x10);
    return;
  } else{
    reg = reg | 0x10;
  }
  reg = reg & (~3);
  reg = reg | (uint8_t)mode;
  DBG(reg);
  writeReg(IIS2DLPC_REG_CTRL_REG1,&reg,1);
}

*/
DFRobot_IIS2DLPC_I2C::DFRobot_IIS2DLPC_I2C(TwoWire * pWire,uint8_t addr)
{
  _deviceAddr = addr;
  _pWire = pWire;
}

int DFRobot_IIS2DLPC_I2C::begin(void)
{
  _pWire->begin();
  
  uint8_t regData = 0x01;
  //writeReg(IIS2DLPC_REG_CTRL_REG2,&regData,1);
  return DFRobot_IIS2DLPC::begin();
}

uint8_t DFRobot_IIS2DLPC_I2C::writeReg(uint8_t reg, const void * pBuf, size_t size)
{
  if(pBuf == NULL){
	  DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);

  for(uint16_t i = 0; i < size; i++){
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
}

uint8_t DFRobot_IIS2DLPC_I2C::readReg(uint8_t reg, uint8_t* pBuf, size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  if( _pWire->endTransmission() != 0){
      return 0;
  }
 //Serial.println("a----------------");
  _pWire->requestFrom(_deviceAddr, (uint8_t) size);
  for(uint16_t i = 0; i < size; i++){
	  
    _pBuf[i] = _pWire->read();
	//Serial.println(_pBuf[i],HEX);
  }
  return size;
}
DFRobot_IIS2DLPC_SPI::DFRobot_IIS2DLPC_SPI(uint8_t cs,SPIClass *pSpi)
{
  _pSpi = pSpi;
  _cs = cs;
}

int DFRobot_IIS2DLPC_SPI::begin(void){

  _pSpi->begin();
  uint8_t regData = 0x2;
  pinMode(_cs,OUTPUT);
  digitalWrite(_cs,1);
  //writeReg(REG_CTRL_REG2,&regData,1);
  _interface = 1;
  return DFRobot_IIS2DLPC::begin();
}
uint8_t DFRobot_IIS2DLPC_SPI::readReg(uint8_t reg,uint8_t * pBuf ,size_t size){
  
  if(pBuf == NULL){
	  DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  size_t count = 0;
  

#if (defined NRF5)
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
#else
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
#endif
  digitalWrite(_cs,0);
  _pSpi->transfer(reg);
  while(size--) {
    *_pBuf = SPI.transfer(0x00);
   //Serial.println(*_pBuf);
    _pBuf++;
    count++;
  }
  _pSpi->endTransaction();
  digitalWrite(_cs,1);
  return count;
}

uint8_t  DFRobot_IIS2DLPC_SPI::writeReg(uint8_t reg,const void *pBuf,size_t size){
  if(pBuf == NULL){
	  DBG("pBuf ERROR!! : null pointer");
  }
  delay(1);
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_cs,0);
  _pSpi->transfer(reg);

  while(size--) {
    _pSpi->transfer(*_pBuf);
    _pBuf ++;
  }
  SPI.endTransaction();
  digitalWrite(_cs,1);

}
#include <DFRobot_H3LIS200DL.h>


volatile intFlag = 0;
//DFRobot_H3LIS200DL_SPI acce;
DFRobot_H3LIS200DL_I2C acce;
void interEvent(){
  intFlag = 1;
}
void setup(void){

  Serial.begin(9600);
  while(acce.begin()){
     Serial.println("init failure")
  }
  Serial.print("chip id : ");
  Serial.print(acce.getID(),HEX);
  //设置量程
  acce.setRange(DFRobot_H3LIS200DL::eOnehundred);
  acce.setAcquireRate(DFRobot_H3LIS200DL::eNormal_50HZ);
  attachInterrupt(0,interEvent, CHANGE);//当int.0电平改变时,触发中断函数blink
  acce.setIntOneTh(20);//0 - 100 / 0 - 200 
  acce.enableInterruptEvent(DFRobot_H3LIS200DL::eINT1,DFRobot_H3LIS200DL::eYhigherThanTh);
  
  delay(1000);
}

void loop(void){
   
   
   if(intFlag == 1){
      DFRobot_H3LIS200DL::eInterruptEvent_t event;
      event = getInterruptEvent(DFRobot_H3LIS200DL::eINT1);
      Serial.print("interrupt event : ");
      Serial.println(event);
   }

	/*
    Serial.print("Acceleration x: "); //print acceleration
    Serial.print(acce.readACCFromX());
    Serial.print(" mg \ty: ");
    Serial.print(acce.readACCFromy());
    Serial.print(" mg \tz: ");
    Serial.print(acce.readACCFromZ());
    Serial.println(" mg");
    delay(300)
    */
}

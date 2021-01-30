# DFRobot_H3LIS200DL
The H3LIS200DL is a low-power high performance 3-axis linear accelerometer <br>
belonging to the “nano” family, with digital I2C/SPI <br>
serial interface standard output. <br>
The device features ultra-low-power operational <br>
modes that allow advanced power saving and <br>
smart sleep-to-wakeup functions.<br>
The H3LIS200DL has dynamically user selectable full scales of ±100g/±200g and is <br>
capable of measuring accelerations with output <br>
data rates from 0.5 Hz to 1 kHz.<br>
The H3LIS200DL is available in a small thin <br>
plastic land grid array package (LGA) and is <br>
guaranteed to operate over an extended <br>
temperature range from -40 °C to +85 °C.<br>


## DFRobot_H3LIS200DL Library for RaspberryPi
---------------------------------------------------------

Provide an RaspberryPi library to get Three-axis acceleration by reading data from H3LIS200DL.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

Provide an RaspberryPi library to get Three-axis acceleration by reading data from H3LIS200DL.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
#include <DFRobot_H3LIS200DL.h>

  def begin(self):
    '''
      @brief Initialize the function
      @return Return 0 indicates a successful initialization, while other values indicates failure and return to error code.
    '''
      

  def getID(self):
    '''
      @brief Get chip id
      @return Returns the eight-digit serial number
    '''


  def setRange(self,range_r):
    '''
      @brief Set the measurement range
      @param range:Range(g)
             eOnehundred =  ±100g
             eTwohundred = ±200g
    '''

  def setAcquireRate(self, rate):
    '''
      @brief Set data measurement rate
      @param range:rate(g)
    '''


  def setIntOneTh(self,threshold):
    '''
      @brief Set the threshold of interrupt source 1 interrupt
      @param threshold:Threshold(g)
    '''



  def setIntTwoTh(self,threshold):
    '''
      @brief Set interrupt source 2 interrupt generation threshold
      @param threshold:Threshold(g)
    '''

  def enableInterruptEvent(self,source,event):
    '''
      @brief Enable interrupt
      @param source:Interrupt pin selection
      @param event:Interrupt event selection
    '''

  def getInt1Event(self,source):
    '''
      @brief Check whether the interrupt event'source' is generated in interrupt 1
      @param source:Interrupt event
                    eXLowThanTh = 0,/<The acceleration in the x direction is less than the threshold>/
                    eXhigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                    eYLowThanTh,/<The acceleration in the y direction is less than the threshold>/
                    eYhigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                    eZLowThanTh,/<The acceleration in the z direction is less than the threshold>/
                    eZhigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
      @return true ：produce
              false：Interrupt event
    '''

  def getInt2Event(self,source):
    '''
      @brief Check whether the interrupt event'source' is generated in interrupt 2
      @param source:Interrupt event
                    eXLowThanTh = 0,/<The acceleration in the x direction is less than the threshold>/
                    eXhigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                    eYLowThanTh,/<The acceleration in the y direction is less than the threshold>/
                    eYhigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                    eZLowThanTh,/<The acceleration in the z direction is less than the threshold>/
                    eZhigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
      @return true ：produce
              false：Interrupt event
    '''

  def enableSleep(self, enable):
    '''
      @brief Enable sleep wake function
      @param enable:true\false
      @return 0
    '''

  def setHFilterMode(self,mode):
    '''
      @brief Set data filtering mode
      @param mode:Four modes
                eCutoffMode1 = 0,
                eCutoffMode2,
                eCutoffMode3,
                eCutoffMode4,
                eShutDown,
    '''

  def readAcceFromXYZ(self):
    '''
      @brief Get the acceleration in the three directions of xyz
      @return Three-axis acceleration 
              acceleration_x;
              acceleration_y;
              acceleration_z;
    '''

```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
树莓派        |      √       |              |             | 




## History

- data 2021-1-26
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

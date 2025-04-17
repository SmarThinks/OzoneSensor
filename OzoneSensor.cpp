/*!
 * @file OzoneSensor.cpp
 * @brief Define the basic structure of the DFRobot OzoneSensor class, the implementation of the basic methods
 * @copyright	Copyright (c) 2025 SMARTHINKS CORP S.A.S.
 * @author [Juan Camilo Chinchilla]
 * @version V0.0.2
 * @date 2025-04-14
 * @url pendiente por repositorio
 */
#include "OzoneSensor.h"

OzoneSensor::OzoneSensor(TwoWire *pWire)
{
  this->_pWire = pWire;
}

OzoneSensor::~OzoneSensor()
{
  this->_pWire = NULL;
}

bool OzoneSensor::begin(uint8_t addr)
{
  this->_addr = addr;
  _pWire->begin();
  _pWire->beginTransmission(_addr);
  if(_pWire->endTransmission() == 0){
    delay(100);
    return true;
  }
  delay(100);
  return false;
}

void OzoneSensor::i2cWrite(uint8_t reg , uint8_t pData)
{
  _pWire->beginTransmission(_addr);
  _pWire->write(reg);
  _pWire->write(pData);
  _pWire->endTransmission();
}

int16_t OzoneSensor::i2cReadOzoneData(uint8_t reg)
{
  uint8_t i = 0;
  uint8_t rxbuf[10]={0};
  _pWire->beginTransmission(_addr);
  _pWire->write(reg);
  _pWire->endTransmission();
  delay(100);
  _pWire->requestFrom(_addr, (uint8_t)2);
    while (_pWire->available())
     rxbuf[i++] = _pWire->read();
  return ((int16_t)rxbuf[0] << 8) + rxbuf[1];
}

void OzoneSensor::setModes(uint8_t mode)
{
  if(mode == MEASURE_MODE_AUTOMATIC){
    i2cWrite(MODE_REGISTER , MEASURE_MODE_AUTOMATIC);
    delay(100);
    _M_Flag = 0;
  }else if(mode == MEASURE_MODE_PASSIVE){
    i2cWrite(MODE_REGISTER , MEASURE_MODE_PASSIVE);
    delay(100);
    _M_Flag = 1;
  }else {
    return;
  }
}

int16_t OzoneSensor::readOzoneData(uint8_t collectNum)
{
  static uint8_t i = 0, j = 0;
  if (collectNum > 0) {
    for(j = collectNum - 1;  j > 0; j--){
      ozoneData[j] = ozoneData[j-1];
    }
    if(_M_Flag == 0){
      i2cWrite(SET_PASSIVE_REGISTER , AUTO_READ_DATA);
      delay(100);
      ozoneData[0] = i2cReadOzoneData(AUTO_DATA_HIGE_REGISTER);
    }else if(_M_Flag == 1){
      i2cWrite(SET_PASSIVE_REGISTER , PASSIVE_READ_DATA);   delay(100);    // read passive data in passive mode, first request once, then read the data
      ozoneData[0] = i2cReadOzoneData(PASS_DATA_HIGE_REGISTER);
    }
    if(i < collectNum) i++;
    return getAverageNum(ozoneData, i);
  }else if(collectNum <= 0 || collectNum > 100){
   return -1;
  }
  return 0;
}

int16_t OzoneSensor::readOzoneDataReal(uint8_t mode)
{
  if(mode == 0){
      i2cWrite(SET_PASSIVE_REGISTER , AUTO_READ_DATA);
      delay(100);
      ozoneData[0] = i2cReadOzoneData(AUTO_DATA_HIGE_REGISTER);
    }else if(mode == 1){
      i2cWrite(SET_PASSIVE_REGISTER , PASSIVE_READ_DATA);   
      delay(100);    // read passive data in passive mode, first request once, then read the data
      ozoneData[0] = i2cReadOzoneData(PASS_DATA_HIGE_REGISTER);
    }
    return ozoneData[0];
}

int OzoneSensor::getAverageNum(int bArray[], int iFilterLen)
{
  unsigned long bTemp = 0;
  for(uint16_t i = 0; i < iFilterLen; i++) {
    bTemp += bArray[i];
  }
  return bTemp / iFilterLen;
}
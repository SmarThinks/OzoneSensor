/*!
 * @file OzoneSensor.h
 * @brief Define the basic structure of the DFRobot OzoneSensor class, the implementation of the basic methods
 * @copyright	Copyright (c) 2025 SMARTHINKS CORP S.A.S.
 * @author [Juan Camilo Chinchilla]
 * @version V0.0.2
 * @date 2025-04-14
 * @url pendiente por repositorio
 */
#ifndef __OzoneSensor_H__
#define __OzoneSensor_H__
#include <Arduino.h>
#include <Wire.h>

#define           OZONE_ADDRESS_0           0x70
#define           OZONE_ADDRESS_1           0x71
#define           OZONE_ADDRESS_2           0x72
#define           OZONE_ADDRESS_3           0x73
#define           MEASURE_MODE_AUTOMATIC    0x00           ///< active  mode
#define           MEASURE_MODE_PASSIVE      0x01           ///< passive mode
#define           AUTO_READ_DATA            0x00           ///< auto read ozone data
#define           PASSIVE_READ_DATA         0x01           ///< passive read ozone data
#define           MODE_REGISTER             0x03           ///< mode register
#define           SET_PASSIVE_REGISTER      0x04           ///< read ozone data register
#define           AUTO_DATA_HIGE_REGISTER   0x09           ///< AUTO data high eight bits
#define           AUTO_DATA_LOW_REGISTER    0x0A           ///< AUTO data Low  eight bits
#define           PASS_DATA_HIGE_REGISTER   0x07           ///< AUTO data high eight bits
#define           PASS_DATA_LOW_REGISTER    0x08           ///< AUTO data Low  eight bits
#define           OCOUNT                    100            ///< Ozone Count Value

class OzoneSensor{
public:
  OzoneSensor(TwoWire *pWire = &Wire);
  ~OzoneSensor();

  /**
   * @fn begin
   * @brief initialization function
   * @param i2c address
   * @n     OZONE_ADDRESS_0  0x70
   * @n     OZONE_ADDRESS_1  0x71
   * @n     OZONE_ADDRESS_2  0x72
   * @n     OZONE_ADDRESS_3  0x73
   * @return bool type
   * @retval true initialization success
   * @retval false initialization failed
   */
  bool begin(uint8_t addr = OZONE_ADDRESS_0);

  /**
   * @fn setModes
   * @brief Set mode Active or passive measurement.
   * @param mode mode is Active or passive.
   * @n       MEASURE_MODE_AUTOMATIC    active  mode
   * @n       MEASURE_MODE_PASSIVE      passive mode
   * @return None
   */
  void setModes(uint8_t mode);

  /**
   * @fn readOzoneData
   * @brief read ozone data.
   * @param collectNum is the number of data collected,(The default value is 20)
   * @n       COLLECT_NUMBER       The collection range is 1-100
   * @return ozone concentration: one part per billion (PPB).
   */
  int16_t readOzoneData(uint8_t collectNum = 20);
  
  /**
   * @fn readOzoneDataReal
   * @brief read ozone data.
   * @param mode is the number of mode (0 is response active and 1 Question/Response))
   * @return ozone concentration real: one part per billion (PPB).
   */
    int16_t readOzoneDataReal(uint8_t mode);

private:
  void i2cWrite(uint8_t reg , uint8_t pData);
  int16_t i2cReadOzoneData(uint8_t reg);
  int ozoneData[OCOUNT] = {0x00};
  int getAverageNum(int bArray[], int iFilterLen);
  uint8_t _addr;       ///< IIC Slave number
  uint8_t _M_Flag = 0; ///< mode flag
  TwoWire *_pWire;
};
#endif
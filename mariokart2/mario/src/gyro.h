#ifndef GYRO_H
#define GYRO_H

#define GYRO_ADDRESS           0xD2 >> 1

#define GYRO_REG_WHO_AM_I      0x0F

#define GYRO_REG_CTRL_REG1     0x20
#define GYRO_REG_CTRL_REG2     0x21
#define GYRO_REG_CTRL_REG3     0x22
#define GYRO_REG_CTRL_REG4     0x23
#define GYRO_REG_CTRL_REG5     0x24
#define GYRO_REG_REFERENCE     0x25
#define GYRO_REG_OUT_TEMP      0x26
#define GYRO_REG_STATUS_REG    0x27

#define GYRO_REG_OUT_X_L       0x28
#define GYRO_REG_OUT_X_H       0x29
#define GYRO_REG_OUT_Y_L       0x2A
#define GYRO_REG_OUT_Y_H       0x2B
#define GYRO_REG_OUT_Z_L       0x2C
#define GYRO_REG_OUT_Z_H       0x2D

#define GYRO_REG_FIFO_CTRL_REG 0x2E
#define GYRO_REG_FIFO_SRC_REG  0x2F

#define GYRO_REG_INT1_CFG      0x30
#define GYRO_REG_INT1_SRC      0x31
#define GYRO_REG_INT1_THS_XH   0x32
#define GYRO_REG_INT1_THS_XL   0x33
#define GYRO_REG_INT1_THS_YH   0x34
#define GYRO_REG_INT1_THS_YL   0x35
#define GYRO_REG_INT1_THS_ZH   0x36
#define GYRO_REG_INT1_THS_ZL   0x37
#define GYRO_REG_INT1_DURATION 0x38

#define GYRO_SCALE_2000DPS 0b10
#define GYRO_SCALE_500DPS  0b01
#define GYRO_SCALE_250DPS  0b00

#endif
#ifndef __MAIN_H
#define __MAIN_H

#define I2C_SPEED 300000

#define SLAVE_ADDRESS  0x0B

#define SAFE_PROCEDURE

#define BUFFERSIZE  4

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

#endif 
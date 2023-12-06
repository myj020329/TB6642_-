#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f4xx_hal.h"

#define KEY_ON	1
#define KEY_OFF	0

typedef enum {
  MOTOR_DIR_CCW = 0,
  MOTOR_DIR_CW,
}MotorDir_Typedef;

typedef enum {
  MOTOR_ENABLE = ENABLE,
  MOTOR_DISABLE = DISABLE,
}MotorSta_Typedef;

void TB6642_setSpeed(uint16_t duty);
void TB6643_setMotorDir(MotorDir_Typedef dir);
void TB6643_setMotorEna(MotorSta_Typedef ena);

void SetMotor1Dir(uint16_t dir);
void TB6642_breakTostop();
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


#endif	/* __MOTOR_H */


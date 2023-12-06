#include "motor.h"
#include "tim.h"

/**
  * 函数功能: 设置电机转速
  * 输入参数: duty:占空比,取值范围是0~1000
  * 返 回 值: 无
  * 说    明: 设置比较值
  */
void TB6642_setSpeed(uint16_t duty)
{
	if( duty > 1000 )
     return;
  uint16_t ccr = duty * (8400 + 1) / 1000;// 占空比转换成比较值
  __HAL_TIM_SET_COMPARE( &htim1, TIM_CHANNEL_1, ccr );  //切换占空比函数
}
/**
  * 函数功能: 设置电机旋转方向
  * 输入参数: dir:电机旋转方向,取值是  MOTOR_DIR_CCW ,MOTOR_DIR_CW
  * 返 回 值: 无
  * 说    明: 控制IN1和IN2来决定电机方向
  *           旋转方向不仅与程序有关，也与电机接线有关，需要具体分析
  *           简单的方法是：如果控制方向与要求相反，调换两根控制线
  */
void TB6643_setMotorDir(MotorDir_Typedef dir)
{
  if( dir == MOTOR_DIR_CCW ) //电机逆时针旋转
  {
    HAL_GPIO_WritePin( GPIOA, IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin( GPIOA, IN2_Pin, GPIO_PIN_RESET);
  }
  if( dir == MOTOR_DIR_CW )  //电机顺时针旋转
  {
    HAL_GPIO_WritePin( GPIOA, IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin( GPIOA, IN2_Pin, GPIO_PIN_SET);
  }
}

/**
  * 函数功能: 设置电机旋转方向
  * 输入参数: ena:脉冲输出状态,取值是  MOTOR_ENABLe ,MOTOR_DISABLE
  * 返 回 值: 无
  * 说    明: 控制定时器输出脉冲
  */
void TB6643_setMotorEna(MotorSta_Typedef ena)
{
  if( ena == MOTOR_ENABLE )
  {
    HAL_TIM_PWM_Start( &htim1, TIM_CHANNEL_1);   //打开占空比输出
  }
  
  if( ena == MOTOR_DISABLE )
  {
    HAL_TIM_PWM_Stop( &htim1, TIM_CHANNEL_1);	//关闭占空比输出
  }
}

/**
  * 函数功能: 刹车制动
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: IN1=IN2=1,就是刹车制动
  */
void TB6642_breakTostop()
{
  HAL_GPIO_WritePin( GPIOA, IN1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin( GPIOA, IN2_Pin, GPIO_PIN_SET);
}

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*等待按键释放 */
		while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

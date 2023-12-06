#include "motor.h"
#include "tim.h"

/**
  * ��������: ���õ��ת��
  * �������: duty:ռ�ձ�,ȡֵ��Χ��0~1000
  * �� �� ֵ: ��
  * ˵    ��: ���ñȽ�ֵ
  */
void TB6642_setSpeed(uint16_t duty)
{
	if( duty > 1000 )
     return;
  uint16_t ccr = duty * (8400 + 1) / 1000;// ռ�ձ�ת���ɱȽ�ֵ
  __HAL_TIM_SET_COMPARE( &htim1, TIM_CHANNEL_1, ccr );  //�л�ռ�ձȺ���
}
/**
  * ��������: ���õ����ת����
  * �������: dir:�����ת����,ȡֵ��  MOTOR_DIR_CCW ,MOTOR_DIR_CW
  * �� �� ֵ: ��
  * ˵    ��: ����IN1��IN2�������������
  *           ��ת���򲻽�������йأ�Ҳ���������йأ���Ҫ�������
  *           �򵥵ķ����ǣ�������Ʒ�����Ҫ���෴����������������
  */
void TB6643_setMotorDir(MotorDir_Typedef dir)
{
  if( dir == MOTOR_DIR_CCW ) //�����ʱ����ת
  {
    HAL_GPIO_WritePin( GPIOA, IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin( GPIOA, IN2_Pin, GPIO_PIN_RESET);
  }
  if( dir == MOTOR_DIR_CW )  //���˳ʱ����ת
  {
    HAL_GPIO_WritePin( GPIOA, IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin( GPIOA, IN2_Pin, GPIO_PIN_SET);
  }
}

/**
  * ��������: ���õ����ת����
  * �������: ena:�������״̬,ȡֵ��  MOTOR_ENABLe ,MOTOR_DISABLE
  * �� �� ֵ: ��
  * ˵    ��: ���ƶ�ʱ���������
  */
void TB6643_setMotorEna(MotorSta_Typedef ena)
{
  if( ena == MOTOR_ENABLE )
  {
    HAL_TIM_PWM_Start( &htim1, TIM_CHANNEL_1);   //��ռ�ձ����
  }
  
  if( ena == MOTOR_DISABLE )
  {
    HAL_TIM_PWM_Stop( &htim1, TIM_CHANNEL_1);	//�ر�ռ�ձ����
  }
}

/**
  * ��������: ɲ���ƶ�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: IN1=IN2=1,����ɲ���ƶ�
  */
void TB6642_breakTostop()
{
  HAL_GPIO_WritePin( GPIOA, IN1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin( GPIOA, IN2_Pin, GPIO_PIN_SET);
}

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*����Ƿ��а������� */
	if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*�ȴ������ͷ� */
		while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

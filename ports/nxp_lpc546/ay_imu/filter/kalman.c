/**
  ******************************************************************************
  * @file    filter.h
  * @author  YANDLD
  * @version V2.5
  * @date    2015.3.26
  * @brief   www.beyondcore.net   http://upcmcu.taobao.com 
  * @note    
  ******************************************************************************
  */

#include <math.h>

#include "kalman.h"



#define M_PI 3.141592653f


///**
// * @brief  һ�ڵ�ͨ�˲���ϵ������
// * @param  time: ����ʱ�� delataT
// * @param  f_cut: ��ֹƵ��
// * @retval ����ֵ
// */
//float lpf_1st_factor_cal(float time, float f_cut)
//{
//    return time / (time + 1 / (2 * M_PI * f_cut));
//}

///**
// * @brief  һ�ڵ�ͨ�˲���
// * @param  old_data: ��һ������
// * @param  new_data: ������
// * @param  factor:   �˲�ϵ��
// * @retval ���
// */
//float inline lpf_1st(float old_data, float new_data, float factor)
//{
//	return old_data * (1 - factor) + new_data * factor; 
//}


//void KalmanSimple1D(KalmanState_t *S, double q, double r)
//{
//    S->Q = q;
//    S->R = r;
//    S->F = 1;
//    S->H = 1;
//}

//void KalmanRun(KalmanState_t *S, double data)
//{
//    float K;

//    
//    //time update - prediction
//    S->X0 = S->F * S->State;
//    S->P0 = S->F * S->Covariance * S->F + S->Q;

//    //measurement update - correction
//    K = S->H * S->P0 / (S->H * S->P0 * S->H + S->R);
//    S->State = S->X0 + K * (data - S->H * S->X0);
//    S->Covariance = (1 - K * S->H) * S->P0;
//}

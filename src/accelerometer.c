#include "stm32f4_discovery_lis302dl.h"

#include "delay.h"

void accelerometer_setup(void) {
    LIS302DL_InitTypeDef LIS302DL_InitStruct;
    LIS302DL_FilterConfigTypeDef LIS302DL_FilterStruct;

    LIS302DL_InitStruct.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
    LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
    LIS302DL_InitStruct.Axes_Enable = LIS302DL_XYZ_ENABLE;
    LIS302DL_InitStruct.Full_Scale = LIS302DL_FULLSCALE_2_3;
    LIS302DL_InitStruct.Self_Test = LIS302DL_SELFTEST_NORMAL;
    LIS302DL_Init(&LIS302DL_InitStruct);

    delay_ms(30);

    LIS302DL_FilterStruct.HighPassFilter_Data_Selection = LIS302DL_FILTEREDDATASELECTION_OUTPUTREGISTER;
    LIS302DL_FilterStruct.HighPassFilter_CutOff_Frequency = LIS302DL_HIGHPASSFILTER_LEVEL_1;
    LIS302DL_FilterStruct.HighPassFilter_Interrupt = LIS302DL_HIGHPASSFILTERINTERRUPT_1_2;
    LIS302DL_FilterConfig(&LIS302DL_FilterStruct);
}

void accelerometer_read(uint8_t* pBuffer) {
    LIS302DL_Read(pBuffer, LIS302DL_OUT_X_ADDR, 6);
}

uint32_t LIS302DL_TIMEOUT_UserCallback(void) {
    /* MEMS Accelerometer Timeout error occured */
    while (1);
}

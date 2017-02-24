/**
 * Brief: STM32F429ZI-DISCOVERY
 **/

#define TAG "Main"

#include <kernel/amos.h>
#include <kernel/utils/log.h>
#include <drivers/display/ili9341.h>

/* -------------------------------------------------------------------- */
int main(void)
{
    DRV_Display_t pDisp;
    DRV_ILI9341_Init(&pDisp);

    pDisp.On();

    while(1)
    {
        LOGD("SysTick: %ld", HAL_SysTick_GetCount());

        HAL_GPIO_SetBit(GPIOG, GPIO_BIT13);
        CORE_Sleep(500);

        HAL_GPIO_ClrBit(GPIOG, GPIO_BIT13);
        CORE_Sleep(500);
    }
}

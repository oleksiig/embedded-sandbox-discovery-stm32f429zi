/**
 * Brief: STM32F429ZI-DISCOVERY
 **/

#define TAG "Main"

#include <kernel/amos.h>
#include <kernel/utils/log.h>
#include <drivers/display/display.h>

/* -------------------------------------------------------------------- */
int main(void)
{
    while(1)
    {
        LOGD("SysTick: %ld", HAL_SysTick_GetCount());

        HAL_GPIO_SetBit(GPIOG, GPIO_BIT13);
        CORE_Sleep(500);

        HAL_GPIO_ClrBit(GPIOG, GPIO_BIT13);
        CORE_Sleep(500);
    }
}

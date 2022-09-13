/**
 * Brief: STM32F429ZI-DISCOVERY
 **/

#include <stdint.h>

#define TAG "Main"

#include "utils/log.h"
#include "utils/intrinsics.h"
#include "hal/hal_mcu.h"
#include "hal/hal_gpio.h"

#include "drivers/display/display.h"

/* -------------------------------------------------------------------- */
int EntryPoint(void)
{
    DRV_DisplayOn();

  //  for(int x = 0; x < DRV_DisplayGetWidth(); x++)
   //     for(int y = 0; y < DRV_DisplayGetHeight(); y++)
   //         DRV_DisplaySetPixel(x, y, Red);

   // DRV_DisplaySetWriteWindow(10, 10, 12, 12);

    //uint32_t pixel = 0x1f;
    //DRV_DisplayWrite(&pixel, 2);

    //LOGD("0x%04lx", pixel);

  /*  for(int x = 0; x < 100; x++)
        for(int y = 0; y < 100; y++)
            DRV_DisplaySetPixel(x, y, Red);
    
    for(int x = 100; x < 200; x++)
        for(int y = 0; y < 100; y++)
            DRV_DisplaySetPixel(x, y, Green);
    
    for(int x = 200; x < 300; x++)
        for(int y = 0; y < 100; y++)
           DRV_DisplaySetPixel(x, y, Blue);
    */
 //   DRV_DisplaySetWriteWindow(0, 0, 300-1,225-1);
 //   DRV_DisplayWrite((void*)&bin2c_splash_raw565, sizeof(bin2c_splash_raw565));

    DRV_DisplayPutString(0, 0, "Hello world!");

    while(1)
    {
     //   LOGD("SysTick: %ld", HAL_SysTick_GetCount());

        HAL_GPIO_SetBit(GPIOG, GPIO_BIT13);
        __delay_cycles(168000000/3);

        HAL_GPIO_ClrBit(GPIOG, GPIO_BIT13);
        __delay_cycles(168000000/3);
        
  /*      for(int x = 0; x < 239; x++)
        {
            HAL_GPIO_SetBit(GPIOG, GPIO_BIT13);
            for(int y = 0; y < 240; y++)
                DRV_DisplaySetPixel(x, y, HAL_SysTick_GetCount()%11);
            HAL_GPIO_ClrBit(GPIOG, GPIO_BIT13);
            for(int y = 0; y < 320; y++)
                DRV_DisplaySetPixel(x, y, HAL_SysTick_GetCount()%11);
            HAL_GPIO_ClrBit(GPIOG, GPIO_BIT13);
        }*/
    }
}

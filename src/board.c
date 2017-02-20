/**
 * Brief: STM32F429ZI-DISCOVERY
 **/

#include <kernel/amos.h>
#include <drivers/console/console_serial.h>
#include <drivers/display/display.h>

/* -------------------------------------------------------------------- */
/* OVERDRIVE OFF!! */
const HAL_ClockSource_t g_pBoardClocks[] =
{
    { "OSC",          8000000,  (CLK_TYPE_XTAL  | CLK_MAIN_OSC)  },
    { "PLL",        168000000,  (CLK_TYPE_PLL0  | CLK_SRC_XTAL)  },
    { "HCLK",       168000000,  (CLK_TYPE_AHB   | CLK_SRC_PLL0)  },
    { "PCLK1",       42000000,  (CLK_TYPE_APB1)                  },
    { "PCLK2",       84000000,  (CLK_TYPE_APB2)                  },

    { NULL, 0, 0 } /* End of list */
};

/* -------------------------------------------------------------------- */
const HAL_GpioPin_t g_pBoardPins[] =
{
    /* Debug UART */
    GPIO_CONFIG(GPIOA, GPIO_BIT10, GPIO_AF1,         GPIO_IN_FLOAT),         // VCP_RX (USART1_RX)
    GPIO_CONFIG(GPIOA, GPIO_BIT9,  GPIO_AF1,         GPIO_OUT_PUSH_PULL),    // VCP_TX (USART1_TX)

    /* LEDs */
    GPIO_CONFIG(GPIOG, GPIO_BIT13,  GPIO_AF_NONE,    GPIO_OUT_PUSH_PULL),    // LD3 (Green)
    GPIO_CONFIG(GPIOG, GPIO_BIT14,  GPIO_AF_NONE,    GPIO_OUT_PUSH_PULL),    // LD4 (Red)

    /* End of list */
    GPIO_CONFIG(NULL, 0, 0, 0)
};

/* -------------------------------------------------------------------- */
BOARD_DESC("STM32F429ZI-DISCOVERY",
            g_pBoardClocks,
            g_pBoardPins,
            NULL);

/* -------------------------------------------------------------------- */
const DRV_SerialConsoleDesc_t g_pSerialConsole =
{
    .pPort = USART1,
    .nBaudrate = 115200
};

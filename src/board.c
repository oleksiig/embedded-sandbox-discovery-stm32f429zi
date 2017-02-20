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
    GPIO_CONFIG(GPIOA, GPIO_BIT10, GPIO_AF1,         GPIO_IN_FLOAT),        // VCP_RX (USART1_RX)
    GPIO_CONFIG(GPIOA, GPIO_BIT9,  GPIO_AF1,         GPIO_OUT_PUSH_PULL),   // VCP_TX (USART1_TX)

    /* LEDs */
    GPIO_CONFIG(GPIOG, GPIO_BIT13,  GPIO_AF_NONE,    GPIO_OUT_PUSH_PULL),   // LD3 (Green)
    GPIO_CONFIG(GPIOG, GPIO_BIT14,  GPIO_AF_NONE,    GPIO_OUT_PUSH_PULL),   // LD4 (Red)

    /* FMC: SDRAM */
    GPIO_CONFIG(GPIOG, GPIO_BIT4,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_BA0
    GPIO_CONFIG(GPIOG, GPIO_BIT5,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_BA1
    GPIO_CONFIG(GPIOF, GPIO_BIT0,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A0
    GPIO_CONFIG(GPIOF, GPIO_BIT1,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A1
    GPIO_CONFIG(GPIOF, GPIO_BIT2,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A2
    GPIO_CONFIG(GPIOF, GPIO_BIT3,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A3
    GPIO_CONFIG(GPIOF, GPIO_BIT4,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A4
    GPIO_CONFIG(GPIOF, GPIO_BIT5,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A5
    GPIO_CONFIG(GPIOF, GPIO_BIT12,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A6
    GPIO_CONFIG(GPIOF, GPIO_BIT13,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A7
    GPIO_CONFIG(GPIOF, GPIO_BIT14,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A8
    GPIO_CONFIG(GPIOF, GPIO_BIT15,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A9
    GPIO_CONFIG(GPIOG, GPIO_BIT0,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A10
    GPIO_CONFIG(GPIOG, GPIO_BIT1,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_A11
    GPIO_CONFIG(GPIOD, GPIO_BIT14,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D0
    GPIO_CONFIG(GPIOD, GPIO_BIT15,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D1
    GPIO_CONFIG(GPIOD, GPIO_BIT0,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D2
    GPIO_CONFIG(GPIOD, GPIO_BIT1,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D3
    GPIO_CONFIG(GPIOE, GPIO_BIT7,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D4
    GPIO_CONFIG(GPIOE, GPIO_BIT8,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D5
    GPIO_CONFIG(GPIOE, GPIO_BIT9,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D6
    GPIO_CONFIG(GPIOE, GPIO_BIT10,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D7
    GPIO_CONFIG(GPIOE, GPIO_BIT11,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D8
    GPIO_CONFIG(GPIOE, GPIO_BIT12,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D9
    GPIO_CONFIG(GPIOE, GPIO_BIT13,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D10
    GPIO_CONFIG(GPIOE, GPIO_BIT14,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D11
    GPIO_CONFIG(GPIOE, GPIO_BIT15,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D12
    GPIO_CONFIG(GPIOD, GPIO_BIT8,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D13
    GPIO_CONFIG(GPIOD, GPIO_BIT9,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D14
    GPIO_CONFIG(GPIOD, GPIO_BIT10,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_D15
    GPIO_CONFIG(GPIOC, GPIO_BIT0,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_SDNWE
    GPIO_CONFIG(GPIOG, GPIO_BIT15,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_SDNCAS
    GPIO_CONFIG(GPIOF, GPIO_BIT11,  GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_SDNRAS
    GPIO_CONFIG(GPIOB, GPIO_BIT6,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_SDNE1
    GPIO_CONFIG(GPIOB, GPIO_BIT5,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_SDCKE1
    GPIO_CONFIG(GPIOG, GPIO_BIT8,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_SDCLK
    GPIO_CONFIG(GPIOE, GPIO_BIT0,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_NBL0
    GPIO_CONFIG(GPIOE, GPIO_BIT1,   GPIO_AF13,      GPIO_OUT_PUSH_PULL),    // FMC_NBL1

    /* End of list */
    GPIO_CONFIG(NULL, 0, 0, 0)
};

/* -------------------------------------------------------------------- */
/* IS42S16400J-7 (64-MBIT)*/
const HAL_EMC_SDRAM_Config_t g_pIS42S16400J =
{
    .nCS        = 1, /* FMC_SDNE1 */
    .nIntBanks  = 4,
    .nColBits   = 8,
    .nRowBits   = 12,
    .nDataBits  = 16,
    .nRows      = 4096,

    /* Timings */
    .tCK        = 7,
    .tRefresh   = 64000000, /*64ms*/
    .tRP        = 2,
    .tRC        = 9,
    .tRCD       = 2,
    .tWR        = 2,
    .tXSR       = 10,
    .tMRD       = 2,
    .tRAS       = 4,
    .tCASd      = 3,
};

const HAL_EmcMem_t g_pBoardMemory[] =
{
    {EMC_MEM_SDRAM, 0xD0000000, 0x800000, &g_pIS42S16400J},
    /* End of list */
    {0, 0, 0, NULL}
};

/* -------------------------------------------------------------------- */
BOARD_DESC("STM32F429ZI-DISCOVERY",
            g_pBoardClocks,
            g_pBoardPins,
            g_pBoardMemory);

/* -------------------------------------------------------------------- */
const DRV_SerialConsoleDesc_t g_pSerialConsole =
{
    .pPort = USART1,
    .nBaudrate = 115200
};

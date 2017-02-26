/**
 * Brief: STM32F429ZI-DISCOVERY
 **/

#include <kernel/amos.h>
#include <drivers/console/console_serial.h>
#include <drivers/display/ili9341.h>

/* -------------------------------------------------------------------- */
/* OVERDRIVE OFF!! */
const HAL_ClockSource_t g_pBoardClocks[] =
{
    { "OSC",          8000000,  (CLK_TYPE_XTAL  | CLK_MAIN_OSC)  },
    { "PLL",        168000000,  (CLK_TYPE_PLL0  | CLK_SRC_XTAL)  },
    { "HCLK",       168000000,  (CLK_TYPE_AHB   | CLK_SRC_PLL0)  },
    { "PCLK1",       42000000,  (CLK_TYPE_APB1)                  },
    { "PCLK2",       84000000,  (CLK_TYPE_APB2)                  },
    { "LTDC",         6000000,  (CLK_TYPE_LCDC)                  }, /* panel pixel clock */
    { NULL, 0, 0 } /* End of list */
};

/* -------------------------------------------------------------------- */
const HAL_GpioPin_t g_pBoardPins[] =
{
    /* Debug UART */
    GPIO_CONFIG(GPIOA, GPIO_BIT9,   GPIO_AF7,       GPIO_OUT_PUSH_PULL),   // VCP_TX (USART1_TX)
    GPIO_CONFIG(GPIOA, GPIO_BIT10,  GPIO_AF7,       GPIO_IN_FLOAT),        // VCP_RX (USART1_RX)

    /* LEDs */
    GPIO_CONFIG(GPIOG, GPIO_BIT13,  GPIO_AF_NONE,   GPIO_OUT_PUSH_PULL),   // LD3 (Green)
    GPIO_CONFIG(GPIOG, GPIO_BIT14,  GPIO_AF_NONE,   GPIO_OUT_PUSH_PULL),   // LD4 (Red)

    /* FMC: SDRAM */
    GPIO_CONFIG(GPIOG, GPIO_BIT4,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_BA0
    GPIO_CONFIG(GPIOG, GPIO_BIT5,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_BA1
    GPIO_CONFIG(GPIOF, GPIO_BIT0,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A0
    GPIO_CONFIG(GPIOF, GPIO_BIT1,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A1
    GPIO_CONFIG(GPIOF, GPIO_BIT2,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A2
    GPIO_CONFIG(GPIOF, GPIO_BIT3,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A3
    GPIO_CONFIG(GPIOF, GPIO_BIT4,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A4
    GPIO_CONFIG(GPIOF, GPIO_BIT5,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A5
    GPIO_CONFIG(GPIOF, GPIO_BIT12,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A6
    GPIO_CONFIG(GPIOF, GPIO_BIT13,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A7
    GPIO_CONFIG(GPIOF, GPIO_BIT14,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A8
    GPIO_CONFIG(GPIOF, GPIO_BIT15,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A9
    GPIO_CONFIG(GPIOG, GPIO_BIT0,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A10
    GPIO_CONFIG(GPIOG, GPIO_BIT1,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_A11
    GPIO_CONFIG(GPIOD, GPIO_BIT14,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D0
    GPIO_CONFIG(GPIOD, GPIO_BIT15,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D1
    GPIO_CONFIG(GPIOD, GPIO_BIT0,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D2
    GPIO_CONFIG(GPIOD, GPIO_BIT1,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D3
    GPIO_CONFIG(GPIOE, GPIO_BIT7,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D4
    GPIO_CONFIG(GPIOE, GPIO_BIT8,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D5
    GPIO_CONFIG(GPIOE, GPIO_BIT9,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D6
    GPIO_CONFIG(GPIOE, GPIO_BIT10,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D7
    GPIO_CONFIG(GPIOE, GPIO_BIT11,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D8
    GPIO_CONFIG(GPIOE, GPIO_BIT12,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D9
    GPIO_CONFIG(GPIOE, GPIO_BIT13,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D10
    GPIO_CONFIG(GPIOE, GPIO_BIT14,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D11
    GPIO_CONFIG(GPIOE, GPIO_BIT15,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D12
    GPIO_CONFIG(GPIOD, GPIO_BIT8,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D13
    GPIO_CONFIG(GPIOD, GPIO_BIT9,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D14
    GPIO_CONFIG(GPIOD, GPIO_BIT10,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_D15
    GPIO_CONFIG(GPIOC, GPIO_BIT0,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_SDNWE
    GPIO_CONFIG(GPIOG, GPIO_BIT15,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_SDNCAS
    GPIO_CONFIG(GPIOF, GPIO_BIT11,  GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_SDNRAS
    GPIO_CONFIG(GPIOB, GPIO_BIT6,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_SDNE1
    GPIO_CONFIG(GPIOB, GPIO_BIT5,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_SDCKE1
    GPIO_CONFIG(GPIOG, GPIO_BIT8,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_SDCLK
    GPIO_CONFIG(GPIOE, GPIO_BIT0,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_NBL0
    GPIO_CONFIG(GPIOE, GPIO_BIT1,   GPIO_AF12,      GPIO_OUT_PUSH_PULL),    // FMC_NBL1

    /* LCD 2.4" SF-TC240T-9370A-T (ILI9341) */
    GPIO_CONFIG(GPIOC, GPIO_BIT10,  GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_R2
    GPIO_CONFIG(GPIOB, GPIO_BIT0,   GPIO_AF9,       GPIO_OUT_PUSH_PULL),    // LCD_R3
    GPIO_CONFIG(GPIOA, GPIO_BIT11,  GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_R4
    GPIO_CONFIG(GPIOA, GPIO_BIT12,  GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_R5
    GPIO_CONFIG(GPIOB, GPIO_BIT1,   GPIO_AF9,       GPIO_OUT_PUSH_PULL),    // LCD_R6
    GPIO_CONFIG(GPIOG, GPIO_BIT6,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_R7
    GPIO_CONFIG(GPIOA, GPIO_BIT6,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_G2
    GPIO_CONFIG(GPIOG, GPIO_BIT10,  GPIO_AF9,       GPIO_OUT_PUSH_PULL),    // LCD_G3
    GPIO_CONFIG(GPIOB, GPIO_BIT10,  GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_G4
    GPIO_CONFIG(GPIOB, GPIO_BIT11,  GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_G5
    GPIO_CONFIG(GPIOC, GPIO_BIT7,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_G6
    GPIO_CONFIG(GPIOD, GPIO_BIT3,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_G7
    GPIO_CONFIG(GPIOD, GPIO_BIT6,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_B2
    GPIO_CONFIG(GPIOG, GPIO_BIT11,  GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_B3
    GPIO_CONFIG(GPIOG, GPIO_BIT12,  GPIO_AF9,       GPIO_OUT_PUSH_PULL),    // LCD_B4
    GPIO_CONFIG(GPIOA, GPIO_BIT3,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_B5
    GPIO_CONFIG(GPIOB, GPIO_BIT8,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_B6
    GPIO_CONFIG(GPIOB, GPIO_BIT9,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_B7
    GPIO_CONFIG(GPIOG, GPIO_BIT7,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_CLK
    GPIO_CONFIG(GPIOC, GPIO_BIT6,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_HSYNC
    GPIO_CONFIG(GPIOA, GPIO_BIT4,   GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_VSYNC
    GPIO_CONFIG(GPIOF, GPIO_BIT10,  GPIO_AF14,      GPIO_OUT_PUSH_PULL),    // LCD_DE/ENABLE

    GPIO_CONFIG(GPIOC, GPIO_BIT2,   GPIO_AF_NONE,   GPIO_OUT_PUSH_PULL),    // CSX
//    GPIO_CONFIG(GPIOD, GPIO_BIT11,  GPIO_AF_NONE,   GPIO_IN_FLOAT),         // TE
    GPIO_CONFIG(GPIOD, GPIO_BIT12,  GPIO_AF_NONE,   GPIO_OUT_PUSH_PULL),    // RDX
    GPIO_CONFIG(GPIOD, GPIO_BIT13,  GPIO_AF_NONE,   GPIO_OUT_PUSH_PULL),    // WRX_DCX

    /* Touchscreen controller STMPE811QTR (addr 0x41) IRQ pin */
    GPIO_CONFIG_IRQ(GPIOA, GPIO_BIT15, GPIO_AF_NONE, GPIO_IN_FLOAT |        // TP_INT1
        GPIO_IRQ_FALLING_EDGE, NULL),

    /* ACP/RF E2P Connector Reset pin */
    GPIO_CONFIG(GPIOA, GPIO_BIT7,   GPIO_AF_NONE,   GPIO_OUT_PUSH_PULL),    // ACP_RST

    /* I2C3: Shared with STMPE811QTR + ACP/RF E2P Connector */
    GPIO_CONFIG(GPIOA, GPIO_BIT8,   GPIO_AF4,       GPIO_OUT_OPEN_DRAIN),    // I2C3_SCL
    GPIO_CONFIG(GPIOC, GPIO_BIT9,   GPIO_AF4,       GPIO_OUT_OPEN_DRAIN),    // I2C3_SDA

    /* SPI5: Shared with ILI9341 + L3GD20 */
    GPIO_CONFIG(GPIOF, GPIO_BIT7,   GPIO_AF5,       GPIO_OUT_PUSH_PULL),    // SPI5_SCK
    GPIO_CONFIG(GPIOF, GPIO_BIT8,   GPIO_AF5,       GPIO_IN_FLOAT),         // SPI5_MISO
    GPIO_CONFIG(GPIOF, GPIO_BIT9,   GPIO_AF5,       GPIO_OUT_PUSH_PULL),    // SPI5_MOSI

    /* L3GD20 */
    GPIO_CONFIG(GPIOC, GPIO_BIT1,   GPIO_AF_NONE,   GPIO_OUT_PUSH_PULL),    // NCS_MEMS_SPI
    GPIO_CONFIG_IRQ(GPIOA, GPIO_BIT1, GPIO_AF_NONE, GPIO_IN_FLOAT |         // MEMS_INT1
        GPIO_IRQ_FALLING_EDGE, NULL),
    GPIO_CONFIG_IRQ(GPIOA, GPIO_BIT2, GPIO_AF_NONE, GPIO_IN_FLOAT |         // MEMS_INT2
        GPIO_IRQ_FALLING_EDGE, NULL),

    /* USB OTG FS */
    GPIO_CONFIG(GPIOB, GPIO_BIT14,   GPIO_AF12,      GPIO_IN_FLOAT),        // OTG_FS_DM
    GPIO_CONFIG(GPIOB, GPIO_BIT15,   GPIO_AF12,      GPIO_IN_FLOAT),        // OTG_FS_DP
    GPIO_CONFIG(GPIOB, GPIO_BIT12,   GPIO_AF12,      GPIO_IN_FLOAT),        // OTG_FS_ID
    GPIO_CONFIG(GPIOB, GPIO_BIT13,   GPIO_AF_NONE,   GPIO_OUT_PUSH_PULL),   // VBUS_FS
    GPIO_CONFIG(GPIOC, GPIO_BIT4,    GPIO_AF_NONE,   GPIO_OUT_PUSH_PULL),   // OTG_FS_PSO
    GPIO_CONFIG(GPIOC, GPIO_BIT5,    GPIO_AF_NONE,   GPIO_IN_FLOAT),        // OTG_FS_OC

    /* USER & WAKE-UP Button */
    GPIO_CONFIG(GPIOA, GPIO_BIT0,    GPIO_AF_NONE,   GPIO_IN_FLOAT),        // B_USER

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

/* ------------------------------------------------------------------ */
BOARD_DESC("STM32F429ZI-DISCOVERY",
            g_pBoardClocks,
            g_pBoardPins,
            g_pBoardMemory);

/* ------------------------------------------------------------------ */
const DRV_SerialConsoleDesc_t g_pSerialConsole =
{
    .pPort          = USART1,
    .nBaudrate      = 115200
};

/* ------------------------------------------------------------------ */
const HAL_DMA_Map_t g_pDMA_MapTable[] =
{
    DMA_MAP(DMA2, DMA2_Stream5, SPI5, e_HAL_DMA_Periph2Mem, 7), /* RX */
    DMA_MAP(DMA2, DMA2_Stream6, SPI5, e_HAL_DMA_Mem2Periph, 7), /* TX */

    /* End of list */
    DMA_MAP(NULL, NULL, NULL, 0, 0)
};

/* ------------------------------------------------------------------ */
const HAL_I2C_PortDesc_t g_pI2CHB_Ports[] =
{
    { I2C3, 100000, HAL_I2C_M_MASTER },

    /* End of list */
    { NULL, 0, 0 }
};

/* ------------------------------------------------------------------ */
const HAL_SPI_PortDesc_t g_SPI_PortsList[] =
{
    {
        .pPort      = SPI5,
        .BaudRate   = { 15000000, 15000000 }, /* min=15MHz, max=15MHz */
        .Flags      = (HAL_SPI_M_MASTER | HAL_SPI_MODE0 | HAL_SPI_8BIT_WORD | HAL_SPI_CS_MODE_SW) 
    },

    /* End of list */
    { NULL, {0, 0}, 0 }
};

/* ------------------------------------------------------------------ */
const HAL_I2C_PortDesc_t g_I2C_PortsList[] =
{
    {
        .pPort      = I2C3,
        .nBaudRate  = 100000,
        .Flags      = HAL_I2C_M_MASTER
    },

    /* End of list */
    { NULL, 0, 0 }
};

/* ------------------------------------------------------------------ */
const ILI9341_Desc_t g_pILI9341 =
{
    .pPort          = SPI5,
    .pCS            = { GPIOC, GPIO_BIT2, HAL_SPI_CS_SW_MODE_BLOCK },
    .pReset         = { NULL, 0 }, /* Reset pin connected to global nRST */
    .pDC            = { GPIOD, GPIO_BIT13 },
    .Orientation    = e_DISP_CW_0,
    .Fmt            = e_DISP_CF_RGB_565
};

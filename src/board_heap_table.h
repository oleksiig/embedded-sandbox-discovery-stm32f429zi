/**
 * Brief: STM32F429ZI-DISCOVERY board heap table
 * (c) alexey.gulchenko@gmail.com
 **/

#ifndef _BOARD_HEAP_TABLE_H_
#define _BOARD_HEAP_TABLE_H_

#include <stdint.h>
#include "utils/heap.h"

/* Memory heap table will be initialized in 'init.c' file */
__attribute__((used)) HeapDesc_t g_pHeapTable[2];

/* STM32F429ZI-DISCOVERY uses external SDRAM memory */
__attribute__((used))
    void UT_MemoryInitHeapTable(void)
{
    /* Mapped regions in linker script file */
    extern uint32_t _heap_base, _heap_end;

    /* Initialize the HEAP */
    UT_MemoryInitHeap(&g_pHeapTable[0], &g_pHeapTable[1], HEAP_SRAM, (uint32_t)&_heap_base, (uint32_t)&_heap_end);
    UT_MemoryInitHeap(&g_pHeapTable[1], 0, HEAP_SDRAM, 0xD0000000 /*FMC bank 2*/, 0xD0800000 /*8Mb*/);
}

#endif /* _BOARD_HEAP_TABLE_H_ */

/**
 * Brief: STM32F429ZI-DISCOVERY board heap table
 * (c) alexey.gulchenko@gmail.com
 **/

#ifndef _BOARD_HEAP_TABLE_H_
#define _BOARD_HEAP_TABLE_H_

/* STM32F429ZI-DISCOVERY uses external SDRAM memory */
HEAPDESC_t g_pHeapTable[2];

/* Board HEAP initialization function */
void CORE_MemoryInitHeapTable(void)
{
    /* Mapped regions */
    extern U32 _heap_base, _heap_end;

    /* Initialize the SDRAM HEAP 8Mb (DEFAULT) */
    CORE_MemoryInitHeap(&g_pHeapTable[0], &g_pHeapTable[1],
        "SDRAM", 0xD0000000 /*FMC bank 2*/, 0xD0800000 /*8Mb*/);

    /* Initialize the SRAM HEAP */
    CORE_MemoryInitHeap(&g_pHeapTable[1], NULL,
        "SRAM",  (U32)&_heap_base, (U32)&_heap_end);
}

#endif /* _BOARD_HEAP_TABLE_H_ */

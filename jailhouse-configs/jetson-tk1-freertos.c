
#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

struct {
  struct jailhouse_cell_desc cell;
  __u64 cpus[1];
  struct jailhouse_memory mem_regions[2];
        struct jailhouse_irqchip irqchips[2];
  } __attribute__((packed)) config = {
  .cell = {
    .signature = JAILHOUSE_CELL_DESC_SIGNATURE,
    .name = "freeRTOS",
    .flags = JAILHOUSE_CELL_PASSIVE_COMMREG,

    .cpu_set_size = sizeof(config.cpus),
    .num_memory_regions = ARRAY_SIZE(config.mem_regions),
  },

  .cpus = {
    0x8,
  },

  .mem_regions = {
    /* UART */ {
      .phys_start = 0x70006000,
      .virt_start = 0x70006000,
      .size = 0x1000,
      .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
        JAILHOUSE_MEM_IO,
    },
    /* RAM */ {
      .phys_start = 0xfa000000,
      .virt_start = 0,
      .size = 0x01000000,
      .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
        JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE,
    },
  },
  .irqchips = {
     /* GIC */ {
       .address = 0x50041000,
       .pin_base = 32,
       .pin_bitmap = {
                0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
       },
    },
    /* GIC */ {
       .address = 0x50041000,
       .pin_base = 160,
       .pin_bitmap = {
                0xffffffff, 0xffffffff
       },
    },
  },

};

// module: tm.ko
// function: sbrg_set_irq_en_mask @ 0x177c0
// size: 160 bytes
//

undefined4
sbrg_set_irq_en_mask(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 < 0x10) {
    iVar1 = tmOnuRegWrite(0,param_1,0,&sbragRegTable,param_4);
    if (iVar1 == 0) {
      return 0;
    }
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14211,"sbrg_set_irq_en_mask"), iVar1 != 0)) {
      printk("[TM][sbrg_set_irq_en_mask]write reg failed!\n");
    }
    return 0xffffffff;
  }
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][sbrg_set_irq_en_mask]input invalid parameter!\n");
  return 1;
}


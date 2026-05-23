// module: tm.ko
// function: sbrg_set_indreg_cmd @ 0x1c68c
// size: 228 bytes
//

undefined4 sbrg_set_indreg_cmd(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_set_indreg_cmd]input:mode = %d, rw = %d, mem_id = %d, ram_addr = %d\n",param_1
           ,param_2,param_3,param_4);
  }
  uVar1 = param_2;
  if (param_2 < 2) {
    uVar1 = param_1;
  }
  if (uVar1 < 2) {
    bVar3 = 3 < param_3;
    if (param_3 < 5) {
      bVar3 = 0xfff < param_4;
    }
    if (!bVar3) {
      iVar2 = tmOnuRegWrite(0x13,param_4 + param_3 * 0x400000 + param_2 * 0x8000000 +
                                 param_1 * -0x80000000,0,&sbragRegTable);
      if (iVar2 == 0) {
        return 0;
      }
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_set_indreg_cmd]reg write failed\n");
      return 0xffffffff;
    }
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][sbrg_set_indreg_cmd]input invalid parameter!\n");
  }
  return 1;
}


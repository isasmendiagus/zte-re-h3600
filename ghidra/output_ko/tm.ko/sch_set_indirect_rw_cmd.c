// module: tm.ko
// function: sch_set_indirect_rw_cmd @ 0x3d744
// size: 244 bytes
//

undefined4 sch_set_indirect_rw_cmd(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  if (g_tm_debug_level < 7) {
    uVar1 = param_2;
    if (param_2 < 2) {
      uVar1 = param_1;
    }
    if (uVar1 < 2) {
      bVar3 = 0xe < param_3;
      if (param_3 < 0x10) {
        bVar3 = 0x1ff < param_4;
      }
      if (!bVar3) {
LAB_0003d794:
        iVar2 = tmOnuRegWrite(0xd,param_4 + param_3 * 0x400000 + param_2 * 0x8000000 +
                                  param_1 * -0x80000000,0,&SchRegTable);
        if (iVar2 == 0) {
          return 0;
        }
        if (6 < g_tm_debug_level) {
          printk("[TM][sch_set_indirect_rw_cmd]reg write failed\n");
          return 0xffffffff;
        }
        return 0xffffffff;
      }
    }
  }
  else {
    printk("[TM][sch_set_indirect_rw_cmd]input: incrEn = %d, indRwEn = %d, RAMID= %d, RAMAddr = %d\n"
           ,param_1,param_2,param_3,param_4);
    uVar1 = param_2;
    if (param_2 < 2) {
      uVar1 = param_1;
    }
    if (uVar1 < 2) {
      bVar3 = 0xe < param_3;
      if (param_3 < 0x10) {
        bVar3 = 0x1ff < param_4;
      }
      if (!bVar3) goto LAB_0003d794;
    }
    if (6 < g_tm_debug_level) {
      printk("[TM][usch_set_indirect_rw_cmd]input invalid parameter!\n");
    }
  }
  return 1;
}


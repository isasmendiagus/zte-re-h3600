// module: tm.ko
// function: smac_set_timestamp_control @ 0x30f10
// size: 196 bytes
//

int smac_set_timestamp_control(uint param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  bool bVar4;
  
  if (g_tm_debug_level < 7) {
    bVar4 = param_2 != 0;
    bVar3 = param_2 == 1;
    if (param_2 < 2) {
      bVar4 = 3 < param_1;
      bVar3 = param_1 == 4;
    }
    if (!bVar4 || bVar3) {
LAB_00030f44:
      uVar2 = 0x10ff01;
      if (param_2 != 1) {
        uVar2 = 0x2000;
      }
      iVar1 = tmOnuRegWrite(10,uVar2,param_1,&smacRegTable);
      if ((iVar1 != 0) && (6 < g_tm_debug_level)) {
        printk("[TM][smac_set_timestamp_control]write reg failed!\n");
        return iVar1;
      }
      return iVar1;
    }
  }
  else {
    printk("[TM][smac_set_timestamp_control]input: smacnum=%d, control_en=%d\n",param_1,param_2);
    bVar4 = param_2 != 0;
    bVar3 = param_2 == 1;
    if (param_2 < 2) {
      bVar4 = 3 < param_1;
      bVar3 = param_1 == 4;
    }
    if (!bVar4 || bVar3) goto LAB_00030f44;
    if (6 < g_tm_debug_level) {
      printk("[TM][smac_set_timestamp_control]input invalid parameter!\n");
    }
  }
  return 1;
}


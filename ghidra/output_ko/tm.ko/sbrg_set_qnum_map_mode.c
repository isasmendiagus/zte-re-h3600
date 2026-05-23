// module: tm.ko
// function: sbrg_set_qnum_map_mode @ 0x22b0c
// size: 272 bytes
//

undefined4 sbrg_set_qnum_map_mode(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  uint local_14;
  
  bVar4 = 2 < param_2;
  bVar3 = param_2 == 3;
  if (param_2 < 4) {
    bVar4 = 6 < param_1;
    bVar3 = param_1 == 7;
  }
  if (!bVar4 || bVar3) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_set_qnum_map_mode]input:port_id = %d,value = %d\n",param_1,param_2);
    }
    iVar2 = tmOnuRegRead(0x4f,&local_14,0,&sbragRegTable);
    if (iVar2 == 0) {
      iVar2 = tmOnuRegWrite(0x4f,local_14 & ~(3 << (param_1 << 1 & 0xff)) |
                                 param_2 << (param_1 << 1 & 0xff),0,&sbragRegTable);
      uVar1 = 0;
      if (iVar2 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][sbrg_set_qnum_map_mode]write reg failed!\n");
        return 0xffffffff;
      }
    }
    else {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_set_qnum_map_mode] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_set_qnum_map_mode]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}


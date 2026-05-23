// module: tm.ko
// function: cla_get_up_mirror_cfg @ 0x12cec
// size: 264 bytes
//

undefined4 cla_get_up_mirror_cfg(uint param_1,uint *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_get_up_mirror_cfg]input: mirror_id = %d\n",param_1);
  }
  if (param_1 < 2) {
    iVar3 = tmOnuRegRead(0x25,&local_14,param_1,&claRegTable);
    if (iVar3 == 0) {
      *param_2 = (local_14 << 2) >> 0x14;
      uVar1 = g_tm_debug_level;
      param_2[1] = (local_14 << 0xe) >> 0x1a;
      param_2[2] = (local_14 << 0x14) >> 0x1d;
      param_2[3] = local_14 & 0x1ff;
      uVar2 = 0;
      if (6 < uVar1) {
        printk(
              "[TM][cla_get_up_mirror_cfg]output: gemport_id = %d, tcont_id = %d, queue_id = %d, flow_id = %d\n"
              );
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][cla_get_up_mirror_cfg]reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][cla_get_up_mirror_cfg]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}


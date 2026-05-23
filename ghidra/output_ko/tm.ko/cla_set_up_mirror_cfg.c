// module: tm.ko
// function: cla_set_up_mirror_cfg @ 0x12be8
// size: 260 bytes
//

undefined4 cla_set_up_mirror_cfg(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_up_mirror_cfg]input: mirror_id = %d, gemport_id = %d, tcont_id = %d, queue_id = %d, flow_id = %d\n"
           ,param_1,*param_2,param_2[1],param_2[2],param_2[3]);
  }
  if ((((param_1 < 2) && (*param_2 < 0x1000)) && (param_2[1] < 0x28)) &&
     ((param_2[2] < 8 && (param_2[3] < 0x200)))) {
    iVar2 = tmOnuRegWrite(0x25,param_2[1] * 0x1000 + *param_2 * 0x40000 + param_2[3] +
                               param_2[2] * 0x200,param_1,&claRegTable);
    uVar1 = 0;
    if (iVar2 != 0) {
      if (g_tm_debug_level == 0) {
        uVar1 = 0xffffffff;
      }
      else {
        printk("[TM][cla_set_up_mirror_cfg]reg write failed\n");
        uVar1 = 0xffffffff;
      }
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][cla_set_up_mirror_cfg]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}


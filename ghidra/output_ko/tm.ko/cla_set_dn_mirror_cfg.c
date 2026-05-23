// module: tm.ko
// function: cla_set_dn_mirror_cfg @ 0x13c6c
// size: 236 bytes
//

undefined4 cla_set_dn_mirror_cfg(uint *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_dn_mirror_cfg]input: da_known = %d, uni_port = %d, queue_id = %d, flow_id = %d\n"
           ,*param_1,param_1[1],param_1[2],param_1[3]);
  }
  if ((((*param_1 < 2) && (param_1[1] < 8)) && (param_1[2] < 8)) && (param_1[3] < 0x200)) {
    iVar2 = tmOnuRegWrite(0x39,param_1[1] * 0x20000 + *param_1 * 0x400000 + param_1[3] +
                               param_1[2] * 0x200,0,&claRegTable);
    uVar1 = 0;
    if (iVar2 != 0) {
      if (g_tm_debug_level == 0) {
        uVar1 = 0xffffffff;
      }
      else {
        printk("[TM][cla_set_dn_mirror_cfg]reg write failed\n");
        uVar1 = 0xffffffff;
      }
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][cla_set_dn_mirror_cfg]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}


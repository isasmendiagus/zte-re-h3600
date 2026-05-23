// module: tm.ko
// function: cla_set_dn_default_bucket_id_cfg @ 0x140bc
// size: 168 bytes
//

undefined4
cla_set_dn_default_bucket_id_cfg
          (uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_dn_default_bucket_id_cfg]input: bucket_id = %d\n",param_1,param_3,
           g_tm_debug_level,param_4);
  }
  if (0x3f < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][cla_set_dn_default_bucket_id_cfg]input invalid parameter!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x3b,param_1,0,&claRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][cla_set_dn_default_bucket_id_cfg]reg write failed\n");
  return 0xffffffff;
}


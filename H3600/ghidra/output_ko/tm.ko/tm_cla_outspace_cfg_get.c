// module: tm.ko
// function: tm_cla_outspace_cfg_get @ 0x4d418
// size: 120 bytes
//

undefined4 tm_cla_outspace_cfg_get(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == 0 || param_1 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x502c,param_4,param_4);
    printk("param outer_hash_num or outer_space_sel is NULL\n");
    return 0xffffffff;
  }
  iVar1 = cla_get_outspace_cfg();
  if (iVar1 != 0) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][tm_cla_outspace_cfg_get]failed\n");
    return 0xffffffff;
  }
  return 0;
}


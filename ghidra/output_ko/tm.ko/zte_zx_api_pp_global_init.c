// module: tm.ko
// function: zte_zx_api_pp_global_init @ 0x61b54
// size: 264 bytes
//

undefined4 zte_zx_api_pp_global_init(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined1 auStack_24 [18];
  byte local_12;
  
  iVar1 = cla_set_mac_req_ctrl_config(*param_1);
  g_mult_unknown_cfg = param_1[1];
  if (iVar1 == 0) {
    iVar1 = 0;
    do {
      iVar3 = cla_get_extra_index_table(iVar1,auStack_24);
      if (iVar3 != 0) {
        if (g_tm_debug_level != 0) {
          printk("[TM][cla_get_acl_extra_index_table] failed\n");
          return 0xffffffff;
        }
        goto LAB_00061b94;
      }
      if (iVar1 == 9 || iVar1 == 0) {
        uVar4 = *(uint *)(param_1 + 0xc);
      }
      else {
        uVar4 = *(uint *)(param_1 + 4);
      }
      iVar3 = iVar1 + 1;
      local_12 = local_12 & 0xf3 | (byte)((uVar4 & 3) << 2);
      iVar1 = cla_set_extra_index_table(iVar1,auStack_24);
      if (iVar1 != 0) {
        printk("ERROR:(%s:%d)","zte_sw_api.c",0x2130);
        printk("cla_set_extra_index_table fail\n");
        return 0xffffffff;
      }
      uVar2 = 0;
      iVar1 = iVar3;
    } while (iVar3 != 0x10);
  }
  else {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_set_mac_req_ctrl_config] failed\n");
    }
LAB_00061b94:
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


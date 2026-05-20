// module: tm.ko
// function: zte_api_pp_global_init @ 0x64040
// size: 196 bytes
//

undefined4 zte_api_pp_global_init(undefined1 *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 auStack_24 [18];
  byte local_12;
  
  g_mult_unknown_cfg = param_1[1];
  uVar4 = *(undefined4 *)(param_1 + 4);
  cla_set_mac_req_ctrl_config(*param_1);
  cla_set_dn_unknown_da_action_cfg(uVar4);
  iVar2 = 0;
  while( true ) {
    iVar1 = cla_get_extra_index_table(iVar2,auStack_24);
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    if (iVar2 - 9U < 2) {
      uVar3 = *(uint *)(param_1 + 0x10);
    }
    else {
      uVar3 = *(uint *)(param_1 + 8);
    }
    iVar1 = iVar2 + 1;
    local_12 = local_12 & 0xf3 | (byte)((uVar3 & 3) << 2);
    iVar2 = cla_set_extra_index_table(iVar2,auStack_24);
    if (iVar2 != 0) break;
    iVar2 = iVar1;
    if (iVar1 == 0x10) {
      return 0;
    }
  }
  printk("ERROR:(%s:%d)","zte_sw_api.c",0x49e);
  printk("cla_set_extra_index_table fail\n");
  return 0xffffffff;
}


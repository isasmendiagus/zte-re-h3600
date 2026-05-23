// module: tm.ko
// function: cla_get_config @ 0x10960
// size: 400 bytes
//

undefined4 cla_get_config(uint *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_14;
  
  local_14 = 0;
  iVar2 = tmOnuRegRead(3,&local_14,0,&claRegTable);
  if (iVar2 == 0) {
    *param_1 = (local_14 << 0xc) >> 0x1f;
    uVar1 = g_tm_debug_level;
    param_1[2] = (local_14 << 0xf) >> 0x1f;
    param_1[4] = (local_14 << 0x11) >> 0x1f;
    param_1[3] = (local_14 << 0x10) >> 0x1f;
    param_1[6] = (local_14 << 0x13) >> 0x1f;
    param_1[5] = (local_14 << 0x12) >> 0x1f;
    param_1[8] = (local_14 << 0x15) >> 0x1f;
    param_1[7] = (local_14 << 0x14) >> 0x1f;
    param_1[10] = (local_14 << 0x1c) >> 0x1f;
    param_1[9] = (local_14 << 0x16) >> 0x1f;
    param_1[1] = (local_14 << 0xe) >> 0x1f;
    param_1[0xb] = (local_14 << 0x1d) >> 0x1f;
    param_1[0xc] = (local_14 << 0x1e) >> 0x1f;
    param_1[0xd] = local_14 & 1;
    if ((((uVar1 < 7) || (printk("[TM][cla_get_config]output: \n"), g_tm_debug_level < 7)) ||
        (printk("age_rd_clear = %d, trap_acl_en = %d, modify_en = %d,up_unicast_ctrl = %d,  \n",
                *param_1,param_1[1],param_1[2],param_1[3]), g_tm_debug_level < 7)) ||
       (printk("dn_unicast_ctrl = %d, dn_multicast_ctrl = %d,dn_broadcast_ctrl = %d,mac_req_ctrl = %d, \n"
               ,param_1[4],param_1[5],param_1[6],param_1[7]), g_tm_debug_level < 7)) {
      return 0;
    }
    printk("v6rd_del_en = %d, dslite_del_en = %d, outport_sel_en = %d, local_ip_mode_dn = %d,local_ip_mode_up = %d \n"
           ,param_1[8],param_1[9],param_1[0xb],param_1[0xc],param_1[0xd]);
    uVar3 = 0;
  }
  else if (g_tm_debug_level == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_config]reg read failed\n");
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


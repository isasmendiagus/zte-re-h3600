// module: tm.ko
// function: cla_get_dn_mtu_length_cfg @ 0x11774
// size: 172 bytes
//

undefined4 cla_get_dn_mtu_length_cfg(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0x10,local_14,0,&claRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 0x3fff;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][cla_get_dn_mtu_length_cfg]output:length = %d\n");
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7704,"cla_get_dn_mtu_length_cfg"), iVar1 != 0)) {
      printk("[TM][cla_get_dn_mtu_length_cfg]reg read failed\n");
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


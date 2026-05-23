// module: tm.ko
// function: sbrg_lookup_vltbl @ 0x1d53c
// size: 524 bytes
//

undefined4 sbrg_lookup_vltbl(uint *param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (param_2 < 0x1000) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_vltbl]input:vlan_id = %d\n",param_2,g_tm_debug_level,param_2);
    }
    iVar3 = sbrg_set_indreg_cmd(0,1,4,param_2);
    if (iVar3 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][sbrg_get_vltbl] reg write failed\n");
      }
      return 0xffffffff;
    }
    iVar3 = sbrg_access_timeout("sbrg_get_vltbl");
    if ((iVar3 == 0) && (iVar3 = tmOnuRegRead(0x4c,local_1c,0,&sbragRegTable), iVar3 == 0)) {
      *param_1 = (local_1c[0] << 0x1b) >> 0x1e;
      uVar1 = g_tm_debug_level;
      param_1[2] = (local_1c[0] << 0x17) >> 0x1e;
      param_1[3] = (local_1c[0] << 0x15) >> 0x1e;
      param_1[4] = (local_1c[0] << 0x13) >> 0x1e;
      param_1[5] = (local_1c[0] << 0x1d) >> 0x1e;
      param_1[1] = (local_1c[0] << 0x19) >> 0x1e;
      param_1[6] = (local_1c[0] << 0x11) >> 0x1e;
      param_1[7] = (local_1c[0] << 0xf) >> 0x1e;
      param_1[8] = local_1c[0] & 1;
      if ((((uVar1 < 7) ||
           (printk("[TM][sbrg_get_vltbl]output:valid       = %d\n"), g_tm_debug_level < 7)) ||
          (printk("[TM][sbrg_get_vltbl]output:wifi1_attri = %d,wifi2_attri = %d\n",param_1[6],
                  param_1[7]), g_tm_debug_level < 7)) ||
         ((printk("[TM][sbrg_get_vltbl]output:pon_attri   = %d,uni4_attri  = %d\n",param_1[5],
                  param_1[4]), g_tm_debug_level < 7 ||
          (printk("[TM][sbrg_get_vltbl]output:uni3_attri  = %d,uni2_attri  = %d\n",param_1[3],
                  param_1[2]), g_tm_debug_level < 7)))) {
        uVar2 = 0;
      }
      else {
        printk("[TM][sbrg_get_vltbl]output:uni1_attri  = %d,uni0_attri  = %d\n",param_1[1],*param_1)
        ;
        uVar2 = 0;
      }
    }
    else {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_get_vltbl] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][sbrg_get_vltbl]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}


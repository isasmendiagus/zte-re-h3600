// module: tm.ko
// function: tm_port_pon_broadcast_floodcontrolmask @ 0x5214c
// size: 176 bytes
//

undefined4 tm_port_pon_broadcast_floodcontrolmask(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_18 [3];
  
  iVar1 = getPort(param_1,local_18);
  if (iVar1 == 0) {
    if (local_18[0] == 0) {
      iVar1 = sbrg_set_pon_brdcst_flood_portmask
                        ((param_2 << 0x1a) >> 0x1f | (param_2 & 0x1f) << 1 | param_2 & 0xc0);
      uVar2 = 0;
      if (iVar1 != 0) {
        printk("tm_port_pon_broadcast_floodcontrolmask fail\n");
        uVar2 = 0xffffffff;
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 1;
    }
    else {
      printk("[TM][sbrg_set_pon_brdcst_flood_portmask]only support pon broadcast flood!\n");
      uVar2 = 1;
    }
  }
  else {
    printk("tm_port_pon_broadcast_floodcontrolmask fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


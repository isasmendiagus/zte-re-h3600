// module: tm.ko
// function: tm_port_unknwn_multicast_floodcontrolmask @ 0x520d0
// size: 124 bytes
//

undefined4 tm_port_unknwn_multicast_floodcontrolmask(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18 [3];
  
  iVar1 = getPort(param_1,local_18);
  if (iVar1 == 0) {
    iVar1 = sbrg_set_unkmul_flood_portmask
                      (local_18[0],
                       (param_2 << 0x1a) >> 0x1f | (param_2 & 0x1f) << 1 | param_2 & 0xc0);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_port_unknwn_multicast_floodcontrolmask fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_port_unknwn_multicast_floodcontrolmask fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


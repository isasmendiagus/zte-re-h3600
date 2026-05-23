// module: tm.ko
// function: zte_api_sw_port_set_port_loopback @ 0x61f94
// size: 132 bytes
//

undefined4 zte_api_sw_port_set_port_loopback(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = zx_mdio_read(*(undefined1 *)((int)&uni_phy + param_1),0);
  iVar2 = zx_mdio_read(*(undefined1 *)((int)&uni_phy + param_1),0x12);
  if (param_3 == 1) {
    uVar1 = uVar1 & 0xefbf | 0x6100;
  }
  else {
    uVar1 = uVar1 & 0xbfff | 0x1200;
  }
  zx_mdio_write(*(undefined1 *)((int)&uni_phy + param_1),0,uVar1);
  zx_mdio_write(*(undefined1 *)((int)&uni_phy + param_1),0x12,
                ~((uint)~(iVar2 << 0x11) >> 0x11) & 0xffff);
  return 0;
}


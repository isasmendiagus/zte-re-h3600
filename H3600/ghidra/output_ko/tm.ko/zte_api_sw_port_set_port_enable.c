// module: tm.ko
// function: zte_api_sw_port_set_port_enable @ 0x647d0
// size: 164 bytes
//

undefined4 zte_api_sw_port_set_port_enable(uint param_1,int param_2)

{
  undefined1 uVar1;
  ushort uVar2;
  undefined1 extraout_r1;
  undefined1 uVar3;
  undefined4 *extraout_r3;
  undefined4 *puVar4;
  
  if (param_1 < 5) {
    uVar2 = zx_mdio_read(*(undefined1 *)((int)&uni_phy + param_1),0);
    if (param_2 != 1) {
      uVar3 = 1;
      uVar2 = uVar2 | 0x800;
      puVar4 = &g_geInitFlag;
    }
    else {
      uVar2 = uVar2 & 0xf7ff;
      puVar4 = extraout_r3;
      uVar3 = extraout_r1;
    }
    uVar1 = *(undefined1 *)((int)&uni_phy + param_1);
    if (param_2 != 1) {
      *(undefined1 *)((int)puVar4 + param_1) = uVar3;
    }
    zx_mdio_write(uVar1,0,uVar2);
    (&g_portEnStatus)[param_1] = (char)param_2;
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][zte_api_sw_port_set_port_enable]input invalid parameter!\n");
  return 1;
}


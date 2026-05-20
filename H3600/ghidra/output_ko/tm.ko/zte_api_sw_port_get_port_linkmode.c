// module: tm.ko
// function: zte_api_sw_port_get_port_linkmode @ 0x645d4
// size: 244 bytes
//

undefined4
zte_api_sw_port_get_port_linkmode
          (uint param_1,undefined1 *param_2,undefined1 *param_3,undefined1 *param_4)

{
  uint uVar1;
  undefined1 uVar2;
  uint uVar3;
  
  if (4 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][zte_api_sw_port_get_port_linkmode]input invalid parameter!\n");
    return 1;
  }
  *param_3 = 0;
  *param_4 = 0;
  *param_2 = 0;
  uVar1 = zx_mdio_read(*(undefined1 *)((int)&uni_phy + param_1),0,param_3,param_4,param_4);
  if ((uVar1 & 0x1000) != 0) {
    *param_2 = 1;
    return 0;
  }
  uVar3 = uVar1 & 0x2040;
  uVar2 = 0;
  if (uVar3 != 0) {
    if (uVar3 != 0x2000) {
      if (uVar3 != 0x40) {
        printk("[%s] output invalid speed mode!\n","zte_api_sw_port_get_port_linkmode");
        return 0xffffffff;
      }
      *param_3 = 2;
      goto LAB_00064658;
    }
    uVar2 = 1;
  }
  *param_3 = uVar2;
LAB_00064658:
  if ((uVar1 & 0x100) == 0) {
    *param_4 = 0;
    return 0;
  }
  *param_4 = 1;
  return 0;
}


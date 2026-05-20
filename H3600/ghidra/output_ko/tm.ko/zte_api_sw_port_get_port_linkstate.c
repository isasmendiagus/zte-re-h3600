// module: tm.ko
// function: zte_api_sw_port_get_port_linkstate @ 0x646cc
// size: 260 bytes
//

undefined4
zte_api_sw_port_get_port_linkstate
          (uint param_1,undefined4 param_2,undefined1 *param_3,undefined1 *param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  if (4 < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][zte_api_sw_port_get_port_linkstate]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  *param_3 = 0;
  *param_4 = 0;
  iVar1 = zx_mdio_read(*(undefined1 *)((int)&uni_phy + param_1),0x1a);
  uVar2 = (uint)(iVar1 << 9) >> 0x10;
  uVar3 = uVar2 & 7;
  *(bool *)param_2 = iVar1 << 0x19 < 0;
  if (uVar3 < 2) {
    *param_3 = 0;
  }
  else if (uVar3 - 2 < 2) {
    *param_3 = 1;
  }
  else if (uVar3 - 4 < 2) {
    *param_3 = 2;
  }
  uVar2 = uVar2 & 5;
  if (uVar3 == 4 || uVar2 == 0) {
    *param_4 = 0;
    return 0;
  }
  if (uVar2 == 1 || uVar3 == 5) {
    *param_4 = 1;
  }
  return 0;
}


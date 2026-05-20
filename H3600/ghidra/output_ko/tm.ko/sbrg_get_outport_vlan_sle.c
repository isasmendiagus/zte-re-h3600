// module: tm.ko
// function: sbrg_get_outport_vlan_sle @ 0x18680
// size: 156 bytes
//

undefined4 sbrg_get_outport_vlan_sle(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0xd,local_14,0,&sbragRegTable);
  if (iVar1 == 0) {
    *param_1 = (char)local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_outport_vlan_sle]output:en = %d\n",local_14[0] & 0xff);
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][sbrg_get_outport_vlan_sle] reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


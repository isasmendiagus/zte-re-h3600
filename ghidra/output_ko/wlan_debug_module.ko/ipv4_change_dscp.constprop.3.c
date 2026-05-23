// module: wlan_debug_module.ko
// function: ipv4_change_dscp.constprop.3 @ 0x154d0
// size: 60 bytes
//

void ipv4_change_dscp_constprop_3(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = (uint)*(byte *)(param_1 + 1) +
          ((*(ushort *)(param_1 + 10) & 0xff) << 8 | (uint)(*(ushort *)(param_1 + 10) >> 8));
  param_2 = param_2 | *(byte *)(param_1 + 1) & 0x1f;
  *(char *)(param_1 + 1) = (char)param_2;
  if (uVar1 + 1 >> 0x10 != 0) {
    uVar1 = uVar1 + 1 & 0xffff;
  }
  uVar1 = uVar1 - param_2;
  uVar1 = uVar1 + (uVar1 >> 0x10);
  *(ushort *)(param_1 + 10) = (ushort)((uVar1 & 0xff) << 8) | (ushort)(uVar1 >> 8) & 0xff;
  return;
}


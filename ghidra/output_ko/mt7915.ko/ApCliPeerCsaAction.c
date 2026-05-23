// module: mt7915.ko
// function: ApCliPeerCsaAction @ 0x69654
// size: 312 bytes
//

void ApCliPeerCsaAction(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 0) {
    return;
  }
  if (param_1 == 0 || (*(int *)(param_2 + 0x3fe4) == 0 || param_3 == 0)) {
    return;
  }
  if (*(char *)(param_1 + 0x795074) != '\x01') {
    return;
  }
  if (*(char *)(param_3 + 0x31) != '\0') {
    if (*(char *)(param_2 + 0x1a) == *(char *)(param_3 + 0x31)) {
      return;
    }
    if (*(char *)(*(int *)(param_2 + 0x3fe4) + 4) != '\x01') {
      iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
      if ((*(uint *)(iVar1 + 0x2c) & 0xc00) != 0) {
        print_vht_op_info(param_3 + 0x118);
        wlan_operate_set_cen_ch_2(param_2,*(undefined1 *)(param_3 + 0x11a));
      }
      if (2 < DebugLevel) {
        printk("[APCLI]  Following root AP to switch channel to ch%u\n",
               *(undefined1 *)(param_3 + 0x31));
      }
      if ((((*(char *)(param_1 + 0x795404) == '\x01') && ((*(ushort *)(param_2 + 0x18) & 0xb1) != 0)
           ) && (iVar2 = RadarChannelCheck(param_1,*(undefined1 *)(param_3 + 0x31)),
                iVar1 = DebugLevel, iVar2 != 0)) &&
         (*(undefined4 *)(param_1 + 0x79540c) = 2, 2 < iVar1)) {
        printk("[APCLI] Following root AP to switch channel\n");
      }
      rtmp_set_channel(param_1,param_2,*(undefined1 *)(param_3 + 0x31));
      return;
    }
    return;
  }
  return;
}


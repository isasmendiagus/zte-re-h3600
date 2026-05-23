// module: mt7915.ko
// function: indicate_ampdu_pkt @ 0xc9e54
// size: 208 bytes
//

void indicate_ampdu_pkt(int param_1,int param_2)

{
  if (((*(uint *)(param_2 + 0x44) & 2) == 0) && (2000 < *(ushort *)(param_2 + 0x40))) {
    DAT_005f3538 = DAT_005f3538 + 1;
    if (0x14 < DAT_005f3538) {
      if (2 < DebugLevel) {
        printk("AMPDU DataSize = %d\n",*(ushort *)(param_2 + 0x40));
      }
      hex_dump("802.11 Header",*(undefined4 *)(param_2 + 0x1c),0x18);
      hex_dump("Payload",*(undefined4 *)(param_2 + 0x3c),0x40);
      DAT_005f3538 = 0;
    }
    wlan_dbg_set_last_error(0,1,0x10a0,"indicate_ampdu_pkt");
    *(int *)(param_1 + 0x9dcdc) = *(int *)(param_1 + 0x9dcdc) + 1;
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
    return;
  }
  ba_reorder();
  return;
}


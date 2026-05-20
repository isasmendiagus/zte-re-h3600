// module: mt7915.ko
// function: dump_ht_cap @ 0x106a80
// size: 300 bytes
//

void dump_ht_cap(int param_1)

{
  byte *pbVar1;
  uint uVar2;
  
  if (param_1 == 0) {
    return;
  }
  pbVar1 = (byte *)wlan_operate_get_ht_cap();
  if (DebugLevel < 1) {
    return;
  }
  printk("Caller: %pS\n");
  if (0 < DebugLevel) {
    printk("\nphy_mode=%d, ch=%d, wdev_type=%d\n",*(undefined2 *)(param_1 + 0x18),
           *(undefined1 *)(param_1 + 0x1a),*(undefined4 *)(param_1 + 0x14));
    if (DebugLevel < 1) {
      return;
    }
    printk("ht_cap: ht_cap->HtCapInfo, \n");
    if (DebugLevel < 1) {
      return;
    }
    uVar2 = (uint)*pbVar1;
    printk("ldpc=%d,ch_width=%d,gf=%d,sgi20=%d,sgi40=%d,tx_stbc=%d,rx_stbc=%d,amsdu_size=%d\n",
           uVar2 & 1,(uVar2 << 0x1e) >> 0x1f,(uVar2 << 0x1b) >> 0x1f,(uVar2 << 0x1a) >> 0x1f,
           ((uint)*pbVar1 << 0x19) >> 0x1f,*pbVar1 >> 7,pbVar1[1] & 3,
           ((uint)pbVar1[1] << 0x1c) >> 0x1f);
    if (DebugLevel < 1) {
      return;
    }
    printk("ht_cap: ht_cap->HtCapParm, \n");
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("mdpu_density=%d, ampdu_factor=%d\n",((uint)pbVar1[2] << 0x1b) >> 0x1d,pbVar1[2] & 3);
  return;
}


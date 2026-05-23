// module: mt7915.ko
// function: WLAN_BeaconLostNumClear @ 0x15a27c
// size: 80 bytes
//

void WLAN_BeaconLostNumClear(undefined4 param_1,uint param_2,int param_3)

{
  if (param_2 < 2) {
    if (param_3 == 0) {
      return;
    }
    (&DAT_005f4544)[param_2] = 0;
    (&DAT_005f4548)[param_2] = 0;
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("BeaconLost WLAN_BeaconLostNumClear error bandid=%d\n");
  return;
}


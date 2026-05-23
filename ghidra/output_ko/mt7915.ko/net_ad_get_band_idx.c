// module: mt7915.ko
// function: net_ad_get_band_idx @ 0x25c2b4
// size: 48 bytes
//

undefined4 net_ad_get_band_idx(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  
  if (param_1 != 0) {
    uVar1 = HcGetBandByWdev();
    *param_2 = uVar1;
    return 0;
  }
  return 0x607;
}


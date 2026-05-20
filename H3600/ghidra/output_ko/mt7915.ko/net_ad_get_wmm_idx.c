// module: mt7915.ko
// function: net_ad_get_wmm_idx @ 0x25c27c
// size: 56 bytes
//

undefined4 net_ad_get_wmm_idx(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  
  if (param_1 != 0) {
    uVar1 = HcGetWmmIdx(0,param_1);
    *param_2 = uVar1;
    return 0;
  }
  return 0x607;
}


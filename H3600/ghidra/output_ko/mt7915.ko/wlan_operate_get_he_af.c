// module: mt7915.ko
// function: wlan_operate_get_he_af @ 0x206288
// size: 28 bytes
//

undefined1 wlan_operate_get_he_af(int param_1)

{
  undefined1 uVar1;
  
  if (param_1 == 0 || *(int *)(param_1 + 0xb14) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined1 *)(*(int *)(param_1 + 0xb14) + 0x68);
  }
  return uVar1;
}


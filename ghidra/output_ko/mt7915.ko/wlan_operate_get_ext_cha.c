// module: mt7915.ko
// function: wlan_operate_get_ext_cha @ 0x107efc
// size: 24 bytes
//

undefined1 wlan_operate_get_ext_cha(int param_1)

{
  undefined1 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0xb14) != 0) {
    uVar1 = *(undefined1 *)(*(int *)(param_1 + 0xb14) + 8);
  }
  return uVar1;
}


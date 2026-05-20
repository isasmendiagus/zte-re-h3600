// module: mt7915.ko
// function: wlan_operate_set_he_bss_color @ 0x2060f4
// size: 28 bytes
//

undefined4 wlan_operate_set_he_bss_color(int param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xb14);
  if (param_1 != 0 && iVar1 != 0) {
    *(undefined1 *)(iVar1 + 0x5c) = param_2;
    *(undefined1 *)(iVar1 + 0x5e) = param_3;
  }
  return 0;
}


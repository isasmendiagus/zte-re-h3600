// module: mt7915.ko
// function: wlan_operate_set_mmps @ 0x107cd8
// size: 36 bytes
//

undefined4 wlan_operate_set_mmps(int param_1,byte param_2)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = *(int *)(param_1 + 0xb14), iVar1 != 0)) {
    *(byte *)(iVar1 + 0x36) = *(byte *)(iVar1 + 0x36) & 0xf3 | (param_2 & 3) << 2;
  }
  return 0;
}


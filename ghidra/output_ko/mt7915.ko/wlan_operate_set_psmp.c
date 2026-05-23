// module: mt7915.ko
// function: wlan_operate_set_psmp @ 0x107d6c
// size: 36 bytes
//

undefined4 wlan_operate_set_psmp(int param_1,byte param_2)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = *(int *)(param_1 + 0xb14), iVar1 != 0)) {
    *(byte *)(iVar1 + 0x37) = *(byte *)(iVar1 + 0x37) & 0xdf | (param_2 & 1) << 5;
  }
  return 0;
}


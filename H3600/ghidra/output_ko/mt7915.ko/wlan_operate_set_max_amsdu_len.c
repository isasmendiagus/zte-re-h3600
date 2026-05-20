// module: mt7915.ko
// function: wlan_operate_set_max_amsdu_len @ 0x107c84
// size: 48 bytes
//

undefined4 wlan_operate_set_max_amsdu_len(int param_1,int param_2)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = *(int *)(param_1 + 0xb14), iVar1 != 0)) {
    *(byte *)(iVar1 + 0x37) = *(byte *)(iVar1 + 0x37) & 0xf7 | (param_2 != 0) << 3;
  }
  return 0;
}


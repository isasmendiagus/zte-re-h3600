// module: mt7915.ko
// function: wlan_operate_set_ht_max_ampdu_len_exp @ 0x107cfc
// size: 36 bytes
//

undefined4 wlan_operate_set_ht_max_ampdu_len_exp(int param_1,byte param_2)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = *(int *)(param_1 + 0xb14), iVar1 != 0)) {
    *(byte *)(iVar1 + 0x38) = *(byte *)(iVar1 + 0x38) & 0xfc | param_2 & 3;
  }
  return 0;
}


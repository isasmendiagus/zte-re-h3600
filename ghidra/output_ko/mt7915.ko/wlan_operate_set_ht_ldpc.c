// module: mt7915.ko
// function: wlan_operate_set_ht_ldpc @ 0x107c5c
// size: 40 bytes
//

undefined4 wlan_operate_set_ht_ldpc(int param_1,byte param_2)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = *(int *)(param_1 + 0xb14), iVar1 != 0)) {
    *(byte *)(iVar1 + 0xb) = param_2;
    *(byte *)(iVar1 + 0x36) = *(byte *)(iVar1 + 0x36) & 0xfe | param_2 & 1;
  }
  return 0;
}


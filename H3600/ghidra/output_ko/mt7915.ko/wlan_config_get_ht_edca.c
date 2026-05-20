// module: mt7915.ko
// function: wlan_config_get_ht_edca @ 0x1067ec
// size: 24 bytes
//

int wlan_config_get_ht_edca(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0xb10);
  if (iVar1 != 0) {
    iVar1 = iVar1 + 0x36;
  }
  return iVar1;
}


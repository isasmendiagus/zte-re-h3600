// module: mt7915.ko
// function: wlan_config_set_ht_mode @ 0x106648
// size: 32 bytes
//

void wlan_config_set_ht_mode(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xb10);
  if (iVar1 != 0) {
    *(char *)(iVar1 + 0x1a) = (char)param_2;
    *(bool *)(iVar1 + 0x1b) = param_2 == 1;
  }
  return;
}


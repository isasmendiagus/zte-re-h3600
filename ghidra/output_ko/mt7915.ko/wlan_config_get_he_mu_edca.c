// module: mt7915.ko
// function: wlan_config_get_he_mu_edca @ 0x206558
// size: 16 bytes
//

int wlan_config_get_he_mu_edca(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xb10);
  if (iVar1 != 0) {
    iVar1 = iVar1 + 0x77;
  }
  return iVar1;
}


// module: mt7915.ko
// function: starec_muru_feature_decision @ 0x104e2c
// size: 124 bytes
//

undefined4 starec_muru_feature_decision(int param_1,undefined4 param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = wlan_config_get_mu_dl_ofdma();
  if (((((iVar1 == 0) && (iVar1 = wlan_config_get_mu_ul_ofdma(param_1), iVar1 == 0)) &&
       (iVar1 = wlan_config_get_mu_dl_mimo(param_1), iVar1 == 0)) &&
      (iVar1 = wlan_config_get_mu_ul_mimo(param_1), iVar1 == 0)) ||
     (1 < *(int *)(param_1 + 0x14) - 1U)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x40000;
  }
  *param_3 = *param_3 | uVar2;
  return 1;
}


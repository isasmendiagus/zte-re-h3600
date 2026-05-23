// module: mt7915.ko
// function: starec_ht_feature_decision @ 0x1388f8
// size: 176 bytes
//

undefined4 starec_ht_feature_decision(int param_1,int param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 8);
  iVar1 = wlan_config_get_amsdu_en();
  iVar2 = hc_get_chip_cap(*(undefined4 *)(iVar5 + 0xa797a0));
  if (((*(char *)(iVar2 + 0x5c) == '\x01' && iVar1 != 0) &&
      ((*(uint *)(param_2 + 0xb4) & 0xc000000) != 0)) && ((*(uint *)(param_2 + 0x2c4) & 0x1e) == 0))
  {
    uVar3 = hc_get_asic_cap(*(undefined4 *)(iVar5 + 0xa797a0));
    uVar4 = 0x8020;
    *(undefined2 *)(param_2 + 0xcc2) = 0xffff;
    if ((uVar3 & 0x1000) == 0) {
      uVar4 = 0x20;
    }
  }
  else {
    uVar4 = 0;
    *(undefined2 *)(param_2 + 0xcc2) = 0;
  }
  if ((*(uint *)(param_2 + 0xb4) & 0x4000000) != 0) {
    uVar4 = uVar4 | 0x200;
  }
  *param_3 = *param_3 | uVar4;
  return 1;
}


// module: mt7915.ko
// function: starec_ap_feature_decision @ 0x16bb4
// size: 80 bytes
//

undefined4 starec_ap_feature_decision(int param_1,int param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(*(int *)(param_1 + 8) + 0xa797a0));
  if (*(char *)(iVar1 + 0x154) == '\x02') {
    uVar2 = 0x800;
  }
  else {
    uVar2 = 0;
  }
  if ((*(uint *)(param_2 + 0x2c4) & 0xe) != 0) {
    uVar2 = uVar2 | 0x1000;
  }
  *param_3 = *param_3 | uVar2;
  return 1;
}


// module: mt7915.ko
// function: net_ad_get_omac_idx @ 0x25c2e4
// size: 68 bytes
//

undefined4 net_ad_get_omac_idx(int param_1,int param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    uVar3 = 0x606;
  }
  else if (param_2 == 0) {
    uVar3 = 0x607;
  }
  else {
    uVar1 = HcGetOmacIdx(iVar2,param_2);
    uVar3 = 0;
    *param_3 = uVar1;
  }
  return uVar3;
}


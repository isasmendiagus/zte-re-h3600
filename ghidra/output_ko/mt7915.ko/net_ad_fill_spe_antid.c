// module: mt7915.ko
// function: net_ad_fill_spe_antid @ 0x25c4a8
// size: 112 bytes
//

undefined4 net_ad_fill_spe_antid(int param_1,int param_2,undefined1 param_3,undefined1 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_34 [4];
  undefined4 local_30;
  undefined1 local_1f;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x606;
  }
  else if (param_2 == 0) {
    uVar2 = 0x607;
  }
  else {
    *(undefined1 *)(param_2 + 0xd8) = param_3;
    *(undefined1 *)(param_2 + 0xd7) = param_4;
    sys_ad_zero_mem(auStack_34,0x1c);
    local_30 = 0x16;
    local_1f = param_3;
    RAParamUpdate(iVar1,param_2,auStack_34);
    uVar2 = 0;
  }
  return uVar2;
}


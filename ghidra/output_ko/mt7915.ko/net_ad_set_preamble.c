// module: mt7915.ko
// function: net_ad_set_preamble @ 0x25ea28
// size: 80 bytes
//

undefined4 net_ad_set_preamble(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  if (param_2 == 0) {
    uVar2 = *(uint *)(iVar1 + 0x795124) & 0xffffffef;
  }
  else {
    uVar2 = *(uint *)(iVar1 + 0x795124) | 0x10;
  }
  *(uint *)(iVar1 + 0x795124) = uVar2;
  return 0;
}


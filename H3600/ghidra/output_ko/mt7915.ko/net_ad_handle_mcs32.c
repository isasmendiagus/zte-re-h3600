// module: mt7915.ko
// function: net_ad_handle_mcs32 @ 0x25ce00
// size: 36 bytes
//

undefined4 net_ad_handle_mcs32(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x606;
  }
  else {
    uVar2 = 0x607;
  }
  return uVar2;
}


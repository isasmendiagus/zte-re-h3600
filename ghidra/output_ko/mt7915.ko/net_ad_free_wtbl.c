// module: mt7915.ko
// function: net_ad_free_wtbl @ 0x25be8c
// size: 96 bytes
//

undefined4 net_ad_free_wtbl(int param_1,undefined4 param_2,int param_3,short *param_4)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  if (param_3 != 0) {
    if ((param_4 != (short *)0x0) && (*param_4 != 0)) {
      *(short *)(param_3 + 0xf8) = *param_4;
    }
    MacTableDeleteEntry(iVar1,*(undefined2 *)(param_3 + 0xe0),param_2);
    return 0;
  }
  return 0x607;
}


// module: mt7915.ko
// function: MTChGrpChannelChk @ 0x1419e4
// size: 92 bytes
//

undefined4 MTChGrpChannelChk(int param_1,uint param_2)

{
  byte *pbVar1;
  
  if (*(char *)(param_1 + 0x4d9) == '\0') {
    return 0;
  }
  if (*(byte *)(param_1 + 0x49e) != param_2) {
    pbVar1 = (byte *)(param_1 + 0x49e);
    do {
      if (pbVar1 == (byte *)(param_1 + (byte)(*(char *)(param_1 + 0x4d9) - 1) + 0x49e)) {
        return 0;
      }
      pbVar1 = pbVar1 + 1;
    } while (*pbVar1 != param_2);
  }
  return 1;
}


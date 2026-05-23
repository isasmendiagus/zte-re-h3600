// module: mt7915.ko
// function: BackgroundScanSkipChannelCheck @ 0x22cf48
// size: 108 bytes
//

undefined4 BackgroundScanSkipChannelCheck(int param_1,uint param_2)

{
  byte *pbVar1;
  
  if (*(char *)(param_1 + 0xa79755) == '\0') {
    return 0;
  }
  if (*(byte *)(param_1 + 0xa79756) != param_2) {
    pbVar1 = (byte *)(param_1 + 0xa79756);
    do {
      if (pbVar1 == (byte *)(param_1 + (byte)(*(char *)(param_1 + 0xa79755) - 1) + 0xa79756)) {
        return 0;
      }
      pbVar1 = pbVar1 + 1;
    } while (*pbVar1 != param_2);
  }
  return 1;
}


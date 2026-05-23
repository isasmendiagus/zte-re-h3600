// module: mt7915.ko
// function: rtstrcasecmp @ 0xee220
// size: 132 bytes
//

undefined4 rtstrcasecmp(byte *param_1,char *param_2)

{
  size_t sVar1;
  size_t sVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  
  sVar1 = strlen((char *)param_1);
  sVar2 = strlen(param_2);
  if (sVar1 != sVar2) {
    return 0;
  }
  uVar4 = (uint)*param_1;
  if (uVar4 != 0) {
    pbVar3 = (byte *)(param_2 + -1);
    do {
      pbVar3 = pbVar3 + 1;
      uVar5 = (uint)*pbVar3;
      if (uVar4 - 0x41 < 0x1a) {
        uVar4 = uVar4 + 0x20 & 0xff;
      }
      if (uVar5 - 0x41 < 0x1a) {
        uVar5 = uVar5 + 0x20 & 0xff;
      }
      if (uVar5 != uVar4) {
        return 0;
      }
      param_1 = param_1 + 1;
      uVar4 = (uint)*param_1;
    } while (uVar4 != 0);
  }
  return 1;
}


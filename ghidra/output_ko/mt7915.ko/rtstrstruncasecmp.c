// module: mt7915.ko
// function: rtstrstruncasecmp @ 0xee2a4
// size: 180 bytes
//

char * rtstrstruncasecmp(char *param_1,char *param_2)

{
  size_t sVar1;
  size_t sVar2;
  size_t sVar3;
  byte *pbVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  
  sVar1 = strlen(param_2);
  if (sVar1 == 0) {
    return param_1;
  }
  sVar2 = strlen(param_1);
  do {
    if ((int)sVar2 < (int)sVar1) {
      return (char *)0x0;
    }
    sVar2 = sVar2 - 1;
    if (0 < (int)sVar1) {
      pbVar5 = (byte *)(param_1 + -1);
      pbVar4 = (byte *)(param_2 + -1);
      sVar3 = 0;
      while( true ) {
        pbVar5 = pbVar5 + 1;
        uVar6 = (uint)*pbVar5;
        pbVar4 = pbVar4 + 1;
        uVar7 = (uint)*pbVar4;
        if (uVar6 - 0x61 < 0x1a) {
          uVar6 = uVar6 - 0x20 & 0xff;
        }
        if (uVar7 - 0x61 < 0x1a) {
          uVar7 = uVar7 - 0x20 & 0xff;
        }
        if (uVar7 != uVar6) break;
        sVar3 = sVar3 + 1;
        if (sVar1 == sVar3) {
          return param_1;
        }
      }
      if (sVar3 == sVar1) {
        return param_1;
      }
    }
    param_1 = param_1 + 1;
  } while( true );
}


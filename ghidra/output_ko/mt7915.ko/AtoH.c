// module: mt7915.ko
// function: AtoH @ 0x13c000
// size: 192 bytes
//

void AtoH(byte *param_1,char *param_2,int param_3)

{
  byte bVar1;
  char *pcVar2;
  char *pcVar3;
  char cVar4;
  char cVar5;
  uint uVar6;
  
  if (param_3 == 0) {
    return;
  }
  pcVar3 = param_2;
  do {
    bVar1 = *param_1;
    uVar6 = (uint)bVar1;
    if ((uVar6 - 0x30 & 0xff) < 10) {
      cVar5 = (char)((uVar6 - 0x30 & 0xf) << 4);
    }
    else if (uVar6 - 0x41 < 6) {
      cVar5 = (bVar1 - 0x37) * '\x10';
    }
    else if (uVar6 - 0x61 < 6) {
      cVar5 = (bVar1 + 0xa9) * '\x10';
    }
    else {
      cVar5 = -0x10;
    }
    *pcVar3 = cVar5;
    bVar1 = param_1[1];
    uVar6 = (uint)bVar1;
    cVar4 = (char)(uVar6 - 0x30);
    if (9 < (uVar6 - 0x30 & 0xff)) {
      if (uVar6 - 0x41 < 6) {
        cVar4 = bVar1 - 0x37;
      }
      else if (uVar6 - 0x61 < 6) {
        cVar4 = bVar1 + 0xa9;
      }
      else {
        cVar4 = -1;
      }
    }
    pcVar2 = pcVar3 + 1;
    *pcVar3 = cVar4 + cVar5;
    pcVar3 = pcVar2;
    param_1 = param_1 + 2;
  } while (pcVar2 != param_2 + param_3);
  return;
}


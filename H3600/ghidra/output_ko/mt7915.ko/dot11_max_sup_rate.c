// module: mt7915.ko
// function: dot11_max_sup_rate @ 0x1289d0
// size: 120 bytes
//

void dot11_max_sup_rate(byte *param_1)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar2 = param_1 + 0xe;
  if (*param_1 == 0) {
    bVar1 = 0;
  }
  else {
    bVar1 = 0;
    pbVar4 = param_1 + 1;
    do {
      pbVar3 = pbVar4 + 1;
      if (bVar1 < (*pbVar4 & 0x7f)) {
        bVar1 = *pbVar4 & 0x7f;
      }
      pbVar4 = pbVar3;
    } while (pbVar3 != param_1 + 1 + *param_1);
  }
  if (pbVar2 == (byte *)0x0 || param_1[0xd] == 0) {
    return;
  }
  pbVar4 = pbVar2;
  do {
    pbVar3 = pbVar4 + 1;
    if (bVar1 < (*pbVar4 & 0x7f)) {
      bVar1 = *pbVar4 & 0x7f;
    }
    pbVar4 = pbVar3;
  } while (pbVar3 != pbVar2 + param_1[0xd]);
  return;
}


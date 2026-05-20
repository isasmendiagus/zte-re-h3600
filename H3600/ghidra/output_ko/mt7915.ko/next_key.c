// module: mt7915.ko
// function: next_key @ 0xb6160
// size: 268 bytes
//

void next_key(byte *param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  int iVar5;
  byte local_38;
  byte local_37 [19];
  
  pbVar4 = &local_38;
  iVar5 = 0;
  local_37[3] = 1;
  local_37[4] = 2;
  local_37[5] = 4;
  local_37[6] = 8;
  local_37[7] = 0x10;
  local_37[8] = 0x20;
  local_37[9] = 0x40;
  local_37[10] = 0x80;
  local_37[0xb] = 0x1b;
  local_37[0xc] = 0x36;
  local_37[0xd] = 0x36;
  local_37[0xe] = 0x36;
  bVar2 = SboxTable[param_1[0xd]];
  bVar1 = local_37[param_2 + 3];
  local_37[0] = SboxTable[param_1[0xe]];
  local_37[1] = SboxTable[param_1[0xf]];
  local_37[2] = SboxTable[param_1[0xc]];
  pbVar3 = param_1;
  while( true ) {
    iVar5 = iVar5 + 1;
    *pbVar3 = *pbVar3 ^ bVar2;
    if (iVar5 == 4) break;
    pbVar4 = pbVar4 + 1;
    bVar2 = *pbVar4;
    pbVar3 = pbVar3 + 1;
  }
  *param_1 = bVar1 ^ *param_1;
  pbVar3 = param_1 + 3;
  do {
    pbVar4 = pbVar3 + 1;
    *pbVar4 = *pbVar4 ^ pbVar3[-3];
    pbVar3 = pbVar4;
  } while (pbVar4 != param_1 + 7);
  pbVar3 = param_1 + 7;
  do {
    pbVar4 = pbVar3 + 1;
    *pbVar4 = *pbVar4 ^ pbVar3[-3];
    pbVar3 = pbVar4;
  } while (pbVar4 != param_1 + 0xb);
  pbVar3 = param_1 + 0xb;
  do {
    pbVar4 = pbVar3 + 1;
    *pbVar4 = *pbVar4 ^ pbVar3[-3];
    pbVar3 = pbVar4;
  } while (pbVar4 != param_1 + 0xf);
  return;
}


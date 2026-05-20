// module: mt7915.ko
// function: RTMPTkipSetMICKey @ 0x1173ec
// size: 100 bytes
//

void RTMPTkipSetMICKey(undefined4 *param_1,byte *param_2)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = 0;
  uVar4 = 0;
  pbVar1 = param_2;
  do {
    uVar4 = uVar4 | (uint)*pbVar1 << (uVar2 & 0xff);
    uVar2 = uVar2 + 8;
    pbVar1 = pbVar1 + 1;
  } while (uVar2 != 0x20);
  uVar3 = 0;
  uVar2 = 0;
  param_1[3] = uVar4;
  pbVar1 = param_2 + 4;
  do {
    uVar2 = uVar2 | (uint)*pbVar1 << (uVar3 & 0xff);
    uVar3 = uVar3 + 8;
    pbVar1 = pbVar1 + 1;
  } while (uVar3 != 0x20);
  param_1[4] = uVar2;
  param_1[5] = uVar4;
  param_1[6] = uVar2;
  *param_1 = 0;
  param_1[7] = 0;
  return;
}


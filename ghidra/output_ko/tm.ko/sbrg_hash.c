// module: tm.ko
// function: sbrg_hash @ 0x1c4b0
// size: 328 bytes
//

uint sbrg_hash(byte *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte bStack_33;
  byte local_32 [34];
  byte abStack_10 [4];
  
  memset(local_32,0,0x22);
  if (param_3 == 0x4c) {
    param_1 = param_1 + 10;
    pbVar3 = local_32;
    do {
      param_1 = param_1 + -1;
      pbVar4 = pbVar3 + 1;
      *pbVar3 = *param_1;
      pbVar3 = pbVar4;
    } while (pbVar4 != local_32 + 10);
    uVar1 = 0;
    pbVar3 = local_32;
    do {
      pbVar4 = pbVar3 + 1;
      uVar2 = (uint)*(ushort *)(crc16_tab + ((uint)*pbVar3 ^ uVar1 >> 8) * 2) ^ uVar1 << 8;
      uVar1 = uVar2 & 0xffff;
      pbVar3 = pbVar4;
    } while (pbVar4 != local_32 + 10);
    uVar2 = uVar2 & 0x3ff;
  }
  else if (param_3 == 0x10c) {
    param_1 = param_1 + 0x22;
    pbVar3 = &bStack_33;
    do {
      param_1 = param_1 + -1;
      pbVar3 = pbVar3 + 1;
      *pbVar3 = *param_1;
    } while (pbVar3 != local_32 + 0x21);
    uVar1 = 0;
    pbVar3 = local_32;
    do {
      pbVar4 = pbVar3 + 1;
      uVar2 = (uint)*(ushort *)(crc16_tab + ((uint)*pbVar3 ^ uVar1 >> 8) * 2) ^ uVar1 << 8;
      uVar1 = uVar2 & 0xffff;
      pbVar3 = pbVar4;
    } while (pbVar4 != abStack_10);
    uVar2 = uVar2 & 0x3ff;
  }
  else {
    if (param_3 != 0x3c) {
      return 0;
    }
    pbVar4 = param_1 + 8;
    pbVar3 = &bStack_33;
    do {
      pbVar4 = pbVar4 + -1;
      pbVar3 = pbVar3 + 1;
      *pbVar3 = *pbVar4;
    } while (pbVar4 != param_1);
    uVar1 = 0;
    pbVar3 = local_32;
    do {
      pbVar4 = pbVar3 + 1;
      uVar2 = (uint)*(ushort *)(crc16_tab + ((uint)*pbVar3 ^ uVar1 >> 8) * 2) ^ uVar1 << 8;
      uVar1 = uVar2 & 0xffff;
      pbVar3 = pbVar4;
    } while (pbVar4 != local_32 + 8);
    uVar2 = uVar2 & 0x3ff;
  }
  return uVar2;
}


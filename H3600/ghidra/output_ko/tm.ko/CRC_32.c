// module: tm.ko
// function: CRC_32 @ 0x16c58
// size: 56 bytes
//

uint CRC_32(int param_1,byte *param_2,int param_3)

{
  byte *pbVar1;
  uint uVar3;
  byte *pbVar2;
  
  if (param_3 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0;
    pbVar2 = param_2;
    do {
      pbVar1 = pbVar2 + 1;
      uVar3 = *(uint *)(param_1 + ((uint)*pbVar2 ^ uVar3 >> 0x18) * 4) ^ uVar3 << 8;
      pbVar2 = pbVar1;
    } while (pbVar1 != param_2 + param_3);
  }
  return uVar3;
}


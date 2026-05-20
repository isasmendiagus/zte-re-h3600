// module: tm.ko
// function: CRC_16 @ 0x16c90
// size: 76 bytes
//

uint CRC_16(int param_1,byte *param_2,int param_3)

{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  if (param_3 != 0) {
    uVar1 = 0;
    pbVar3 = param_2;
    do {
      pbVar2 = pbVar3 + -1;
      uVar1 = *(uint *)(param_1 + ((uVar1 << 8) >> 0x10 ^ (uint)*pbVar3) * 4) & 0xffff ^
              (uVar1 & 0xff) << 8;
      pbVar3 = pbVar2;
    } while (pbVar2 != param_2 + -param_3);
    return uVar1;
  }
  return 0;
}


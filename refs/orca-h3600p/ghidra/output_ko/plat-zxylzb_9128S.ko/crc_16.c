// module: plat-zxylzb_9128S.ko
// function: crc_16 @ 0x1015c
// size: 60 bytes
//

uint crc_16(byte *param_1,int param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  
  if (param_2 != 0) {
    pbVar2 = param_1;
    do {
      pbVar1 = pbVar2 + 1;
      param_3 = ((uint)*(ushort *)(&crc16_tab + ((uint)*pbVar2 ^ param_3 >> 8) * 2) ^ param_3 << 8)
                & 0xffff;
      pbVar2 = pbVar1;
    } while (pbVar1 != param_1 + param_2);
  }
  return param_3;
}


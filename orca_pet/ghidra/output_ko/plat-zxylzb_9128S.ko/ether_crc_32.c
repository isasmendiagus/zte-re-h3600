// module: plat-zxylzb_9128S.ko
// function: ether_crc_32 @ 0x101d4
// size: 60 bytes
//

uint ether_crc_32(byte *param_1,int param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  
  if (param_2 != 0) {
    pbVar2 = param_1;
    do {
      pbVar1 = pbVar2 + 1;
      param_3 = *(uint *)(crc32_table + ((*pbVar2 ^ param_3) & 0xff) * 4) ^ param_3 >> 8;
      pbVar2 = pbVar1;
    } while (pbVar1 != param_1 + param_2);
  }
  return ~param_3;
}


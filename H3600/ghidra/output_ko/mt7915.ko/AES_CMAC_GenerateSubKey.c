// module: mt7915.ko
// function: AES_CMAC_GenerateSubKey @ 0x1233e4
// size: 328 bytes
//

void AES_CMAC_GenerateSubKey(undefined4 param_1,int param_2,byte *param_3,byte *param_4)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  int local_14;
  
  local_14 = 0;
  if (param_2 == 0x10) {
    local_14 = param_2;
    RT_AES_Encrypt(&_LANCHOR1,0x10,param_1,0x10,param_3,&local_14);
    bVar1 = *param_3;
    pbVar3 = param_3;
    do {
      pbVar2 = pbVar3 + 1;
      *pbVar3 = *pbVar3 << 1 | pbVar3[1] >> 7;
      pbVar3 = pbVar2;
    } while (pbVar2 != param_3 + 0xf);
    param_3[0xf] = param_3[0xf] << 1;
    if ((bVar1 & 0x80) != 0) {
      pbVar2 = &UNK_002986d3;
      pbVar3 = param_3;
      do {
        pbVar2 = pbVar2 + 1;
        *pbVar3 = *pbVar2 ^ *pbVar3;
        pbVar3 = pbVar3 + 1;
      } while (pbVar2 != &DAT_002986e3);
    }
    bVar1 = *param_3;
    pbVar2 = param_4 + -1;
    pbVar3 = param_3;
    do {
      pbVar4 = pbVar3 + 1;
      pbVar2 = pbVar2 + 1;
      *pbVar2 = *pbVar3 << 1 | *pbVar4 >> 7;
      pbVar3 = pbVar4;
    } while (pbVar4 != param_3 + 0xf);
    param_4[0xf] = param_3[0xf] << 1;
    if ((bVar1 & 0x80) != 0) {
      pbVar3 = &UNK_002986d3;
      do {
        pbVar3 = pbVar3 + 1;
        *param_4 = *pbVar3 ^ *param_4;
        param_4 = param_4 + 1;
      } while (pbVar3 != &DAT_002986e3);
    }
  }
  else if (-1 < DebugLevel) {
    printk("AES_CMAC_GenerateSubKey: key length is %d bytes, it must be %d bytes(128 bits).\n",
           param_2,0x10);
  }
  return;
}


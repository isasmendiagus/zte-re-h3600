// module: mt7915.ko
// function: CompareMUEdcaParameters @ 0x205310
// size: 160 bytes
//

undefined4 CompareMUEdcaParameters(byte *param_1,int param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  if ((*(byte *)(param_2 + 0x1478) == 0) || (*(byte *)(param_2 + 0x1478) == (*param_1 & 0xf))) {
    pbVar3 = param_1 + 0xc;
    pbVar2 = (byte *)(param_2 + 0x147c);
    while (((((uint)*pbVar2 == ((uint)param_1[1] << 0x1b) >> 0x1f &&
             ((uint)pbVar2[-1] == (param_1[1] & 0xf))) && (param_1[2] == pbVar2[-2])) &&
           (pbVar2[-3] == param_1[2]))) {
      pbVar1 = pbVar2 + 1;
      param_1 = param_1 + 3;
      pbVar2 = pbVar2 + 8;
      if (*pbVar1 != *param_1) {
        return 0;
      }
      if (param_1 == pbVar3) {
        return 1;
      }
    }
  }
  return 0;
}


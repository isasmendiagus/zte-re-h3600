// module: mt7915.ko
// function: TriEventTableSetEntry @ 0x144c24
// size: 212 bytes
//

undefined4
TriEventTableSetEntry
          (int param_1,byte *param_2,undefined4 param_3,int param_4,char param_5,byte param_6,
          byte param_7)

{
  byte bVar1;
  byte *pbVar2;
  
  if (param_5 != '\0') {
    if ((*(byte *)(param_4 + 1) & 0x40) != 0) {
      *(undefined4 *)(param_2 + 0x284) = *(undefined4 *)(param_1 + 0x7956ac);
    }
    return 0;
  }
  pbVar2 = param_2;
  while (((pbVar2[2] != 1 || (*(ushort *)(pbVar2 + 10) != (ushort)param_7)) ||
         (pbVar2[9] != param_6))) {
    pbVar2 = pbVar2 + 10;
    if (pbVar2 == param_2 + 0x280) {
      if (0x3f < *param_2) {
        return 0;
      }
      RTMPMoveMemory(param_2 + (uint)*param_2 * 10 + 3,param_3,6);
      bVar1 = *param_2;
      param_2[(uint)bVar1 * 10 + 2] = 1;
      *(ushort *)(param_2 + (uint)bVar1 * 10 + 10) = (ushort)param_7;
      param_2[(uint)bVar1 * 10 + 9] = param_6;
      *param_2 = bVar1 + 1;
      return 0;
    }
  }
  return 0;
}


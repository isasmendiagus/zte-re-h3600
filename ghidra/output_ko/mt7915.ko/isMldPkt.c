// module: mt7915.ko
// function: isMldPkt @ 0x24246c
// size: 240 bytes
//

undefined4 isMldPkt(char *param_1,ushort *param_2,byte *param_3,int *param_4)

{
  int iVar1;
  byte *pbVar2;
  byte bVar3;
  int iVar4;
  
  if ((*param_1 == '3') && (param_1[1] == '3' && (ushort)(*param_2 << 8 | *param_2 >> 8) == 0x86dd))
  {
    bVar3 = (byte)param_2[4];
    iVar4 = 0x28;
    while (bVar3 != 0x3a) {
      pbVar2 = (byte *)((int)param_2 + iVar4 + 2);
      if (bVar3 == 0x2b) {
        bVar3 = *(byte *)((int)param_2 + iVar4 + 2);
        iVar1 = (pbVar2[1] + 1) * 8;
      }
      else {
        if (bVar3 < 0x2c) {
          if (bVar3 != 0) {
            return 0;
          }
        }
        else {
          iVar1 = 8;
          if (bVar3 == 0x2c) {
            bVar3 = *pbVar2;
            goto LAB_002424ec;
          }
          if (bVar3 != 0x3c) {
            return 0;
          }
        }
        bVar3 = *pbVar2;
        iVar1 = (pbVar2[1] + 1) * 8;
      }
LAB_002424ec:
      iVar4 = iVar4 + iVar1;
    }
    bVar3 = *(byte *)((int)param_2 + iVar4 + 2);
    if ((0x81 < bVar3) && ((bVar3 < 0x85 || (bVar3 == 0x8f)))) {
      if (param_3 != (byte *)0x0) {
        *param_3 = bVar3;
      }
      if (param_4 != (int *)0x0) {
        *param_4 = (int)param_2 + iVar4 + 2;
      }
      return 1;
    }
  }
  return 0;
}


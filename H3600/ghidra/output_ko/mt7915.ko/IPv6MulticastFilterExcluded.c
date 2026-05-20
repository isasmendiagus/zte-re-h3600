// module: mt7915.ko
// function: IPv6MulticastFilterExcluded @ 0x24255c
// size: 156 bytes
//

bool IPv6MulticastFilterExcluded(byte *param_1,short *param_2)

{
  ushort uVar1;
  byte bVar2;
  int iVar3;
  
  bVar2 = *param_1 & 1 ^ 1;
  if (*param_1 != 0x33) {
    bVar2 = 1;
  }
  if (*param_2 != -0x227a) {
    bVar2 = 1;
  }
  if (bVar2 != 0) {
    return false;
  }
  uVar1 = (ushort)*(byte *)(param_2 + 4);
  if (uVar1 == 0) {
    iVar3 = 0x28;
    do {
      uVar1 = (ushort)*(byte *)((int)param_2 + iVar3 + 2);
      iVar3 = iVar3 + (*(byte *)((int)param_2 + iVar3 + 3) + 1) * 8;
    } while (uVar1 == 0);
  }
  if ((ushort)IPv6MulticastFilterExclued != uVar1) {
    return IPv6MulticastFilterExclued._2_2_ == uVar1;
  }
  return true;
}


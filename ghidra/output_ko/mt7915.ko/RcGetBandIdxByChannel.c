// module: mt7915.ko
// function: RcGetBandIdxByChannel @ 0xabee8
// size: 192 bytes
//

byte RcGetBandIdxByChannel(int param_1,uint param_2)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  byte bVar4;
  int iVar5;
  
  if (*(char *)(*(int *)(param_1 + 0x4328) + 0x79504d) == '\0') {
    return 0;
  }
  cVar1 = *(char *)(param_1 + 0x32d8);
  if (param_2 < 0xf) {
    if (cVar1 == '\0') {
      return 0;
    }
    if ((*(byte *)(param_1 + 0x1360) & 1) != 0) goto LAB_000abf98;
    if (cVar1 == '\x01') {
      return *(byte *)(param_1 + 0x1360) & 1;
    }
    bVar2 = *(byte *)(param_1 + 0x16b4) & 1;
    bVar4 = *(byte *)(param_1 + 0x16b4) & 1;
  }
  else {
    if (cVar1 == '\0') {
      return 0;
    }
    if ((*(byte *)(param_1 + 0x1360) & 2) != 0) {
LAB_000abf98:
      iVar5 = 0;
      goto LAB_000abf7c;
    }
    if (cVar1 == '\x01') {
      return *(byte *)(param_1 + 0x1360) & 2;
    }
    bVar2 = *(byte *)(param_1 + 0x16b4) & 2;
    bVar4 = *(byte *)(param_1 + 0x16b4) & 2;
  }
  if (bVar2 == 0) {
    return bVar4;
  }
  iVar5 = 1;
LAB_000abf7c:
  pbVar3 = (byte *)(iVar5 * 0x354 + param_1 + 0x169c);
  bVar2 = 0;
  if (pbVar3 != (byte *)0x0) {
    bVar2 = *pbVar3;
  }
  return bVar2;
}


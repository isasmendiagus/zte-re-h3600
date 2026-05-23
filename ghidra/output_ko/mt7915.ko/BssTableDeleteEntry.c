// module: mt7915.ko
// function: BssTableDeleteEntry @ 0x10e75c
// size: 344 bytes
//

void BssTableDeleteEntry(uint *param_1,void *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  void *__dest;
  uint uVar3;
  uint uVar4;
  
  uVar3 = *param_1;
  uVar4 = uVar3 - 1;
  if (0xfe < uVar4) {
    return;
  }
  uVar2 = 0;
  while (((byte)param_1[uVar2 * 0x2bd + 5] != param_3 ||
         (iVar1 = memcmp((void *)((int)param_1 + uVar2 * 0xaf4 + 0xe),param_2,6), iVar1 != 0))) {
    uVar2 = uVar2 + 1 & 0xff;
    if (uVar3 <= uVar2 || 0xff < uVar3) {
      return;
    }
  }
  if (uVar2 < uVar4) {
    do {
      uVar3 = uVar2 + 1;
      __dest = (void *)param_1[uVar2 * 0x2bd + 0x13e];
      memmove(param_1 + uVar2 * 0x2bd + 2,param_1 + uVar3 * 0x2bd + 2,0xaf4);
      if (__dest != (void *)0x0) {
        RTMPZeroMemory(__dest,0x400);
        memmove(__dest,(void *)param_1[uVar3 * 0x2bd + 0x13e],
                (uint)*(ushort *)((int)param_1 + uVar3 * 0xaf4 + 0x4f6));
        param_1[uVar2 * 0x2bd + 0x13e] = (uint)__dest;
      }
      uVar4 = *param_1 - 1;
      uVar2 = uVar3 & 0xff;
    } while ((uVar3 & 0xff) < uVar4);
  }
  uVar3 = param_1[uVar4 * 0x2bd + 0x13e];
  __memzero(param_1 + uVar4 * 0x2bd + 2,0xaf4);
  if (uVar3 == 0) {
    uVar4 = *param_1 - 1;
  }
  else {
    RTMPZeroMemory(uVar3,0x400);
    uVar4 = *param_1 - 1;
    param_1[uVar4 * 0x2bd + 0x13e] = uVar3;
  }
  *param_1 = uVar4;
  return;
}


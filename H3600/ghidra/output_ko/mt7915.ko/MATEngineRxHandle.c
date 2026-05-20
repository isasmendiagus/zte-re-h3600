// module: mt7915.ko
// function: MATEngineRxHandle @ 0x79e24
// size: 280 bytes
//

undefined4 MATEngineRxHandle(int param_1,int param_2)

{
  void *__src;
  byte *pbVar1;
  ushort uVar2;
  byte *__dest;
  int iVar3;
  
  if (*(int *)(param_1 + 0x794b28) != 1) {
    return 0;
  }
  __dest = *(byte **)(param_2 + 0xcc);
  if ((__dest != (byte *)0x0) && ((*__dest & 1) == 0)) {
    uVar2 = *(ushort *)(__dest + 0xc) << 8 | *(ushort *)(__dest + 0xc) >> 8;
    if (uVar2 == 0x8100) {
      pbVar1 = __dest + 0x12;
      uVar2 = *(ushort *)(__dest + 0x10) << 8 | *(ushort *)(__dest + 0x10) >> 8;
    }
    else {
      pbVar1 = __dest + 0xe;
    }
    if (uVar2 == 0x800) {
      iVar3 = 0;
    }
    else if (uVar2 == 0x806) {
      iVar3 = 1;
    }
    else if (uVar2 == 0x8863) {
      iVar3 = 2;
    }
    else if (uVar2 == 0x8864) {
      iVar3 = 3;
    }
    else {
      if (uVar2 != 0x86dd) {
        return 0;
      }
      iVar3 = 4;
    }
    if ((*(code **)((&DAT_00291860)[iVar3 * 2] + 8) != (code *)0x0) &&
       (__src = (void *)(**(code **)((&DAT_00291860)[iVar3 * 2] + 8))
                                  (param_1 + 0x794b28,param_2,pbVar1,0), __src != (void *)0x0)) {
      memmove(__dest,__src,6);
      return 0;
    }
  }
  return 0;
}


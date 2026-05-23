// module: mt7915.ko
// function: RcUpdateBw @ 0xac7a8
// size: 92 bytes
//

uint RcUpdateBw(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_1 + 4);
  if (param_2 == 0 || (*(ushort *)(iVar1 + 2) & 0x18) != 0) {
    uVar2 = ((*(ushort *)(iVar1 + 2) ^ 0x20) << 0x1a) >> 0x1f;
    if (param_2 < 2) {
      uVar2 = 0;
    }
    if (uVar2 == 0) {
      *(char *)(iVar1 + 7) = (char)param_2;
    }
    else {
      *(undefined1 *)(iVar1 + 7) = 1;
    }
  }
  else {
    *(undefined1 *)(iVar1 + 7) = 0;
  }
  return param_2;
}


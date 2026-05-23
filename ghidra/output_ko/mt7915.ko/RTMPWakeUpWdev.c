// module: mt7915.ko
// function: RTMPWakeUpWdev @ 0x1296c8
// size: 88 bytes
//

void RTMPWakeUpWdev(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 == 0) {
    return;
  }
  if (*(ushort *)(iVar1 + 0x2124a4) < 2) {
    *(undefined2 *)(iVar1 + 0x2124a4) = 2;
  }
  if (*(int *)(iVar1 + 0x2124ac) != 0 && *(int *)(iVar1 + 0x2124ac) != 3) {
    if (*(char *)(iVar1 + 0x2124c0) != '\0') {
      RTMP_FORCE_WAKEUP(param_1);
      return;
    }
    return;
  }
  return;
}


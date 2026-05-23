// module: mt7915.ko
// function: MSTA_Remove @ 0x68670
// size: 168 bytes
//

void MSTA_Remove(int param_1)

{
  int *piVar1;
  
  if (param_1 == 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x286294) & 3) != 3) {
    return;
  }
  piVar1 = (int *)(&DAT_0036db58 + param_1);
  do {
    if (*piVar1 != 0) {
      RtmpOSNetDevProtect(1);
      RtmpOSNetDevDetach(*piVar1);
      RtmpOSNetDevProtect(0);
      wdev_deinit(param_1,piVar1);
      RtmpOSNetDevFree(*piVar1);
      *(undefined1 *)(piVar1 + 0x84ccd) = 0;
      *piVar1 = 0;
    }
    piVar1 = piVar1 + 0x84dec;
  } while (piVar1 != (int *)(param_1 + 0x794ab8));
  return;
}


// module: mt7915.ko
// function: rtmp_handle_mic_error_event @ 0xcb278
// size: 252 bytes
//

void rtmp_handle_mic_error_event(undefined4 param_1,int param_2)

{
  ushort uVar1;
  int *piVar2;
  uint uVar3;
  byte *pbVar4;
  
  pbVar4 = *(byte **)(param_2 + 0x10);
  piVar2 = (int *)MacTableLookup(param_1,*(undefined4 *)(param_2 + 0x2c));
  if (piVar2 == (int *)0x0) {
    return;
  }
  if ((*(uint *)(param_2 + 0x44) & 0x80000) != 0) {
    return;
  }
  if ((*pbVar4 & 0x10) == 0) {
    if ((*pbVar4 & 0x60) == 0) {
      return;
    }
  }
  else {
    uVar1 = *(ushort *)(param_2 + 0x4e);
    uVar3 = HcGetMaxStaNum(param_1);
    if ((uVar1 < uVar3) && ((piVar2[0xb1] & 0x10U) != 0)) {
      if (*piVar2 != 2 && *piVar2 != 0x40001) {
        ap_handle_mic_error_event(param_1,piVar2,param_2);
        return;
      }
      goto LAB_000cb2f0;
    }
    if ((*pbVar4 & 0x60) == 0) {
      return;
    }
  }
  if (2 < DebugLevel) {
    printk("Rx bc/mc Cipher Err(MPDUsize=%d, WCID=%d, CipherErr=%d)\n",
           *(undefined2 *)(param_2 + 0x48),*(undefined2 *)(param_2 + 0x4e),
           ((uint)pbVar4[1] << 0x1d) >> 0x1e);
  }
  if (*piVar2 != 2 && *piVar2 != 0x40001) {
    return;
  }
LAB_000cb2f0:
  sta_handle_mic_error_event(param_1,piVar2,param_2);
  return;
}


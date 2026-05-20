// module: mt7915.ko
// function: sta_2040_coex_scan_check @ 0x1444fc
// size: 316 bytes
//

void sta_2040_coex_scan_check(int param_1,int param_2)

{
  int extraout_r1;
  uint uVar1;
  undefined1 auStack_41 [6];
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 auStack_38 [32];
  
  if ((param_2 != 0) && ((*(ushort *)(param_2 + 0x18) & 0x4e) == 0)) {
    return;
  }
  if ((*(uint *)(param_1 + 0x795124) & 0x40000) == 0) {
    return;
  }
  uVar1 = (uint)*(ushort *)(param_1 + 0x7956a2);
  if (uVar1 == 0) {
    return;
  }
  __aeabi_uidivmod(*(undefined4 *)(param_1 + 0x82921c),uVar1);
  if (extraout_r1 != uVar1 - 1) {
    return;
  }
  if (DebugLevel < 3) {
    if (0x45 < *(uint *)(param_1 + 0xa39e80)) {
      return;
    }
  }
  else {
    printk("MMCHK - LastOneSecTotalTxCount/LastOneSecRxOkDataCnt  = %d/%d\n",
           *(undefined4 *)(param_1 + 0xa39e80),*(undefined4 *)(param_1 + 0xa39e84));
    if (0x45 < *(uint *)(param_1 + 0xa39e80)) goto LAB_001445a0;
  }
  if (*(uint *)(param_1 + 0xa39e84) < 0x46) {
    __memzero(auStack_38,0x20);
    local_39 = 0;
    local_3b = 2;
    local_3a = 4;
    if (param_2 != 0) {
      cntl_scan_request(param_2,auStack_41);
    }
    *(byte *)(param_1 + 0x7956b5) = *(byte *)(param_1 + 0x7956b5) | 1;
  }
LAB_001445a0:
  if (2 < DebugLevel) {
    printk(" LastOneSecTotalTxCount/LastOneSecRxOkDataCnt  = %d/%d\n",
           *(undefined4 *)(param_1 + 0xa39e80),*(undefined4 *)(param_1 + 0xa39e84));
  }
  return;
}


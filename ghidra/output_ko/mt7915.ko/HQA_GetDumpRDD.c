// module: mt7915.ko
// function: HQA_GetDumpRDD @ 0x27026c
// size: 1188 bytes
//

void HQA_GetDumpRDD(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint local_30;
  
  iVar4 = param_1 + 0xa3b86c;
  local_30 = 0;
  OS_SPIN_LOCK(iVar4);
  *(undefined1 *)(param_1 + 0xa3b871) = 1;
  OS_SPIN_UNLOCK(iVar4);
  iVar2 = DebugLevel;
  if (DebugLevel < 1) {
    *(undefined1 *)(param_1 + 0xa7cbda) = 1;
  }
  else {
    printk("[RDD DUMP START][HQA_GetDumpRDD]\n");
    iVar2 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7cbda) = 1;
    if (2 < iVar2) {
      printk("log_cb->idx is %d, log_cb->len is %d\n",*(undefined4 *)(param_1 + 0xa3b874),
             *(undefined4 *)(param_1 + 0xa3b878));
      iVar2 = DebugLevel;
    }
  }
  if ((*(char *)(param_1 + 0xa3ba95) == '\x01') || (*(char *)(param_1 + 0xa3ba96) == '\x01')) {
    DAT_005f662c = 0;
  }
  if (2 < iVar2) {
    printk("idx: %d\n",DAT_005f662c);
    iVar2 = DebugLevel;
  }
  iVar6 = DAT_005f662c;
  iVar7 = *(int *)(param_1 + 0xa3b874);
  iVar5 = *(int *)(param_1 + 0xa3b878);
  if (iVar7 < DAT_005f662c) {
    iVar7 = iVar7 + iVar5;
  }
  iVar7 = iVar7 - DAT_005f662c;
  if (iVar7 < 0x51) {
    __aeabi_idivmod(iVar7 + DAT_005f662c,iVar5);
    iVar9 = extraout_r1_01;
  }
  else {
    __aeabi_idivmod(DAT_005f662c + 0x50,iVar5);
    iVar9 = extraout_r1;
  }
  if (2 < iVar2) {
    printk("remindIdx: %d, end: %d\n",iVar7,iVar9);
    iVar5 = *(int *)(param_1 + 0xa3b878);
    iVar6 = DAT_005f662c;
  }
  uVar8 = 0;
  while( true ) {
    __aeabi_idivmod(iVar6,iVar5);
    iVar6 = *(int *)(param_1 + 0xa3b880) + extraout_r1_00 * 0x2c;
    iVar2 = extraout_r1_00;
    DAT_005f662c = extraout_r1_00;
    if (*(char *)(iVar6 + 4) != '\0') {
      if (*(char *)(iVar6 + 0x10) == '\0') {
        if (0 < DebugLevel) {
          printk("[RDD]0x%08x %08x\n",*(undefined4 *)(iVar6 + 8),*(undefined4 *)(iVar6 + 0xc));
        }
        iVar5 = local_30 + 1;
        iVar2 = local_30 * 4;
        local_30 = local_30 + 2;
        *(undefined4 *)(param_3 + iVar2 + 0x12) = *(undefined4 *)(iVar6 + 8);
        uVar3 = *(uint *)(iVar6 + 0xc);
        *(uint *)(iVar6 + 0xc) =
             uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
             uVar3 >> 0x18;
        *(uint *)(param_3 + iVar5 * 4 + 0x12) = *(uint *)(iVar6 + 0xc);
      }
      iVar2 = DAT_005f662c;
      if (DebugLevel < 1) {
        *(undefined1 *)(*(int *)(param_1 + 0xa3b880) + DAT_005f662c * 0x2c + 4) = 0;
        uVar3 = *(uint *)(iVar6 + 0x11);
      }
      else {
        printk("[RDD]0x%08x %08x\n",*(undefined4 *)(iVar6 + 0x11),*(undefined4 *)(iVar6 + 0x15));
        iVar2 = DAT_005f662c;
        *(undefined1 *)(*(int *)(param_1 + 0xa3b880) + DAT_005f662c * 0x2c + 4) = 0;
        uVar3 = *(uint *)(iVar6 + 0x11);
      }
      uVar8 = uVar8 + 1;
      *(uint *)(iVar6 + 0x11) =
           uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18
      ;
      uVar3 = *(uint *)(iVar6 + 0x15);
      iVar5 = param_3 + local_30 * 4;
      *(uint *)(iVar6 + 0x15) =
           uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18
      ;
      *(undefined4 *)(iVar5 + 0x12) = *(undefined4 *)(iVar6 + 0x11);
      *(undefined4 *)(iVar5 + 0x16) = *(undefined4 *)(iVar6 + 0x15);
      local_30 = local_30 + 2;
    }
    if (*(char *)(param_1 + 0xa7cbdb) != '\0' && 0xd6 < uVar8) break;
    iVar5 = *(int *)(param_1 + 0xa3b878);
    DAT_005f662c = iVar2 + 1;
    if (iVar5 <= DAT_005f662c) {
      DAT_005f662c = 0;
    }
    iVar6 = DAT_005f662c;
    if (iVar9 == DAT_005f662c) {
LAB_002704ac:
      if (2 < DebugLevel) {
        printk("[After RDD dumping] idx: %d, end: %d\n",DAT_005f662c,iVar9);
        if ((2 < DebugLevel) &&
           (printk("[HQA_GetDumpRDD]: Total Count As a Group of Two Pulses = %d\n",local_30 >> 1),
           2 < DebugLevel)) {
          printk("[HQA_GetDumpRDD] idx = %d, log_cb->idx = %d, pAd->fgDumpStart = %d\n",DAT_005f662c
                 ,*(undefined4 *)(param_1 + 0xa3b874),*(undefined1 *)(param_1 + 0xa7cbda));
        }
      }
      uVar8 = local_30 >> 1;
      if ((*(int *)(param_1 + 0xa3b874) == DAT_005f662c) && (*(char *)(param_1 + 0xa7cbda) != '\0'))
      {
        if (0 < DebugLevel) {
          printk("[RDD DUMP END]\n");
        }
        *(undefined1 *)(param_1 + 0xa7cbda) = 0;
      }
      OS_SPIN_LOCK(iVar4);
      *(undefined1 *)(param_1 + 0xa3b871) = 0;
      OS_SPIN_UNLOCK(iVar4);
      if (uVar8 == 0) {
        *(undefined4 *)(param_3 + 0xe) = 0;
        FUN_0026cdd0(param_3,param_2,6,0);
      }
      else {
        uVar3 = local_30 >> 9 & 0xff;
        uVar1 = local_30 >> 0x11 & 0xff;
        *(uint *)(param_3 + 0xe) = uVar8 << 0x18 | uVar3 << 0x10 | uVar1 << 8 | local_30 >> 0x19;
        FUN_0026cdd0(param_3,param_2,
                     ((local_30 >> 0x19) << 0x18 | uVar1 << 0x10 | uVar3 << 8 | uVar8 & 0xff) * 8 +
                     6,0);
      }
      *(undefined1 *)(param_1 + 0xa3ba95) = 0;
      *(undefined1 *)(param_1 + 0xa3ba96) = 0;
      return;
    }
  }
  *(short *)(param_1 + 0xa7cbd8) = (short)iVar2;
  goto LAB_002704ac;
}


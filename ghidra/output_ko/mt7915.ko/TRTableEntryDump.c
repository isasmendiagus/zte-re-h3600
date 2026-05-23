// module: mt7915.ko
// function: TRTableEntryDump @ 0x147ebc
// size: 1136 bytes
//

void TRTableEntryDump(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar2 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 <= param_2 || 0x11f < param_2) {
    printk(&_LC0,0x66);
    dump_stack();
  }
  iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 <= param_2 || 0x11f < param_2) {
    return;
  }
  if (DebugLevel < 1) goto LAB_00147f40;
  printk("Dump TR_ENTRY called by function %s(%d)\n",param_3,param_4);
  if (DebugLevel < 1) {
LAB_00148058:
    if (0 < DebugLevel) {
      iVar1 = param_2 * 0x620 + param_1;
      printk("\tfunc_tb_idx=%d\n",*(undefined1 *)(iVar1 + 0x2f6aa));
      if (DebugLevel < 1) goto LAB_00147f40;
      printk("\tAddr=%02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(iVar1 + 0x2f6ab),
             *(undefined1 *)(iVar1 + 0x2f6ac),*(undefined1 *)(iVar1 + 0x2f6ad),
             *(undefined1 *)(iVar1 + 0x2f6ae),*(undefined1 *)(iVar1 + 0x2f6af),
             *(undefined1 *)(iVar1 + 0x2f6b0));
      goto LAB_001480f4;
    }
LAB_0014818c:
    if (0 < DebugLevel) {
      iVar1 = param_2 * 0x620 + param_1;
      printk("\t\tbIAmBadAtheros=%d, isCached=%d, PortSecured=%d, PsMode=%d, LockEntryTx=%d\n",
             *(undefined1 *)(iVar1 + 0x2f760),*(undefined1 *)(iVar1 + 0x2f761),
             *(undefined1 *)(iVar1 + 0x2f762),*(undefined1 *)(iVar1 + 0x2f763),
             *(undefined1 *)(iVar1 + 0x2f765));
      if (DebugLevel < 1) goto LAB_00147f40;
      printk("\tTxRx Characters\n");
      goto LAB_001481ec;
    }
LAB_0014824c:
    if (0 < DebugLevel) {
      printk("\tCurrTxRate=%x\n",*(undefined1 *)(param_2 * 0x620 + param_1 + 0x2f766));
      if (DebugLevel < 1) goto LAB_00147f40;
      printk("\tQueuing Info\n");
      goto LAB_00148294;
    }
  }
  else {
    printk("TR_ENTRY[%d]\n",param_2);
    if (DebugLevel < 1) goto LAB_00147f40;
    iVar1 = param_1 + param_2 * 0x620;
    printk("\tEntryType=%x\n",*(undefined4 *)(iVar1 + 0x2f6a0));
    if (0 < DebugLevel) {
      printk("\twdev=%p\n",*(undefined4 *)(iVar1 + 0x2f6a4));
      if (DebugLevel < 1) goto LAB_00147f40;
      printk("\twcid=%d\n",*(undefined2 *)(param_1 + param_2 * 0x620 + 0x2f6a8));
      goto LAB_00148058;
    }
LAB_001480f4:
    if (0 < DebugLevel) {
      iVar1 = param_2 * 0x620 + param_1;
      printk("\tBSSID=%02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(iVar1 + 0x2f75a),
             *(undefined1 *)(iVar1 + 0x2f75b),*(undefined1 *)(iVar1 + 0x2f75c),
             *(undefined1 *)(iVar1 + 0x2f75d),*(undefined1 *)(iVar1 + 0x2f75e),
             *(undefined1 *)(iVar1 + 0x2f75f));
      if (DebugLevel < 1) goto LAB_00147f40;
      printk("\tFlags\n");
      goto LAB_0014818c;
    }
LAB_001481ec:
    if (0 < DebugLevel) {
      iVar1 = param_2 * 0x620 + param_1;
      printk("\t\tNonQosDataSeq=%d\n",*(undefined2 *)(iVar1 + 0x2f6b2));
      if (DebugLevel < 1) goto LAB_00147f40;
      printk("\t\tTxSeq[0]=%d, TxSeq[1]=%d, TxSeq[2]=%d, TxSeq[3]=%d\n",
             *(undefined2 *)(iVar1 + 0x2f6b4),*(undefined2 *)(iVar1 + 0x2f6b6),
             *(undefined2 *)(iVar1 + 0x2f6b8),*(undefined2 *)(iVar1 + 0x2f6ba));
      goto LAB_0014824c;
    }
LAB_00148294:
    if (DebugLevel < 1) goto LAB_00147f40;
    iVar1 = param_2 * 0x620 + param_1;
    printk("\t\tenq_cap=%d, deq_cap=%d\n",*(undefined1 *)(iVar1 + 0x2f758),
           *(undefined1 *)(iVar1 + 0x2f759));
    if (DebugLevel < 1) goto LAB_00147f40;
    printk("\t\tQueuedPkt: TxQ[0]=%d, TxQ[1]=%d, TxQ[2]=%d, TxQ[3]=%d, PSQ=%d\n",
           *(undefined4 *)(iVar1 + 0x2f6cc),*(undefined4 *)(iVar1 + 0x2f6dc),
           *(undefined4 *)(iVar1 + 0x2f6ec),*(undefined4 *)(iVar1 + 0x2f6fc),
           *(undefined4 *)(iVar1 + 0x2f70c));
  }
  if (0 < DebugLevel) {
    iVar1 = param_2 * 0x620 + param_1;
    printk("\t\tdeq_cnt=%d, deq_bytes=%d\n",*(undefined4 *)(iVar1 + 0x2f74c),
           *(undefined4 *)(iVar1 + 0x2f750));
  }
LAB_00147f40:
  uVar3 = 0;
  do {
    if (*(code **)(iVar2 + 0xc) != (code *)0x0) {
      (**(code **)(iVar2 + 0xc))
                (param_1,*(undefined2 *)(param_1 + param_2 * 0x620 + 0x2f6a8),0,uVar3 & 0xff);
    }
    uVar4 = uVar3 + 1;
    ge_tx_swq_dump(param_1,uVar3);
    uVar3 = uVar4;
  } while (uVar4 != 4);
  return;
}


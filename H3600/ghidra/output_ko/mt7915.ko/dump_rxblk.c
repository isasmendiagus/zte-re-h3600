// module: mt7915.ko
// function: dump_rxblk @ 0xc5b0c
// size: 544 bytes
//

void dump_rxblk(int param_1,int param_2)

{
  int iVar1;
  
  if (2 < DebugLevel) {
    printk("Dump RX_BLK Structure:\n");
    if (2 < DebugLevel) {
      printk("\tHW rx info:\n");
    }
  }
  hex_dump("RawData",param_2,0x10);
  if (2 < DebugLevel) {
    printk("\tData Pointer info:\n");
  }
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 2) {
    if (2 < DebugLevel) {
      printk("\t\trmac_info=0x%p\n",*(undefined4 *)(param_2 + 0x18));
    }
    if (*(int *)(param_2 + 0x18) != 0) {
      asic_dump_rmac_info(param_1);
    }
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("\t\tpRxPacket=0x%p, MPDUtotalByteCnt=%d\n",*(undefined4 *)(param_2 + 0x38),
         *(undefined2 *)(param_2 + 0x48));
  if (DebugLevel < 3) {
LAB_000c5bfc:
    if (DebugLevel < 3) goto LAB_000c5c78;
    printk("\t\tOpMode=%d\n",*(undefined1 *)(param_2 + 0x4b));
    if (DebugLevel < 3) {
      return;
    }
    printk("\tMirror Info from RMAC Info:\n");
  }
  else {
    printk("\t\tpData=0x%p\n",*(undefined4 *)(param_2 + 0x3c));
    if (DebugLevel < 3) {
      return;
    }
    printk("\t\tDataSize=%d\n",*(undefined2 *)(param_2 + 0x40));
    if (2 < DebugLevel) {
      printk("\t\tFlags=0x%x\n",*(undefined4 *)(param_2 + 0x44));
      if (DebugLevel < 3) {
        return;
      }
      printk("\t\tUserPriority=%d\n",*(undefined1 *)(param_2 + 0x4a));
      goto LAB_000c5bfc;
    }
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("\t\tWCID=%d\n",*(undefined2 *)(param_2 + 0x4e));
  if (DebugLevel < 3) {
    return;
  }
  printk("\t\tTID=%d\n",*(undefined1 *)(param_2 + 0x53));
LAB_000c5c78:
  if (DebugLevel < 3) {
    return;
  }
  printk("\t\tKey_idx=%d\n",*(undefined1 *)(param_2 + 0x51));
  if (DebugLevel < 3) {
    return;
  }
  printk("\t\tBSS_IDX=%d\n",*(undefined1 *)(param_2 + 0x52));
  return;
}


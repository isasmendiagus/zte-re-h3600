// module: mt7915.ko
// function: ShowManualTxOP @ 0xe13d4
// size: 276 bytes
//

undefined4 ShowManualTxOP(int param_1)

{
  undefined2 local_14;
  undefined2 local_12;
  
  if (0 < DebugLevel) {
    printk("CURRENT: ManualTxOP = %d\n",*(undefined1 *)(param_1 + 0x795b0e));
    if (((0 < DebugLevel) &&
        (printk("       : bEnableTxBurst = %d\n",*(undefined1 *)(param_1 + 0x795071)),
        0 < DebugLevel)) &&
       (printk("       : MacTab.Size = %d\n",*(undefined2 *)(param_1 + 0x285920)), 0 < DebugLevel))
    {
      printk("       : RDG_ACTIVE = %d\n",(uint)(*(int *)(param_1 + 0xa39f84) << 0xb) >> 0x1f);
    }
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f4014,&local_14);
  if (0 < DebugLevel) {
    printk("       : AC0 TxOP = 0x%x\n",local_14);
    if (0 < DebugLevel) {
      printk("       : AC1 TxOP = 0x%x\n",local_12);
    }
  }
  return 1;
}


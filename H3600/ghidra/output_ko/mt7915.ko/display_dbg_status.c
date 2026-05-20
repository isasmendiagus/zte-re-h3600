// module: mt7915.ko
// function: display_dbg_status @ 0x97a68
// size: 176 bytes
//

void display_dbg_status(int param_1)

{
  char *pcVar1;
  undefined4 uVar2;
  
  if (0 < DebugLevel) {
    pcVar1 = "enable";
    if ((*(byte *)(param_1 + 4) & 1) == 0) {
      pcVar1 = "disable";
    }
    printk("debug mode: %s\n",pcVar1);
    if (0 < DebugLevel) {
      uVar2 = *(undefined4 *)(param_1 + 0x1c);
      printk("TXCMD TX statistics:\ntotal=%d, protect=%d, txdata=%d, trigdata=%d, sw_fid=%d\n",
             *(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 0x10),
             *(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18),uVar2);
      if (0 < DebugLevel) {
        printk("TXCMD RX statistics:\nSPL=%d, CMDRPT(txdata)=%d, CMDRPT(trigdata)=%d, RXRPT=%d\n",
               *(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0x20),
               *(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x28),uVar2);
      }
    }
  }
  return;
}


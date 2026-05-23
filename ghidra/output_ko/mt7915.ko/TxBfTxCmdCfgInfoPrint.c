// module: mt7915.ko
// function: TxBfTxCmdCfgInfoPrint @ 0x87d5c
// size: 104 bytes
//

void TxBfTxCmdCfgInfoPrint(undefined4 param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  uVar1 = *param_2;
  uVar2 = param_2[1];
  if (DebugLevel < 1) {
    return;
  }
  printk("============================= Global Setting ========================================\n");
  if (DebugLevel < 1) {
    return;
  }
  printk("TxCmdBfManual = 0x%02X, TxCmdBfBit = 0x%02X\n",uVar1,uVar2);
  if (DebugLevel < 1) {
    return;
  }
  printk("=====================================================================================\n");
  return;
}


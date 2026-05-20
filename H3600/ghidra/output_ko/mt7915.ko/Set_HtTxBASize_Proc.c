// module: mt7915.ko
// function: Set_HtTxBASize_Proc @ 0xdde4c
// size: 108 bytes
//

undefined4 Set_HtTxBASize_Proc(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 uVar2;
  bool bVar3;
  
  uVar1 = os_str_tol(param_2,0,10);
  uVar1 = uVar1 & 0xff;
  uVar2 = (undefined1)(uVar1 - 1);
  if (0x3e < (uVar1 - 1 & 0xff)) {
    uVar2 = 7;
    uVar1 = 8;
  }
  bVar3 = -1 < DebugLevel;
  *(undefined1 *)(param_1 + 0x795950) = uVar2;
  if (bVar3) {
    printk("Set_HtTxBASize ::(TxBASize= %d)\n",uVar1 - 1);
  }
  return 1;
}


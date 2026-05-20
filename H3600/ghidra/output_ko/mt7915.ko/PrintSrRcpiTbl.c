// module: mt7915.ko
// function: PrintSrRcpiTbl @ 0x16d360
// size: 108 bytes
//

void PrintSrRcpiTbl(int param_1)

{
  int iVar1;
  
  if (-1 < DebugLevel) {
    printk(&_LC102,"PrintSrRcpiTbl");
  }
  iVar1 = 0;
  do {
    if (-1 < DebugLevel) {
      printk("u1RcpiTblMcs[%d] = %x\n",iVar1,*(undefined1 *)(param_1 + iVar1));
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0xc);
  return;
}


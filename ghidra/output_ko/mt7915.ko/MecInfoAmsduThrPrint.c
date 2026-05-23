// module: mt7915.ko
// function: MecInfoAmsduThrPrint @ 0x1a75d8
// size: 276 bytes
//

void MecInfoAmsduThrPrint(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  if (0 < DebugLevel) {
    printk("[+] PHY Rate Threshold for AMSDU Length Setting\n");
  }
  iVar2 = 0;
  if (0 < DebugLevel) goto LAB_001a7620;
LAB_001a7608:
  do {
    bVar4 = iVar2 == 1;
    iVar2 = 1;
    if (bVar4) {
      return;
    }
  } while (DebugLevel < 1);
LAB_001a7620:
  if (iVar2 == 0) {
    uVar1 = 0x40;
  }
  else {
    uVar1 = 0x100;
  }
  printk("    BA %2u\n",uVar1);
  if (0 < DebugLevel) goto code_r0x001a764c;
  goto LAB_001a76ac;
code_r0x001a764c:
  printk("     Num   Len    Threshold\n");
  if (0 < DebugLevel) {
    printk("      1    1.7K      0 Mbps\n");
    iVar3 = param_2 + iVar2 * 6;
    if ((0 < DebugLevel) &&
       (printk("      2    3.3K   %4u Mbps\n",*(undefined2 *)(iVar3 + 0x24)), 0 < DebugLevel)) {
      printk("      3    4.8K   %4u Mbps\n",*(undefined2 *)(iVar3 + 0x26));
LAB_001a76ac:
      if (0 < DebugLevel) {
        printk("      4    6.3K   %4u Mbps\n",*(undefined2 *)(param_2 + iVar2 * 6 + 0x28));
      }
    }
  }
  goto LAB_001a7608;
}


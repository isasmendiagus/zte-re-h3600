// module: mt7915.ko
// function: HcGetRepeaterOmac @ 0xa9198
// size: 108 bytes
//

undefined1 HcGetRepeaterOmac(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  
  if (((param_1 == 0) || (*(int *)(param_1 + 0x14) != 0x100)) ||
     (iVar1 = OcGetRepeaterEntry(*(undefined4 *)(param_1 + 0xabc),*(undefined1 *)(param_1 + 0xe)),
     iVar1 == 0)) {
    uVar2 = 0xff;
  }
  else {
    uVar2 = *(undefined1 *)(iVar1 + 1);
  }
  if (2 < DebugLevel) {
    printk("%s(): Get ReptOmacIdx: %d!\n","HcGetRepeaterOmac",uVar2);
  }
  return uVar2;
}


// module: mt7915.ko
// function: SetTxPowerCompInfo @ 0xc10dc
// size: 416 bytes
//

undefined4 SetTxPowerCompInfo(int *param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  char *pcVar3;
  int iVar4;
  undefined1 auStack_2f7 [735];
  
  uVar1 = *(uint *)(*param_1 + 0x3c);
  memcpy(auStack_2f7,"CCK_1M2M   ",0x2df);
  uVar1 = uVar1 & 0xff;
  if (uVar1 < *(byte *)((int)param_1 + 0x2b7242)) {
    HcGetBandByWdev(param_1 + uVar1 * 0x160d + 0xadc92);
    uVar1 = HcGetBandByWdev(param_1 + 0xdb6d6);
    if (0 < DebugLevel) {
      printk("%s: ucBandIdx = %d\n","SetTxPowerCompInfo",uVar1);
    }
    if (uVar1 < 2) {
      if ((((0 < DebugLevel) &&
           (printk("=============================================================================\n"
                  ), 0 < DebugLevel)) &&
          (printk("                       Tx Power Compenstation Info                 \n"),
          0 < DebugLevel)) &&
         (printk("=============================================================================\n"),
         0 < DebugLevel)) {
        printk(&_LC371,uVar1);
      }
      puVar2 = auStack_2f7;
      pcVar3 = (char *)((int)param_1 + (short)uVar1 * 0xc4 + 0x794eae);
      iVar4 = DebugLevel;
      do {
        if (0 < iVar4) {
          printk("         %s : %3d, %3d, %3d, %3d                               \n",puVar2,
                 (int)pcVar3[-1],(int)*pcVar3,(int)pcVar3[1],(int)pcVar3[2]);
          iVar4 = DebugLevel;
        }
        puVar2 = puVar2 + 0xf;
        pcVar3 = pcVar3 + 4;
      } while (puVar2 != &stack0xffffffe8);
      if (0 < iVar4) {
        printk("-----------------------------------------------------------------------------\n");
        return 1;
      }
      return 1;
    }
  }
  return 0;
}


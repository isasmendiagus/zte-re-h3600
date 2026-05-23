// module: mt7915.ko
// function: HQA_HIFTestSetRxData @ 0x2741a4
// size: 300 bytes
//

undefined4 HQA_HIFTestSetRxData(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(param_3 + 0xc);
  uVar1 = *(ushort *)(param_3 + 8);
  uVar2 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  if (*(char *)(param_1 + 0xa3baf8) == '\0') goto LAB_0027422c;
  if (DebugLevel < 3) {
    if (uVar2 == 0) goto LAB_0027422c;
LAB_0027420c:
    uVar4 = 0;
    iVar3 = DebugLevel;
    do {
      if (2 < iVar3) {
        printk(&_LC67,*(undefined1 *)(param_3 + 0x10 + uVar4));
        iVar3 = DebugLevel;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar2);
  }
  else {
    printk("%s: RxExpect Dump(%u): ","HQA_HIFTestSetRxData",uVar2);
    iVar3 = DebugLevel;
    if (uVar2 != 0) goto LAB_0027420c;
  }
  if (2 < iVar3) {
    printk(&_LC18);
  }
LAB_0027422c:
  LoopBack_ExpectRx(param_1,uVar2,param_3 + 0x10);
  FUN_0026cdd0(param_3,param_2,2,0);
  if (0 < DebugLevel) {
    printk("%s: len:%u, rx_len:%u\n","HQA_HIFTestSetRxData",uVar1 << 8 | uVar1 >> 8,uVar2);
  }
  return 0;
}


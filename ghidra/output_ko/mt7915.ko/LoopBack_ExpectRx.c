// module: mt7915.ko
// function: LoopBack_ExpectRx @ 0x28d318
// size: 244 bytes
//

void LoopBack_ExpectRx(int param_1,uint param_2,void *param_3)

{
  int iVar1;
  int iVar2;
  
  if (0xf000 < param_2) {
    if (DebugLevel < 3) {
      param_2 = 0xf000;
    }
    else {
      printk("%s, max length is %d\n","LoopBack_ExpectRx",0xf000);
      param_2 = 0xf000;
    }
  }
  os_move_mem((void *)(param_1 + 0xa68b58),param_3,param_2);
  iVar1 = DebugLevel;
  *(uint *)(param_1 + 0xa59b54) = param_2;
  if (2 < iVar1) {
    printk("%s, Length = %d\n","LoopBack_ExpectRx",param_2);
    iVar1 = DebugLevel;
  }
  iVar2 = 0;
  do {
    if (2 < iVar1) {
      printk("TXD(TXWI) %d 0x%08lX\n",iVar2,*(undefined4 *)(param_1 + 0xa68b58 + iVar2 * 4));
      iVar1 = DebugLevel;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x14);
  if (2 < iVar1) {
    printk(&_LC18,"LoopBack_ExpectRx");
    return;
  }
  return;
}


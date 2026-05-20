// module: mt7915.ko
// function: rlmCalCacheStatus @ 0x1c88fc
// size: 268 bytes
//

void rlmCalCacheStatus(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (0 < DebugLevel) {
    if ((*param_1 & 1) == 0) {
      uVar2 = 0x46;
    }
    else {
      uVar2 = 0x54;
    }
    printk("TxLPF Cal Done::(%c)\n",uVar2,param_3,*param_1,param_4);
    if (0 < DebugLevel) {
      if ((*param_1 & 2) == 0) {
        uVar2 = 0x46;
      }
      else {
        uVar2 = 0x54;
      }
      printk("TxIQ Cal Done::(%c)\n",uVar2);
      if (0 < DebugLevel) {
        if ((*param_1 & 4) == 0) {
          uVar2 = 0x46;
        }
        else {
          uVar2 = 0x54;
        }
        printk("TxDC Cal Done::(%c)\n",uVar2);
        if (0 < DebugLevel) {
          if ((*param_1 & 8) == 0) {
            uVar2 = 0x46;
          }
          else {
            uVar2 = 0x54;
          }
          printk("RxFI Cal Done::(%c)\n",uVar2);
        }
      }
    }
  }
  iVar3 = 0;
  do {
    if (0 < DebugLevel) {
      uVar1 = 1 << (iVar3 + 4U & 0xff);
      if (uVar1 == (*param_1 & uVar1)) {
        uVar2 = 0x54;
      }
      else {
        uVar2 = 0x46;
      }
      printk("RxFD(%d) Cal Done::(%c)\n",iVar3,uVar2,uVar1,param_4);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 9);
  return;
}


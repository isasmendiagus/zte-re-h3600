// module: mt7915.ko
// function: pci_ate_init @ 0x27fcf4
// size: 160 bytes
//

undefined4 pci_ate_init(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (2 < DebugLevel) {
    printk(&_LC65,"pci_ate_init",param_3,DebugLevel,param_4);
  }
  if ((*(int *)(param_1 + 0xa3abcc) == 0) &&
     (iVar1 = os_alloc_mem(param_1,param_1 + 0xa3abcc,0x33ff), iVar1 != 0)) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: Allocate test packet fail at pakcet\n","pci_ate_init");
    return 1;
  }
  chip_interrupt_enable(param_1);
  return 0;
}


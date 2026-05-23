// module: mt7915.ko
// function: ZTE_Sta_Blacklist_Show @ 0x161190
// size: 348 bytes
//

undefined4 ZTE_Sta_Blacklist_Show(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  void *local_1c [2];
  
  local_1c[0] = (void *)0x0;
  iVar5 = *param_1;
  os_alloc_mem(0,local_1c,0x408);
  if (local_1c[0] == (void *)0x0) {
    uVar2 = 0;
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","ZTE_Sta_Blacklist_Show");
    }
  }
  else {
    __memzero(local_1c[0],0x408);
    memmove(local_1c[0],(void *)((int)param_1 + *(int *)(iVar5 + 0x3c) * 0x5834 + 0x2bc2b2),0x408);
    if (*(int *)((int)local_1c[0] + 4) == 0) {
      printk("The MAP Blacklist is empty!\n");
    }
    else {
      printk("===============  Access Control List  ===============\n");
      uVar3 = 0;
      if (*(int *)((int)local_1c[0] + 4) != 0) {
        do {
          uVar4 = uVar3 + 1;
          iVar5 = 0;
          printk("Entry #%02d: ",uVar4);
          do {
            iVar1 = iVar5 + uVar3 * 8;
            iVar5 = iVar5 + 1;
            printk("%02X ",*(undefined1 *)((int)local_1c[0] + iVar1 + 8));
          } while (iVar5 != 6);
          printk(&_LC16);
          uVar3 = uVar4;
        } while (uVar4 < *(uint *)((int)local_1c[0] + 4));
      }
    }
    if (local_1c[0] != (void *)0x0) {
      os_free_mem();
    }
    uVar2 = 1;
  }
  return uVar2;
}


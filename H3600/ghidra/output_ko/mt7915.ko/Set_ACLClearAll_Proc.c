// module: mt7915.ko
// function: Set_ACLClearAll_Proc @ 0x2d6b8
// size: 568 bytes
//

undefined4 Set_ACLClearAll_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  void *local_14;
  
  iVar3 = *param_1;
  local_14 = (void *)0x0;
  cVar1 = os_str_tol(param_2,0,10);
  if (cVar1 == '\x01') {
    os_alloc_mem(0,&local_14,0x408);
    if (local_14 == (void *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: Allocate memory fail!!!\n","Set_ACLClearAll_Proc");
        return 0;
      }
      return 0;
    }
    __memzero(local_14,0x408);
    memmove(local_14,(void *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb671),0x408);
    iVar2 = *(int *)((int)local_14 + 4);
    if (iVar2 == 0) {
      if ((1 < DebugLevel) && (printk("The Access Control List is empty!\n"), 1 < DebugLevel)) {
        printk("No need to clear the Access Control List!\n");
      }
      if (local_14 != (void *)0x0) {
        os_free_mem();
        return 1;
      }
    }
    else {
      do {
        __memzero((void *)((int)local_14 + iVar2 * 8),6);
        iVar2 = *(int *)((int)local_14 + 4) + -1;
        *(int *)((int)local_14 + 4) = iVar2;
      } while (iVar2 != 0);
      __memzero((char *)((int)param_1 +
                        (int)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" +
                             *(int *)(iVar3 + 0x3c) * 0x5834 + 0x31)),0x408);
      memmove((void *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb671),local_14,0x408);
      ApUpdateAccessControlList(param_1,*(undefined1 *)(iVar3 + 0x3c));
      if (local_14 != (void *)0x0) {
        os_free_mem();
      }
      if (2 < DebugLevel) {
        printk("Set::%s(Policy=%u, Entry#=%u)\n","Set_ACLClearAll_Proc",
               *(undefined4 *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb671),
               *(undefined4 *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb675));
      }
    }
  }
  else {
    if (cVar1 != '\0') {
      return 0;
    }
    if ((1 < DebugLevel) && (printk("Your input is 0!\n"), 1 < DebugLevel)) {
      printk("The Access Control List will be kept unchanged!\n");
      return 1;
    }
  }
  return 1;
}


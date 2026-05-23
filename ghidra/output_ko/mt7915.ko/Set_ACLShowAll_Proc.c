// module: mt7915.ko
// function: Set_ACLShowAll_Proc @ 0x2d42c
// size: 648 bytes
//

undefined4 Set_ACLShowAll_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *local_1c;
  
  iVar4 = *param_1;
  local_1c = (int *)0x0;
  cVar1 = os_str_tol(param_2,0,10);
  if (cVar1 == '\x01') {
    os_alloc_mem(0,&local_1c,0x408);
    if (local_1c == (int *)0x0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: Allocate memory fail!!!\n","Set_ACLShowAll_Proc");
      return 0;
    }
    __memzero(local_1c,0x408);
    memmove(local_1c,(void *)((int)param_1 + *(int *)(iVar4 + 0x3c) * 0x5834 + 0x2bb671),0x408);
    iVar4 = local_1c[1];
    if (iVar4 == 0) {
      if (1 < DebugLevel) {
        printk("The Access Control List is empty!\n");
      }
    }
    else {
      if (2 < DebugLevel) {
        printk("=============== Access Control Policy ===============\n");
        if (((2 < DebugLevel) && (printk("Policy is %u : ",*local_1c), 2 < DebugLevel)) &&
           (printk(&_LC241,*(undefined4 *)(pACL_PolicyMessage + *local_1c * 4)), 2 < DebugLevel)) {
          printk("===============  Access Control List  ===============\n");
        }
        iVar4 = local_1c[1];
      }
      if (iVar4 != 0) {
        uVar2 = 0;
        do {
          uVar5 = uVar2 + 1;
          if (2 < DebugLevel) {
            printk("Entry #%02d: ",uVar5);
          }
          iVar3 = 0;
          iVar4 = DebugLevel;
          do {
            if (2 < iVar4) {
              printk("%02X ",*(undefined1 *)((int)local_1c + iVar3 + uVar2 * 8 + 8));
              iVar4 = DebugLevel;
            }
            iVar3 = iVar3 + 1;
          } while (iVar3 != 6);
          if (2 < iVar4) {
            printk(&_LC220);
          }
          uVar2 = uVar5;
        } while (uVar5 < (uint)local_1c[1]);
      }
    }
    os_free_mem(local_1c);
  }
  else {
    if (cVar1 != '\0') {
      return 0;
    }
    if ((1 < DebugLevel) && (printk("Your input is 0!\n"), 1 < DebugLevel)) {
      printk("The Access Control List will not be dumped!\n");
      return 1;
    }
  }
  return 1;
}


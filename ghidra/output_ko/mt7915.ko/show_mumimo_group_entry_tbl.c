// module: mt7915.ko
// function: show_mumimo_group_entry_tbl @ 0x17fe4c
// size: 1576 bytes
//

void show_mumimo_group_entry_tbl(int param_1,int param_2)

{
  char cVar1;
  char *__s;
  size_t __n;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint local_48;
  undefined1 auStack_41 [29];
  
  if (param_2 == 0) {
    return;
  }
  cVar1 = delimitcnt(param_2,&_LC251);
  if (1 < (byte)(cVar1 + 1U)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("Num of Input Parameters Wrong\n");
    return;
  }
  __s = (char *)rstrtok(param_2,&_LC251);
  if (__s == (char *)0x0) {
    iVar3 = 0;
    uVar2 = 0;
  }
  else {
    do {
      __n = strlen(__s);
      memcpy(auStack_41,__s,__n);
      uVar2 = os_str_tol(__s,0,10);
      __s = (char *)rstrtok(0,&_LC251);
    } while (__s != (char *)0x0);
    uVar2 = uVar2 & 0xffff;
    if (0x1ff < uVar2) {
      if (DebugLevel < 0) {
        return;
      }
      printk("Group Entry Idx is Wrong\n");
      return;
    }
    iVar3 = uVar2 << 4;
  }
  cVar1 = *(char *)(param_1 + 0x795a5c);
  uVar4 = iVar3 + *(int *)(param_1 + 0x795a58);
  if (0xdfffffff < uVar4) {
    FUN_0017f59c(param_1);
  }
  if (cVar1 != '\0') {
    return;
  }
  if (0 < DebugLevel) {
    printk("MURU MUM GROUP TABLE ENTRY: GROUP IDX = %d\n",uVar2);
  }
  local_48 = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar4,&local_48);
  uVar2 = local_48;
  if (0 < DebugLevel) {
    printk("|-DW0 (Addr: 0x%08X)(Value: 0x%08X)\n",uVar4,local_48);
    if (DebugLevel < 1) {
LAB_001803b0:
      if (DebugLevel < 1) {
LAB_00180430:
        if ((0 < DebugLevel) &&
           (printk("| |-u1DlVld      = %u\n",(uVar2 << 1) >> 0x1f), 0 < DebugLevel)) {
          printk("| |-u1UlVld      = %u\n",uVar2 >> 0x1f);
        }
      }
      else {
        printk("| |-u1PFIDUser0  = %u\n",(uVar2 << 0x12) >> 0x1b);
        if (0 < DebugLevel) {
          printk("| |-u1PFIDUser1  = %u\n",(uVar2 << 0xd) >> 0x1b);
LAB_001803f0:
          if ((0 < DebugLevel) &&
             (printk("| |-u1PFIDUser2  = %u\n",(uVar2 << 8) >> 0x1b), 0 < DebugLevel)) {
            printk("| |-u1PFIDUser3  = %u\n",(uVar2 << 3) >> 0x1b);
            goto LAB_00180430;
          }
        }
      }
    }
    else {
      printk("| |-u1NumUser    = %u\n",uVar2 & 3);
      if (0 < DebugLevel) {
        printk("| |-u1DlGi       = %u\n",(uVar2 << 0x1c) >> 0x1e);
        if (DebugLevel < 1) goto LAB_001803f0;
        printk("| |-u1UlGi       = %u\n",(uVar2 << 0x1a) >> 0x1e);
        if (0 < DebugLevel) {
          printk("| |-u1Ax         = %u\n",(uVar2 << 0x17) >> 0x1f);
          goto LAB_001803b0;
        }
      }
    }
  }
  local_48 = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar4 + 4,&local_48);
  uVar2 = local_48;
  if (0 < DebugLevel) {
    printk("|-DW1 (Addr: 0x%08X)(Value: 0x%08X)\n",uVar4 + 4,local_48);
    if (0 < DebugLevel) {
      printk("| |-u1RuAlloc    = %u\n",uVar2 & 0xff);
      if (((DebugLevel < 1) ||
          (printk("| |-u1NssUser0   = %u\n",(uVar2 << 0x16) >> 0x1e), DebugLevel < 1)) ||
         (printk("| |-u1NssUser1   = %u\n",(uVar2 << 0x14) >> 0x1e), DebugLevel < 1))
      goto LAB_0017ffdc;
      printk("| |-u1NssUser2   = %u\n",(uVar2 << 0x12) >> 0x1e);
    }
    if (0 < DebugLevel) {
      printk("| |-u1NssUser3   = %u\n",(uVar2 << 0x10) >> 0x1e);
    }
  }
LAB_0017ffdc:
  local_48 = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar4 + 8,&local_48);
  uVar2 = local_48;
  if (0 < DebugLevel) {
    printk("|-DW2 (Addr: 0x%08X)(Value: 0x%08X)\n",uVar4 + 8,local_48);
    if (DebugLevel < 1) {
LAB_001801f0:
      if ((0 < DebugLevel) &&
         (printk("| |-u1DlWfUser0  = %u\n",(uVar2 << 0xc) >> 0x1c), 0 < DebugLevel)) {
        printk("| |-u1DlWfUser1  = %u\n",(uVar2 << 8) >> 0x1c);
LAB_00180230:
        if ((0 < DebugLevel) &&
           (printk("| |-u1DlWfUser2  = %u\n",(uVar2 << 4) >> 0x1c), 0 < DebugLevel)) {
          printk("| |-u1DlWfUser3  = %u\n",uVar2 >> 0x1c);
        }
      }
    }
    else {
      printk("| |-u1DlMcsUser0 = %u\n",uVar2 & 0xf);
      if (0 < DebugLevel) {
        printk("| |-u1DlMcsUser1 = %u\n",(uVar2 << 0x18) >> 0x1c);
        if (DebugLevel < 1) goto LAB_00180230;
        printk("| |-u1DlMcsUser2 = %u\n",(uVar2 << 0x14) >> 0x1c);
        if (0 < DebugLevel) {
          printk("| |-u1DlMcsUser3 = %u\n",(uVar2 << 0x10) >> 0x1c);
          goto LAB_001801f0;
        }
      }
    }
  }
  local_48 = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar4 + 0xc,&local_48);
  uVar2 = local_48;
  if (DebugLevel < 1) {
    return;
  }
  printk("|-DW3 (Addr: 0x%08X)(Value: 0x%08X)\n",uVar4 + 0xc,local_48);
  if (0 < DebugLevel) {
    printk("| |-u1UlMcsUser0 = %u\n",uVar2 & 0xf);
    if (DebugLevel < 1) {
      return;
    }
    printk("| |-u1UlMcsUser1 = %u\n",(uVar2 << 0x18) >> 0x1c);
    if (DebugLevel < 1) goto LAB_0018010c;
    printk("| |-u1UlMcsUser2 = %u\n",(uVar2 << 0x14) >> 0x1c);
    if (DebugLevel < 1) {
      return;
    }
    printk("| |-u1UlMcsUser3 = %u\n",(uVar2 << 0x10) >> 0x1c);
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("| |-u1UlWfUser0  = %u\n",(uVar2 << 0xc) >> 0x1c);
  if (DebugLevel < 1) {
    return;
  }
  printk("| |-u1UlWfUser1  = %u\n",(uVar2 << 8) >> 0x1c);
LAB_0018010c:
  if ((0 < DebugLevel) && (printk("| |-u1UlWfUser2  = %u\n",(uVar2 << 4) >> 0x1c), 0 < DebugLevel))
  {
    printk("| |-u1UlWfUser3  = %u\n",uVar2 >> 0x1c);
  }
  return;
}


// module: mt7915.ko
// function: show_stainfo_proc @ 0xe3730
// size: 1972 bytes
//

undefined4 show_stainfo_proc(int param_1,undefined4 param_2)

{
  ushort uVar1;
  byte *__s;
  size_t sVar2;
  int *piVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  ushort *puVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined1 local_35;
  undefined4 local_34;
  undefined1 local_2e [4];
  undefined1 local_2a;
  undefined1 local_29;
  undefined4 *puVar15;
  
  local_34 = 0;
  local_35 = 0x3a;
  if (0 < DebugLevel) {
    printk("%s(): Input string=%s\n","show_stainfo_proc",param_2);
  }
  __s = (byte *)rstrtok(param_2,&local_35);
  if (__s == (byte *)0x0) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk("%s(): i= %d\n","show_stainfo_proc",0);
    return 0;
  }
  iVar8 = 0;
  do {
    if (0 < DebugLevel) {
      sVar2 = strlen((char *)__s);
      printk("%s(): token(len=%zu) =%s\n","show_stainfo_proc",sVar2,__s);
    }
    sVar2 = strlen((char *)__s);
    puVar6 = local_2e + iVar8;
    iVar8 = iVar8 + 1;
    if (sVar2 != 2) {
      return 0;
    }
    if (((&_ctype)[*__s] & 0x44) == 0) {
      return 0;
    }
    if (((&_ctype)[__s[1]] & 0x44) == 0) {
      return 0;
    }
    AtoH(__s,puVar6);
    __s = (byte *)rstrtok(0,&local_35);
  } while (__s != (byte *)0x0);
  if (DebugLevel < 1) {
    if (iVar8 != 6) {
      return 0;
    }
  }
  else {
    printk("%s(): i= %d\n","show_stainfo_proc",iVar8);
    if (iVar8 != 6) {
      return 0;
    }
    if (0 < DebugLevel) {
      printk("\nAddr %02x:%02x:%02x:%02x:%02x:%02x\n",local_2e[0],local_2e[1],local_2e[2],
             local_2e[3],local_2a,local_29);
    }
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    piVar3 = (int *)MacTableLookup(param_1,local_2e);
    if (*(char *)(param_1 + 0x286285) != '\0') goto LAB_000e3848;
  }
  else if (*(char *)(param_1 + 0x286285) != '\0') {
    return 0;
  }
  piVar3 = (int *)MacTableLookup2(param_1,local_2e,0);
LAB_000e3848:
  if (piVar3 != (int *)0x0) {
    if (*piVar3 != 0) {
      printk(&_LC22);
      printk("EntryType : %d\n",*piVar3);
      printk("Entry Capability:\n");
      uVar4 = get_phymode_str(*(byte *)((int)piVar3 + 0xbf) >> 5);
      printk("\tPhyMode:%-10s\n",uVar4);
      uVar4 = get_bw_str(((uint)*(ushort *)((int)piVar3 + 0xbe) << 0x17) >> 0x1e);
      printk("\tBW:%-6s\n",uVar4);
      printk("\tDataRate:\n");
      if (*(byte *)((int)piVar3 + 0xbf) < 0x80) {
        printk(" %-6d",*(byte *)((int)piVar3 + 0xbe) & 0x3f);
      }
      else {
        printk("%dS-M%d",((int)(*(byte *)((int)piVar3 + 0xbe) & 0x3f) >> 4) + 1,
               *(byte *)((int)piVar3 + 0xbe) & 0xf);
      }
      printk(" %-6d",((uint)*(byte *)((int)piVar3 + 0xbf) << 0x1e) >> 0x1f);
      printk(" %-6d\n",((uint)*(byte *)((int)piVar3 + 0xbf) << 0x1d) >> 0x1f);
      printk("Entry Operation Features\n");
      printk("\t%-4s%-4s%-4s%-4s%-8s%-7s%-7s%-7s%-10s%-6s%-6s%-6s%-6s%-7s%-7s\n",&_LC338,&_LC617,
             &_LC339,&_LC618,"MIMOPS","RSSI0","RSSI1","RSSI2",&_LC623,&_LC624,&_LC625,&_LC626,
             &_LC627,&_LC628,&_LC629);
      local_34 = 0;
      getRate((short)piVar3[0x2f]);
      printk("\t%-4d",(short)piVar3[0x3e]);
      printk(&_LC347,(char)piVar3[0x39]);
      printk(&_LC347,(char)piVar3[0x2be]);
      printk(&_LC347,piVar3[0x2d] & 1);
      printk(&_LC631,(char)piVar3[0x344]);
      printk(&_LC632,(int)(char)piVar3[0x43]);
      printk(&_LC632,(int)*(char *)((int)piVar3 + 0x10d));
      printk(&_LC632,(int)*(char *)((int)piVar3 + 0x10e));
      uVar4 = get_phymode_str(*(byte *)((int)piVar3 + 0xbd) >> 5);
      printk("%-10s",uVar4);
      uVar4 = get_bw_str(((uint)*(ushort *)(piVar3 + 0x2f) << 0x17) >> 0x1e);
      printk(&_LC634,uVar4);
      if (*(byte *)((int)piVar3 + 0xbd) < 0x80) {
        printk(&_LC348,*(byte *)(piVar3 + 0x2f) & 0x3f);
      }
      else {
        printk("%dS-M%d",((int)(*(byte *)(piVar3 + 0x2f) & 0x3f) >> 4) + 1,
               *(byte *)(piVar3 + 0x2f) & 0xf);
      }
      printk(&_LC348,((uint)*(byte *)((int)piVar3 + 0xbd) << 0x1e) >> 0x1f);
      printk(&_LC348,((uint)*(byte *)((int)piVar3 + 0xbd) << 0x1d) >> 0x1f);
      printk(&_LC632,piVar3[0x2c2] - piVar3[0x2ba]);
      printk(&_LC632,local_34);
      iVar8 = piVar3[0x2dd];
      iVar9 = piVar3[0x2dc];
      if (iVar8 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = __aeabi_uidiv((iVar8 - iVar9) * 100,iVar8);
      }
      printk("%-10d, %d, %d%%\n",iVar9,iVar8,uVar4);
      printk(&_LC22);
      uVar1 = *(ushort *)(piVar3 + 0x38);
      uVar5 = HcGetMaxStaNum(param_1);
      if (uVar5 < uVar1) {
        printk(&_LC636,0x2248);
        dump_stack();
      }
      uVar1 = *(ushort *)(piVar3 + 0x38);
      iVar10 = param_1 + 0x1c0;
      printk("Entry TxRx Info\n");
      iVar8 = (uint)uVar1 * 0x620;
      iVar9 = param_1 + iVar8;
      printk("\tEntryType : %d\n",*(undefined4 *)(iVar9 + 0x2f6a0));
      printk("\tHookingWdev : %p\n",*(undefined4 *)(iVar9 + 0x2f6a4));
      printk("\tIndexing : FuncTd=%d, WCID=%d\n",*(undefined1 *)(iVar9 + 0x2f6aa),
             *(undefined2 *)(iVar10 + iVar8 + 0x2f4e8));
      printk("Entry TxRx Features\n");
      printk("\tIsCached, PortSecured, PsMode, LockTx, VndAth\n");
      printk("\t%d\t%d\t%d\t%d\t%d\n",*(undefined1 *)(iVar9 + 0x2f761),
             *(undefined1 *)(iVar9 + 0x2f762),*(undefined1 *)(iVar9 + 0x2f763),
             *(undefined1 *)(iVar9 + 0x2f765),*(undefined1 *)(iVar9 + 0x2f760));
      printk("\t%-6s%-6s%-6s%-6s%-6s%-6s%-6s\n","TxQId","PktNum","QHead","QTail","EnQCap","DeQCap",
             "PktSeq");
      iVar13 = param_1 + iVar8 + 0x2f734;
      puVar12 = (ushort *)(param_1 + iVar8 + 0x2f6b2);
      puVar7 = (undefined4 *)(param_1 + iVar8 + 0x2f6cc);
      iVar8 = 0;
      do {
        _raw_spin_lock_bh(iVar13);
        puVar14 = puVar7 + -1;
        puVar15 = puVar7 + -2;
        uVar4 = *puVar7;
        puVar12 = puVar12 + 1;
        uVar5 = (uint)*puVar12;
        iVar11 = iVar8 + 1;
        puVar7 = puVar7 + 4;
        printk("\t%d %6d  %p  %6p %d %d %d\n",iVar8,uVar4,*puVar15,*puVar14,
               *(undefined1 *)(iVar9 + 0x2f758),*(undefined1 *)(iVar9 + 0x2f759),uVar5);
        _raw_spin_unlock_bh(iVar13);
        iVar13 = iVar13 + 4;
        iVar8 = iVar11;
      } while (iVar11 != 4);
      iVar8 = (uint)uVar1 * 0x620;
      iVar13 = iVar10 + iVar8 + 0x2f584;
      _raw_spin_lock_bh(iVar13);
      printk("\tpsQ %6d  %p  %p %d %d  NoQ:%d\n",*(undefined4 *)(iVar9 + 0x2f70c),
             *(undefined4 *)(iVar9 + 0x2f704),*(undefined4 *)(iVar9 + 0x2f708),
             *(undefined1 *)(iVar9 + 0x2f758),*(undefined1 *)(iVar9 + 0x2f759),
             *(undefined2 *)(iVar10 + iVar8 + 0x2f4f2),uVar5);
      _raw_spin_unlock_bh(iVar13);
      printk(&_LC22);
      return 1;
    }
    if (0 < DebugLevel) {
      printk("Invalid MAC address!\n");
      return 0;
    }
  }
  return 0;
}


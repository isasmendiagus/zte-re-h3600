// module: plat-zxylzb_9128S.ko
// function: shell_sym @ 0x10970
// size: 1592 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void shell_sym(void)

{
  undefined4 uVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  code *pcVar5;
  size_t sVar6;
  undefined1 *puVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  undefined1 **ppuVar11;
  int iVar12;
  undefined1 *local_138;
  undefined4 local_134;
  undefined1 *local_130;
  undefined1 auStack_128 [4];
  undefined1 auStack_124 [4];
  uint local_120;
  undefined1 *local_11c [5];
  undefined1 auStack_107 [227];
  
  pcVar9 = sym;
  if (sym_type == 3) {
    pcVar10 = (char *)0x0;
    uVar4 = 0;
  }
  else {
    pcVar2 = strchr(sym,0x3d);
    uVar1 = data_base;
    if (pcVar2 == (char *)0x0) {
      pcVar10 = (char *)0x0;
      uVar4 = 0;
    }
    else {
      pcVar10 = pcVar2 + 1;
      iVar3 = isint(pcVar10,data_base);
      if (iVar3 == 0) {
        printk("invalid data %s\n",pcVar9);
        return;
      }
      *pcVar2 = '\0';
      uVar4 = simple_strtoul(pcVar10,0,uVar1);
      pcVar9 = sym;
    }
  }
  iVar3 = isint(pcVar9,0x10);
  if (iVar3 == 0) {
    sVar6 = strlen(pcVar9);
    uVar8 = full_name_hash(pcVar9,sVar6);
    iVar3 = (uVar8 & 0xff) * 0x60;
    if (((uVar8 != *(uint *)(syms_cache + iVar3 + 4)) ||
        (iVar12 = strcmp(pcVar9,syms_cache + iVar3 + 8), iVar12 != 0 || iVar3 == -0x22284)) ||
       (pcVar5 = *(code **)(syms_cache + iVar3), pcVar5 == (code *)0x0)) {
      pcVar5 = (code *)kallsyms_lookup_name(pcVar9);
      if (pcVar5 == (code *)0x0) goto LAB_00010a94;
      sVar6 = strlen(pcVar9);
      if (sVar6 < 0x3f) {
        uVar8 = full_name_hash(pcVar9,sVar6);
        iVar3 = (uVar8 & 0xff) * 0x60;
        *(uint *)(syms_cache + iVar3 + 4) = uVar8;
        *(code **)(syms_cache + iVar3) = pcVar5;
        strcpy(syms_cache + iVar3 + 8,pcVar9);
        syms_cache[iVar3 + 0x48] = 0;
      }
    }
  }
  else {
    pcVar5 = (code *)simple_strtoul(pcVar9,0,0x10);
    if (pcVar5 < (code *)0xbf000001) {
LAB_00010a94:
      printk("unknown symbol \"%s\"\n",sym);
      return;
    }
  }
  if (v2p != 0) {
    puVar7 = (undefined1 *)((uint)pcVar5 >> 0x15);
    iVar3 = *(int *)(*(int *)(*(int *)(((uint)&local_138 & 0xffffe000) + 0xc) + 0x18c) + 0x24);
    local_138 = puVar7;
    printk("pgd 0x%x ,0x%x:pgd_val = 0x%x,index 0x%x\n",iVar3,iVar3 + (int)puVar7 * 8,
           *(undefined4 *)(iVar3 + (int)puVar7 * 8));
    printk("pud_val = 0x%lx\n",*(undefined4 *)(iVar3 + (int)puVar7 * 8));
    printk("pmd_val = 0x%lx\n",*(undefined4 *)(iVar3 + (int)puVar7 * 8));
    uVar8 = (uint)((int)pcVar5 << 0xb) >> 0x17;
    iVar3 = (*(uint *)(iVar3 + (int)puVar7 * 8) & 0xfffff000) + 0x80000000;
    iVar12 = iVar3 + uVar8 * 4;
    printk("0x%x:pte_val = 0x%lx\n",iVar12,*(undefined4 *)(iVar3 + uVar8 * 4));
    uVar8 = *(uint *)(iVar12 + -0x800);
    if (uVar8 == 0) {
      printk("not mapped in pte\n");
    }
    else {
      printk("vaddr = %x, paddr = %x\n",pcVar5,(uVar8 & 0xfffff000) + ((uint)pcVar5 & 0xfff));
    }
  }
  switch(sym_type) {
  case 0:
    if (pcVar10 == (char *)0x0) {
      shell_dump_sym_data(pcVar5,0);
      return;
    }
    printk("sym %s set to %d(0x%.2x)\n",sym,uVar4 & 0xff,uVar4 & 0xff);
    DataSynchronizationBarrier(0xe);
    if (_kallsyms_lookup != (code *)0x0) {
      (*_kallsyms_lookup)();
    }
    *pcVar5 = SUB41(uVar4,0);
    break;
  case 1:
    if (pcVar10 == (char *)0x0) {
      shell_dump_sym_data(pcVar5,1);
      return;
    }
    printk("sym %s set to %d(0x%.4x)\n",sym,uVar4 & 0xffff,uVar4 & 0xffff);
    DataSynchronizationBarrier(0xe);
    if (_kallsyms_lookup != (code *)0x0) {
      (*_kallsyms_lookup)();
    }
    *(short *)pcVar5 = (short)uVar4;
    break;
  case 2:
    if (pcVar10 == (char *)0x0) {
      shell_dump_sym_data(pcVar5,2);
      return;
    }
    printk("sym %s set to %d(0x%.8x)\n",sym,uVar4,uVar4);
    DataSynchronizationBarrier(0xe);
    if (_kallsyms_lookup != (code *)0x0) {
      (*_kallsyms_lookup)();
    }
    *(uint *)pcVar5 = uVar4;
    break;
  case 3:
    if (func_no_check == 0) {
      local_138 = auStack_107;
      iVar3 = kallsyms_lookup(pcVar5,&local_120,auStack_124,auStack_128);
      if (((iVar3 == 0) || (local_120 < 5)) || (((uint)pcVar5 & 3) != 0)) {
        printk("symbol %s is not a function\n",sym);
        return;
      }
    }
    if (func_param == (char *)0x0) {
switchD_00010de8_default:
      printk("call func %s\n",sym);
      (*pcVar5)();
    }
    else {
      iVar3 = 0;
      pcVar9 = func_param;
      ppuVar11 = local_11c;
      do {
        pcVar10 = strchr(pcVar9,0x2c);
        if (pcVar10 == (char *)0x0) {
          iVar12 = iVar3;
          if (*pcVar9 != '\0') {
            iVar12 = iVar3 + 1;
            puVar7 = (undefined1 *)simple_strtoul(pcVar9,0,0x10);
            local_11c[iVar3] = puVar7;
          }
          switch(iVar12) {
          case 1:
            printk("call func %s,with p %x\n",sym,local_11c[0]);
            (*pcVar5)(local_11c[0]);
            return;
          case 2:
            printk("call func %s,with p %x,%x\n",sym,local_11c[0],local_11c[1]);
            (*pcVar5)(local_11c[0],local_11c[1]);
            return;
          case 3:
            local_138 = local_11c[2];
            printk("call func %s,with p %x,%x,%x\n",sym,local_11c[0],local_11c[1]);
            (*pcVar5)(local_11c[0],local_11c[1],local_11c[2]);
            return;
          case 4:
            local_138 = local_11c[2];
            local_134 = local_11c[3];
            printk("call func %s,with p %x,%x,%x,%x\n",sym,local_11c[0],local_11c[1]);
            (*pcVar5)(local_11c[0],local_11c[1],local_11c[2],local_11c[3]);
            return;
          case 5:
            goto switchD_00010de8_caseD_5;
          default:
            goto switchD_00010de8_default;
          }
        }
        *pcVar10 = '\0';
        iVar3 = iVar3 + 1;
        puVar7 = (undefined1 *)simple_strtoul(pcVar9,0,0x10);
        *ppuVar11 = puVar7;
        pcVar9 = pcVar10 + 1;
        ppuVar11 = ppuVar11 + 1;
      } while (iVar3 != 5);
switchD_00010de8_caseD_5:
      local_138 = local_11c[2];
      local_134 = local_11c[3];
      local_130 = local_11c[4];
      printk("call func %s,with p %x,%x,%x,%x,%x\n",sym,local_11c[0],local_11c[1]);
      local_138 = local_11c[4];
      (*pcVar5)(local_11c[0],local_11c[1],local_11c[2],local_11c[3]);
    }
    break;
  default:
    printk("sym %s address at 0x%.8x\n",sym,pcVar5);
    return;
  case 5:
    __print_symbol("address info: %s\n",pcVar5);
    return;
  }
  return;
}


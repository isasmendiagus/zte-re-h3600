// module: plat-zxylzb_9128S.ko
// function: dump_task_info @ 0x12b94
// size: 1288 bytes
//

void dump_task_info(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  uint local_70 [20];
  
  iVar1 = find_task_by_vpid();
  if (iVar1 == 0) {
    return;
  }
  iVar2 = get_task_full_path_constprop_9();
  if (iVar2 < 1) {
    puVar5 = (undefined1 *)(iVar1 + 0x2d8);
  }
  else {
    puVar5 = &task_path;
  }
  printk("task %d , name %s stack %.8x ",param_1,puVar5,*(undefined4 *)(iVar1 + 4));
  if (*(int *)(iVar1 + 0x18c) == 0) {
    printk(&_LC25);
  }
  else {
    printk("pgd %.8x\n",*(undefined4 *)(*(int *)(iVar1 + 0x18c) + 0x24));
  }
  iVar2 = *(int *)(iVar1 + 0x2d0);
  printk("cap_inheritable: %.8x\n",*(undefined4 *)(iVar2 + 0x28));
  printk("cap_permitted: %.8x\n",*(undefined4 *)(iVar2 + 0x30));
  printk("cap_effective: %.8x\n",*(undefined4 *)(iVar2 + 0x38));
  printk("cap_bset: %.8x\n",*(undefined4 *)(iVar2 + 0x40));
  iVar2 = *(int *)(iVar1 + 4);
  if (*(int *)(((uint)&local_80 & 0xffffe000) + 0xc) == iVar1) {
    printk("it is current task\n");
  }
  printk("thread at %.8x,kernel context:\n",iVar2);
  local_80 = *(undefined4 *)(iVar2 + 0x38);
  printk("e1 : %08x  e0 : %08x  pc : %08x  sp : %08x\n",*(undefined4 *)(iVar2 + 0x44),
         *(undefined4 *)(iVar2 + 0x40),*(undefined4 *)(iVar2 + 0x3c));
  local_80 = *(undefined4 *)(iVar2 + 0x28);
  printk("fp : %08x  sl : %08x  r9 : %08x  r8 : %08x\n",*(undefined4 *)(iVar2 + 0x34),
         *(undefined4 *)(iVar2 + 0x30),*(undefined4 *)(iVar2 + 0x2c));
  local_80 = *(undefined4 *)(iVar2 + 0x18);
  printk("r7 : %08x  r6 : %08x  r5 : %08x  r4 : %08x\n",*(undefined4 *)(iVar2 + 0x24),
         *(undefined4 *)(iVar2 + 0x20),*(undefined4 *)(iVar2 + 0x1c));
  printk("kernel backtrace:\n");
  show_stack(iVar1,0);
  if (*(int *)(iVar1 + 0x18c) != 0) {
    iVar6 = *(int *)(iVar1 + 4);
    iVar2 = 0;
    printk("user context:\n");
    local_80 = *(undefined4 *)(iVar6 + 0x1fe4);
    local_7c = *(undefined4 *)(iVar6 + 0x1fe0);
    local_78 = *(undefined4 *)(iVar6 + 0x1fdc);
    printk("pc : [<%08lx>]    lr : [<%08lx>]    psr: %08lx\nsp : %08lx  ip : %08lx  fp : %08lx\n",
           *(undefined4 *)(iVar6 + 0x1fec),*(undefined4 *)(iVar6 + 0x1fe8),
           *(undefined4 *)(iVar6 + 0x1ff0));
    printk("r10: %08lx  r9 : %08lx  r8 : %08lx\n",*(undefined4 *)(iVar6 + 0x1fd8),
           *(undefined4 *)(iVar6 + 0x1fd4),*(undefined4 *)(iVar6 + 0x1fd0));
    local_80 = *(undefined4 *)(iVar6 + 0x1fc0);
    printk("r7 : %08lx  r6 : %08lx  r5 : %08lx  r4 : %08lx\n",*(undefined4 *)(iVar6 + 0x1fcc),
           *(undefined4 *)(iVar6 + 0x1fc8),*(undefined4 *)(iVar6 + 0x1fc4));
    local_80 = *(undefined4 *)(iVar6 + 0x1fb0);
    printk("r3 : %08lx  r2 : %08lx  r1 : %08lx  r0 : %08lx\n",*(undefined4 *)(iVar6 + 0x1fbc),
           *(undefined4 *)(iVar6 + 0x1fb8),*(undefined4 *)(iVar6 + 0x1fb4));
    iVar6 = *(int *)(iVar1 + 0x18c);
    printk("start_code %08lx\n",*(undefined4 *)(iVar6 + 0x80));
    printk("end_code %08lx\n",*(undefined4 *)(iVar6 + 0x84));
    printk("start_data %08lx\n",*(undefined4 *)(iVar6 + 0x88));
    printk("end_data %08lx\n",*(undefined4 *)(iVar6 + 0x8c));
    printk("start_brk %08lx\n",*(undefined4 *)(iVar6 + 0x90));
    printk("brk %08lx\n",*(undefined4 *)(iVar6 + 0x94));
    printk("start_stack %08lx\n",*(undefined4 *)(iVar6 + 0x98));
    printk("arg_start %08lx\n",*(undefined4 *)(iVar6 + 0x9c));
    printk("arg_end %08lx\n",*(undefined4 *)(iVar6 + 0xa0));
    printk("env_start %08lx\n",*(undefined4 *)(iVar6 + 0xa4));
    printk("env_end %08lx\n",*(undefined4 *)(iVar6 + 0xa8));
    my_dump_vma(iVar1);
    uVar10 = *(uint *)(*(int *)(iVar1 + 0x18c) + 0x98);
    uVar7 = *(uint *)(*(int *)(iVar1 + 4) + 0x1fdc);
    do {
      uVar3 = user_va2pa(iVar1,uVar7);
      if (uVar3 == 0 || (uVar7 == 0 || uVar10 <= uVar7)) {
LAB_00013060:
        if (iVar2 == 0) goto LAB_00012cf4;
        break;
      }
      uVar9 = uVar3 & 0xfffff000;
      if (uVar9 < 8) {
        iVar6 = user_va2pa(iVar1,uVar7 - 8);
        if (iVar6 == 0) goto LAB_00013060;
        iVar6 = *(int *)(iVar6 + -0x80000000);
      }
      else {
        iVar6 = *(int *)(uVar3 + 0x7ffffff8);
      }
      if (uVar7 + 4 != iVar6) {
        printk("invalid stack\n");
        goto LAB_00013060;
      }
      iVar6 = iVar2;
      if (iVar2 == 0) {
        iVar6 = 1;
        local_70[0] = *(int *)(uVar3 + 0x80000000) - 0xc;
      }
      if (uVar9 < 4) {
        iVar8 = user_va2pa(iVar1,uVar7 - 4);
        iVar2 = iVar6;
        if (iVar8 != 0) {
          local_70[iVar6] = *(uint *)(iVar8 + -0x80000000);
          goto LAB_00012fd4;
        }
        goto LAB_00013060;
      }
      if (0xb < uVar9) {
        uVar7 = *(uint *)(uVar3 + 0x7ffffff4);
      }
      local_70[iVar6] = *(uint *)(uVar3 + 0x7ffffffc);
      if (uVar9 < 0xc) {
LAB_00012fd4:
        iVar2 = iVar6 + 1;
        iVar8 = user_va2pa(iVar1,uVar7 - 0xc);
        if (iVar8 == 0) goto LAB_00013060;
        uVar7 = *(uint *)(iVar8 + -0x80000000);
      }
      iVar2 = iVar6 + 1;
    } while (iVar2 < 0x14);
    iVar8 = 0;
    mytree = 0;
    iVar6 = build_func_usyms(iVar1);
    do {
      uVar7 = local_70[iVar8];
      iVar4 = mytree;
      if (uVar7 == 0) break;
      while (iVar4 != 0) {
        if (uVar7 < *(uint *)(iVar4 + 0xc)) {
          iVar4 = *(int *)(iVar4 + 8);
        }
        else {
          if (uVar7 < *(uint *)(iVar4 + 0x10)) goto LAB_00012ff8;
          iVar4 = *(int *)(iVar4 + 4);
        }
      }
      iVar4 = get_usyms_lib(iVar1,uVar7);
      if (iVar4 == 0) {
        printk("%.8x\n",uVar7);
      }
      else {
LAB_00012ff8:
        printk("%.8x %s+%.8x\n",uVar7,iVar4 + 0x14,uVar7 - *(int *)(iVar4 + 0xc));
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < iVar2);
    if (iVar6 != 0) {
      kfree(iVar6);
    }
  }
LAB_00012cf4:
  printk("open file:\n");
  dump_task_fd(iVar1);
  return;
}


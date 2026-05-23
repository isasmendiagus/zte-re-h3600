// module: plat-zxylzb_9128S.ko
// function: shellWriteProc @ 0x11058
// size: 1712 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint shellWriteProc(undefined4 param_1,uint param_2,uint param_3)

{
  undefined4 *puVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  size_t sVar7;
  int *piVar8;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  undefined4 uVar12;
  uint uVar13;
  undefined1 *puVar14;
  undefined4 uVar15;
  uint *puVar16;
  char *__s;
  char *pcVar17;
  undefined1 *local_40;
  char *local_3c;
  undefined4 *local_38;
  undefined4 *local_34;
  undefined4 local_30;
  uint local_2c;
  
  uVar5 = param_3;
  if (0x7e < param_3) {
    uVar5 = 0x7f;
  }
  uVar13 = *(uint *)(((uint)&local_40 & 0xffffe000) + 8);
  uVar10 = param_2 + uVar5;
  uVar11 = uVar10;
  if (!CARRY4(param_2,uVar5)) {
    uVar11 = uVar10 - (uVar13 + 1);
  }
  if (!CARRY4(param_2,uVar5) && uVar10 <= uVar13) {
    uVar13 = 0;
  }
  if (uVar13 == 0) {
    iVar4 = __copy_from_user(cmd_line,param_2,uVar5);
    if (iVar4 != 0) {
      return 0xfffffff2;
    }
  }
  else if (uVar5 != 0) {
    __memzero(cmd_line,uVar5,uVar11);
    return 0xfffffff2;
  }
  cmd_line[uVar5] = 0;
  proc_get_cmd(cmd_line);
  iVar4 = proc_argc;
  if (proc_argc < 2) {
switchD_0001115c_caseD_47:
    printk(&_LC0,
           "Usage: echo [OPTIONS] > /proc/tm/shell \nexample -f sym p1,p2,p3 \n        sym=1, set sym to 1 \n        sym, get sym value \nOptions:\n  -b,         data is byte\n  -w,         data is word , 2 bytes\n  -l,         data is dword , 4 bytes\n  -f,         data is function with check\n  -F,         data is function ,no check\n  -c,         data counts\n  -a,         get sym address\n  -s,         translate address to sym name\n  -d,         data base is dec, default is hex\n  -p,         pid, dec mode\n  -P,         pid\'s full path\n  -t,         vaddr to paddr\n  -h,         help\n"
          );
    return param_3;
  }
  sym_type = 2;
  func_no_check = 0;
  func_param = 0;
  pid_path = 0;
  v2p = 0;
  data_base = (undefined1 *)0x10;
  sym_pid = (undefined1 *)0xffffffff;
  data_cnt = 1;
  optreset = 1;
  optind = 1;
  sym = (char *)0x0;
  while (iVar2 = getopt(iVar4,(char **)proc_argv,"p:c:tFsadbwlfh?"), iVar2 != -1) {
    switch(iVar2) {
    case 0x46:
      func_no_check = 1;
      sym_type = 3;
      break;
    default:
      goto switchD_0001115c_caseD_47;
    case 0x61:
      sym_type = 4;
      break;
    case 0x62:
      sym_type = 0;
      break;
    case 99:
      uVar5 = simple_strtoul(optarg,0,data_base);
      data_cnt = uVar5 & 0xff;
      break;
    case 100:
      data_base = (undefined1 *)0xa;
      break;
    case 0x66:
      sym_type = 3;
      break;
    case 0x6c:
      sym_type = 2;
      break;
    case 0x70:
      sym_pid = (undefined1 *)simple_strtoul(optarg,0,10);
      break;
    case 0x73:
      sym_type = 5;
      break;
    case 0x74:
      v2p = 1;
      break;
    case 0x77:
      sym_type = 1;
    }
  }
  if (iVar4 <= optind) {
    printk("error: no symbol,%d/%d\n",optind,iVar4);
    return param_3;
  }
  __s = *(char **)(proc_argv + optind * 4);
  if (optind < iVar4 + -1) {
    func_param = *(undefined4 *)(proc_argv + optind * 4 + 4);
  }
  else {
    func_param = 0;
  }
  sym = __s;
  if ((int)sym_pid < 0) {
    shell_sym();
    return param_3;
  }
  if (sym_type == 3) {
    pcVar17 = (char *)0x0;
    uVar5 = 0;
    puVar14 = sym_pid;
  }
  else {
    local_40 = sym_pid;
    pcVar3 = strchr(__s,0x3d);
    if (pcVar3 == (char *)0x0) {
      pcVar17 = (char *)0x0;
      uVar5 = 0;
      puVar14 = local_40;
    }
    else {
      pcVar17 = pcVar3 + 1;
      local_40 = data_base;
      iVar4 = isint(pcVar17,data_base);
      if (iVar4 == 0) {
        printk("invalid data %s\n",__s,local_40);
        return param_3;
      }
      *pcVar3 = '\0';
      uVar5 = simple_strtoul(pcVar17);
      puVar14 = sym_pid;
      __s = sym;
    }
  }
  iVar4 = find_task_by_vpid(puVar14);
  if ((iVar4 == 0) || (*(int *)(iVar4 + 0x18c) == 0)) goto LAB_00011628;
  iVar2 = isint(__s,0x10);
  if (iVar2 == 0) {
    local_3c = (char *)(iVar4 + 0x2d8);
    sVar7 = strlen(__s);
    uVar11 = full_name_hash(__s,sVar7);
    puVar1 = (undefined4 *)((uVar11 & 0xff) * 0x60);
    if (uVar11 == *(uint *)(syms_cache + (int)(puVar1 + 1))) {
      local_40 = syms_cache;
      local_38 = puVar1;
      local_34 = &sym + (uVar11 & 0xff) * 0x18;
      iVar2 = strcmp(__s,syms_cache + (int)(puVar1 + 2));
      if (iVar2 != 0) goto LAB_000114a0;
      pcVar3 = local_40 + (int)(local_38 + 0x12);
      local_40 = local_40 + (int)local_38;
      local_38 = local_34;
      iVar2 = strcmp(local_3c,pcVar3);
      if (local_40 == (undefined1 *)0x0 || iVar2 != 0) goto LAB_000114a0;
      iVar2 = local_38[1];
LAB_00011568:
      if ((*(short *)(local_40 + 0x58) == 1) && (sym_type != 4)) {
        if (*(int *)(local_40 + 0x5c) == 1) {
          sym_type = 0;
        }
        else {
          sym_type = 1;
          if (*(int *)(local_40 + 0x5c) != 2) {
            sym_type = 2;
          }
        }
      }
      else {
        sym_type = 4;
      }
    }
    else {
LAB_000114a0:
      piVar8 = (int *)usyms_lookup_name(iVar4,__s,pid_path);
      if (piVar8 == (int *)0x0) goto LAB_00011628;
      iVar2 = *piVar8;
      if (iVar2 != 0) {
        local_2c = (uint)*(ushort *)((int)piVar8 + 6);
        local_30 = CONCAT22(local_30._2_2_,(short)piVar8[1]);
        sVar7 = strlen(__s);
        if (sVar7 < 0x3f) {
          uVar11 = full_name_hash(__s,sVar7);
          iVar6 = (uVar11 & 0xff) * 0x60;
          local_40 = syms_cache + iVar6;
          *(uint *)(syms_cache + iVar6 + 4) = uVar11;
          *(int *)(syms_cache + iVar6) = iVar2;
          strcpy(syms_cache + iVar6 + 8,__s);
          uVar9 = *(undefined4 *)(local_3c + 4);
          uVar12 = *(undefined4 *)(local_3c + 8);
          uVar15 = *(undefined4 *)(local_3c + 0xc);
          *(undefined4 *)(syms_cache + iVar6 + 0x48) = *(undefined4 *)local_3c;
          *(undefined4 *)(syms_cache + iVar6 + 0x4c) = uVar9;
          *(undefined4 *)(syms_cache + iVar6 + 0x50) = uVar12;
          *(undefined4 *)(syms_cache + iVar6 + 0x54) = uVar15;
          *(undefined4 *)(syms_cache + iVar6 + 0x58) = local_30;
          *(uint *)(syms_cache + iVar6 + 0x5c) = local_2c;
          if (local_40 != (undefined1 *)0x0) goto LAB_00011568;
        }
      }
    }
    iVar4 = user_va2pa(iVar4,iVar2);
  }
  else {
    iVar2 = simple_strtoul(__s,0,0x10);
    iVar6 = check_user_addr(iVar4,iVar2);
    if (iVar6 == 0) goto LAB_00011628;
    iVar4 = user_va2pa(iVar4,iVar2);
    if (iVar4 == 0) {
      printk("va %.8lx no pa\n",iVar2);
      goto LAB_00011628;
    }
  }
  if (iVar2 != 0) {
    puVar16 = (uint *)(iVar4 + -0x80000000);
    if (sym_type == 1) {
      if (pcVar17 != (char *)0x0) {
        printk("sym %s set to %d(0x%.4x)\n",sym,uVar5 & 0xffff,uVar5 & 0xffff);
        DataSynchronizationBarrier(0xe);
        if (_kallsyms_lookup != (code *)0x0) {
          (*_kallsyms_lookup)();
        }
        *(short *)puVar16 = (short)uVar5;
        return param_3;
      }
    }
    else {
      if (sym_type != 2) {
        if (sym_type != 0) {
          printk("sym %s va 0x%.8x pa 0x%.8x\n",sym);
          return param_3;
        }
        if (pcVar17 == (char *)0x0) {
          shell_dump_sym_data(puVar16,0);
          return param_3;
        }
        printk("sym %s set to %d(0x%.2x)\n",sym,uVar5 & 0xff,uVar5 & 0xff);
        DataSynchronizationBarrier(0xe);
        if (_kallsyms_lookup != (code *)0x0) {
          (*_kallsyms_lookup)();
        }
        *(char *)puVar16 = (char)uVar5;
        return param_3;
      }
      if (pcVar17 != (char *)0x0) {
        printk("sym %s set to %d(0x%.8x)\n",sym,uVar5,uVar5);
        DataSynchronizationBarrier(0xe);
        if (_kallsyms_lookup != (code *)0x0) {
          (*_kallsyms_lookup)();
        }
        *puVar16 = uVar5;
        return param_3;
      }
    }
    shell_dump_sym_data(puVar16);
    return param_3;
  }
LAB_00011628:
  printk("pid 0x%x unknown symbol \"%s\"\n",sym_pid,sym);
  return param_3;
}


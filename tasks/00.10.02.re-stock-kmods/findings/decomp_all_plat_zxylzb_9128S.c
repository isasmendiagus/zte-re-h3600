/* ============= FUNCTION: tm_set_onu_mac @ 00010000 ============= */

undefined4 tm_set_onu_mac(uint param_1,undefined1 *param_2)

{
  if (param_1 < 5 && param_2 != (undefined1 *)0x0) {
    *(uint *)(npp_base + (short)param_1 * 8 + 0x120) =
         (uint)(byte)param_2[3] << 0x10 | (uint)(byte)param_2[2] << 0x18 | (uint)(byte)param_2[5] |
         (uint)(byte)param_2[4] << 8;
    *(uint *)(npp_base + (short)param_1 * 8 + 0x124) = (uint)CONCAT11(*param_2,param_2[1]);
    return 0;
  }
  return 0xffffffff;
}


/* ============= FUNCTION: tm_get_onu_mac @ 0001008c ============= */

undefined4 tm_get_onu_mac(uint param_1,undefined1 *param_2)

{
  undefined4 uVar1;
  
  if (4 < param_1 || param_2 == (undefined1 *)0x0) {
    return 0xffffffff;
  }
  uVar1 = *(undefined4 *)(npp_base + (short)param_1 * 8 + 0x124);
  param_2[1] = (char)uVar1;
  *param_2 = (char)((uint)uVar1 >> 8);
  uVar1 = *(undefined4 *)(npp_base + (short)param_1 * 8 + 0x120);
  param_2[5] = (char)uVar1;
  param_2[2] = (char)((uint)uVar1 >> 0x18);
  param_2[3] = (char)((uint)uVar1 >> 0x10);
  param_2[4] = (char)((uint)uVar1 >> 8);
  return 0;
}


/* ============= FUNCTION: tm_get_tpid @ 00010118 ============= */

undefined4 tm_get_tpid(int param_1)

{
  return *(undefined4 *)(npp_base + param_1 * 4 + 0x9c);
}


/* ============= FUNCTION: zx_tm_init @ 00010138 ============= */

undefined4 zx_tm_init(void)

{
  printk("zx_tm_init start\n");
  printk("zx_tm_init end\n");
  return 0;
}


/* ============= FUNCTION: crc_16 @ 0001015c ============= */

uint crc_16(byte *param_1,int param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  
  if (param_2 != 0) {
    pbVar2 = param_1;
    do {
      pbVar1 = pbVar2 + 1;
      param_3 = ((uint)*(ushort *)(&crc16_tab + ((uint)*pbVar2 ^ param_3 >> 8) * 2) ^ param_3 << 8)
                & 0xffff;
      pbVar2 = pbVar1;
    } while (pbVar1 != param_1 + param_2);
  }
  return param_3;
}


/* ============= FUNCTION: crc_16_de @ 00010198 ============= */

uint crc_16_de(byte *param_1,int param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  
  if (param_2 != 0) {
    pbVar2 = param_1;
    do {
      pbVar1 = pbVar2 + -1;
      param_3 = ((uint)*(ushort *)(&crc16_tab + ((uint)*pbVar2 ^ param_3 >> 8) * 2) ^ param_3 << 8)
                & 0xffff;
      pbVar2 = pbVar1;
    } while (pbVar1 != param_1 + -param_2);
  }
  return param_3;
}


/* ============= FUNCTION: ether_crc_32 @ 000101d4 ============= */

uint ether_crc_32(byte *param_1,int param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  
  if (param_2 != 0) {
    pbVar2 = param_1;
    do {
      pbVar1 = pbVar2 + 1;
      param_3 = *(uint *)(crc32_table + ((*pbVar2 ^ param_3) & 0xff) * 4) ^ param_3 >> 8;
      pbVar2 = pbVar1;
    } while (pbVar1 != param_1 + param_2);
  }
  return ~param_3;
}


/* ============= FUNCTION: proc_parse_mac @ 00010210 ============= */

undefined4 proc_parse_mac(char *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined4 uStack_20;
  undefined1 auStack_1c [4];
  undefined1 auStack_18 [4];
  undefined1 auStack_14 [4];
  undefined1 auStack_10 [4];
  undefined1 auStack_c [4];
  
  iVar1 = sscanf(param_1,"%x:%x:%x:%x:%x:%x",&uStack_20,auStack_1c,auStack_18,auStack_14,auStack_10,
                 auStack_c);
  if (iVar1 == 6) {
    puVar4 = (undefined1 *)(param_2 + -1);
    puVar3 = &uStack_20;
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = (char)*puVar3;
      puVar3 = puVar3 + 1;
    } while (puVar4 != (undefined1 *)(param_2 + 5));
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: proc_parse_ip @ 00010288 ============= */

undefined4 proc_parse_ip(char *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined4 uStack_18;
  undefined1 auStack_14 [4];
  undefined1 auStack_10 [4];
  undefined1 auStack_c [4];
  
  iVar1 = sscanf(param_1,"%d.%d.%d.%d",&uStack_18,auStack_14,auStack_10,auStack_c);
  if (iVar1 == 4) {
    puVar4 = (undefined1 *)(param_2 + -1);
    puVar3 = &uStack_18;
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = (char)*puVar3;
      puVar3 = puVar3 + 1;
    } while (puVar4 != (undefined1 *)(param_2 + 3));
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


/* ============= FUNCTION: proc_get_cmd @ 000102f0 ============= */

void proc_get_cmd(byte *param_1)

{
  byte bVar1;
  size_t sVar2;
  char *pcVar3;
  byte *pbVar4;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  bool bVar9;
  byte *pbVar5;
  
  proc_argc = 1;
  if (param_1 == (byte *)0x0) {
    return;
  }
  sVar2 = strlen((char *)param_1);
  if (0 < (int)sVar2) {
    pbVar5 = param_1;
    do {
      pbVar4 = pbVar5 + 1;
      bVar1 = *pbVar5;
      bVar9 = 0xc < bVar1;
      if (bVar1 != 0xd) {
        bVar9 = bVar1 != 9;
      }
      if (!bVar9 || (bVar1 == 0xd || bVar1 == 10)) {
        *pbVar5 = 0x20;
      }
      pbVar5 = pbVar4;
    } while (pbVar4 != param_1 + sVar2);
  }
  iVar7 = 1;
  puVar8 = DAT_000103b0;
  do {
    uVar6 = (uint)*param_1;
    bVar1 = (&_ctype)[uVar6];
    while ((bVar1 & 0x20) != 0) {
      param_1 = param_1 + 1;
      uVar6 = (uint)*param_1;
      bVar1 = (&_ctype)[uVar6];
    }
    if (uVar6 == 0) {
      proc_argc = iVar7;
      return;
    }
    puVar8 = puVar8 + 1;
    *puVar8 = param_1;
    pcVar3 = strchr((char *)param_1,0x20);
    iVar7 = iVar7 + 1;
    if (pcVar3 == (char *)0x0) {
      proc_argc = iVar7;
      return;
    }
    *pcVar3 = '\0';
    param_1 = (byte *)(pcVar3 + 1);
  } while (iVar7 != 0x1e);
  proc_argc = iVar7;
  return;
}


/* ============= FUNCTION: getopt @ 000103b4 ============= */

int getopt(int ___argc,char **___argv,char *__shortopts)

{
  char *pcVar1;
  byte *pbVar2;
  uint __c;
  
  if ((optreset == 0) && (__c = (uint)*place_37758, __c != 0)) {
    pbVar2 = place_37758 + 1;
LAB_00010400:
    place_37758 = pbVar2;
    optopt = __c;
    if (__c == 0x3a) goto LAB_00010408;
  }
  else {
    optreset = 0;
    pcVar1 = ___argv[optind];
    if ((___argc <= optind) || (*pcVar1 != '-')) {
      place_37758 = &_LC2;
      optreset = 0;
      return -1;
    }
    __c = (uint)(byte)pcVar1[1];
    pbVar2 = (byte *)(pcVar1 + 2);
    optopt = __c;
    if (__c == 0x2d) {
      place_37758 = pbVar2;
      if (pcVar1[2] == '\0') {
        place_37758 = &_LC2;
        optind = optind + 1;
        optreset = 0;
        return -1;
      }
    }
    else {
      if (__c != 0) goto LAB_00010400;
      pbVar2 = &_LC2;
      place_37758 = &_LC2;
      pcVar1 = strchr(__shortopts,0x2d);
      if (pcVar1 == (char *)0x0) {
        return -1;
      }
      optopt = 0x2d;
    }
    __c = 0x2d;
  }
  pcVar1 = strchr(__shortopts,__c);
  if (pcVar1 != (char *)0x0) {
    if (pcVar1[1] == ':') {
      if (*pbVar2 == 0) {
        optind = optind + 1;
        if (___argc <= optind) {
          place_37758 = &_LC2;
          if (*__shortopts != ':') {
            printk("option requires an argument -- %c\n",__c);
            return 0x3f;
          }
          return 0x3a;
        }
        pbVar2 = (byte *)___argv[optind];
      }
      optarg = pbVar2;
      optind = optind + 1;
      place_37758 = &_LC2;
    }
    else {
      optarg = (byte *)0x0;
      if (*pbVar2 == 0) {
        optind = optind + 1;
      }
    }
    return optopt;
  }
LAB_00010408:
  if (*pbVar2 == 0) {
    optind = optind + 1;
  }
  if (*__shortopts != ':') {
    printk("unknown option -- %c\n",__c);
  }
  return 0x3f;
}


/* ============= FUNCTION: tm_proc_init @ 000105e8 ============= */

undefined4 tm_proc_init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  tm_proc_root = proc_mkdir(&_LC5,0,param_3,param_4,param_4);
  if (tm_proc_root != 0) {
    create_shell_proc();
    return 0;
  }
  printk("proc_mkdir tm failed");
  return 0xffffffff;
}


/* ============= FUNCTION: isint @ 00010630 ============= */

undefined4 isint(byte *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1 == (byte *)0x0) {
    return 0;
  }
  uVar1 = (uint)*param_1;
  if (uVar1 == 0x2d) {
    uVar1 = (uint)param_1[1];
    param_1 = param_1 + 1;
  }
  if (uVar1 == 0x30) {
    if ((param_1[1] & 0xdf) == 0x42) {
      uVar1 = (uint)param_1[2];
      param_2 = 2;
      param_1 = param_1 + 2;
    }
    else if ((param_1[1] & 0xdf) == 0x58) {
      uVar1 = (uint)param_1[2];
      param_2 = 0x10;
      param_1 = param_1 + 2;
    }
    else {
      param_2 = 8;
    }
  }
  while( true ) {
    uVar2 = uVar1 - 0x30;
    if (((&_ctype)[uVar1] & 0x44) == 0) {
      return 0;
    }
    if (9 < uVar2) {
      uVar2 = uVar1 - 0x57;
      if ((5 < uVar1 - 0x61) && (uVar2 = 0, uVar1 - 0x41 < 6)) {
        uVar2 = uVar1 - 0x37;
      }
    }
    if (param_2 <= (int)uVar2) break;
    param_1 = param_1 + 1;
    uVar1 = (uint)*param_1;
    if (uVar1 == 0) {
      return 1;
    }
  }
  return 0;
}


/* ============= FUNCTION: module_proc_open @ 000106f4 ============= */

void module_proc_open(undefined4 param_1,undefined4 param_2)

{
  single_open(param_2,shellReadProc,0);
  return;
}


/* ============= FUNCTION: shellReadProc @ 00010708 ============= */

void shellReadProc(undefined4 param_1)

{
  seq_printf(param_1,&_LC0,
             "Usage: echo [OPTIONS] > /proc/tm/shell \nexample -f sym p1,p2,p3 \n        sym=1, set sym to 1 \n        sym, get sym value \nOptions:\n  -b,         data is byte\n  -w,         data is word , 2 bytes\n  -l,         data is dword , 4 bytes\n  -f,         data is function with check\n  -F,         data is function ,no check\n  -c,         data counts\n  -a,         get sym address\n  -s,         translate address to sym name\n  -d,         data base is dec, default is hex\n  -p,         pid, dec mode\n  -P,         pid\'s full path\n  -t,         vaddr to paddr\n  -h,         help\n"
            );
  return;
}


/* ============= FUNCTION: shell_dump_sym_data @ 0001071c ============= */

void shell_dump_sym_data(uint *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  byte bStack_6d;
  uint local_6c [18];
  
  if (param_2 == 0) {
    if (data_cnt == 1) {
      DataSynchronizationBarrier(0xf);
      printk("sym %s is %d(0x%.2x)\n",sym,(byte)*param_1,(byte)*param_1);
      iVar5 = 1;
    }
    else {
      iVar5 = 1;
    }
  }
  else if (param_2 == 1) {
    if (data_cnt == 1) {
      DataSynchronizationBarrier(0xf);
      printk("sym %s is %d(0x%.4x)\n",sym,(ushort)*param_1,(ushort)*param_1);
      iVar5 = 1;
    }
    else {
      iVar5 = 2;
    }
  }
  else if (data_cnt == 1) {
    DataSynchronizationBarrier(0xf);
    printk("sym %s is %d(0x%.8x)\n",sym,*param_1,*param_1);
    iVar5 = 1;
  }
  else {
    iVar5 = 4;
  }
  if ((1 < (int)data_cnt) && (uVar6 = data_cnt & 0xffff, uVar6 != 0)) {
    uVar1 = __aeabi_idiv(0x10,iVar5);
    do {
      printk("%08x:",param_1);
      uVar8 = 0;
      puVar7 = param_1;
      if ((int)uVar6 <= (int)uVar1) {
        uVar1 = uVar6;
      }
      do {
        if (iVar5 == 4) {
          uVar3 = *puVar7;
          DataSynchronizationBarrier(0xf);
          local_6c[uVar8] = uVar3;
        }
        else if (iVar5 == 2) {
          uVar3 = (uint)(ushort)*puVar7;
          DataSynchronizationBarrier(0xf);
          *(ushort *)((int)local_6c + uVar8 * 2) = (ushort)*puVar7;
        }
        else {
          uVar3 = (uint)(byte)*puVar7;
          DataSynchronizationBarrier(0xf);
          *(byte *)((int)local_6c + uVar8) = (byte)*puVar7;
        }
        uVar8 = uVar8 + 1;
        printk(" %0*x",(int)(short)iVar5 << 1,uVar3);
        puVar7 = (uint *)((int)puVar7 + iVar5);
      } while (uVar8 != uVar1);
      iVar2 = uVar1 * iVar5;
      param_1 = (uint *)((int)param_1 + iVar5 * (uVar1 - 1) + iVar5);
      if (iVar2 < 1) {
        iVar2 = 0;
      }
      else {
        pbVar4 = &bStack_6d;
        do {
          pbVar4 = pbVar4 + 1;
          if ((((&_ctype)[*pbVar4] & 0x97) == 0) || ((*pbVar4 & 0x80) != 0)) {
            *pbVar4 = 0x2e;
          }
        } while (pbVar4 != (byte *)((int)local_6c + iVar2 + -1));
      }
      *(undefined1 *)((int)local_6c + iVar2) = 0;
      printk("    %s\n",local_6c);
      uVar6 = uVar6 - uVar1 & 0xffff;
    } while (uVar6 != 0);
  }
  return;
}


/* ============= FUNCTION: shell_sym @ 00010970 ============= */

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
        pcVar2 = (char *)(iVar3 + DAT_00010fd4);
        *(uint *)(syms_cache + iVar3 + 4) = uVar8;
        *(code **)(syms_cache + iVar3) = pcVar5;
        strcpy(pcVar2,pcVar9);
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


/* ============= FUNCTION: user_va2pa @ 00010fd8 ============= */

int user_va2pa(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = *(uint *)((*(uint *)(*(int *)(*(int *)(param_1 + 0x18c) + 0x24) + (param_2 >> 0x15) * 8) &
                    0xfffff000) + ((param_2 << 0xb) >> 0x17) * 4 + 0x7ffff800);
  iVar2 = 0;
  if (uVar1 != 0) {
    iVar2 = (uVar1 & 0xfffff000) + (param_2 & 0xfff);
  }
  return iVar2;
}


/* ============= FUNCTION: check_user_addr @ 00011018 ============= */

bool check_user_addr(int param_1,uint param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)find_vma(*(undefined4 *)(param_1 + 0x18c));
  if (puVar1 == (uint *)0x0) {
    return false;
  }
  if (param_2 < *puVar1) {
    return false;
  }
  return param_2 < puVar1[1];
}


/* ============= FUNCTION: shellWriteProc @ 00011058 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint shellWriteProc(undefined4 param_1,uint param_2,uint param_3)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  size_t sVar6;
  int *piVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  undefined4 uVar11;
  uint uVar12;
  undefined1 *puVar13;
  undefined4 uVar14;
  uint *puVar15;
  char *__s;
  undefined4 *puVar16;
  char *pcVar17;
  undefined4 *puVar18;
  undefined1 *local_40;
  char *local_3c;
  undefined4 *local_38;
  undefined4 *local_34;
  undefined4 local_30;
  uint local_2c;
  
  uVar4 = param_3;
  if (0x7e < param_3) {
    uVar4 = 0x7f;
  }
  uVar12 = *(uint *)(((uint)&local_40 & 0xffffe000) + 8);
  uVar9 = param_2 + uVar4;
  uVar10 = uVar9;
  if (!CARRY4(param_2,uVar4)) {
    uVar10 = uVar9 - (uVar12 + 1);
  }
  if (!CARRY4(param_2,uVar4) && uVar9 <= uVar12) {
    uVar12 = 0;
  }
  if (uVar12 == 0) {
    iVar3 = __copy_from_user(DAT_000117d0,param_2,uVar4);
    if (iVar3 != 0) {
      return 0xfffffff2;
    }
  }
  else if (uVar4 != 0) {
    __memzero(DAT_000117d0,uVar4,uVar10);
    return 0xfffffff2;
  }
  cmd_line[uVar4] = 0;
  proc_get_cmd(cmd_line);
  iVar3 = proc_argc;
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
  while (iVar1 = getopt(iVar3,(char **)proc_argv,"p:c:tFsadbwlfh?"), iVar1 != -1) {
    switch(iVar1) {
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
      uVar4 = simple_strtoul(optarg,0,data_base);
      data_cnt = uVar4 & 0xff;
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
  if (iVar3 <= optind) {
    printk("error: no symbol,%d/%d\n",optind,iVar3);
    return param_3;
  }
  __s = *(char **)(proc_argv + optind * 4);
  if (optind < iVar3 + -1) {
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
    uVar4 = 0;
    puVar13 = sym_pid;
  }
  else {
    local_40 = sym_pid;
    pcVar2 = strchr(__s,0x3d);
    if (pcVar2 == (char *)0x0) {
      pcVar17 = (char *)0x0;
      uVar4 = 0;
      puVar13 = local_40;
    }
    else {
      pcVar17 = pcVar2 + 1;
      local_40 = data_base;
      iVar3 = isint(pcVar17,data_base);
      if (iVar3 == 0) {
        printk("invalid data %s\n",__s,local_40);
        return param_3;
      }
      *pcVar2 = '\0';
      uVar4 = simple_strtoul(pcVar17);
      puVar13 = sym_pid;
      __s = sym;
    }
  }
  iVar3 = find_task_by_vpid(puVar13);
  if ((iVar3 == 0) || (*(int *)(iVar3 + 0x18c) == 0)) goto LAB_00011628;
  iVar1 = isint(__s,0x10);
  if (iVar1 == 0) {
    local_3c = (char *)(iVar3 + 0x2d8);
    sVar6 = strlen(__s);
    uVar10 = full_name_hash(__s,sVar6);
    puVar16 = (undefined4 *)((uVar10 & 0xff) * 0x60);
    if (uVar10 == *(uint *)(syms_cache + (int)(puVar16 + 1))) {
      local_40 = syms_cache;
      local_38 = puVar16;
      local_34 = &sym + (uVar10 & 0xff) * 0x18;
      iVar1 = strcmp(__s,syms_cache + (int)(puVar16 + 2));
      if (iVar1 != 0) goto LAB_000114a0;
      pcVar2 = local_40 + (int)(local_38 + 0x12);
      local_40 = local_40 + (int)local_38;
      local_38 = local_34;
      iVar1 = strcmp(local_3c,pcVar2);
      if (local_40 == (undefined1 *)0x0 || iVar1 != 0) goto LAB_000114a0;
      iVar1 = local_38[1];
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
      piVar7 = (int *)usyms_lookup_name(iVar3,__s,pid_path);
      if (piVar7 == (int *)0x0) goto LAB_00011628;
      iVar1 = *piVar7;
      if (iVar1 != 0) {
        local_2c = (uint)*(ushort *)((int)piVar7 + 6);
        local_30 = CONCAT22(local_30._2_2_,(short)piVar7[1]);
        sVar6 = strlen(__s);
        if (sVar6 < 0x3f) {
          uVar10 = full_name_hash(__s,sVar6);
          iVar5 = (uVar10 & 0xff) * 0x60;
          pcVar2 = (char *)(DAT_000117d4 + iVar5 + 8);
          local_40 = (undefined1 *)(DAT_000117d4 + iVar5);
          *(uint *)(syms_cache + iVar5 + 4) = uVar10;
          *(int *)(syms_cache + iVar5) = iVar1;
          strcpy(pcVar2,__s);
          puVar18 = (undefined4 *)(DAT_000117d4 + iVar5 + 0x48);
          puVar16 = (undefined4 *)(DAT_000117d4 + iVar5 + 0x58);
          uVar8 = *(undefined4 *)(local_3c + 4);
          uVar11 = *(undefined4 *)(local_3c + 8);
          uVar14 = *(undefined4 *)(local_3c + 0xc);
          *puVar18 = *(undefined4 *)local_3c;
          puVar18[1] = uVar8;
          puVar18[2] = uVar11;
          puVar18[3] = uVar14;
          *puVar16 = local_30;
          puVar16[1] = local_2c;
          if (local_40 != (undefined1 *)0x0) goto LAB_00011568;
        }
      }
    }
    iVar3 = user_va2pa(iVar3,iVar1);
  }
  else {
    iVar1 = simple_strtoul(__s,0,0x10);
    iVar5 = check_user_addr(iVar3,iVar1);
    if (iVar5 == 0) goto LAB_00011628;
    iVar3 = user_va2pa(iVar3,iVar1);
    if (iVar3 == 0) {
      printk("va %.8lx no pa\n",iVar1);
      goto LAB_00011628;
    }
  }
  if (iVar1 != 0) {
    puVar15 = (uint *)(iVar3 + -0x80000000);
    if (sym_type == 1) {
      if (pcVar17 != (char *)0x0) {
        printk("sym %s set to %d(0x%.4x)\n",sym,uVar4 & 0xffff,uVar4 & 0xffff);
        DataSynchronizationBarrier(0xe);
        if (_kallsyms_lookup != (code *)0x0) {
          (*_kallsyms_lookup)();
        }
        *(short *)puVar15 = (short)uVar4;
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
          shell_dump_sym_data(puVar15,0);
          return param_3;
        }
        printk("sym %s set to %d(0x%.2x)\n",sym,uVar4 & 0xff,uVar4 & 0xff);
        DataSynchronizationBarrier(0xe);
        if (_kallsyms_lookup != (code *)0x0) {
          (*_kallsyms_lookup)();
        }
        *(char *)puVar15 = (char)uVar4;
        return param_3;
      }
      if (pcVar17 != (char *)0x0) {
        printk("sym %s set to %d(0x%.8x)\n",sym,uVar4,uVar4);
        DataSynchronizationBarrier(0xe);
        if (_kallsyms_lookup != (code *)0x0) {
          (*_kallsyms_lookup)();
        }
        *puVar15 = uVar4;
        return param_3;
      }
    }
    shell_dump_sym_data(puVar15);
    return param_3;
  }
LAB_00011628:
  printk("pid 0x%x unknown symbol \"%s\"\n",sym_pid,sym);
  return param_3;
}


/* ============= FUNCTION: create_shell_proc @ 000117d8 ============= */

int create_shell_proc(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = proc_create_data("shell",0x1a4,param_1,DAT_00011814,0);
  return -(uint)(iVar1 == 0);
}


/* ============= FUNCTION: myfile_read @ 00011818 ============= */

undefined4 myfile_read(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uStack_10;
  
  if (param_2 != 0 && param_1 != 0) {
    uVar3 = (uint)&uStack_10 & 0xffffe000;
    uVar2 = *(undefined4 *)(uVar3 + 8);
    *(undefined4 *)(uVar3 + 8) = 0;
    uStack_10 = param_4;
    uVar1 = (**(code **)(*(int *)(param_1 + 0x14) + 8))();
    *(undefined4 *)(((uint)&uStack_10 & 0xffffe000) + 8) = uVar2;
    return uVar1;
  }
  return 0xffffffff;
}


/* ============= FUNCTION: get_task_full_path.constprop.9 @ 00011870 ============= */

size_t get_task_full_path_constprop_9
                 (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  size_t __n;
  
  iVar2 = *(int *)(param_1 + 0x18c);
  if (((iVar2 != 0) && (iVar3 = *(int *)(iVar2 + 0x188), iVar3 != 0)) &&
     (iVar2 = __get_free_pages(0x800d0,0,param_3,iVar2,param_4), iVar2 != 0)) {
    pvVar1 = (void *)d_path(iVar3 + 8,iVar2,0x1000);
    if (pvVar1 == (void *)0x0) {
      __n = 0xffffffff;
    }
    else {
      __n = (iVar2 + 0xfff) - (int)pvVar1;
      if (0x7e < (int)__n) {
        __n = 0x7f;
      }
      pvVar1 = memcpy(&task_path,pvVar1,__n);
      *(undefined1 *)((int)pvVar1 + __n) = 0;
    }
    free_pages(iVar2,0);
    return __n;
  }
  return 0xffffffff;
}


/* ============= FUNCTION: myfile_open.constprop.10 @ 0001190c ============= */

uint myfile_open_constprop_10(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = filp_open(param_1,0,0);
  if (uVar1 < 0xfffff001) {
    return uVar1;
  }
  printk("filp_open [%s] failed.\n",param_1);
  return 0;
}


/* ============= FUNCTION: myfile_lseek.constprop.14 @ 00011940 ============= */

undefined4 myfile_lseek_constprop_14(int param_1,int param_2)

{
  undefined4 uVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 local_18 [2];
  
  if (param_1 != 0) {
    uVar3 = *(undefined4 *)(((uint)local_18 & 0xffffe000) + 8);
    *(undefined4 *)(((uint)local_18 & 0xffffe000) + 8) = 0;
    local_18[0] = 0;
    pcVar2 = *(code **)(*(int *)(param_1 + 0x14) + 4);
    uVar1 = (*pcVar2)(param_1,pcVar2,param_2,param_2 >> 0x1f);
    *(undefined4 *)(((uint)local_18 & 0xffffe000) + 8) = uVar3;
    return uVar1;
  }
  return 0xffffffff;
}


/* ============= FUNCTION: get_elf_header.constprop.5 @ 000119a0 ============= */

undefined4
get_elf_header_constprop_5
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  myfile_lseek_constprop_14(param_1,0,param_3,param_4,param_4);
  iVar1 = myfile_read(param_1,Ehdr32,0x34);
  if (iVar1 != 0x34) {
    return 0xffffffff;
  }
  is_big_endian = (uint)(Ehdr32[5] == '\x02');
  is_32bit_elf = (uint)(Ehdr32[4] != '\x02');
  if ((Ehdr32[5] == '\x02') == 0) {
    return 0;
  }
  Ehdr32._16_2_ = Ehdr32._16_2_ << 8 | (ushort)Ehdr32._16_2_ >> 8;
  Ehdr32._18_2_ = Ehdr32._18_2_ << 8 | (ushort)Ehdr32._18_2_ >> 8;
  Ehdr32._20_4_ =
       Ehdr32._20_4_ << 0x18 | ((uint)Ehdr32._20_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._20_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._20_4_ >> 0x18;
  Ehdr32._24_4_ =
       Ehdr32._24_4_ << 0x18 | ((uint)Ehdr32._24_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._24_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._24_4_ >> 0x18;
  Ehdr32._28_4_ =
       Ehdr32._28_4_ << 0x18 | ((uint)Ehdr32._28_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._28_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._28_4_ >> 0x18;
  Ehdr32._32_4_ =
       Ehdr32._32_4_ << 0x18 | ((uint)Ehdr32._32_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._32_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._32_4_ >> 0x18;
  Ehdr32._36_4_ =
       Ehdr32._36_4_ << 0x18 | ((uint)Ehdr32._36_4_ >> 8 & 0xff) << 0x10 |
       ((uint)Ehdr32._36_4_ >> 0x10 & 0xff) << 8 | (uint)Ehdr32._36_4_ >> 0x18;
  Ehdr32._40_2_ = Ehdr32._40_2_ << 8 | (ushort)Ehdr32._40_2_ >> 8;
  Ehdr32._42_2_ = Ehdr32._42_2_ << 8 | (ushort)Ehdr32._42_2_ >> 8;
  Ehdr32._44_2_ = Ehdr32._44_2_ << 8 | (ushort)Ehdr32._44_2_ >> 8;
  Ehdr32._46_2_ = Ehdr32._46_2_ << 8 | (ushort)Ehdr32._46_2_ >> 8;
  Ehdr32._48_2_ = Ehdr32._48_2_ << 8 | (ushort)Ehdr32._48_2_ >> 8;
  Ehdr32._50_2_ = Ehdr32._50_2_ << 8 | (ushort)Ehdr32._50_2_ >> 8;
  return 0;
}


/* ============= FUNCTION: get_data @ 00011aa8 ============= */

int get_data(undefined4 param_1,undefined4 param_2,uint param_3,char *param_4)

{
  int iVar1;
  uint uVar2;
  
  if (param_4 == (char *)0x0) {
    param_4 = "unkown";
  }
  if (param_3 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = myfile_lseek_constprop_14();
    if (iVar1 < 0) {
      printk("Unable to seek to 0x%lx for %s\n",param_2,param_4);
      iVar1 = 0;
    }
    else if ((param_3 < 0x200000) && (iVar1 = __kmalloc(param_3,0xd0), iVar1 != 0)) {
      uVar2 = myfile_read(param_1,iVar1,param_3);
      if (uVar2 != param_3) {
        printk("Unable to read in 0x%lx bytes of %s\n",param_3,param_4);
        kfree(iVar1);
        iVar1 = 0;
      }
    }
    else {
      printk("Out of memory allocating 0x%lx bytes for %s\n",param_3,param_4);
      iVar1 = 0;
    }
  }
  return iVar1;
}


/* ============= FUNCTION: get_32bit_elf_symbols @ 00011b7c ============= */

uint * get_32bit_elf_symbols(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  if (*(int *)(param_2 + 0x24) == 0x10) {
    puVar2 = (uint *)get_data(param_1,*(undefined4 *)(param_2 + 0x10),
                              *(undefined4 *)(param_2 + 0x14),"symtab shndx");
    if (puVar2 != (uint *)0x0) {
      if ((is_big_endian != 0) &&
         (iVar3 = __aeabi_uidiv(*(undefined4 *)(param_2 + 0x14),*(undefined4 *)(param_2 + 0x24)),
         0 < iVar3)) {
        iVar5 = 0;
        puVar1 = puVar2;
        do {
          iVar5 = iVar5 + 1;
          uVar7 = *puVar1;
          uVar6 = puVar1[1];
          uVar4 = puVar1[2];
          *puVar1 = uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8 |
                    uVar7 >> 0x18;
          puVar1[1] = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
                      uVar6 >> 0x18;
          puVar1[2] = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                      uVar4 >> 0x18;
          *(ushort *)((int)puVar1 + 0xe) =
               *(ushort *)((int)puVar1 + 0xe) << 8 | *(ushort *)((int)puVar1 + 0xe) >> 8;
          puVar1 = puVar1 + 4;
        } while (iVar3 != iVar5);
      }
    }
    return puVar2;
  }
  printk("Invalid entsize of section, %d, should be %d\n",*(int *)(param_2 + 0x24),0x10,param_4,
         param_4);
  return (uint *)0x0;
}


/* ============= FUNCTION: get_32bit_section_headers.constprop.7 @ 00011c3c ============= */

undefined4 get_32bit_section_headers_constprop_7(undefined4 param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  
  if (section_headers == (uint *)0x0) {
    if (Ehdr32._46_2_ != 0x28) {
      printk("Invalid size of section header %d, should be %d\n",Ehdr32._46_2_,0x34);
      return 0xffffffff;
    }
    section_headers =
         (uint *)get_data(param_1,Ehdr32._32_4_,(uint)(ushort)Ehdr32._48_2_ * 0x28,"section headers"
                         );
    if (section_headers == (uint *)0x0) {
      return 0xffffffff;
    }
    if ((is_big_endian != 0) && (Ehdr32._48_2_ != 0)) {
      iVar4 = 0;
      puVar1 = section_headers;
      do {
        uVar10 = *puVar1;
        iVar4 = iVar4 + 1;
        uVar9 = puVar1[1];
        uVar8 = puVar1[2];
        uVar7 = puVar1[3];
        uVar6 = puVar1[4];
        uVar5 = puVar1[5];
        uVar12 = puVar1[6];
        uVar11 = puVar1[7];
        uVar2 = puVar1[8];
        uVar3 = puVar1[9];
        *puVar1 = uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
                  uVar10 >> 0x18;
        puVar1[1] = uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
                    uVar9 >> 0x18;
        puVar1[2] = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
                    uVar8 >> 0x18;
        puVar1[3] = uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8 |
                    uVar7 >> 0x18;
        puVar1[4] = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
                    uVar6 >> 0x18;
        puVar1[5] = uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 |
                    uVar5 >> 0x18;
        puVar1[6] = uVar12 << 0x18 | (uVar12 >> 8 & 0xff) << 0x10 | (uVar12 >> 0x10 & 0xff) << 8 |
                    uVar12 >> 0x18;
        puVar1[7] = uVar11 << 0x18 | (uVar11 >> 8 & 0xff) << 0x10 | (uVar11 >> 0x10 & 0xff) << 8 |
                    uVar11 >> 0x18;
        puVar1[9] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                    uVar3 >> 0x18;
        puVar1[8] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                    uVar2 >> 0x18;
        puVar1 = puVar1 + 10;
      } while (iVar4 < (int)(uint)(ushort)Ehdr32._48_2_);
      return 0;
    }
  }
  return 0;
}


/* ============= FUNCTION: get_string_table.part.0.constprop.13 @ 00011d60 ============= */

void get_string_table_part_0_constprop_13
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (uint)(ushort)Ehdr32._50_2_;
  if (uVar1 == 0) {
    return;
  }
  if (uVar1 < (ushort)Ehdr32._48_2_) {
    iVar2 = section_headers + uVar1 * 0x28;
    if (*(int *)(iVar2 + 0x14) != 0) {
      string_table = get_data(param_1,*(undefined4 *)(iVar2 + 0x10),*(int *)(iVar2 + 0x14),
                              "string table",param_4);
    }
    string_table_length = 0;
    if (string_table != 0) {
      string_table_length = *(undefined4 *)(iVar2 + 0x14);
    }
    return;
  }
  return;
}


/* ============= FUNCTION: func_insert @ 00011dcc ============= */

undefined4 func_insert(int *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = param_1;
  iVar3 = 0;
  do {
    while( true ) {
      iVar2 = *piVar1;
      if (iVar2 == 0) {
        *param_2 = iVar3;
        param_2[1] = 0;
        param_2[2] = 0;
        *piVar1 = (int)param_2;
        rb_insert_color(param_2,param_1);
        return 0;
      }
      piVar1 = (int *)(iVar2 + 4);
      iVar3 = iVar2;
      if (*(uint *)(iVar2 + 0xc) < (uint)param_2[4]) break;
      piVar1 = (int *)(iVar2 + 8);
    }
  } while (*(uint *)(iVar2 + 0x10) <= (uint)param_2[3]);
  return 0xffffffff;
}


/* ============= FUNCTION: func_search @ 00011e44 ============= */

void func_search(int *param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    return;
  }
  do {
    while (param_2 < *(uint *)(iVar1 + 0xc)) {
      iVar1 = *(int *)(iVar1 + 8);
      if (iVar1 == 0) {
        return;
      }
    }
    if (param_2 < *(uint *)(iVar1 + 0x10)) {
      return;
    }
    iVar1 = *(int *)(iVar1 + 4);
  } while (iVar1 != 0);
  return;
}


/* ============= FUNCTION: func_print @ 00011e88 ============= */

void func_print(void)

{
  int iVar1;
  
  iVar1 = rb_first();
  if (iVar1 == 0) {
    return;
  }
  do {
    printk("func %s : %.8x-%.8x\n",iVar1 + 0x14,*(undefined4 *)(iVar1 + 0xc),
           *(undefined4 *)(iVar1 + 0x10));
    iVar1 = rb_next(iVar1);
  } while (iVar1 != 0);
  return;
}


/* ============= FUNCTION: build_func_usyms @ 00011ec4 ============= */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void * build_func_usyms(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  int iVar6;
  size_t __n;
  uint uVar7;
  char *__s2;
  uint uVar8;
  uint __n_00;
  uint *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  char *__src;
  void *local_54;
  uint local_4c;
  uint local_48;
  int local_34;
  uint *local_30;
  
  iVar1 = get_task_full_path_constprop_9();
  if ((iVar1 < 1) || (iVar1 = myfile_open_constprop_10(&task_path), iVar1 == 0)) {
    return (void *)0x0;
  }
  if (string_table != 0) {
    kfree();
    string_table = 0;
  }
  if (section_headers != 0) {
    kfree();
    section_headers = 0;
  }
  string_table_length = 0;
  iVar2 = get_elf_header_constprop_5(iVar1);
  if (iVar2 < 0) {
    filp_close(iVar1,0);
    return (void *)0x0;
  }
  cur_task = param_1;
  if (is_32bit_elf == 0) {
    printk("\nIt is not 32 bit elf file\n");
    goto LAB_000124bc;
  }
  iVar2 = get_32bit_section_headers_constprop_7(iVar1);
  if (iVar2 < 0) goto LAB_000124bc;
  if (string_table == 0) {
    get_string_table_part_0_constprop_13(iVar1);
  }
  local_54 = (void *)kmalloc_order(0x6800,0xd0,3);
  if (Ehdr32._48_2_ == 0) {
LAB_000124d8:
    local_4c = 0x200;
LAB_000123e0:
    uVar7 = 0;
    pvVar5 = local_54;
    do {
      iVar2 = func_insert(DAT_00012520,pvVar5);
      uVar7 = uVar7 + 1;
      pvVar5 = (void *)((int)pvVar5 + 0x34);
      if (iVar2 < 0) break;
    } while (uVar7 < local_4c);
  }
  else {
    local_34 = 0;
    local_30 = (uint *)0x0;
    iVar10 = 0;
    iVar2 = section_headers;
    do {
      if ((*(int *)(iVar2 + 4) == 9) && (iVar12 = *(int *)(iVar2 + 0x14), iVar12 != 0)) {
        iVar14 = *(int *)(iVar2 + 0x24);
        local_34 = __aeabi_uidiv(iVar12,iVar14);
        if (iVar14 == 8) {
          local_30 = (uint *)get_data(iVar1,*(undefined4 *)(iVar2 + 0x10),iVar12,"rel section");
          if (local_30 != (uint *)0x0) {
            if ((is_big_endian != 0) &&
               (iVar12 = __aeabi_uidiv(*(undefined4 *)(iVar2 + 0x14),*(undefined4 *)(iVar2 + 0x24)),
               0 < iVar12)) {
              iVar14 = 0;
              puVar9 = local_30;
              do {
                iVar14 = iVar14 + 1;
                uVar7 = *puVar9;
                uVar8 = puVar9[1];
                *puVar9 = uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8
                          | uVar7 >> 0x18;
                puVar9[1] = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 |
                            (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
                puVar9 = puVar9 + 2;
              } while (iVar12 != iVar14);
            }
          }
        }
        else {
          printk("Invalid entsize of section, %d, should be %d\n",iVar14,8);
          local_30 = (uint *)0x0;
        }
      }
      iVar10 = iVar10 + 1;
      iVar2 = iVar2 + 0x28;
    } while (iVar10 < (int)(uint)(ushort)Ehdr32._48_2_);
    if ((ushort)Ehdr32._48_2_ == 0) goto LAB_000124d8;
    uVar7 = 0;
    iVar10 = 0;
    local_4c = 0x200;
    iVar12 = 0;
    local_48 = 0;
    iVar2 = section_headers;
    do {
      if ((*(int *)(iVar2 + 4) == 0xb || *(int *)(iVar2 + 4) == 2) &&
         (iVar3 = get_32bit_elf_symbols(iVar1,iVar2), iVar14 = string_table, iVar3 != 0)) {
        uVar8 = *(uint *)(iVar2 + 0x18);
        if (uVar8 == (ushort)Ehdr32._50_2_) {
          local_48 = string_table_length;
          iVar4 = __aeabi_uidiv(*(undefined4 *)(iVar2 + 0x14),*(undefined4 *)(iVar2 + 0x24));
          if (0 < iVar4) goto LAB_00012158;
        }
        else {
          if ((uVar8 < (ushort)Ehdr32._48_2_) &&
             (iVar14 = section_headers + uVar8 * 0x28, *(int *)(iVar14 + 4) == 3)) {
            iVar10 = get_data(iVar1,*(undefined4 *)(iVar14 + 0x10),*(undefined4 *)(iVar14 + 0x14),
                              "string table");
            if (iVar10 == 0) {
              local_48 = 0;
            }
            else {
              local_48 = *(uint *)(iVar14 + 0x14);
            }
          }
          iVar4 = __aeabi_uidiv(*(undefined4 *)(iVar2 + 0x14),*(undefined4 *)(iVar2 + 0x24));
          iVar14 = iVar10;
          if (0 < iVar4) {
LAB_00012158:
            iVar11 = 0;
            iVar10 = iVar3 + 0x10;
            do {
              while ((((*(short *)(iVar10 + -2) == 0 && (*(int *)(iVar2 + 4) != 0xb)) ||
                      (iVar14 == 0 || (*(byte *)(iVar10 + -4) & 0xf) != 2)) ||
                     (*(uint *)(iVar10 + -8) < 8))) {
LAB_0001217c:
                iVar11 = iVar11 + 1;
                iVar10 = iVar10 + 0x10;
                if (iVar4 == iVar11) goto LAB_000122a4;
              }
              if (*(uint *)(iVar10 + -0x10) < local_48) {
                __src = (char *)(iVar14 + *(uint *)(iVar10 + -0x10));
              }
              else {
                __src = "<corrupt>";
              }
              strncpy((char *)((int)local_54 + uVar7 * 0x34 + 0x14),__src,0x20);
              if (*(int *)(iVar2 + 4) == 0xb) {
                if ((local_30 != (uint *)0x0) && (local_34 != 0)) {
                  iVar13 = 0;
                  puVar9 = local_30;
                  do {
                    __s2 = "<corrupt>";
                    iVar13 = iVar13 + 1;
                    uVar8 = *(uint *)(iVar3 + (puVar9[1] >> 8) * 0x10);
                    if (uVar8 < local_48) {
                      __s2 = (char *)(iVar14 + uVar8);
                    }
                    iVar6 = strcmp(__src,__s2);
                    if (iVar6 == 0) {
                      iVar13 = user_va2pa(cur_task,*puVar9);
                      if ((iVar13 != 0) &&
                         (uVar8 = *(uint *)(iVar13 + -0x80000000), 0x3fffffff < uVar8)) {
                        *(uint *)((int)local_54 + uVar7 * 0x34 + 0xc) = uVar8;
                        *(uint *)((int)local_54 + uVar7 * 0x34 + 0x10) =
                             uVar8 + *(int *)(iVar10 + -8);
                        goto LAB_00012224;
                      }
                      break;
                    }
                    puVar9 = puVar9 + 2;
                  } while (iVar13 != local_34);
                }
                goto LAB_0001217c;
              }
              *(undefined4 *)((int)local_54 + uVar7 * 0x34 + 0xc) = *(undefined4 *)(iVar10 + -0xc);
              *(int *)((int)local_54 + uVar7 * 0x34 + 0x10) =
                   *(int *)(iVar10 + -8) + *(int *)(iVar10 + -0xc);
LAB_00012224:
              uVar7 = uVar7 + 1;
              if (uVar7 < local_4c) goto LAB_0001217c;
              uVar8 = local_4c * 0x34;
              __n_00 = uVar8 + 0x6800;
              pvVar5 = (void *)__kmalloc(__n_00,0xd0);
              if (pvVar5 == (void *)0x0 || local_54 == (void *)0x0) {
                kfree(local_54);
                if (pvVar5 == (void *)0x0) {
                  if (iVar14 != string_table) {
                    kfree(iVar14);
                  }
                  kfree(iVar3);
                  goto LAB_000124bc;
                }
              }
              else {
                if (uVar8 <= __n_00) {
                  __n_00 = uVar8;
                }
                memcpy(pvVar5,local_54,__n_00);
                kfree(local_54);
              }
              iVar11 = iVar11 + 1;
              local_4c = local_4c + 0x200;
              iVar10 = iVar10 + 0x10;
              local_54 = pvVar5;
            } while (iVar4 != iVar11);
          }
LAB_000122a4:
          if (iVar14 != string_table) {
            kfree(iVar14);
            iVar14 = 0;
          }
        }
        kfree(iVar3);
        iVar10 = iVar14;
      }
      iVar12 = iVar12 + 1;
      iVar2 = iVar2 + 0x28;
    } while (iVar12 < (int)(uint)(ushort)Ehdr32._48_2_);
    if (local_4c != 0) goto LAB_000123e0;
  }
  if (local_54 != (void *)0x0) {
    filp_close(iVar1,0);
    __n = strlen(&task_path);
    if (0x7e < (int)__n) {
      __n = 0x7f;
    }
    memcpy(DAT_00012524,(void *)((int)DAT_00012524 + -0xd4),__n);
    last_task_path[0x7f] = 0;
    return local_54;
  }
LAB_000124bc:
  filp_close(iVar1,0);
  last_task_path[0] = 0;
  return (void *)0x0;
}


/* ============= FUNCTION: usyms_lookup_name @ 00012528 ============= */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined8 * usyms_lookup_name(undefined4 param_1,char *param_2,char *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  size_t __n;
  char *__s2;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint local_40;
  int local_30;
  
  if (param_3 == (char *)0x0) {
    iVar2 = get_task_full_path_constprop_9();
    if (iVar2 < 1) {
      return (undefined8 *)0x0;
    }
    param_3 = &task_path;
  }
  printk("open file %s\n",param_3);
  iVar2 = myfile_open_constprop_10(param_3);
  if (iVar2 == 0) {
    return (undefined8 *)0x0;
  }
  if (string_table != 0) {
    kfree();
    string_table = 0;
  }
  if (section_headers != 0) {
    kfree();
    section_headers = 0;
  }
  string_table_length = 0;
  iVar3 = get_elf_header_constprop_5(iVar2);
  if (iVar3 < 0) {
    filp_close(iVar2,0);
    return (undefined8 *)0x0;
  }
  cur_task = param_1;
  if (is_32bit_elf == 0) {
    printk("\nIt is not 32 bit elf file\n");
  }
  else {
    iVar3 = get_32bit_section_headers_constprop_7(iVar2);
    if (-1 < iVar3) {
      if (string_table == 0) {
        get_string_table_part_0_constprop_13(iVar2);
      }
      if (Ehdr32._48_2_ != 0) {
        iVar3 = 0;
        local_40 = 0;
        iVar9 = 0;
        local_30 = -1;
        iVar13 = section_headers;
        do {
          if ((*(int *)(iVar13 + 4) == 0xb || *(int *)(iVar13 + 4) == 2) &&
             (iVar4 = get_32bit_elf_symbols(iVar2,iVar13), iVar4 != 0)) {
            uVar8 = *(uint *)(iVar13 + 0x18);
            if (uVar8 == (ushort)Ehdr32._50_2_) {
              iVar10 = __aeabi_uidiv(*(undefined4 *)(iVar13 + 0x14),*(undefined4 *)(iVar13 + 0x24));
              local_40 = string_table_length;
              iVar3 = string_table;
              if (0 < iVar10) goto LAB_000126e4;
            }
            else {
              if ((uVar8 < (ushort)Ehdr32._48_2_) &&
                 (iVar10 = uVar8 * 0x28 + section_headers, *(int *)(iVar10 + 4) == 3)) {
                iVar3 = get_data(iVar2,*(undefined4 *)(iVar10 + 0x10),*(undefined4 *)(iVar10 + 0x14)
                                 ,"string table");
                if (iVar3 == 0) {
                  local_40 = 0;
                }
                else {
                  local_40 = *(uint *)(iVar10 + 0x14);
                }
              }
              iVar10 = __aeabi_uidiv(*(undefined4 *)(iVar13 + 0x14),*(undefined4 *)(iVar13 + 0x24));
              if (0 < iVar10) {
LAB_000126e4:
                iVar11 = 0;
                iVar12 = iVar4;
                do {
                  uVar8 = *(byte *)(iVar12 + 0xc) & 0xf;
                  if ((iVar3 != 0) && (uVar8 - 1 < 2)) {
                    __s2 = "<corrupt>";
                    uVar5 = *(uint *)(iVar4 + iVar11 * 0x10);
                    if (uVar5 < local_40) {
                      __s2 = (char *)(iVar3 + uVar5);
                    }
                    iVar6 = strcmp(param_2,__s2);
                    iVar1 = DAT_0001289c;
                    if (iVar6 == 0) {
                      sym_info._0_4_ = *(undefined4 *)(iVar12 + 4);
                      uVar7 = *(undefined4 *)(iVar12 + 8);
                      *(short *)(DAT_0001289c + 4) = (short)uVar8;
                      *(short *)(iVar1 + 6) = (short)uVar7;
                      local_30 = 0;
                      break;
                    }
                  }
                  iVar11 = iVar11 + 1;
                  iVar12 = iVar12 + 0x10;
                } while (iVar11 < iVar10);
              }
              if (iVar3 != string_table) {
                kfree(iVar3);
                iVar3 = 0;
              }
            }
            kfree(iVar4);
          }
          iVar9 = iVar9 + 1;
          iVar13 = iVar13 + 0x28;
        } while (iVar9 < (int)(uint)(ushort)Ehdr32._48_2_);
        if (local_30 != -1) {
          filp_close(iVar2,0);
          __n = strlen(param_3);
          if (0x7e < (int)__n) {
            __n = 0x7f;
          }
          memcpy(last_task_path,param_3,__n);
          last_task_path[0x7f] = 0;
          return &sym_info;
        }
      }
    }
  }
  filp_close(iVar2,0);
  last_task_path[0] = 0;
  return (undefined8 *)0x0;
}


/* ============= FUNCTION: usyms_lookup_addr @ 000128a0 ============= */

undefined4 usyms_lookup_addr(undefined4 param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  char *__src;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  int local_34;
  uint local_30;
  
  iVar1 = myfile_open_constprop_10();
  if (iVar1 != 0) {
    if (string_table != 0) {
      kfree();
      string_table = 0;
    }
    if (section_headers != 0) {
      kfree();
      section_headers = 0;
    }
    string_table_length = 0;
    iVar2 = get_elf_header_constprop_5(iVar1);
    if (iVar2 < 0) {
      filp_close(iVar1,0);
      return 0;
    }
    if (is_32bit_elf == 0) {
      printk("\nIt is not 32 bit elf file\n");
    }
    else {
      iVar2 = get_32bit_section_headers_constprop_7(iVar1);
      if (-1 < iVar2) {
        if (string_table == 0) {
          get_string_table_part_0_constprop_13(iVar1);
        }
        if (Ehdr32._48_2_ != 0) {
          local_30 = 0;
          iVar2 = 0;
          local_34 = -1;
          iVar10 = 0;
          iVar9 = section_headers;
          do {
            if ((*(int *)(iVar9 + 4) == 0xb || *(int *)(iVar9 + 4) == 2) &&
               (puVar3 = (uint *)get_32bit_elf_symbols(iVar1,iVar9), puVar3 != (uint *)0x0)) {
              uVar6 = *(uint *)(iVar9 + 0x18);
              if (uVar6 == (ushort)Ehdr32._50_2_) {
                iVar7 = __aeabi_uidiv(*(undefined4 *)(iVar9 + 0x14),*(undefined4 *)(iVar9 + 0x24));
                local_30 = string_table_length;
                iVar2 = string_table;
                if (0 < iVar7) goto LAB_00012a00;
              }
              else {
                if ((uVar6 < (ushort)Ehdr32._48_2_) &&
                   (iVar7 = section_headers + uVar6 * 0x28, *(int *)(iVar7 + 4) == 3)) {
                  iVar2 = get_data(iVar1,*(undefined4 *)(iVar7 + 0x10),*(undefined4 *)(iVar7 + 0x14)
                                   ,"string table");
                  if (iVar2 == 0) {
                    local_30 = 0;
                  }
                  else {
                    local_30 = *(uint *)(iVar7 + 0x14);
                  }
                }
                iVar7 = __aeabi_uidiv(*(undefined4 *)(iVar9 + 0x14),*(undefined4 *)(iVar9 + 0x24));
                iVar5 = string_table;
                if (0 < iVar7) {
LAB_00012a00:
                  iVar5 = string_table;
                  iVar4 = 0;
                  puVar8 = puVar3;
                  do {
                    iVar4 = iVar4 + 1;
                    if ((((iVar2 != 0) && (((byte)puVar8[3] & 0xf) - 1 < 2)) &&
                        (puVar8[1] <= param_2)) && (param_2 < puVar8[1] + puVar8[2])) {
                      if (*puVar8 < local_30) {
                        __src = (char *)(iVar2 + *puVar8);
                      }
                      else {
                        __src = "<corrupt>";
                      }
                      local_34 = 0;
                      strncpy(DAT_00012b8c,__src,0x20);
                      sym_node._12_4_ = puVar8[1];
                      sym_node._16_4_ = puVar8[2] + puVar8[1];
                      break;
                    }
                    puVar8 = puVar8 + 4;
                  } while (iVar4 < iVar7);
                }
                if (iVar2 != iVar5) {
                  kfree(iVar2);
                  iVar2 = 0;
                }
              }
              kfree(puVar3);
            }
            iVar10 = iVar10 + 1;
            iVar9 = iVar9 + 0x28;
          } while (iVar10 < (int)(uint)(ushort)Ehdr32._48_2_);
          if (local_34 != -1) {
            filp_close(iVar1,0);
            return DAT_00012b90;
          }
        }
      }
    }
    filp_close(iVar1,0);
    last_task_path[0] = 0;
  }
  return 0;
}


/* ============= FUNCTION: dump_task_info @ 00012b94 ============= */

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


/* ============= FUNCTION: register_ptp_int @ 0001309c ============= */

void register_ptp_int(undefined4 param_1)

{
  ptp_isr = param_1;
  *(uint *)(npp_base + 4) = *(uint *)(npp_base + 4) & 0xfffdffff;
  return;
}


/* ============= FUNCTION: register_oam_int @ 000130c8 ============= */

void register_oam_int(undefined4 param_1)

{
  oam_isr = param_1;
  *(uint *)(npp_base + 4) = *(uint *)(npp_base + 4) & 0xfffbffff;
  return;
}


/* ============= FUNCTION: pon_npp_int @ 000130f4 ============= */

undefined4 pon_npp_int(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *npp_base;
  uVar2 = npp_base[1];
  if (((uVar1 & ~uVar2 & 0x20000) != 0) && (ptp_isr != (code *)0x0)) {
    (*ptp_isr)(0,0);
  }
  if (((uVar1 & ~uVar2 & 0x40000) != 0) && (oam_isr != (code *)0x0)) {
    (*oam_isr)(0,0);
  }
  return 0;
}


/* ============= FUNCTION: pon_npp_int_enable @ 0001316c ============= */

void pon_npp_int_enable(uint param_1)

{
  *(uint *)(npp_base + 4) = *(uint *)(npp_base + 4) & ~param_1;
  return;
}


/* ============= FUNCTION: tm_pon_npp_init @ 0001318c ============= */

undefined4 tm_pon_npp_init(void)

{
  printk("pon_npp init\n");
  *(undefined4 *)(npp_base + 8) = 0xffffff;
  *(undefined4 *)(npp_base + 0xc) = 0xfffff;
  msleep(1);
  pon_npp_idm_init();
  pon_npp_spa_init();
  pon_npp_sipc_init();
  pon_npp_smct_init();
  *(undefined4 *)(npp_base + 4) = 0xffffffff;
  *(undefined4 *)(npp_base + 0x48) = 0;
  pon_npp_smac_init();
  request_threaded_irq(g_npp_irq,pon_npp_int,0,0,"pon_npp",0);
  *(uint *)(npp_base + 0x40) = *(uint *)(npp_base + 0x40) | 0x300;
  *(undefined4 *)(npp_base + 0x10008) = 0x80;
  pon_npp_uopc_init();
  return 0;
}


/* ============= FUNCTION: pon_npp_sipc_init @ 0001325c ============= */

void pon_npp_sipc_init(void)

{
  *(undefined4 *)(npp_base + 0xc000) = 0x11;
  return;
}


/* ============= FUNCTION: smac_init @ 00013278 ============= */

void smac_init(int param_1)

{
  param_1 = param_1 * 0x40000;
  *(undefined4 *)(npp_base + param_1 + 0x40000) = 0xbae003;
  *(undefined4 *)(npp_base + param_1 + 0x40004) = 0xffff;
  *(undefined4 *)(npp_base + param_1 + 0x40008) = 0x80000001;
  *(undefined ***)(npp_base + param_1 + 0x400e0) = &PTR_caseD_47_00011200;
  *(uint *)(npp_base + param_1 + 0x40d00) = *(uint *)(npp_base + param_1 + 0x40d00) & 0xfffffffd;
  *(uint *)(npp_base + param_1 + 0x40d30) = *(uint *)(npp_base + param_1 + 0x40d30) & 0xffffffdf;
  return;
}


/* ============= FUNCTION: smac_sopc_mode_switch @ 00013320 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void smac_sopc_mode_switch(uint param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    (*_request_threaded_irq)(0x66665b0);
    if ((*(uint *)(dma_cfg_byteorder + npp_base + 4) & 1 << (param_1 + 5 & 0xff)) != 0) {
      *(uint *)(dma_cfg_byteorder + npp_base + 4) =
           *(uint *)(dma_cfg_byteorder + npp_base + 4) | 1 << (param_1 & 0xff);
      break;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *(uint *)(npp_base + 0x19038) =
       *(uint *)(npp_base + 0x19038) & ~(1 << (param_1 + 0x10 & 0xff)) |
       (uint)(param_2 != 1) << (param_1 + 0x10 & 0xff);
                    /* WARNING: Could not recover jumptable at 0x000133c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_request_threaded_irq)(0x66665b0);
  return;
}


/* ============= FUNCTION: gephy_ldo_test @ 000133dc ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
gephy_ldo_test(undefined2 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  undefined1 uVar3;
  uint uVar4;
  uint extraout_r3;
  undefined1 *puVar5;
  undefined1 *puVar6;
  uint uVar7;
  uint uVar8;
  
  uVar4 = _DAT_f0807004 | _DAT_f0807000;
  if (uVar4 != 0) {
    uVar8 = _DAT_f0807010 & 0xffff;
    uVar1 = _DAT_f080700c & 0xfffe0000;
    uVar2 = _DAT_f080700c >> 0xf;
    uVar7 = _DAT_f080700c & 0x8000;
    puVar5 = &uni_phy;
    do {
      while ((uVar8 == 0 && (uVar1 == 0))) {
        if (uVar2 == 0) goto LAB_00013440;
        uVar3 = *puVar5;
LAB_00013470:
        gephy_flag = 0;
        zx_mdio_write(uVar3,0x10,0xb640,uVar4,param_4);
        puVar6 = puVar5 + 1;
        zx_mdio_write(*puVar5,0x11,param_1);
        uVar4 = extraout_r3;
        puVar5 = puVar6;
        if (puVar6 == &DAT_000216ec) {
          return 0;
        }
      }
      if (uVar7 != 0) {
        uVar3 = *puVar5;
        uVar4 = 0;
        goto LAB_00013470;
      }
LAB_00013440:
      puVar5 = puVar5 + 1;
    } while (puVar5 != &DAT_000216ec);
  }
  return 0;
}


/* ============= FUNCTION: gephy_tx_dac_drv_force_enable @ 000134a8 ============= */

void gephy_tx_dac_drv_force_enable(int param_1,int param_2)

{
  gephy_flag = 0;
  if (g_phy_dbg_lvl != '\0') {
    printk("Debug:GE%u tx dac drv force:%u",param_1,param_2);
  }
  if (param_2 == 0) {
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb676);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb677);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb667);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb668);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb6c2);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb6c1);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb678);
    zx_mdio_write((&uni_phy)[param_1],0x11,0xf);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb669);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
  }
  else if (param_2 == 1) {
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb676);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb677);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb667);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb668);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb6c2);
    zx_mdio_write((&uni_phy)[param_1],0x11,2);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb6c1);
    zx_mdio_write((&uni_phy)[param_1],0x11,1);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb678);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb669);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
  }
  gephy_flag = 1;
  return;
}


/* ============= FUNCTION: zx_phy_int @ 00013714 ============= */

undefined4 zx_phy_int(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  
  *(undefined1 *)((int)&has_phy_int + (param_2 & 3)) = 1;
  iVar1 = (*(uint *)(g_phy_hwirq + (param_2 & 3) * 4) >> 5) * 4;
  piVar2 = (int *)(iVar1 + -0xfefee80);
  *piVar2 = 1 << (*(uint *)(g_phy_hwirq + (param_2 & 3) * 4) & 0x1f);
  iVar1 = _test_and_set_bit(0,DAT_0001377c,piVar2,iVar1,param_4);
  if (iVar1 == 0) {
    __tasklet_hi_schedule(DAT_00013780);
  }
  return 1;
}


/* ============= FUNCTION: gephy_ldo_timer_func @ 00013784 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void gephy_ldo_timer_func(void)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  undefined4 uVar4;
  ushort uVar5;
  ushort uVar6;
  uint uVar7;
  byte bVar8;
  undefined1 *puVar9;
  uint uVar10;
  uint *puVar11;
  char *pcVar12;
  char *pcVar13;
  byte *pbVar14;
  uint *puVar15;
  char *pcVar16;
  uint *puVar17;
  byte *pbVar18;
  ushort *puVar19;
  uint *puVar20;
  int iVar21;
  int iVar22;
  bool bVar23;
  undefined1 *local_4c;
  int local_44;
  ushort local_38 [4];
  ushort local_30 [6];
  
  puVar9 = &uni_phy;
  if (gephy_flag != '\0') {
    iVar21 = temp_ctrl_read();
    if (_DAT_f0807004 != 0 || _DAT_f0807000 != 0) {
      pcVar12 = (char *)&LdoCfgFlag2;
      pcVar16 = (char *)&LdoCfgFlag1;
      if (0x32 < iVar21) goto LAB_00013d00;
      do {
        if (*pcVar16 == '\x01') {
          uVar2 = *puVar9;
          *pcVar16 = '\0';
          *pcVar12 = '\x01';
          zx_mdio_write(uVar2,0x10,0xb640);
          zx_mdio_write(*puVar9,0x11,0x1f);
        }
        while( true ) {
          pcVar16 = pcVar16 + 1;
          pcVar12 = pcVar12 + 1;
          puVar9 = puVar9 + 1;
          if (pcVar16 == (char *)&LdoCfgFlag2) goto LAB_000137a0;
          if (iVar21 < 0x33) break;
LAB_00013d00:
          if ((0x3b < iVar21) && (*pcVar12 == '\x01')) {
            uVar2 = *puVar9;
            *pcVar16 = '\x01';
            *pcVar12 = '\0';
            zx_mdio_write(uVar2,0x10,0xb640);
            zx_mdio_write(*puVar9,0x11,0x1c);
          }
        }
      } while( true );
    }
    pcVar16 = (char *)&LdoCfgFlag1;
    pcVar12 = (char *)&LdoCfgFlag2;
    if (0x32 < iVar21) goto LAB_00013c44;
    do {
      if (*pcVar16 == '\x01') {
        zx_mdio_write(*puVar9,0x10,0xb640);
        zx_mdio_write(*puVar9,0x11,0x1f);
        *pcVar12 = '\x01';
        *pcVar16 = '\0';
      }
      while( true ) {
        puVar9 = puVar9 + 1;
        pcVar16 = pcVar16 + 1;
        pcVar12 = pcVar12 + 1;
        if (puVar9 == &DAT_000216ec) goto LAB_000137a0;
        if (iVar21 < 0x33) break;
LAB_00013c44:
        if ((0x3b < iVar21) && (*pcVar12 == '\x01')) {
          zx_mdio_write(*puVar9,0x10,0xb640);
          zx_mdio_write(*puVar9,0x11,0x1c);
          *pcVar16 = '\x01';
          *pcVar12 = '\0';
        }
      }
    } while( true );
  }
LAB_000137a0:
  pcVar16 = DAT_00013ed8;
  if (g_phy_avoid_button == '\0') {
    puVar11 = (uint *)&g_phy_dbg_lvl;
  }
  else {
    uVar10 = 0;
    pcVar12 = DAT_00013ed8;
    pcVar13 = DAT_00013edc;
    do {
      if (((*pcVar13 == '\x01') && (*pcVar12 == '\x01')) && (pcVar16[uVar10 + 8] == '\x01')) {
        gephy_tx_dac_drv_force_enable(uVar10 & 0xff,0);
        *pcVar12 = '\0';
      }
      uVar10 = uVar10 + 1;
      pcVar12 = pcVar12 + 1;
      pcVar13 = pcVar13 + 1;
    } while (uVar10 != 4);
    puVar9 = &uni_phy;
    puVar11 = DAT_00013ee0 + -0x10;
    puVar17 = DAT_00013ee0 + 4;
    puVar15 = DAT_00013ee0 + 5;
    uVar10 = 0;
    local_4c = &uni_phy;
    puVar20 = DAT_00013ee0;
    do {
      uVar7 = zx_mdio_read(*puVar9,5);
      if ((uVar7 & 0x60) == 0) {
        iVar21 = 3;
      }
      else {
        iVar21 = 0;
      }
      if ((uVar7 & 0x180) != 0) {
        iVar21 = 1;
      }
      uVar7 = zx_mdio_read(*puVar9,10);
      if ((uVar7 & 0xc00) == 0) {
        if ((char)*puVar11 != '\0') goto LAB_00013e98;
LAB_00013a28:
        if (((iVar21 != 3) || (DAT_00013edc[uVar10] != '\x01')) || (DAT_00013eec[uVar10] != '\0'))
        goto LAB_00013880;
        uVar7 = *puVar20;
        if ((char)*puVar15 == '\0') {
          uVar7 = uVar7 + 1;
          *puVar20 = uVar7;
        }
      }
      else {
        if ((char)*puVar11 != '\0') {
          iVar21 = 2;
LAB_00013e98:
          printk("DEBUG:gephy link partner ability mac:%u speed:%s\n",uVar10,(&phy_speed)[iVar21]);
          goto LAB_00013a28;
        }
LAB_00013880:
        uVar7 = *puVar20;
      }
      iVar21 = DAT_00013ee4;
      if ((4 < uVar7) && (*(char *)(uVar10 + DAT_00013ee4) == '\0')) {
        cVar1 = *(char *)(DAT_00013ee4 + -0x5c);
        iVar22 = DAT_00013ee4 + 8;
        *(undefined1 *)(uVar10 + DAT_00013ee4 + 4) = 0;
        *(undefined1 *)(uVar10 + iVar22) = 0;
        *(undefined1 *)(uVar10 + iVar21) = 1;
        if (cVar1 != '\0') {
          printk("DEBUG:Port[%u] LinkStatus:%u no cable cnt:%u,reneg cnt:%u\n",uVar10,
                 *(undefined1 *)(uVar10 + iVar21 + -4),uVar7,0);
        }
      }
      iVar21 = zx_mdio_read(*puVar9,0);
      if ((*puVar20 < 0x1e) || ((char)*puVar15 != '\0')) {
        if ((iVar21 << 0x14 < 0) && ((char)*puVar17 == '\0')) {
          gephy_tx_dac_drv_force_enable(uVar10 & 0xff);
          uVar7 = *puVar11;
          *(char *)puVar17 = '\x01';
          if ((char)uVar7 != '\0') {
            printk("DEBUG:Port[%u] Powerdown and txDacTxDrvNoForce:%u\n",uVar10);
          }
        }
      }
      else {
        gephy_tx_dac_drv_force_enable(uVar10 & 0xff);
        uVar7 = *puVar11;
        *(char *)puVar15 = '\x01';
        if ((char)uVar7 != '\0') {
          printk("DEBUG:Port[%u] no cable cnt:%u txDacTxDrvNoForce Flag:%u\n",uVar10,*puVar20);
        }
      }
      uVar10 = uVar10 + 1;
      puVar9 = puVar9 + 1;
      puVar20 = puVar20 + 1;
      puVar17 = (uint *)((int)puVar17 + 1);
      puVar15 = (uint *)((int)puVar15 + 1);
    } while (uVar10 != 4);
    pbVar18 = DAT_00013ee8 + 4;
    puVar19 = local_38;
    uVar10 = 0;
    puVar9 = &uni_phy;
    local_30[0] = 0;
    local_30[1] = 0;
    local_30[2] = 0;
    local_30[3] = 0;
    pbVar14 = DAT_00013ee8;
    do {
      zx_mdio_read(*puVar9,0x1a);
      (*_request_threaded_irq)(0x1a36e);
      iVar21 = zx_mdio_read(*puVar9,0x1a);
      if (*pbVar14 < 0x14) {
        bVar8 = *pbVar18;
        if (DAT_00013eec[uVar10] == '\x01') {
          bVar23 = bVar8 == 0x1d;
          if (bVar8 < 0x1e) {
            bVar23 = (uint)(iVar21 << 0x16) >> 0x1e == 2;
          }
          if (bVar23) {
            uVar5 = zx_mdio_read(*puVar9,10);
            uVar2 = *puVar9;
            local_30[uVar10] = uVar5 & 0xff;
            uVar6 = zx_mdio_read(uVar2,0x14);
            iVar21 = DAT_00013ef0;
            *puVar19 = uVar6;
            iVar22 = *(int *)(npp_base + uVar10 * 0x40000 + 0x40788);
            uVar5 = local_30[uVar10];
            if ((uVar5 == 0) && (uVar6 == 0)) {
LAB_00013b10:
              bVar8 = *pbVar18 + 1;
              *pbVar18 = bVar8;
            }
            else if ((iVar22 == 0) || (iVar22 == *(int *)(DAT_00013ef0 + uVar10 * 4))) {
              local_44 = uVar10 * 4;
              gephy_tx_dac_drv_force_enable(uVar10 & 0xff,1);
              uVar2 = *puVar9;
              *pbVar14 = *pbVar14 + 1;
              zx_mdio_write(uVar2,0,0x1340);
              uVar7 = *puVar11;
              *pbVar18 = 0;
              bVar8 = 0;
              if ((char)uVar7 != '\0') {
                printk("Err:GE %u have idle err:%u,data err:%u,oct:%u,g_oct:%u restart auto-neg times:%u\n"
                       ,uVar10,uVar5,*puVar19,iVar22,*(undefined4 *)(iVar21 + local_44),*pbVar14);
                bVar8 = *pbVar18;
              }
            }
            else {
              if ((uVar5 == 0) && (*puVar19 == 0)) goto LAB_00013b10;
              bVar8 = *pbVar18;
            }
            local_44 = uVar10 * 4;
            *(int *)(iVar21 + local_44) = iVar22;
          }
        }
      }
      else {
        bVar8 = *pbVar18;
      }
      uVar10 = uVar10 + 1;
      puVar9 = puVar9 + 1;
      if (bVar8 == 0x1e) {
        *pbVar14 = 0;
      }
      pbVar18 = pbVar18 + 1;
      puVar19 = puVar19 + 1;
      pbVar14 = pbVar14 + 1;
    } while (uVar10 != 4);
    uVar10 = 0;
    pcVar12 = DAT_00013eec + 0x24;
    pbVar14 = (byte *)(DAT_00013eec + 0x28);
    pcVar16 = DAT_00013eec;
    do {
      zx_mdio_read(*local_4c,0x1a);
      iVar21 = zx_mdio_read(*local_4c,0x1a);
      uVar7 = (uint)(iVar21 << 0x16) >> 0x1e;
      bVar23 = uVar7 == 1;
      if (uVar7 < 2) {
        bVar23 = *pcVar16 == '\x01';
      }
      bVar8 = *pbVar14;
      if ((bVar23) && (bVar8 < 0x1e)) {
        bVar8 = bVar8 + 1;
        *pbVar14 = bVar8;
      }
      pbVar14 = pbVar14 + 1;
      if ((bVar8 == 0x1e) && (*pcVar12 == '\0')) {
        gephy_tx_dac_drv_force_enable(uVar10 & 0xff);
        uVar3 = *puVar11;
        *pcVar12 = '\x01';
        if ((char)uVar3 != '\0') {
          printk("DEBUG:Port[%u] link no ge and txDacDrvNoForce:%s\n",uVar10,(&phy_speed)[uVar7]);
        }
      }
      uVar10 = uVar10 + 1;
      pcVar12 = pcVar12 + 1;
      pcVar16 = pcVar16 + 1;
      local_4c = local_4c + 1;
    } while (uVar10 != 4);
  }
  uVar4 = DAT_00013ed4;
  puVar11[9] = jiffies + 200;
  add_timer(uVar4);
  return;
}


/* ============= FUNCTION: pon_npp_smac_config_speed_duplex.part.0 @ 00013ef4 ============= */

void pon_npp_smac_config_speed_duplex_part_0(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_1 * 0x40000 + 0x40000;
  uVar2 = *(uint *)(npp_base + iVar1);
  if (param_2 == 2) {
    uVar2 = uVar2 & 0xffff7fff | 0x2000;
  }
  else {
    if (param_3 == 0) {
      uVar2 = uVar2 & 0xffffdfff | 0x8000;
    }
    else {
      uVar2 = uVar2 | 0xa000;
    }
    if (param_2 == 1) {
      uVar2 = uVar2 | 0x4000;
    }
    else {
      uVar2 = uVar2 & 0xffffbfff;
    }
  }
  *(uint *)(npp_base + iVar1) = uVar2;
  return;
}


/* ============= FUNCTION: pon_npp_smac_enable.part.3 @ 00013f50 ============= */

void pon_npp_smac_enable_part_3(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x40000 + 0x40000;
  *(uint *)(npp_base + iVar1) = *(uint *)(npp_base + iVar1) | 3;
  return;
}


/* ============= FUNCTION: pon_npp_smac_disable.part.4 @ 00013f80 ============= */

void pon_npp_smac_disable_part_4(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x40000 + 0x40000;
  *(uint *)(npp_base + iVar1) = *(uint *)(npp_base + iVar1) & 0xfffffffc;
  return;
}


/* ============= FUNCTION: switch_phy_int_check.part.5 @ 00013fb0 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void switch_phy_int_check_part_5(uint param_1)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  int unaff_r7;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  bool bVar12;
  
  if (param_1 < 4) {
    zx_mdio_read((&uni_phy)[param_1],0x1a);
    iVar7 = 10;
    do {
      (*_request_threaded_irq)(0x66665b0);
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    uVar6 = zx_mdio_read((&uni_phy)[param_1],0x1a);
    if ((uVar6 & 0x40) == 0) {
      printk("mac %d link down\n",param_1);
      pon_npp_smac_disable_part_4(param_1);
      *(undefined1 *)((int)&g_linkStatus + param_1) = 0;
      return;
    }
    uVar6 = uVar6 & 0x380;
    uVar8 = uVar6 >> 8;
    bVar12 = g_phy_avoid_button != '\0';
    if (!bVar12) {
      unaff_r7 = param_1 << 2;
    }
    *(undefined1 *)((int)&g_linkStatus + param_1) = 1;
    if (bVar12) {
      unaff_r7 = param_1 * 4;
      *(undefined1 *)((int)&g_noerr_times + param_1) = 0;
      *(undefined1 *)((int)&no_cable_en + param_1) = 0;
      *(undefined1 *)((int)&g_txNoForceFlag + param_1) = 0;
      *(undefined1 *)((int)&g_phyPwrdnFlag + param_1) = 0;
      *(undefined1 *)((int)&g_speed_un_ge_cnt + param_1) = 0;
      *(undefined1 *)((int)&g_speed_action_flag + param_1) = 0;
      cVar1 = *(char *)((int)&g_geLdoFlag + param_1);
      *(undefined4 *)(g_no_cable_cnt + unaff_r7) = 0;
      bVar3 = g_reneg_times;
      if (cVar1 == '\0') {
        bVar3 = 0;
      }
      if (*(int *)(g_SpeedChange + unaff_r7) == 1) {
        uVar9 = zx_mdio_read((&uni_phy)[param_1],9);
        if (((uVar8 == 1) && ((uVar9 & 0x300) != 0)) &&
           (*(byte *)((int)&gephy_reneg_cnt + param_1) < bVar3)) {
          uVar4 = 0;
          puVar5 = (undefined4 *)g_no_cable_cnt;
          puVar10 = &g_txNoForceFlag;
          do {
            uVar2 = uVar4 & 0xff;
            uVar4 = uVar4 + 1;
            gephy_tx_dac_drv_force_enable(uVar2);
            *puVar5 = 0;
            *(undefined1 *)puVar10 = 0;
            puVar5 = puVar5 + 1;
            puVar10 = (undefined4 *)((int)puVar10 + 1);
          } while (uVar4 != 4);
          *(char *)((int)&gephy_reneg_cnt + param_1) =
               *(char *)((int)&gephy_reneg_cnt + param_1) + '\x01';
          zx_mdio_write((&uni_phy)[param_1],0,0x1340);
          if (g_phy_dbg_lvl != '\0') {
            printk("%s %d mac %u own parten 0x%x speed %s re auto-neg\n",DAT_000142d8,0x568,param_1,
                   uVar9,&_LC14);
          }
        }
        *(undefined4 *)(g_SpeedChange + unaff_r7) = 0;
      }
    }
    if (uVar6 == *(uint *)(uni_phy_stat + unaff_r7)) {
      pon_npp_smac_enable_part_3(param_1);
      return;
    }
    if (uVar8 == 3) {
      return;
    }
    uVar9 = (uVar6 << 0x18) >> 0x1f;
  }
  else {
    if (4 < param_1) {
      pon_reset(1 << (param_1 + 6 & 0xff));
      smac_init(param_1);
      unaff_r7 = param_1 << 2;
      smac_sopc_mode_switch(param_1,0);
      uVar6 = 0;
      goto LAB_00014000;
    }
    uVar9 = 0;
    unaff_r7 = param_1 << 2;
    uVar8 = 0;
    uVar6 = 0;
  }
  iVar7 = param_1 * 0x40000 + 0x40090;
  uVar11 = *(undefined4 *)(npp_base + iVar7);
  pon_reset(1 << (param_1 + 6 & 0xff));
  smac_init(param_1);
  pon_npp_smac_config_speed_duplex_part_0(param_1,uVar8,uVar9);
  smac_sopc_mode_switch(param_1,uVar9);
  pon_npp_smac_enable_part_3(param_1);
  *(undefined4 *)(npp_base + iVar7) = uVar11;
LAB_00014000:
  *(uint *)(uni_phy_stat + unaff_r7) = uVar6;
  *(int *)(g_lanPortRstMonitor + unaff_r7) = *(int *)(g_lanPortRstMonitor + unaff_r7) + 1;
  return;
}


/* ============= FUNCTION: phy_process @ 000142dc ============= */

void phy_process(void)

{
  char *pcVar1;
  undefined1 uVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  
  pcVar3 = DAT_00014374;
  uVar6 = 0;
  pcVar7 = DAT_00014374;
  do {
    if (*pcVar7 != '\0') {
      uVar2 = (&uni_phy)[uVar6];
      *pcVar7 = '\0';
      uVar4 = zx_mdio_read(uVar2,0x19);
      uVar5 = *(uint *)(pcVar3 + uVar6 * 4 + 8);
      if ((uVar4 & 2) != 0) {
        pcVar1 = pcVar3 + uVar6 * 4 + 0x80;
        pcVar1[0] = '\x01';
        pcVar1[1] = '\0';
        pcVar1[2] = '\0';
        pcVar1[3] = '\0';
      }
      *(int *)((uVar5 >> 5) * 4 + -0xfefef00) = 1 << (uVar5 & 0x1f);
      if (uVar6 != 4) {
        switch_phy_int_check_part_5(uVar6 & 0xff);
      }
    }
    uVar6 = uVar6 + 1;
    pcVar7 = pcVar7 + 1;
  } while (uVar6 != 5);
  return;
}


/* ============= FUNCTION: pon_npp_smac_config_speed_duplex @ 00014378 ============= */

void pon_npp_smac_config_speed_duplex(uint param_1)

{
  if (4 < param_1) {
    return;
  }
  pon_npp_smac_config_speed_duplex_part_0();
  return;
}


/* ============= FUNCTION: gephy_ldo_init @ 00014384 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 gephy_ldo_init(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 *in_r3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  
  puVar7 = &g_geLdoFlag;
  puVar4 = &uni_phy;
  puVar8 = in_r3;
  do {
    puVar5 = puVar4 + 1;
    zx_mdio_write(*puVar4,0x17,0x2448,in_r3,puVar8);
    uVar3 = _DAT_f0807010;
    uVar6 = _DAT_f080700c;
    iVar2 = _DAT_f0807004;
    iVar1 = _DAT_f0807000;
    zx_mdio_write(*puVar4,0x10,0xb640);
    if (iVar2 == 0 && iVar1 == 0) {
      zx_mdio_write(*puVar4,0x11,0x1f);
      *(undefined1 *)puVar7 = 0;
    }
    else {
      if (((uVar3 & 0xffff) == 0) && ((uVar6 & 0xfffe0000) == 0)) {
        uVar6 = uVar6 >> 0xf;
      }
      else {
        uVar6 = uVar6 & 0x8000;
      }
      if (uVar6 == 0) {
        zx_mdio_write(*puVar4,0x11,0x1f);
        *(undefined1 *)puVar7 = 0;
      }
      else {
        zx_mdio_write(*puVar4,0x11,0x1f);
        *(undefined1 *)puVar7 = 1;
      }
    }
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    in_r3 = DAT_00014458;
    puVar4 = puVar5;
  } while (puVar5 != DAT_00014458);
  return 0;
}


/* ============= FUNCTION: smac_del_extphy_scan @ 0001445c ============= */

void smac_del_extphy_scan(void)

{
  del_timer(DAT_00014464);
  return;
}


/* ============= FUNCTION: switch_smac_get_rx_flow_crtl @ 00014468 ============= */

undefined4 switch_smac_get_rx_flow_crtl(uint param_1)

{
  if (param_1 < 5) {
    return *(undefined4 *)(npp_base + param_1 * 0x40000 + 0x40090);
  }
  return 0;
}


/* ============= FUNCTION: switch_smac_set_rx_flow_crtl @ 0001449c ============= */

void switch_smac_set_rx_flow_crtl(uint param_1,undefined4 param_2)

{
  if (4 < param_1) {
    return;
  }
  *(undefined4 *)(npp_base + param_1 * 0x40000 + 0x40090) = param_2;
  return;
}


/* ============= FUNCTION: switch_phy_int_check @ 000144c8 ============= */

void switch_phy_int_check(uint param_1)

{
  if (3 < param_1) {
    return;
  }
  switch_phy_int_check_part_5();
  return;
}


/* ============= FUNCTION: register_phy_int @ 000144d4 ============= */

undefined4 register_phy_int(void)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  undefined4 local_28 [4];
  
  local_28[0] = *DAT_00014560;
  local_28[1] = DAT_00014560[1];
  local_28[2] = DAT_00014560[2];
  local_28[3] = DAT_00014560[3];
  iVar3 = 0;
  puVar4 = (undefined4 *)g_phy_irq;
  puVar5 = &uni_phy;
  puVar6 = DAT_00014564;
  do {
    iVar2 = irq_to_desc(*puVar4);
    uVar1 = *puVar5;
    *puVar6 = *(undefined4 *)(iVar2 + 8);
    zx_mdio_write(uVar1,0x18,5);
    iVar2 = iVar3 + 1;
    request_threaded_irq(*puVar4,zx_phy_int,0,0,local_28[iVar3],iVar3);
    iVar3 = iVar2;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  } while (iVar2 != 4);
  return 0;
}


/* ============= FUNCTION: pon_npp_smac_enable @ 00014568 ============= */

void pon_npp_smac_enable(uint param_1)

{
  if (4 < param_1) {
    return;
  }
  pon_npp_smac_enable_part_3();
  return;
}


/* ============= FUNCTION: pon_npp_smac_disable @ 00014574 ============= */

void pon_npp_smac_disable(uint param_1)

{
  if (4 < param_1) {
    return;
  }
  pon_npp_smac_disable_part_4();
  return;
}


/* ============= FUNCTION: extphy_timer_func @ 00014580 ============= */

void extphy_timer_func(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  uVar5 = (uint)(byte)lan_up_port;
  iVar1 = uVar5 * 4;
  uVar2 = zx_mdio_read((&uni_phy)[uVar5],0x1e);
  zx_mdio_write((&uni_phy)[uVar5],0x1e,0);
  zx_mdio_read((&uni_phy)[uVar5],0x1a);
  uVar3 = zx_mdio_read((&uni_phy)[uVar5],0x1a);
  zx_mdio_write((&uni_phy)[uVar5],0x1e,uVar2);
  if ((uVar3 & 0x380) == *(uint *)(uni_phy_stat + iVar1)) {
    pon_npp_smac_enable(uVar5);
  }
  else if ((uVar3 & 0x40) == 0) {
    if (*(uint *)(uni_phy_stat + iVar1) != 0xffffffff) {
      *(undefined4 *)(uni_phy_stat + iVar1) = 0xffffffff;
      printk("mac %d link down,s %.4x\n",uVar5,uVar3);
    }
    pon_npp_smac_disable(uVar5);
  }
  else {
    uVar6 = (uVar3 << 9) >> 0x10;
    printk("status=0x%x \n",uVar3);
    uVar4 = uVar6 & 7;
    if (uVar4 < 2) {
      iVar8 = 0;
    }
    else if (uVar4 - 2 < 2) {
      iVar8 = 1;
    }
    else if (uVar4 - 4 < 2) {
      iVar8 = 2;
    }
    else {
      iVar8 = 0;
    }
    uVar6 = uVar6 & 5;
    if (uVar4 == 4 || uVar6 == 0) {
      iVar7 = 0;
    }
    else if (uVar6 == 1 || uVar4 == 5) {
      iVar7 = 1;
    }
    else {
      iVar7 = 0;
    }
    printk("mac %d phy status changed: %s %s\n",uVar5,(&phy_speed)[iVar8],
           *(undefined4 *)((int)&phy_duplex + iVar7 * 4));
    pon_reset(1 << (uVar5 + 6 & 0xff));
    smac_init(uVar5);
    pon_npp_smac_config_speed_duplex(uVar5,iVar8,iVar7);
    smac_sopc_mode_switch(uVar5,iVar7);
    pon_npp_smac_enable(uVar5);
    *(uint *)(uni_phy_stat + iVar1) = uVar3 & 0x380;
  }
  extphy_timer._8_4_ = jiffies + 10;
  add_timer(DAT_00014748);
  return;
}


/* ============= FUNCTION: pon_npp_smac_mode @ 0001474c ============= */

void pon_npp_smac_mode(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = (param_1 + 0x18) * 4;
  *(uint *)(npp_base + iVar1) = *(uint *)(npp_base + iVar1) & 0xfc7fffff | param_2;
  return;
}


/* ============= FUNCTION: zx5201_config @ 00014780 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zx5201_config(void)

{
  undefined4 uVar1;
  undefined4 in_r3;
  uint uVar2;
  
  DataSynchronizationBarrier(0xf);
  uVar2 = uRamf060000c & 0xffe7f7ff;
  DataSynchronizationBarrier(0xe);
  if (_kallsyms_lookup != (code *)0x0) {
    (*_kallsyms_lookup)();
  }
  uRamf060000c = uVar2;
  zx_mdio_write(8,0x12,0x8402);
  zx_mdio_write(9,0x16,0xa0f);
  zx_mdio_write(9,0x1b,0x800);
  zx_mdio_write(8,0x1d,0x355);
  zx_mdio_write(8,0x10,0xb62d);
  zx_mdio_write(8,0x11,6);
  zx_mdio_write(9,0x12,4);
  uVar2 = zx_mdio_read(9,0x15);
  uVar1 = zx_mdio_read(9,0x14);
  zx_mdio_write(9,0x11,uVar2 & 0xc1ff | 0x2800);
  zx_mdio_write(9,0x10,uVar1);
  zx_mdio_write(9,0x12,0x204);
  uVar2 = zx_mdio_read(9,0x16);
  zx_mdio_write(9,0x16,uVar2 & 0xfff3 | 4);
  if (product_vid != ' ') {
    return;
  }
  uVar2 = zx_mdio_read(9,0x17);
  zx_mdio_write(9,0x17,uVar2 & 0xfff9);
  uVar2 = zx_mdio_read(9,0x17);
  zx_mdio_write(9,0x17,uVar2 & 0xfffe);
  zx_mdio_write(8,0x10,0xb409);
  zx_mdio_write(8,0x11,0);
  zx_mdio_write(8,0x10,0xb407);
  zx_mdio_write(8,0x11,0);
  zx_mdio_write(8,0x10,0xb406);
  zx_mdio_write(8,0x11,0);
  zx_mdio_write(8,0x10,0xb408);
  zx_mdio_write(8,0x11,0,in_r3);
  return;
}


/* ============= FUNCTION: pon_npp_smac_init @ 00014988 ============= */

undefined4 pon_npp_smac_init(void)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  gephy_ldo_init();
  iVar3 = 0x40000;
  uVar2 = 0;
  puVar4 = &uni_phy;
  puVar5 = DAT_00014ae8;
  puVar6 = DAT_00014ae8 + -0x2c;
  do {
    zx_mdio_write(*puVar4,0x10,0x8001);
    zx_mdio_write(*puVar4,0x11,0);
    smac_init(uVar2 & 0xff);
    *(uint *)(npp_base + iVar3) = *(uint *)(npp_base + iVar3) | 2;
    uVar2 = uVar2 + 1;
    iVar3 = iVar3 + 0x40000;
    *(undefined1 *)puVar6 = 1;
    *puVar5 = 0xffffffff;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  } while (uVar2 != 4);
  phy_process(0);
  init_timer_key(gephy_ldo_timer,0,0,0);
  gephy_ldo_timer._8_4_ = jiffies + 200;
  gephy_ldo_timer._16_4_ = gephy_ldo_timer_func;
  gephy_ldo_timer._20_4_ = 0;
  add_timer(gephy_ldo_timer);
  register_phy_int();
  zx5201_config();
  init_timer_key(extphy_timer,0,0,0);
  extphy_timer._8_4_ = jiffies + 10;
  extphy_timer._20_4_ = 0;
  extphy_timer._16_4_ = extphy_timer_func;
  add_timer(extphy_timer);
  uni_phy_stat._16_4_ = 0xffffffff;
  uVar2 = (uint)(byte)lan_up_port;
  uVar1 = zx_mdio_read((&uni_phy)[uVar2],0);
  zx_mdio_write((&uni_phy)[uVar2],0,uVar1 | 0x800);
  return 0;
}


/* ============= FUNCTION: smct_dump_pmau @ 00014aec ============= */

void smct_dump_pmau(void)

{
  printk("left %d\n",*(undefined4 *)(npp_base + 0x100d8));
  return;
}


/* ============= FUNCTION: pon_npp_smct_init @ 00014b0c ============= */

void pon_npp_smct_init(void)

{
  *(undefined4 *)(npp_base + 0x10000) = 0xb;
  *(undefined4 *)(tm_set_onu_mac + npp_base + 4) = 0xb;
  *(undefined4 *)(npp_base + 0x10010) = 0x3810;
  return;
}


/* ============= FUNCTION: pon_npp_spa_init @ 00014b44 ============= */

void pon_npp_spa_init(void)

{
  *(undefined4 *)(npp_base + 0x141c0) = 0;
  return;
}


/* ============= FUNCTION: pon_npp_uopc_init @ 00014b60 ============= */

undefined4 pon_npp_uopc_init(void)

{
  *(uint *)(npp_base + 0x18000) = *(uint *)(npp_base + 0x18000) | 8;
  return 0;
}


/* ============= FUNCTION: hwnat_is_from_cpu @ 00014b8c ============= */

undefined4 hwnat_is_from_cpu(void)

{
  return 1;
}


/* ============= FUNCTION: multicast_flood_is_bind @ 00014b94 ============= */

undefined4 multicast_flood_is_bind(void)

{
  return 1;
}


/* ============= FUNCTION: hwnat_skb_to_foe @ 00014b9c ============= */

undefined4 hwnat_skb_to_foe(void)

{
  return 0;
}


/* ============= FUNCTION: idm_eth_get_stats @ 00014ba4 ============= */

int idm_eth_get_stats(int param_1)

{
  return param_1 + 0x4cc;
}


/* ============= FUNCTION: _idm_skb_stack_pop @ 00014bb0 ============= */

int _idm_skb_stack_pop(int param_1)

{
  int iVar1;
  ushort uVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar1 = param_1 * 4;
  puVar5 = &idm_lock_stack + param_1;
  _raw_spin_lock_bh(puVar5);
  if (*(int *)(idm_skb_stack_idx + iVar1) != 0) {
    iVar4 = *(int *)(idm_skb_stack_idx + iVar1) + -1;
    *(int *)(idm_skb_stack_idx + iVar1) = iVar4;
    iVar4 = *(int *)(idm_skb_stack + (iVar4 + param_1 * 0x400) * 4);
    _raw_spin_unlock_bh(puVar5);
    uVar2 = *(ushort *)(iVar4 + 0xbc);
    uVar3 = *(undefined2 *)(iVar4 + 0xbe);
    *(int *)(idm_pop_cnt + iVar1) = *(int *)(idm_pop_cnt + iVar1) + 1;
    skb_recycle(iVar4);
    if ((uVar2 & 1) != 0) {
      *(undefined2 *)(iVar4 + 0xbe) = uVar3;
      *(ushort *)(iVar4 + 0xbc) = *(ushort *)(iVar4 + 0xbc) | 1;
    }
    return iVar4;
  }
  _raw_spin_unlock_bh(puVar5);
  *(int *)(idm_skb_stack_empty + iVar1) = *(int *)(idm_skb_stack_empty + iVar1) + 1;
  return 0;
}


/* ============= FUNCTION: idm_skb_stack_pop @ 00014c5c ============= */

int idm_skb_stack_pop(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = param_1 + 1;
  if (((int)uVar3 < 3) && (iVar1 = _idm_skb_stack_pop(uVar3 & 0xff), iVar1 != 0)) {
    iVar2 = (*(int *)(iVar1 + 0xc4) - *(int *)(iVar1 + 200)) + -0x20;
    if (param_2 <= iVar2) {
      return iVar1;
    }
    __dev_kfree_skb_any(iVar1,1,iVar2,iVar1,param_4);
    *(int *)(idm_pop_size_err + uVar3 * 4) = *(int *)(idm_pop_size_err + uVar3 * 4) + 1;
    return 0;
  }
  return 0;
}


/* ============= FUNCTION: dump_idm_data @ 00014cd0 ============= */

void dump_idm_data(undefined1 *param_1,uint param_2)

{
  uint uVar1;
  
  if (0x7f < param_2) {
    param_2 = 0x80;
  }
  if (param_2 != 0) {
    uVar1 = 0;
    printk("%.2x ",*param_1);
    while (uVar1 = uVar1 + 1, uVar1 != param_2) {
      printk("%.2x ",param_1[uVar1]);
      if ((uVar1 & 0xf) == 0xf) {
        printk(&_LC0);
      }
    }
  }
  printk(&_LC0);
  return;
}


/* ============= FUNCTION: idm_net_int @ 00014d48 ============= */

undefined4 idm_net_int(void)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  
  iVar1 = (int)idm_netdev;
  puVar3 = (uint *)(npp_base + 0x8020);
  *(int *)((int)idm_netdev + 0x598) = *(int *)((int)idm_netdev + 0x598) + 1;
  puVar4 = (uint *)(npp_base + 0x8024);
  *(uint *)(iVar1 + 0x4c8) = *puVar3 & ~idm_int_mask;
  idm_int_mask = *puVar4 | 0x14;
  *(uint *)(npp_base + 0x8024) = idm_int_mask;
  if ((-1 < *(int *)(iVar1 + 0x530) << 0x1e) &&
     (iVar2 = _test_and_set_bit(0,iVar1 + 0x530), iVar2 == 0)) {
    __napi_schedule(iVar1 + 0x528);
    return 1;
  }
  *(int *)(iVar1 + 0x59c) = *(int *)(iVar1 + 0x59c) + 1;
  return 1;
}


/* ============= FUNCTION: idm_mode_proc_open @ 00014df8 ============= */

void idm_mode_proc_open(undefined4 param_1,undefined4 param_2)

{
  single_open(param_2,idm_proc_read,0);
  return;
}


/* ============= FUNCTION: idm_proc_read @ 00014e0c ============= */

int idm_proc_read(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = seq_printf(param_1,"idm_pop_size_err[0]: %u\n",idm_pop_size_err._0_4_,param_4,param_4);
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_pop_size_err[1]: %u\n",idm_pop_size_err._4_4_);
  iVar3 = seq_printf(param_1 + (iVar1 + iVar2) * 0x58,"idm_pop_size_err[2]: %u\n",
                     idm_pop_size_err._8_4_);
  iVar3 = iVar3 + iVar1 + iVar2;
  iVar1 = seq_printf(param_1 + iVar3 * 0x58,"idm_push_failed[0]: %u\n",idm_push_failed._0_4_);
  iVar1 = iVar1 + iVar3;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed[1]: %u\n",idm_push_failed._4_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_failed[2]: %u\n",idm_push_failed._8_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed_res[0]: %u\n",idm_push_failed_res._0_4_
                    );
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_failed_res[1]: %u\n",idm_push_failed_res._4_4_
                    );
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed_res[2]: %u\n",idm_push_failed_res._8_4_
                    );
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_failed_res[3]: %u\n",
                     idm_push_failed_res._12_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed_res[4]: %u\n",
                     idm_push_failed_res._16_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_failed_res[5]: %u\n",
                     idm_push_failed_res._20_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_failed_res[6]: %u\n",
                     idm_push_failed_res._24_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_cnt[0]: %u\n",idm_push_cnt._0_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_push_cnt[1]: %u\n",idm_push_cnt._4_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_push_cnt[2]: %u\n",idm_push_cnt._8_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_pop_cnt[0]: %u\n",idm_pop_cnt._0_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_pop_cnt[1]: %u\n",idm_pop_cnt._4_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_pop_cnt[2]: %u\n",idm_pop_cnt._8_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_skb_stack_full[0]: %u\n",idm_skb_stack_full._0_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_skb_stack_full[1]: %u\n",idm_skb_stack_full._4_4_);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_skb_stack_full[2]: %u\n",idm_skb_stack_full._8_4_);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_skb_stack_empty[0]: %u\n",idm_skb_stack_empty._0_4_
                    );
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_skb_stack_empty[1]: %u\n",idm_skb_stack_empty._4_4_
                    );
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_skb_stack_empty[2]: %u\n",idm_skb_stack_empty._8_4_
                    );
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_rx_arp_count: %u\n",idm_rx_arp_count);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_poll_cnt: %u\n",idm_poll_cnt);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_txtq_err: %u\n",idm_txtq_err);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_tx_done_total: %u\n",idm_tx_done_total);
  iVar2 = iVar2 + iVar1;
  iVar1 = seq_printf(param_1 + iVar2 * 0x58,"idm_tx_full: %u\n",idm_tx_full);
  iVar1 = iVar1 + iVar2;
  iVar2 = seq_printf(param_1 + iVar1 * 0x58,"idm_sw_tx_full: %u\n",idm_sw_tx_full);
  return iVar2 + iVar1;
}


/* ============= FUNCTION: idm_proc_write @ 000151fc ============= */

undefined4 idm_proc_write(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined1 auStack_30 [4];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  uVar6 = *(uint *)(((uint)auStack_30 & 0xffffe000) + 8);
  uVar4 = param_2 + 1;
  uVar5 = uVar4;
  if (param_2 != -1) {
    uVar5 = uVar4 - (uVar6 + 1);
  }
  if (param_2 != -1 && uVar4 <= uVar6) {
    uVar6 = 0;
  }
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (uVar6 == 0) {
    iVar2 = __copy_from_user(&local_2c,param_2,1);
    if (iVar2 == 0) {
      iVar3 = simple_strtoul(&local_2c,0,10);
      iVar2 = DAT_00015310;
      if (iVar3 == 0) {
        return param_3;
      }
      printk("clean idm stat\n");
      iVar1 = DAT_00015314;
      iVar8 = DAT_00015314 + 0x18;
      iVar7 = DAT_00015314 + 0x40;
      iVar10 = DAT_00015314 + -0xc;
      iVar9 = DAT_00015314 + 0x4c;
      iVar3 = 0;
      do {
        *(undefined4 *)(iVar1 + iVar3 * 4) = 0;
        *(undefined4 *)(iVar8 + iVar3 * 4) = 0;
        *(undefined4 *)(iVar7 + iVar3 * 4) = 0;
        *(undefined4 *)(iVar10 + iVar3 * 4) = 0;
        *(undefined4 *)(iVar9 + iVar3 * 4) = 0;
        *(undefined4 *)(iVar2 + iVar3 * 4) = 0;
        iVar3 = iVar3 + 1;
      } while (iVar3 != 3);
      idm_rx_arp_count = 0;
      idm_poll_cnt = 0;
      idm_txtq_err = 0;
      idm_tx_done_total = 0;
      idm_tx_full = 0;
      idm_sw_tx_full = 0;
      return param_3;
    }
  }
  else {
    __memzero(&local_2c,1,uVar5);
  }
  printk(&_LC33);
  return 0xffffffff;
}


/* ============= FUNCTION: idm_net_register @ 00015318 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * idm_net_register(undefined4 param_1,char *param_2)

{
  char *__dest;
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  __dest = (char *)alloc_etherdev_mqs(0xf0,1,1);
  if (__dest == (char *)0x0) {
    return (char *)0x0;
  }
  *(char **)(__dest + 0x4c0) = __dest;
  *(undefined4 *)(__dest + 0x4c4) = param_1;
  *(undefined1 **)(__dest + 300) = &idm_net_netdev_ops;
  uVar1 = msecs_to_jiffies(5000);
  *(undefined4 *)(__dest + 600) = uVar1;
  strcpy(__dest,param_2);
  puVar3 = *(undefined4 **)(__dest + 0x1dc);
  _DAT_00021724 = CONCAT11((char)param_1,DAT_00021724);
  *puVar3 = idm_mac;
  idm_lock_stack = 0;
  idm_lock_tx = 0;
  *(undefined2 *)(puVar3 + 1) = _DAT_00021724;
  DAT_000285b8 = 0;
  DAT_000285bc = 0;
  idm_lock_tx_done = 0;
  iVar2 = register_netdev(__dest);
  if (-1 < iVar2) {
    return __dest;
  }
  free_netdev(__dest);
  return (char *)0x0;
}


/* ============= FUNCTION: idm_net_timeout @ 000153dc ============= */

void idm_net_timeout(int param_1)

{
  netif_tx_wake_queue(*(undefined4 *)(param_1 + 0x240));
  *(undefined4 *)(param_1 + 0x260) = jiffies;
  return;
}


/* ============= FUNCTION: idm_net_stop @ 00015400 ============= */

undefined4 idm_net_stop(char *param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x240) == 0) {
    warn_slowpath_null("include/linux/netdevice.h",0xa06);
    printk(&_LC36);
  }
  else {
    _set_bit(0,*(int *)(param_1 + 0x240) + 0x50);
  }
  netif_carrier_off(param_1);
  iVar1 = strcmp(param_1,"idm0");
  if (iVar1 == 0) {
    napi_disable(param_1 + 0x528);
    idm_int_mask = *(uint *)(npp_base + 0x8024) | 0x14;
    *(uint *)(npp_base + 0x8024) = idm_int_mask;
  }
  return 0;
}


/* ============= FUNCTION: idm_net_open @ 000154ac ============= */

undefined4 idm_net_open(char *param_1)

{
  code *pcVar1;
  int iVar2;
  
  _clear_bit(0,*(int *)(param_1 + 0x240) + 0x50);
  netif_carrier_on(param_1);
  iVar2 = strcmp(param_1,"idm0");
  if (iVar2 == 0) {
    if ((*(uint *)(param_1 + 0x530) & 1) == 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)software_udf(0x12,0x1553c);
      (*pcVar1)();
    }
    DataMemoryBarrier(0xb);
    _clear_bit(0,param_1 + 0x530);
    idm_int_mask = *(uint *)(npp_base + 0x8024) & 0xfffffffb;
    *(uint *)(npp_base + 0x8024) = idm_int_mask;
  }
  return 0;
}


/* ============= FUNCTION: _idm_skb_stack_push @ 00015540 ============= */

undefined4 _idm_skb_stack_push(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  if ((*(int *)(param_1 + 0x68) == 0) && ((*(byte *)(param_1 + 0x72) & 0xc) == 0)) {
    if (*(int *)(param_1 + 0xc4) - *(int *)(param_1 + 200) < 0x660) {
      idm_push_failed_res._12_4_ = idm_push_failed_res._12_4_ + 1;
    }
    else if (*(int *)(param_1 + 0xd4) == 1) {
      if (((*(byte *)(param_1 + 0x72) & 1) == 0) ||
         ((*(uint *)(*(int *)(param_1 + 0xc4) + 0x20) & 0xffff) == 1)) {
        iVar1 = param_2 * 4;
        puVar3 = &idm_lock_stack + param_2;
        _raw_spin_lock_bh(puVar3);
        uVar2 = *(uint *)(idm_skb_stack_idx + iVar1);
        if (0x3ff < uVar2) {
          _raw_spin_unlock_bh(puVar3);
          *(int *)(idm_skb_stack_full + iVar1) = *(int *)(idm_skb_stack_full + iVar1) + 1;
          __dev_kfree_skb_any(param_1);
          return 0xffffffff;
        }
        *(uint *)(idm_skb_stack_idx + iVar1) = uVar2 + 1;
        *(int *)(idm_skb_stack + (uVar2 + param_2 * 0x400) * 4) = param_1;
        _raw_spin_unlock_bh(puVar3);
        *(int *)(idm_push_cnt + iVar1) = *(int *)(idm_push_cnt + iVar1) + 1;
        return 0;
      }
      idm_push_failed_res._20_4_ = idm_push_failed_res._20_4_ + 1;
    }
    else {
      idm_push_failed_res._16_4_ = idm_push_failed_res._16_4_ + 1;
    }
  }
  else {
    idm_push_failed_res._8_4_ = idm_push_failed_res._8_4_ + 1;
  }
  *(int *)(idm_push_failed + param_2 * 4) = *(int *)(idm_push_failed + param_2 * 4) + 1;
  __dev_kfree_skb_any(param_1);
  return 0;
}


/* ============= FUNCTION: idm_skb_stack_push @ 000156c0 ============= */

void idm_skb_stack_push(int param_1)

{
  if ((*(ushort *)(param_1 + 0xbc) & 0x10) == 0) {
    __dev_kfree_skb_any(param_1,1);
    return;
  }
  _idm_skb_stack_push(param_1,0);
  return;
}


/* ============= FUNCTION: idm_check_tx_done_nolock @ 000156dc ============= */

int idm_check_tx_done_nolock(void)

{
  ushort uVar1;
  uint uVar2;
  undefined4 in_r3;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar3 = *(uint *)(npp_base + 0x8044) & 0xffff;
  if (uVar3 != 0) {
    uVar2 = 0;
    if (0xff < uVar3) {
      uVar3 = 0x100;
    }
    do {
      uVar4 = uVar2;
      uVar2 = idm_tx_done + 1;
      iVar5 = *(int *)(skb_tq + idm_tx_done * 4);
      if (0x3ff < uVar2) {
        uVar2 = 0;
      }
      *(undefined4 *)(skb_tq + idm_tx_done * 4) = 0;
      idm_tx_done = uVar2;
      if (iVar5 == 0) {
        idm_txtq_err = idm_txtq_err + 1;
      }
      else {
        uVar1 = *(ushort *)(iVar5 + 0xbc);
        if ((uVar1 & 0x20) == 0) {
          if ((uVar1 & 0x40) == 0) {
            __dev_kfree_skb_any(iVar5,1);
          }
          else {
            _idm_skb_stack_push(iVar5,2,uVar2,uVar1,in_r3);
          }
        }
        else {
          _idm_skb_stack_push(iVar5,1,uVar2,uVar1,in_r3);
        }
      }
      uVar2 = uVar4 + 1;
    } while (uVar2 != uVar3);
    iVar5 = uVar4 + 1;
    *(int *)(npp_base + 0x8040) = iVar5;
    idm_tx_done_total = iVar5 + idm_tx_done_total;
    idm_skb_tx = idm_skb_tx - iVar5;
    return 0x100 - iVar5;
  }
  return 0x100;
}


/* ============= FUNCTION: idm_check_tx_done_lock @ 000157e8 ============= */

void idm_check_tx_done_lock(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 extraout_r2;
  undefined4 in_r3;
  
  uVar1 = DAT_00015810;
  uVar2 = _raw_spin_lock_irqsave(DAT_00015810);
  idm_check_tx_done_nolock();
  _raw_spin_unlock_irqrestore(uVar1,uVar2,extraout_r2,in_r3);
  return;
}


/* ============= FUNCTION: idm_timer_func @ 00015814 ============= */

void idm_timer_func(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 in_r3;
  
  if (idm_tx_scan != 0) {
    idm_check_tx_done_lock();
  }
  if ((idm_net_check_speed != 0) && (idm_check_cnt = idm_check_cnt + 1, 99 < idm_check_cnt)) {
    uVar2 = *(int *)(idm_netdev._4_4_ + 0x4d4) + *(int *)((int)idm_netdev + 0x4d4);
    if (uVar2 < idm_last_rx_bytes) {
      uVar1 = (idm_last_rx_bytes - 1) - uVar2;
    }
    else {
      uVar1 = uVar2 - idm_last_rx_bytes;
    }
    idm_check_cnt = 0;
    idm_last_rx_bytes = uVar2;
    if (0xfffff < uVar1) {
      idm_net_check_speed = 0;
    }
  }
  idm_poll_cnt = idm_poll_cnt + 1;
  idm_timer._8_4_ = jiffies + 1;
  add_timer(DAT_000158cc,idm_poll_cnt,idm_timer._8_4_,in_r3);
  return;
}


/* ============= FUNCTION: hwnat_set_hook_ptr @ 000158d0 ============= */

undefined4 hwnat_set_hook_ptr(void)

{
  hwnat_skb_to_foe_hook = hwnat_skb_to_foe;
  multicast_flood_is_bind_hook = multicast_flood_is_bind;
  hwnat_is_from_cpu_hook = hwnat_is_from_cpu;
  return 0;
}


/* ============= FUNCTION: hwnat_unset_hook_ptr @ 00015904 ============= */

undefined4 hwnat_unset_hook_ptr(void)

{
  hwnat_skb_to_foe_hook = 0;
  multicast_flood_is_bind_hook = 0;
  hwnat_is_from_cpu_hook = 0;
  return 0;
}


/* ============= FUNCTION: idm_invalid_cache @ 00015924 ============= */

void idm_invalid_cache(uint param_1,int param_2)

{
  dma_cache_maint(param_1 & 0xffffffe0,
                  (param_2 + 0x1f + param_1 & 0xffffffe0) - (param_1 & 0xffffffe0),2);
  return;
}


/* ============= FUNCTION: idm_int_disable @ 00015940 ============= */

void idm_int_disable(uint param_1)

{
  idm_int_mask = *(uint *)(npp_base + 0x8024) | param_1;
  *(uint *)(npp_base + 0x8024) = idm_int_mask;
  return;
}


/* ============= FUNCTION: idm_int_enable @ 00015978 ============= */

void idm_int_enable(uint param_1)

{
  idm_int_mask = *(uint *)(npp_base + 0x8024) & ~param_1;
  *(uint *)(npp_base + 0x8024) = idm_int_mask;
  return;
}


/* ============= FUNCTION: dump_idm_desc_rx @ 000159b0 ============= */

void dump_idm_desc_rx(undefined4 *param_1)

{
  printk("0x%.8x 0x%.8x:idm %u,len %u ssid %d ssid vld %d\n",*param_1,param_1[1],
         *(byte *)((int)param_1 + 7) >> 7,*(ushort *)(param_1 + 1) & 0x3fff,
         *(byte *)((int)param_1 + 6) & 7,((uint)*(byte *)((int)param_1 + 6) << 0x1c) >> 0x1f);
  return;
}


/* ============= FUNCTION: idm_net_poll @ 00015a00 ============= */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

int idm_net_poll(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  byte bVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint local_40;
  int local_3c;
  int local_34;
  
  uVar11 = *(uint *)(param_1 + -0x60);
  *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + 1;
  if ((uVar11 & 0x10) != 0) {
    *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + 1;
    idm_check_tx_done_lock();
  }
  if ((uVar11 & 4) != 0) {
    *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 0x7c) + 1;
  }
  local_34 = 5;
  local_3c = 0;
  local_40 = param_2;
  do {
    uVar11 = *(uint *)(npp_base + 0x804c) & 0xffff;
    if (uVar11 == 0) break;
    if ((int)local_40 < 1) {
      if (idm_recv_cmpl == (code *)0x0) {
        return local_3c;
      }
      goto LAB_00015d18;
    }
    if ((int)local_40 <= (int)uVar11) {
      uVar11 = local_40;
    }
    if (0 < idm_net_debug) {
      printk("idm recv %u,jiffies %x\n",uVar11,jiffies);
    }
    uVar15 = 0;
    do {
      while( true ) {
        uVar2 = rx_desc;
        uVar1 = idm_rx_index;
        uVar15 = uVar15 + 1;
        uVar10 = idm_rx_index + 1;
        iVar13 = rx_desc + idm_rx_index * 8;
        uVar8 = rx_desc;
        if (0x7ff < uVar10) {
          uVar8 = 0;
        }
        iVar12 = *(int *)(skb_rq + ((int)(idm_rx_index * 8) >> 1));
        idm_rx_index = uVar10;
        if (0x7ff < uVar10) {
          idm_rx_index = uVar8;
        }
        uVar8 = (uint)(*(byte *)(iVar13 + 7) >> 7);
        iVar14 = *(int *)((int)&idm_netdev + uVar8 * 4);
        if (iVar12 == 0) break;
        uVar10 = *(ushort *)(iVar13 + 4) & 0x3fff;
        if (0 < idm_net_debug) {
          dump_idm_desc_rx(iVar13);
          dump_idm_data(*(undefined4 *)(iVar12 + 0xcc),*(undefined4 *)(iVar12 + 100));
          idm_net_debug = idm_net_debug + -1;
        }
        iVar5 = _idm_skb_stack_pop(0);
        if (iVar5 == 0) {
          iVar5 = __alloc_skbuff(0x6c4,0x20,0,0xffffffff);
          if (iVar5 != 0) {
            iVar7 = *(int *)(iVar5 + 0xcc) + 0x20;
            *(int *)(iVar5 + 0x18) = iVar14;
            iVar6 = *(int *)(iVar5 + 0xc0) + 0x20;
            *(int *)(iVar5 + 0xcc) = iVar7;
            *(int *)(iVar5 + 0xc0) = iVar6;
            goto LAB_00015ba4;
          }
          printk("idm failed to alloc skb\n");
          *(int *)(iVar14 + 0x4e4) = *(int *)(iVar14 + 0x4e4) + 1;
        }
        else {
          iVar7 = *(int *)(iVar5 + 0xcc);
          iVar6 = *(int *)(iVar5 + 0xc0);
LAB_00015ba4:
          uVar3 = rx_desc;
          *(int *)(iVar5 + 0xc0) = iVar6 + 0x20;
          *(int *)(iVar5 + 0xcc) = iVar7 + 0x20;
          *(int *)(uVar2 + uVar1 * 8) = iVar7 + -0x7fffffe0;
          *(int *)(skb_rq + ((int)(iVar13 - uVar3) >> 3) * 4) = iVar5;
          *(ushort *)(iVar5 + 0xbc) = *(ushort *)(iVar5 + 0xbc) | 0x10;
          skb_put(iVar12,uVar10);
          *(int *)(iVar12 + 0x18) = iVar14;
          if ((*(byte *)(iVar13 + 6) & 8) == 0) {
            bVar9 = 0xff;
          }
          else {
            bVar9 = (byte)(((uint)*(byte *)(iVar13 + 6) << 0x1d) >> 0x1d);
          }
          *(byte *)(iVar12 + 0xb7) = bVar9;
          if (idm_skb_recv == (code *)0x0) {
            uVar4 = eth_type_trans(iVar12,iVar14);
            *(undefined2 *)(iVar12 + 0xa4) = uVar4;
            netif_receive_skb_sk(*(undefined4 *)(iVar12 + 0x14),iVar12);
          }
          else {
            (*idm_skb_recv)(uVar8,iVar12);
          }
          *(uint *)(iVar14 + 0x4d4) = *(int *)(iVar14 + 0x4d4) + uVar10;
          *(int *)(iVar14 + 0x4cc) = *(int *)(iVar14 + 0x4cc) + 1;
        }
LAB_00015afc:
        if (uVar15 == uVar11) goto LAB_00015ca0;
      }
      *(int *)(iVar14 + 0x4e4) = *(int *)(iVar14 + 0x4e4) + 1;
      iVar12 = _idm_skb_stack_pop(0);
      if (iVar12 == 0) {
        iVar12 = __alloc_skbuff(0x6c4,0x20,0,0xffffffff);
        if (iVar12 == 0) {
          printk("idm failed to alloc skb\n");
          goto LAB_00015afc;
        }
        iVar5 = *(int *)(iVar12 + 0xcc) + 0x20;
        *(int *)(iVar12 + 0x18) = iVar14;
        iVar14 = *(int *)(iVar12 + 0xc0) + 0x20;
        *(int *)(iVar12 + 0xcc) = iVar5;
        *(int *)(iVar12 + 0xc0) = iVar14;
      }
      else {
        iVar5 = *(int *)(iVar12 + 0xcc);
        iVar14 = *(int *)(iVar12 + 0xc0);
      }
      uVar8 = rx_desc;
      *(int *)(iVar12 + 0xc0) = iVar14 + 0x20;
      *(int *)(iVar12 + 0xcc) = iVar5 + 0x20;
      *(int *)(uVar2 + uVar1 * 8) = iVar5 + -0x7fffffe0;
      *(int *)(skb_rq + ((int)(iVar13 - uVar8) >> 3) * 4) = iVar12;
      *(ushort *)(iVar12 + 0xbc) = *(ushort *)(iVar12 + 0xbc) | 0x10;
    } while (uVar15 != uVar11);
LAB_00015ca0:
    if (idm_skb_flush != (code *)0x0) {
      (*idm_skb_flush)();
    }
    *(uint *)(npp_base + 0x8048) = uVar11 & 0xffff | (uVar11 & 0xffff) << 0x10;
    local_34 = local_34 + -1;
    local_40 = local_40 - uVar11;
    local_3c = local_3c + uVar11;
  } while (local_34 != 0);
  if (idm_recv_cmpl != (code *)0x0) {
LAB_00015d18:
    (*idm_recv_cmpl)();
  }
  if (0 < (int)local_40) {
    napi_complete_done(param_1,0);
    disableIRQinterrupts();
    idm_int_mask = *(uint *)(npp_base + 0x8024) & 0xffffffeb;
    *(uint *)(npp_base + 0x8024) = idm_int_mask;
  }
  return local_3c;
}


/* ============= FUNCTION: dump_idm_desc_tx @ 00015e68 ============= */

void dump_idm_desc_tx(undefined4 *param_1)

{
  printk("0x%.8x 0x%.8x:idm %u,len %u ssid %d\n",*param_1,param_1[1],
         *(byte *)((int)param_1 + 7) >> 7,*(ushort *)(param_1 + 1) & 0x3fff,
         ((uint)*(byte *)((int)param_1 + 7) << 0x19) >> 0x1d);
  return;
}


/* ============= FUNCTION: idm_net_tx @ 00015ea8 ============= */

undefined4 idm_net_tx(undefined4 *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int local_30;
  undefined4 local_2c;
  
  if ((*(uint *)(((uint)&local_30 & 0xffffe000) + 4) & 0x1fff00) == 0) {
    local_2c = _raw_spin_lock_irqsave(DAT_00016128);
  }
  else {
    local_2c = 0;
    _raw_spin_lock();
  }
  if (param_1 != (undefined4 *)0x0) {
    iVar7 = 0;
    iVar8 = 0x2c5a4;
    do {
      while( true ) {
        puVar6 = (undefined4 *)*param_1;
        *param_1 = 0;
        if ((idm_skb_tx < 0x200) ||
           (local_30 = iVar8, idm_check_tx_done_nolock(), iVar8 = local_30,
           *(uint *)(local_30 + -0xf48) < 0x400)) break;
        if (*(uint *)(npp_base + 0x8044) < 0x4000000) {
          *(int *)(local_30 + -0xf54) = *(int *)(local_30 + -0xf54) + 1;
        }
        else {
          *(int *)(local_30 + -0xf58) = *(int *)(local_30 + -0xf58) + 1;
        }
LAB_00016034:
        local_30 = iVar8;
        __dev_kfree_skb_any(param_1,1);
        *(int *)(param_2 + 0x4e8) = *(int *)(param_2 + 0x4e8) + 1;
        param_1 = puVar6;
        iVar8 = local_30;
        if (puVar6 == (undefined4 *)0x0) goto LAB_00016060;
      }
      iVar1 = tx_desc;
      uVar2 = idm_tx_index;
      uVar3 = idm_tx_index + 1;
      iVar4 = tx_desc + idm_tx_index * 8;
      idm_tx_index = uVar3;
      if (0x3ff < uVar3) {
        idm_tx_index = 0;
      }
      if (iVar4 == 0) goto LAB_00016034;
      iVar5 = *(int *)(param_2 + 0x4c0);
      if ((uint)param_1[0x19] < 0x21) {
        param_1[0x19] = 0x21;
      }
      *(int *)(iVar1 + uVar2 * 8) = param_1[0x33] + -0x80000000;
      iVar1 = idm_net_debug;
      *(uint *)(iVar4 + 4) =
           param_1[0x19] | *(int *)(param_2 + 0x4c4) << 0x1f |
           (uint)*(byte *)((int)param_1 + 0xb7) << 0x1c;
      if (0 < iVar1) {
        local_30 = iVar8;
        printk("send len %u,data %x,head %x\n",param_1[0x19],param_1[0x33],param_1[0x32]);
        dump_idm_desc_tx(iVar4);
        dump_idm_data(param_1[0x33],param_1[0x19]);
        *(int *)(local_30 + 0xf4) = *(int *)(local_30 + 0xf4) + -1;
        iVar8 = local_30;
      }
      iVar7 = iVar7 + 1;
      iVar4 = iVar4 - tx_desc;
      *(int *)(iVar5 + 0x4d0) = *(int *)(iVar5 + 0x4d0) + 1;
      idm_skb_tx = idm_skb_tx + 1;
      *(int *)(iVar5 + 0x4d8) = *(int *)(iVar5 + 0x4d8) + param_1[0x19];
      *(undefined4 **)(skb_tq + (iVar4 >> 3) * 4) = param_1;
      param_1 = puVar6;
    } while (puVar6 != (undefined4 *)0x0);
LAB_00016060:
    if (iVar7 != 0) {
      DataSynchronizationBarrier(0xf);
      *(int *)(npp_base + 0x8040) = iVar7 << 0x10;
    }
  }
  if ((*(uint *)(((uint)&local_30 & 0xffffe000) + 4) & 0x1fff00) != 0) {
    _raw_spin_unlock(DAT_00016128);
    return 0;
  }
  _raw_spin_unlock_irqrestore(DAT_00016128,local_2c);
  return 0;
}


/* ============= FUNCTION: idm_creat_status_proc @ 0001612c ============= */

void idm_creat_status_proc(void)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  
  uVar1 = proc_mkdir(&_LC43,0);
  iVar2 = proc_create_data(&_LC44,0x180,uVar1,DAT_00016184,0);
  if (iVar2 == 0) {
    pcVar3 = "idm_status_proc failed!\n";
  }
  else {
    pcVar3 = "idm_status_proc success!\n";
  }
  printk(pcVar3);
  return;
}


/* ============= FUNCTION: idm_cfg_byteorder @ 00016188 ============= */

void idm_cfg_byteorder(int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(npp_base + 0x8000) & 0xfff0ffff;
  if (param_1 != 0) {
    uVar1 = uVar1 | 0xf0000;
  }
  *(uint *)(npp_base + 0x8000) = uVar1;
  return;
}


/* ============= FUNCTION: pon_npp_idm_init @ 000161b8 ============= */

int pon_npp_idm_init(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  
  idm_netdev._4_4_ = idm_net_register(1,&_LC47);
  if (idm_netdev._4_4_ == 0) {
    iVar4 = -1;
    printk("failed to register idm1 net\n");
  }
  else {
    idm_netdev._0_4_ = idm_net_register(0,&_LC37);
    if ((int)idm_netdev == 0) {
      iVar4 = -1;
      printk("failed to register idm0 net\n");
    }
    else {
      netif_napi_add((int)idm_netdev,(int)idm_netdev + 0x528,idm_net_poll,0xff);
      *(undefined4 *)(npp_base + 0x8024) = 0x1f;
      idm_int_mask = 0x1f;
      *(undefined4 *)(npp_base + 0x8018) = 0x40;
      *(undefined4 *)(npp_base + 0x801c) = 5000;
      *(undefined4 *)(npp_base + 0x8010) = 0x40;
      *(uint *)(npp_base + 0x8000) = *(uint *)(npp_base + 0x8000) | 0xf0000;
      *(uint *)(npp_base + 0x8000) = *(uint *)(npp_base + 0x8000) & 0xf00fffff | 0x2000000;
      iVar4 = (int)idm_netdev;
      idm_creat_status_proc();
      pcVar1 = "mac learn:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n" + pp_base + 0x38;
      pcVar1[0] = '@';
      pcVar1[1] = '\x06';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      idm_desc_addr._0_4_ = (*arm_dma_ops)(0,0x6020,0x2e6bc,0xd0,0);
      if (((uint)idm_desc_addr == 0) || (((uint)idm_desc_addr & 0x1f) != 0)) {
        iVar4 = -1;
      }
      else {
        *(undefined4 *)(npp_base + 0x80c0) = 0;
        printk("idm_desc_init %x/%x\n",(uint)idm_desc_addr,idm_desc_addr._4_4_);
        *(int *)(npp_base + 0x8008) = idm_desc_addr._4_4_;
        *(int *)(npp_base + 0x8004) = idm_desc_addr._4_4_ + 0x4000;
        rx_desc = (int *)(idm_desc_addr._4_4_ + -0x80000000);
        __memzero(rx_desc,0x6000);
        piVar5 = rx_desc + 0x1000;
        piVar7 = rx_desc;
        tx_desc = piVar5;
        do {
          iVar2 = _idm_skb_stack_pop(0);
          if (iVar2 == 0) {
            iVar2 = __alloc_skbuff(0x6c4,0x20,0,0xffffffff);
            if (iVar2 == 0) {
              printk("idm failed to alloc skb\n");
              return -1;
            }
            *(int *)(iVar2 + 0x18) = iVar4;
            *(int *)(iVar2 + 0xcc) = *(int *)(iVar2 + 0xcc) + 0x20;
            *(int *)(iVar2 + 0xc0) = *(int *)(iVar2 + 0xc0) + 0x20;
          }
          iVar8 = *(int *)(iVar2 + 0xcc);
          iVar3 = (int)piVar7 - (int)rx_desc;
          *(int *)(iVar2 + 0xcc) = iVar8 + 0x20;
          *(int *)(iVar2 + 0xc0) = *(int *)(iVar2 + 0xc0) + 0x20;
          piVar6 = piVar7 + 2;
          *piVar7 = iVar8 + -0x7fffffe0;
          iVar8 = npp_base;
          *(int *)(skb_rq + (iVar3 >> 3) * 4) = iVar2;
          *(ushort *)(iVar2 + 0xbc) = *(ushort *)(iVar2 + 0xbc) | 0x10;
          *(undefined4 *)(iVar8 + 0x8048) = 0x10000;
          piVar7 = piVar6;
        } while (piVar5 != piVar6);
        idm_rx_index = 0;
        idm_tx_index = 0;
        idm_tx_done = 0;
        *(undefined4 *)(npp_base + 0x800c) = 0x4000800;
        iVar2 = 0x200;
        do {
          iVar8 = __alloc_skbuff(0x6c4,0x20,0,0xffffffff);
          if (iVar8 == 0) {
            printk("idm failed to alloc skb\n");
            break;
          }
          *(int *)(iVar8 + 0x18) = iVar4;
          *(int *)(iVar8 + 0xcc) = *(int *)(iVar8 + 0xcc) + 0x20;
          *(int *)(iVar8 + 0xc0) = *(int *)(iVar8 + 0xc0) + 0x20;
          _idm_skb_stack_push(iVar8,0);
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
        hwnat_set_hook_ptr();
        iVar4 = 0;
        init_timer_key(idm_timer,0,0,0);
        idm_timer._20_4_ = 0;
        idm_timer._8_4_ = jiffies + 100;
        idm_timer._16_4_ = idm_timer_func;
        add_timer(idm_timer);
        iVar2 = request_threaded_irq(g_idm_irq,idm_net_int,0,0,&_LC43,0);
        if (iVar2 < 0) {
          printk("request idm irq failed\n");
          return iVar2;
        }
        printk("request idm irq succeed \n");
        idm_net_check_speed = 0;
        printk("idm net init ok\n");
      }
    }
  }
  return iVar4;
}


/* ============= FUNCTION: dump_idm_net_info @ 000165c8 ============= */

void dump_idm_net_info(uint param_1)

{
  int iVar1;
  
  if (1 < param_1) {
    printk("invalid port %d\n");
    return;
  }
  iVar1 = *(int *)((int)&idm_netdev + param_1 * 4);
  printk(&_LC55,iVar1);
  printk("irq     %u\n",*(undefined4 *)(iVar1 + 0x598));
  printk("irq_err %u\n",*(undefined4 *)(iVar1 + 0x59c));
  printk("poll    %u\n",*(undefined4 *)(iVar1 + 0x5a0));
  printk("rx int  %u\n",*(undefined4 *)(iVar1 + 0x5a4));
  printk("tx int  %u\n",*(undefined4 *)(iVar1 + 0x5a8));
  return;
}


/* ============= FUNCTION: _dump_vlan_info @ 00016658 ============= */

void _dump_vlan_info(undefined4 param_1,uint param_2)

{
  undefined4 *puVar1;
  
  printk("vlan %u:",param_1);
  puVar1 = (undefined4 *)&port_name;
  do {
    if ((param_2 & 3) != 0) {
      printk(" %s(%u)",*puVar1);
    }
    puVar1 = puVar1 + 1;
    param_2 = param_2 >> 2;
  } while (puVar1 != (undefined4 *)&pon_tm_net_netdev_ops);
  printk(&_LC2);
  return;
}


/* ============= FUNCTION: get_mac_status @ 000166bc ============= */

char * get_mac_status(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  param_1 = param_1 & 0xf;
  if (param_1 == 0) {
    return "invalid";
  }
  if (param_1 != 0xf) {
    sprintf(&buf_name_18119,"valid %d",param_1,param_4,param_4);
    return &buf_name_18119;
  }
  return "static";
}


/* ============= FUNCTION: L2ReadProc @ 00016708 ============= */

undefined4 L2ReadProc(void *param_1)

{
  undefined4 *in_stack_00000000;
  
  memcpy(param_1,
         "Usage: echo [OPTIONS] add/del/show/hash/cls > /proc/xxx/l2 \nexample -m xx:xx:xx:xx:xx:xx -v 1 -p 0 add \n        show \nOptions:\n  -m,         set mac address\n  -v,         set vlan id,default is 1\n  -p,         set uni port, default is 0\n  -h,         help\n"
         ,0x101);
  *in_stack_00000000 = 1;
  return 0x100;
}


/* ============= FUNCTION: VlanReadProc @ 00016730 ============= */

undefined4 VlanReadProc(void *param_1)

{
  undefined4 *in_stack_00000000;
  
  memcpy(param_1,
         "Usage: echo [OPTIONS] add/del/show > /proc/xxx/l2 \nexample -v 1 -p 0 add \n        show \nOptions:\n  -v,         set vlan id,default is 1\n  -p,         set uni port, default is 0\n  -t,         set memtag,default is 3,1 delete ,2 include,3 no change\n  -h,         help\n"
         ,0x10b);
  *in_stack_00000000 = 1;
  return 0x10a;
}


/* ============= FUNCTION: brg_ram_get @ 00016758 ============= */

undefined4 brg_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0x32;
  do {
    if ((*(uint *)(pp_base + 0x8018) & 1) != 0) {
      *(uint *)(pp_base + 0x8014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar1 = pp_base;
      iVar3 = 0x32;
      do {
        if ((*(uint *)(pp_base + 0x8018) & 1) != 0) {
          param_2[2] = *(undefined4 *)(pp_base + 0x8024);
          iVar2 = pp_base;
          param_2[1] = *(undefined4 *)(iVar1 + 0x8020);
          *param_2 = *(undefined4 *)(iVar2 + 0x801c);
          return 0;
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  printk("brg ram get timeout\n");
  return 0xfffffff5;
}


/* ============= FUNCTION: brg_ram_set @ 00016828 ============= */

undefined4 brg_ram_set(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 0x32;
  do {
    if ((*(uint *)(pp_base + 0x8018) & 1) != 0) {
      *(uint *)(pp_base + 0x8014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(pp_base + 0x8024) = param_2[2];
      *(undefined4 *)(pp_base + 0x8020) = param_2[1];
      *(undefined4 *)(pp_base + 0x801c) = *param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk(0x1fe00);
  return 0xfffffff5;
}


/* ============= FUNCTION: pon_pp_port_isolate.part.1 @ 000168cc ============= */

void pon_pp_port_isolate_part_1(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = param_1 * 4 + 0x83c0;
  *(uint *)(pp_base + iVar1) = *(uint *)(pp_base + iVar1) | param_2;
  return;
}


/* ============= FUNCTION: brg_cal_mac_hash @ 00016900 ============= */

uint brg_cal_mac_hash(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = crc_16(param_1,6,0,param_4,param_4);
  return uVar1 & 0x3ff;
}


/* ============= FUNCTION: dump_mac_data @ 00016918 ============= */

void dump_mac_data(undefined4 param_1,undefined4 param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  
  printk("depth %u id %u\n",param_1,param_2);
  uVar1 = *param_3;
  uVar2 = get_mac_status((byte)param_3[8] >> 4);
  printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar1,uVar2,
         (uint)(byte)param_3[7] | ((byte)param_3[8] & 0xf) << 8,param_3[6],param_3[5],param_3[4],
         param_3[3],param_3[2],param_3[1]);
  return;
}


/* ============= FUNCTION: pon_pp_del_mac @ 000169ac ============= */

undefined4 pon_pp_del_mac(char *param_1,uint param_2)

{
  short sVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 local_34;
  char local_33;
  char local_32;
  char local_31;
  char local_30;
  char local_2f;
  char local_2e;
  byte local_2d;
  byte local_2c;
  
  if (param_1 == (char *)0x0) {
    uVar5 = 0xffffffff;
  }
  else {
    iVar6 = 0;
    sVar1 = *(short *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2);
    uVar3 = crc_16(param_1,6,0);
    uVar3 = sVar1 - 1U & uVar3 & 0x3ff;
    do {
      iVar4 = brg_ram_get(uVar3,&local_34,iVar6);
      if (iVar4 < 0) {
        return 0xfffffffe;
      }
      if ((local_2c & 0xf0) != 0) {
        if ((((local_2e == *param_1) && (local_2f == param_1[1])) && (local_30 == param_1[2])) &&
           (((local_31 == param_1[3] && (local_32 == param_1[4])) &&
            ((param_2 & 0xfff) == ((uint)local_2d | (local_2c & 0xf) << 8) && local_33 == param_1[5]
            )))) {
          local_2c = local_2c & 0xf;
          iVar4 = brg_ram_set(uVar3,&local_34,iVar6);
          if (iVar4 < 0) {
            return 0xfffffffd;
          }
          printk("del mac : ");
          printk("depth %u id %u\n",uVar3,iVar6);
          uVar2 = local_34;
          uVar5 = get_mac_status(local_2c >> 4);
          printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar2,uVar5,
                 (uint)local_2d | (local_2c & 0xf) << 8,local_2e,local_2f,local_30,local_31,local_32
                 ,local_33);
        }
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 != 4);
    uVar5 = 0;
  }
  return uVar5;
}


/* ============= FUNCTION: pon_pp_cls_port_mac @ 00016b84 ============= */

undefined4 pon_pp_cls_port_mac(int param_1)

{
  if ((*(uint *)(pp_base + 0x8004) & 0x10000) == 0) {
    *(uint *)(pp_base + 0x8004) = *(uint *)(pp_base + 0x8004) | param_1 << 8 | 0x10000;
    return 0;
  }
  return 0xffffffff;
}


/* ============= FUNCTION: pon_pp_add_mac @ 00016bcc ============= */

uint pon_pp_add_mac(char *param_1,uint param_2,uint param_3)

{
  short sVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  undefined1 local_34;
  char local_33;
  char local_32;
  char local_31;
  char local_30;
  char local_2f;
  char local_2e;
  byte local_2d;
  byte local_2c;
  byte local_2b;
  
  if (param_1 == (char *)0x0 || 7 < param_3) {
    uVar6 = 0xffffffff;
  }
  else {
    sVar1 = *(short *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2);
    uVar3 = crc_16(param_1,6,0);
    uVar3 = sVar1 - 1U & uVar3 & 0x3ff;
    iVar7 = 0;
    do {
      iVar4 = brg_ram_get(uVar3,&local_34,iVar7);
      if (iVar4 < 0) {
        return 0xfffffffe;
      }
      uVar6 = (uint)local_2c;
      if ((local_2c & 0xf0) == 0) {
        local_31 = param_1[3];
        local_2c = (byte)((param_2 << 0x14) >> 0x1c) | 0xf0;
        local_2e = *param_1;
        local_2f = param_1[1];
        local_2b = local_2b & 0xfe;
        local_30 = param_1[2];
        local_32 = param_1[4];
        local_33 = param_1[5];
        local_2d = (byte)(param_2 & 0xfff);
        local_34 = (undefined1)(1 << (param_3 & 0xff));
        iVar4 = brg_ram_set(uVar3,&local_34,iVar7);
        if (-1 < iVar4) {
          printk("add mac : ");
          printk("depth %u id %u\n",uVar3,iVar7);
          uVar2 = local_34;
          uVar5 = get_mac_status(local_2c >> 4);
          printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar2,uVar5,
                 (uint)local_2d | (local_2c & 0xf) << 8,local_2e,local_2f,local_30,local_31,local_32
                 ,local_33);
          return uVar6 & 0xf0;
        }
        return 0xfffffffd;
      }
      iVar7 = iVar7 + 1;
      if ((((local_2e == *param_1) && (local_2f == param_1[1])) && (local_30 == param_1[2])) &&
         (((local_31 == param_1[3] && (local_32 == param_1[4])) &&
          ((param_2 & 0xfff) == ((uint)local_2d | (uVar6 & 0xf) << 8) && local_33 == param_1[5]))))
      {
        printk("mac exist");
        return 0;
      }
    } while (iVar7 != 4);
    uVar6 = 0;
  }
  return uVar6;
}


/* ============= FUNCTION: pon_pp_dump_mac @ 00016e28 ============= */

void pon_pp_dump_mac(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  byte local_2d;
  byte local_2c;
  
  uVar6 = (uint)*(ushort *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2);
  printk("mac table depth %u\n",uVar6);
  if (uVar6 != 0) {
    uVar5 = 0;
    do {
      iVar4 = 0;
      do {
        iVar2 = brg_ram_get(uVar5,&local_34,iVar4);
        if (iVar2 < 0) break;
        if ((local_2c & 0xf0) != 0) {
          printk("depth %u id %u\n",uVar5,iVar4);
          uVar1 = local_34;
          uVar3 = get_mac_status(local_2c >> 4);
          printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar1,uVar3,
                 (uint)local_2d | (local_2c & 0xf) << 8,local_2e,local_2f,local_30,local_31,local_32
                 ,local_33);
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 != 4);
      uVar5 = uVar5 + 1;
    } while (uVar6 != uVar5);
  }
  return;
}


/* ============= FUNCTION: pon_pp_dump_hash_mac @ 00016f3c ============= */

void pon_pp_dump_hash_mac(uint param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  byte local_25;
  byte local_24;
  
  if (*(ushort *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2) <= param_1) {
    return;
  }
  iVar4 = 0;
  do {
    iVar2 = brg_ram_get(param_1,&local_2c,iVar4);
    if (iVar2 < 0) {
      return;
    }
    if ((local_24 & 0xf0) != 0) {
      printk("depth %u id %u\n",param_1,iVar4);
      uVar1 = local_2c;
      uVar3 = get_mac_status(local_24 >> 4);
      printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar1,uVar3,
             (uint)local_25 | (local_24 & 0xf) << 8,local_26,local_27,local_28,local_29,local_2a,
             local_2b);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 4);
  return;
}


/* ============= FUNCTION: pon_pp_learned_mac @ 00017034 ============= */

int pon_pp_learned_mac(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined1 auStack_24 [8];
  byte local_1c;
  
  uVar1 = *(ushort *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2);
  if (uVar1 == 0) {
    iVar5 = 0;
  }
  else {
    uVar4 = 0;
    iVar5 = 0;
    do {
      iVar2 = 0;
      do {
        iVar3 = iVar2 + 1;
        iVar2 = brg_ram_get(uVar4,auStack_24,iVar2);
        if (iVar2 < 0) break;
        if ((local_1c & 0xf0) != 0) {
          iVar5 = iVar5 + 1;
        }
        iVar2 = iVar3;
      } while (iVar3 != 4);
      uVar4 = uVar4 + 1;
    } while (uVar1 != uVar4);
  }
  return iVar5;
}


/* ============= FUNCTION: L2WriteProc @ 000170c8 ============= */

uint L2WriteProc(undefined4 param_1,uint param_2,uint param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  short sVar5;
  undefined2 uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  uint uVar11;
  uint uVar12;
  undefined4 *puVar13;
  uint uVar14;
  undefined1 *puVar15;
  char *__s1;
  undefined1 *puVar16;
  char *pcVar17;
  undefined1 *local_48;
  undefined1 *local_44;
  undefined1 *local_40;
  undefined1 *local_3c;
  undefined4 uStack_38;
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [4];
  undefined1 auStack_28 [4];
  undefined1 auStack_24 [4];
  
  uVar9 = param_3;
  if (0x7e < param_3) {
    uVar9 = 0x7f;
  }
  uVar14 = *(uint *)(((uint)&local_48 & 0xffffe000) + 8);
  uVar11 = param_2 + uVar9;
  uVar12 = uVar11;
  if (!CARRY4(param_2,uVar9)) {
    uVar12 = uVar11 - (uVar14 + 1);
  }
  if (!CARRY4(param_2,uVar9) && uVar11 <= uVar14) {
    uVar14 = 0;
  }
  if (uVar14 == 0) {
    iVar8 = __copy_from_user(DAT_00017500,param_2,uVar9);
    if (iVar8 != 0) {
      return 0xfffffff2;
    }
  }
  else if (uVar9 != 0) {
    __memzero(DAT_00017500,uVar9,uVar12);
    return 0xfffffff2;
  }
  l2_cmd_line[uVar9] = 0;
  proc_get_cmd(l2_cmd_line);
  iVar8 = proc_argc;
  if (proc_argc < 2) {
LAB_000171b0:
    printk(&_LC16,
           "Usage: echo [OPTIONS] add/del/show/hash/cls > /proc/xxx/l2 \nexample -m xx:xx:xx:xx:xx:xx -v 1 -p 0 add \n        show \nOptions:\n  -m,         set mac address\n  -v,         set vlan id,default is 1\n  -p,         set uni port, default is 0\n  -h,         help\n"
          );
    return param_3;
  }
  l2_port = 0;
  l2_has_mac = '\0';
  l2_vlan = 1;
  __memzero(&l2_mac,6);
  optind = 1;
  optreset = 1;
  while (iVar7 = getopt(iVar8,(char **)proc_argv,"m:v:p:h?"), iVar7 != -1) {
    if (iVar7 == 0x70) {
      bVar4 = simple_strtoul(optarg,0,10);
      l2_port = bVar4 & 7;
    }
    else if (iVar7 == 0x76) {
      sVar5 = simple_strtoul(optarg,0,10);
      l2_vlan = sVar5 * 0xfff;
    }
    else {
      if (iVar7 != 0x6d) goto LAB_000171b0;
      local_48 = auStack_30;
      local_44 = auStack_2c;
      local_3c = auStack_24;
      local_40 = auStack_28;
      iVar7 = sscanf(optarg,"%x:%x:%x:%x:%x:%x",&uStack_38,auStack_34);
      if (iVar7 != 6) {
        printk("invalid mac %s\n",optarg);
        return param_3;
      }
      puVar13 = &uStack_38;
      puVar16 = DAT_000174fc;
      do {
        puVar15 = puVar16 + 1;
        *puVar16 = (char)*puVar13;
        puVar13 = puVar13 + 1;
        puVar16 = puVar15;
      } while (puVar15 != (undefined1 *)0x2e772);
      l2_has_mac = '\x01';
    }
  }
  if (iVar8 <= optind) {
    printk("error: no rule,%d/%d\n",optind,iVar8);
    return param_3;
  }
  pcVar17 = *(char **)(proc_argv + optind * 4);
  l2_cmd = pcVar17;
  if (optind < iVar8 + -1) {
    __s1 = *(char **)(proc_argv + optind * 4 + 4);
    l2_param = __s1;
    iVar8 = strcmp(pcVar17,"show");
    if (iVar8 != 0) goto LAB_00017308;
    if (__s1 != (char *)0x0) {
      iVar8 = strcmp(__s1,"cnt");
      if (iVar8 != 0) {
        uVar6 = simple_strtoul(__s1,0,10);
        pon_pp_dump_hash_mac(uVar6);
        return param_3;
      }
      uVar10 = pon_pp_learned_mac();
      printk("mac learned %d\n",uVar10);
      return param_3;
    }
  }
  else {
    l2_param = (char *)0x0;
    iVar8 = strcmp(pcVar17,"show");
    if (iVar8 != 0) {
LAB_00017308:
      iVar8 = strcmp(pcVar17,"cls");
      if ((iVar8 == 0) && ((*(uint *)(pp_base + 0x8004) & 0x10000) == 0)) {
        *(uint *)(pp_base + 0x8004) =
             *(uint *)(pp_base + 0x8004) | (1 << l2_port & 0xffU) << 8 | 0x10000;
      }
      pcVar17 = l2_cmd;
      if (l2_has_mac == '\0') {
        printk("need input mac\n");
        return param_3;
      }
      iVar8 = strcmp(l2_cmd,"add");
      if (iVar8 == 0) {
        pon_pp_add_mac(&l2_mac,l2_vlan,l2_port);
        return param_3;
      }
      iVar8 = strcmp(pcVar17,"del");
      if (iVar8 != 0) {
        iVar8 = strcmp(pcVar17,"hash");
        uVar3 = l2_mac._2_1_;
        uVar2 = l2_mac._1_1_;
        uVar1 = (undefined1)l2_mac;
        if (iVar8 != 0) {
          return param_3;
        }
        puVar16 = (undefined1 *)(uint)l2_mac._3_1_;
        uVar11 = (uint)l2_mac._4_1_;
        uVar12 = (uint)l2_mac._5_1_;
        uVar9 = crc_16(&l2_mac,6,0);
        local_3c = (undefined1 *)(uVar9 & 0x3ff);
        local_48 = puVar16;
        local_44 = (undefined1 *)uVar11;
        local_40 = (undefined1 *)uVar12;
        printk("mac %.2x %.2x %.2x %.2x %.2x %.2x hash is %d\n",uVar1,uVar2,uVar3);
        return param_3;
      }
      pon_pp_del_mac(&l2_mac,l2_vlan);
      return param_3;
    }
  }
  pon_pp_dump_mac();
  return param_3;
}


/* ============= FUNCTION: pon_pp_add_port_to_vlan @ 00017504 ============= */

int pon_pp_add_port_to_vlan(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint local_1c [3];
  
  if (param_2 < 8) {
    iVar1 = brg_ram_get(param_1 & 0xfff,local_1c);
    if (iVar1 < 0) {
      iVar1 = -1;
    }
    else {
      uVar2 = param_2 * 2 + 1;
      local_1c[0] = (local_1c[0] | 1) & ~(3 << (uVar2 & 0xff)) | (param_3 & 3) << (uVar2 & 0xff);
      iVar1 = brg_ram_set(param_1 & 0xfff,local_1c,4);
      iVar1 = iVar1 >> 0x1f;
    }
    return iVar1;
  }
  return -1;
}


/* ============= FUNCTION: pon_pp_del_port_from_vlan @ 00017588 ============= */

void pon_pp_del_port_from_vlan(undefined4 param_1,undefined4 param_2)

{
  pon_pp_add_port_to_vlan(param_1,param_2,0);
  return;
}


/* ============= FUNCTION: dump_vlan_info @ 00017590 ============= */

undefined4 dump_vlan_info(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_1c [4];
  
  param_1 = param_1 & 0xfff;
  iVar1 = brg_ram_get(param_1,local_1c,4);
  if (iVar1 < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    if ((local_1c[0] & 1) == 0) {
      printk("vlan table %d invlaid\n",param_1);
      return 0;
    }
    _dump_vlan_info(param_1);
    printk("1:tag delete;2:tag include;3 tag no change\n");
    uVar2 = 0;
  }
  return uVar2;
}


/* ============= FUNCTION: VlanWriteProc @ 00017604 ============= */

uint VlanWriteProc(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *__s1;
  undefined4 uStack_28;
  
  uVar6 = param_3;
  if (0x7e < param_3) {
    uVar6 = 0x7f;
  }
  uVar5 = *(uint *)(((uint)&uStack_28 & 0xffffe000) + 8);
  uVar3 = param_2 + uVar6;
  uVar4 = uVar3;
  if (!CARRY4(param_2,uVar6)) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (!CARRY4(param_2,uVar6) && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  uStack_28 = param_4;
  if (uVar5 == 0) {
    iVar2 = __copy_from_user(DAT_00017830,param_2,uVar6);
    if (iVar2 != 0) {
      return 0xfffffff2;
    }
  }
  else if (uVar6 != 0) {
    __memzero(DAT_00017830,uVar6,uVar4);
    return 0xfffffff2;
  }
  vlan_cmd_line[uVar6] = 0;
  proc_get_cmd(vlan_cmd_line);
  iVar2 = proc_argc;
  if (proc_argc < 2) {
LAB_000176e8:
    printk(&_LC16,
           "Usage: echo [OPTIONS] add/del/show/hash/cls > /proc/xxx/l2 \nexample -m xx:xx:xx:xx:xx:xx -v 1 -p 0 add \n        show \nOptions:\n  -m,         set mac address\n  -v,         set vlan id,default is 1\n  -p,         set uni port, default is 0\n  -h,         help\n"
          );
  }
  else {
    vlan_port = 0;
    optreset = 1;
    optind = 1;
    vlan_vlan = 1;
    vlan_tag = 3;
    while (iVar1 = getopt(iVar2,(char **)proc_argv,"t:v:p:h?"), iVar1 != -1) {
      if (iVar1 == 0x74) {
        vlan_tag = simple_strtoul(optarg,0,10);
      }
      else if (iVar1 == 0x76) {
        vlan_vlan = simple_strtoul(optarg,0,10);
      }
      else {
        if (iVar1 != 0x70) goto LAB_000176e8;
        vlan_port = simple_strtoul(optarg,0,10);
      }
    }
    if (optind < iVar2) {
      __s1 = *(char **)(proc_argv + optind * 4);
      vlan_cmd = __s1;
      iVar2 = strcmp(__s1,"show");
      if (iVar2 == 0) {
        dump_vlan_info(vlan_vlan);
        return param_3;
      }
      iVar2 = strcmp(__s1,"add");
      if (iVar2 == 0) {
        pon_pp_add_port_to_vlan(vlan_vlan,vlan_port,vlan_tag);
        return param_3;
      }
      iVar2 = strcmp(__s1,"del");
      if (iVar2 == 0) {
        pon_pp_add_port_to_vlan(vlan_vlan,vlan_port);
        return param_3;
      }
    }
    else {
      printk("error: no rule,%d/%d\n",optind,iVar2);
    }
  }
  return param_3;
}


/* ============= FUNCTION: dump_all_vlan_info @ 00017834 ============= */

undefined4 dump_all_vlan_info(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint local_14 [3];
  
  uVar3 = 0;
  do {
    while( true ) {
      iVar1 = brg_ram_get(uVar3,local_14,4);
      if (iVar1 < 0) {
        return 0xffffffff;
      }
      if ((local_14[0] & 1) == 0) break;
      uVar2 = uVar3 & 0xffff;
      uVar3 = uVar3 + 1;
      _dump_vlan_info(uVar2);
      if (uVar3 == 0x1000) goto LAB_00017888;
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 != 0x1000);
LAB_00017888:
  printk("1:tag delete;2:tag include;3 tag no change\n");
  return 0;
}


/* ============= FUNCTION: pon_pp_port_isolate @ 000178ac ============= */

void pon_pp_port_isolate(uint param_1)

{
  if (7 < param_1) {
    return;
  }
  pon_pp_port_isolate_part_1();
  return;
}


/* ============= FUNCTION: pon_pp_set_aging_time @ 000178b8 ============= */

void pon_pp_set_aging_time(int param_1)

{
  *(int *)(pp_base + 0x8188) = param_1 * 0x1107;
  return;
}


/* ============= FUNCTION: pon_pp_brg_int @ 000178e0 ============= */

void pon_pp_brg_int(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 uStack_27;
  
  uVar3 = *(uint *)(pp_base + 0x8054) & ~*(uint *)(pp_base + 0x8050);
  if ((uVar3 & 1) != 0) {
    uVar1 = *(uint *)(pp_base + 0x8060);
    uVar2 = *(uint *)(pp_base + 0x8064);
    printk("port migrate:pbm %d to pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n",
           *(uint *)(pp_base + 0x8068) & 0xff,(*(uint *)(pp_base + 0x8068) << 0x10) >> 0x18,
           uVar2 >> 0x10 & 0xfff,uVar2 >> 8 & 0xff,uVar2 & 0xff,uVar1 >> 0x18,uVar1 >> 0x10 & 0xff,
           uVar1 >> 8 & 0xff,uVar1 & 0xff);
    *(undefined4 *)(pp_base + 0x8068) = 0;
  }
  if ((uVar3 & 2) != 0) {
    uVar1 = *(uint *)(pp_base + 0x80a8);
    uVar2 = *(uint *)(pp_base + 0x80ac);
    uStack_27 = (undefined1)(uVar2 >> 8);
    printk(0x1fff0,*(uint *)(pp_base + 0x80b0) & 0xff,uVar2 >> 0x10 & 0xfff,uStack_27,uVar2 & 0xff,
           uVar1 >> 0x18,uVar1 >> 0x10 & 0xff,uVar1 >> 8 & 0xff,uVar1 & 0xff);
    *(undefined4 *)(pp_base + 0x80b0) = 0;
  }
  if ((uVar3 & 4) != 0) {
    uVar1 = *(uint *)(pp_base + 0x80f0);
    uVar2 = *(uint *)(pp_base + 0x80f4);
    uStack_27 = (undefined1)(uVar2 >> 8);
    printk("hash collision:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n",
           *(uint *)(pp_base + 0x80f8) & 0xff,uVar2 >> 0x10 & 0xfff,uStack_27,uVar2 & 0xff,
           uVar1 >> 0x18,uVar1 >> 0x10 & 0xff,uVar1 >> 8 & 0xff,uVar1 & 0xff);
    *(undefined4 *)(pp_base + 0x80f8) = 0;
  }
  if ((uVar3 & 8) != 0) {
    uVar3 = *(uint *)(pp_base + 0x8138);
    uVar1 = *(uint *)(pp_base + 0x813c);
    uStack_27 = (undefined1)(uVar1 >> 8);
    printk("mac aged:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n",
           *(uint *)(pp_base + 0x8140) & 0xff,uVar1 >> 0x10 & 0xfff,uStack_27,uVar1 & 0xff,
           uVar3 >> 0x18,uVar3 >> 0x10 & 0xff,uVar3 >> 8 & 0xff,uVar3 & 0xff);
    *(undefined4 *)(pp_base + 0x8140) = 0;
  }
  return;
}


/* ============= FUNCTION: pon_pp_brg_init @ 00017ba4 ============= */

undefined4 pon_pp_brg_init(void)

{
  uint uVar1;
  uint uVar2;
  
  *(char **)(pp_base + 0x8004) = " %d/%d failed\n";
  *(undefined4 *)(pp_base + 0x8340) = 0xff5555ff;
  *(undefined4 *)(pp_base + 0x8344) = 0x1e;
  *(undefined4 *)(pp_base + 0x8380) = 0x1f;
  *(undefined4 *)(pp_base + 0x863c) = 0xaaaaaaaa;
  *(undefined4 *)(pp_base + 0x81c0) = 0xff;
  *(undefined4 *)(pp_base + 0x81c4) = 0x5555;
  *(undefined4 *)(pp_base + 0x8188) = 0x13f434;
  *(undefined4 *)(pp_base + 0x82c0) = 0xff;
  *(undefined4 *)(pp_base + 0x8300) = 0xffff;
  *(undefined4 *)(pp_base + 0x8304) = 0x1e;
  *(undefined4 *)(pp_base + 0x8050) = 0xfffffffa;
  *(undefined4 *)(pp_base + 0x8008) = 0xff00;
  uVar1 = 0;
  do {
    uVar2 = uVar1 & 0xff;
    uVar1 = uVar1 + 1;
    pon_pp_add_port_to_vlan(0,uVar2,3);
    pon_pp_add_port_to_vlan(1,uVar2,3);
  } while (uVar1 != 8);
  pon_pp_port_isolate_part_1(6,0xdf);
  pon_pp_port_isolate_part_1(7,0xdf);
  return 0;
}


/* ============= FUNCTION: create_l2_proc @ 00017d0c ============= */

int create_l2_proc(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = proc_create_data(&_LC37,0x124,param_1,DAT_00017d48,0);
  return -(uint)(iVar1 == 0);
}


/* ============= FUNCTION: create_vlan_proc @ 00017d4c ============= */

int create_vlan_proc(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = proc_create_data(&_LC38,0x124,param_1,DAT_00017d88,0);
  return -(uint)(iVar1 == 0);
}


/* ============= FUNCTION: cla_ram_set @ 00017d8c ============= */

undefined4 cla_ram_set(uint param_1,undefined4 *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(pp_base + 0xc018) & 1) != 0) {
      *(uint *)(pp_base + 0xc014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(pp_base + 0xc028) = param_2[3];
      *(undefined4 *)(pp_base + 0xc024) = param_2[2];
      *(undefined4 *)(pp_base + 0xc020) = param_2[1];
      *(undefined4 *)(pp_base + 0xc01c) = *param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("set cla ram %d/%d failed\n",param_3,param_1,(uint *)(pp_base + 0xc018),param_4);
  return 0xfffffff5;
}


/* ============= FUNCTION: cla_ram_get @ 00017e4c ============= */

undefined4 cla_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 5;
  do {
    if ((*(uint *)(pp_base + 0xc018) & 1) != 0) {
      *(uint *)(pp_base + 0xc014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar1 = pp_base;
      iVar3 = 5;
      do {
        if ((*(uint *)(pp_base + 0xc018) & 1) != 0) {
          param_2[3] = *(undefined4 *)(pp_base + 0xc028);
          iVar2 = pp_base;
          param_2[2] = *(undefined4 *)(iVar1 + 0xc024);
          iVar1 = pp_base;
          param_2[1] = *(undefined4 *)(iVar2 + 0xc020);
          *param_2 = *(undefined4 *)(iVar1 + 0xc01c);
          return 0;
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  printk("get cla ram %d/%d failed\n",param_3,param_1);
  return 0xfffffff5;
}


/* ============= FUNCTION: cla_ram_dump @ 00017f38 ============= */

undefined4 cla_ram_dump(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar1 = cla_ram_get(param_1,&local_18,param_2);
  if (iVar1 < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("0x%.8x 0x%.8x 0x%.8x 0x%.8x\n",local_18,local_14,local_10,local_c);
    uVar2 = 0;
  }
  return uVar2;
}


/* ============= FUNCTION: pon_pp_cla_init @ 00017f88 ============= */

undefined4 pon_pp_cla_init(void)

{
  *(undefined4 *)(pp_base + 0xc080) = 0x1000;
  *(undefined4 *)(pp_base + 0xc084) = 2;
  return 0;
}


/* ============= FUNCTION: zx_pon_pp_int @ 00017fc0 ============= */

undefined4 zx_pon_pp_int(void)

{
  if ((*(uint *)(pp_base + 0x20000) & 1 &
      ~*(uint *)("mac learn:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n" + pp_base + 0x14))
      != 0) {
    pon_pp_brg_int();
  }
  return 1;
}


/* ============= FUNCTION: tm_pon_pp_init @ 00017ffc ============= */

undefined4 tm_pon_pp_init(void)

{
  printk("pon_pp init\n");
  pon_pp_ctrl_init();
  pon_pp_brg_init();
  pon_pp_cla_init();
  request_threaded_irq(g_pp_irq,zx_pon_pp_int,0,0,"pon_pp",0);
  return 0;
}


/* ============= FUNCTION: pon_pp_ctrl_init @ 0001805c ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 pon_pp_ctrl_init(void)

{
  pp_base[10] = 0x1070104;
  *pp_base = 2;
  (*_request_threaded_irq)(0x66665b0);
  return 0;
}


/* ============= FUNCTION: sadm_ram_set @ 000180a4 ============= */

undefined4 sadm_ram_set(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(pp_base + 0x4018) & 1) != 0) {
      *(uint *)(pp_base + 0x4014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(pp_base + 0x401c) = *param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("sadm ram set timeout\n");
  return 0xfffffff5;
}


/* ============= FUNCTION: sadm_ram_get @ 00018120 ============= */

undefined4 sadm_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(pp_base + 0x4018) & 1) != 0) {
      *(uint *)(pp_base + 0x4014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar2 = 5;
      do {
        if ((*(uint *)(pp_base + 0x4018) & 1) != 0) {
          *param_2 = *(undefined4 *)(pp_base + 0x401c);
          return 0;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("sadm ram get timeout\n");
  return 0xfffffff5;
}


/* ============= FUNCTION: sadm_port_limit @ 000181c8 ============= */

/* WARNING: Type propagation algorithm not settling */

undefined4 sadm_port_limit(uint param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_1c [3];
  
  if (param_1 < 8) {
    local_1c[0] = (uint)((*(int *)(pp_base + 0x4024) + 1) * param_2 * 0x20) / 250000;
    iVar1 = sadm_ram_set(param_1,local_1c,2);
    if (-1 < iVar1) {
      local_1c[1] = 1;
      uVar2 = sadm_ram_set(param_1,local_1c + 1,0);
      return uVar2;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: sadm_dump_port @ 00018254 ============= */

void sadm_dump_port(uint param_1)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  uint local_20 [2];
  
  if (7 < param_1) {
    return;
  }
  iVar4 = *(int *)(pp_base + 0x4024);
  iVar2 = sadm_ram_get(param_1,local_20,0);
  if (-1 < iVar2) {
    printk("sadm bucket fill time 0x%x\n",iVar4);
    printk("port bucket:\n");
    pcVar5 = "enable";
    pcVar3 = pcVar5;
    if ((local_20[0] & 1) == 0) {
      pcVar3 = "disable";
    }
    printk("\tbucket %s\n",pcVar3);
    iVar2 = sadm_ram_get(param_1,local_20,2);
    uVar1 = local_20[0];
    if (-1 < iVar2) {
      iVar2 = __aeabi_uidiv(0x773594,iVar4 + 1);
      printk("\tbucket fill 0x%x(%u bps)\n",uVar1,uVar1 * iVar2);
      iVar4 = sadm_ram_get(param_1,local_20,4);
      if (-1 < iVar4) {
        printk("\tbucket max 0x%x\n",local_20[0]);
        iVar4 = sadm_ram_get(param_1,local_20,1);
        if (-1 < iVar4) {
          printk("cast bucket:\n");
          if ((local_20[0] & 1) == 0) {
            pcVar5 = "disable";
          }
          printk("\tbucket %s\n",pcVar5);
          iVar4 = sadm_ram_get(param_1,local_20,3);
          if (-1 < iVar4) {
            printk("\tbucket fill 0x%x(%u bps)\n",local_20[0],local_20[0] * iVar2);
            iVar2 = sadm_ram_get(param_1,local_20,5);
            if (-1 < iVar2) {
              printk("\tbucket max 0x%x\n",local_20[0]);
            }
          }
        }
      }
    }
  }
  return;
}


/* ============= FUNCTION: pon_pp_sadm_init @ 000183e8 ============= */

void pon_pp_sadm_init(void)

{
  return;
}


/* ============= FUNCTION: pon_tm_bmu_init @ 000183ec ============= */

undefined4 pon_tm_bmu_init(void)

{
  int iVar1;
  undefined4 in_r3;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = ZX_RESERVE_MEM_SIZE * 0x100000;
  iVar2 = pdt_mem_size + -0x40000000;
  bppe_va_addr = iVar2 + ZX_RESERVE_MEM_SIZE * -0x100000;
  if (u32_BPPE_POOL_SIZE != 0) {
    uVar3 = 0;
    uVar4 = 0;
    do {
      iVar1 = uVar3 * 2;
      uVar3 = uVar3 + 1;
      *(short *)(bppe_va_addr + iVar1) = (short)uVar4;
      uVar4 = (uVar3 & 0xff) << 8 | uVar3 >> 8 & 0xff;
    } while (uVar3 < u32_BPPE_POOL_SIZE);
    iVar1 = ZX_RESERVE_MEM_SIZE << 0x14;
    iVar2 = pdt_mem_size + -0x40000000;
  }
  jumbo_bppe_va_addr = (iVar2 + 0x10000) - iVar1;
  uVar4 = 0;
  if (u32_JUMBO_BPPE_POOL_SIZE != 0) {
    uVar4 = 0;
    uVar3 = 0;
    do {
      iVar1 = uVar4 * 2;
      uVar4 = uVar4 + 1;
      *(short *)(jumbo_bppe_va_addr + iVar1) = (short)uVar3;
      uVar3 = (uVar4 & 0xff) << 8 | uVar4 >> 8 & 0xff;
    } while (uVar4 < u32_JUMBO_BPPE_POOL_SIZE);
  }
  dma_cache_maint(bppe_va_addr,0x20000,1,uVar4,in_r3);
  *(undefined4 *)(tm_base + 0x8000) = 0;
  *(undefined4 *)(tm_base + 0x8004) = 0x104c040;
  *(undefined4 *)(tm_base + 0x8008) = 0x104c040;
  *(uint *)(tm_base + 0x8058) = (u32_BPPE_POOL_SIZE >> 5) - 1;
  *(uint *)(tm_base + 0x805c) = (u32_JUMBO_BPPE_POOL_SIZE >> 5) - 1;
  *(int *)(tm_base + 0xf4) = pdt_mem_size + 0x40520000 + ZX_RESERVE_MEM_SIZE * -0x100000;
  *(uint *)(tm_base + 0xf8) =
       u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x40520000 +
       ZX_RESERVE_MEM_SIZE * -0x100000;
  *(int *)(tm_base + 0xe8) = pdt_mem_size + 0x40000000 + ZX_RESERVE_MEM_SIZE * -0x100000;
  *(int *)(tm_base + 0xec) = pdt_mem_size + 0x40010000 + ZX_RESERVE_MEM_SIZE * -0x100000;
  *(uint *)(tm_base + 0xfc) = u32_BP_SIZE | u32_JUMBO_BP_SIZE << 0x10;
  *(uint *)(tm_base + 0x8048) = u32_BPPE_POOL_SIZE << 0x10;
  *(uint *)(tm_base + 0x804c) = u32_JUMBO_BPPE_POOL_SIZE << 0x10;
  __memzero(DAT_0001862c,0x28);
  return 0;
}


/* ============= FUNCTION: pon_tm_bmu_disable @ 00018630 ============= */

void pon_tm_bmu_disable(void)

{
  *(undefined4 *)(tm_base + 0x8000) = 0;
  return;
}


/* ============= FUNCTION: pon_tm_bmu_enable @ 0001864c ============= */

void pon_tm_bmu_enable(void)

{
  *(undefined4 *)(tm_base + 0x8000) = 1;
  return;
}


/* ============= FUNCTION: pon_tm_bmu_alloc_bp @ 00018668 ============= */

uint pon_tm_bmu_alloc_bp(void)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  _raw_spin_lock_bh(&alloc_lock);
  if (bmu_alloc_timeout != 0) {
    uVar2 = *(uint *)(tm_base + 0x8014) & 1;
    if (uVar2 != 0) {
      puVar1 = &alloc_lock;
      goto LAB_000186ec;
    }
    uVar3 = *(uint *)(tm_base + 0x800c);
    bmu_alloc_timeout = 0;
    if ((int)uVar3 < 0) {
      bmu_alloc_timeout = uVar2;
      _raw_spin_unlock_bh(&alloc_lock);
      bmu_status._36_4_ = bmu_status._36_4_ + 1;
      return uVar3 & 0xffff;
    }
  }
  *(uint *)(tm_base + 0x8014) = *(uint *)(tm_base + 0x8014) | 1;
  iVar4 = 200;
  do {
    uVar2 = *(uint *)(tm_base + 0x8014) & 3;
    if (uVar2 == 0) {
      uVar3 = *(uint *)(tm_base + 0x800c);
      if ((int)uVar3 < 0) {
        _raw_spin_unlock_bh(DAT_00018790);
        bmu_alloc_timeout = uVar2;
        bmu_status._8_4_ = bmu_status._8_4_ + 1;
        return uVar3 & 0xffff;
      }
      break;
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  bmu_alloc_timeout = 1;
  puVar1 = DAT_00018790;
LAB_000186ec:
  _raw_spin_unlock_bh(puVar1);
  bmu_status._0_4_ = bmu_status._0_4_ + 1;
  return 0xffffffff;
}


/* ============= FUNCTION: pp_bmu_free_bp @ 00018794 ============= */

undefined4 pp_bmu_free_bp(uint param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  _raw_spin_lock_bh(&free_lock);
  iVar1 = 200;
  do {
    if (allow_free_cnt != 0) {
      allow_free_cnt = allow_free_cnt - 1;
      if (param_3 != 0) {
        bmu_status._16_4_ = bmu_status._16_4_ + 1;
      }
      bmu_status._12_4_ = bmu_status._12_4_ + 1;
      *(uint *)(tm_base + 0x8010) = param_1 | param_3 << 0xf;
      _raw_spin_unlock_bh(DAT_00018860);
      return 0;
    }
    iVar1 = iVar1 + -1;
    allow_free_cnt = (uint)(*(int *)(tm_base + 0x80dc) << 0x17) >> 0x1a;
  } while (iVar1 != 0);
  _raw_spin_unlock_bh(&free_lock);
  bmu_status._4_4_ = bmu_status._4_4_ + 1;
  return 0xffffffff;
}


/* ============= FUNCTION: zte_pp_free_skb_data @ 00018864 ============= */

void zte_pp_free_skb_data(void)

{
  return;
}


/* ============= FUNCTION: pon_tm_bmu_alloc_jumbo_bp @ 00018868 ============= */

uint pon_tm_bmu_alloc_jumbo_bp(void)

{
  int iVar1;
  uint uVar2;
  
  if ((*(uint *)(tm_base + 0x8014) & 1) != 0) {
    bmu_status._0_4_ = bmu_status._0_4_ + 1;
    return 0xffffffff;
  }
  _raw_spin_lock_bh(DAT_00018950);
  *(undefined4 *)(tm_base + 0x8014) = 3;
  iVar1 = 200;
  do {
    if ((*(uint *)(tm_base + 0x8014) & 1) == 0) {
      uVar2 = *(uint *)(tm_base + 0x800c);
      if ((int)uVar2 < 0) {
        _raw_spin_unlock_bh(&alloc_lock);
        bmu_status._8_4_ = bmu_status._8_4_ + 1;
        return uVar2 & 0xffff;
      }
      break;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  _raw_spin_unlock_bh(&alloc_lock);
  bmu_status._0_4_ = bmu_status._0_4_ + 1;
  return 0xffffffff;
}


/* ============= FUNCTION: _check_bppe @ 00018954 ============= */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void _check_bppe(int param_1)

{
  ushort uVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  ushort *puVar15;
  int iVar16;
  ushort *puVar17;
  int local_244;
  uint local_23c;
  undefined4 local_22c;
  ushort local_228 [258];
  
  if (param_1 == 0) {
    puVar2 = (uint *)__kmalloc((u32_BPPE_POOL_SIZE >> 5) << 2,0xd0);
    uVar13 = u32_BPPE_POOL_SIZE;
    normal_bp_bits = puVar2;
    if (puVar2 != (uint *)0x0) {
      local_244 = bppe_va_addr;
      local_23c = u32_BPPE_POOL_SIZE >> 5;
      if (local_23c != 0) {
        __memzero();
      }
      uVar4 = *(uint *)(tm_base + 0x8048);
      uVar5 = *(undefined4 *)(tm_base + 0x8080);
      goto LAB_00018a68;
    }
  }
  else {
    puVar2 = (uint *)__kmalloc((u32_JUMBO_BPPE_POOL_SIZE >> 5) << 2,0xd0);
    uVar13 = u32_JUMBO_BPPE_POOL_SIZE;
    jumbo_bp_bits = puVar2;
    if (puVar2 != (uint *)0x0) {
      local_244 = jumbo_bppe_va_addr;
      local_23c = u32_JUMBO_BPPE_POOL_SIZE >> 5;
      if (local_23c != 0) {
        __memzero();
      }
      uVar4 = *(uint *)(tm_base + 0x804c);
      uVar5 = *(undefined4 *)(tm_base + 0x8084);
LAB_00018a68:
      piVar10 = &bppe_va_addr;
      uVar6 = uVar4 & 0xffff;
      uVar7 = uVar4 >> 0x10;
      if (uVar7 < uVar6) {
        uVar7 = uVar7 + uVar13;
      }
      printk("bppe ptr 0x%x,bppe cnt 0x%x bp_type 0x%x  \n",uVar4,uVar5,param_1);
      dma_cache_maint(local_244,0x20000,2);
      if (uVar7 == uVar6) {
        iVar9 = 0;
      }
      else {
        iVar16 = 0;
        iVar9 = 0;
        uVar4 = uVar6;
        do {
          uVar1 = *(ushort *)(local_244 + uVar4 * 2);
          uVar14 = (uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8);
          if (uVar14 < uVar13) {
            iVar3 = _test_and_set_bit(uVar14,puVar2);
            if (iVar3 != 0) {
              if (piVar10[0x12] == 0) {
                iVar9 = iVar9 + 1;
                printk("bppe bp %d : repeat @ %u\n",uVar14,uVar4);
              }
              else {
                iVar9 = iVar9 + 1;
                printk("bppe bp %d : repeat @:",uVar14);
                iVar3 = 0;
                uVar11 = uVar6;
                local_22c = piVar10;
                do {
                  iVar3 = iVar3 + 1;
                  uVar1 = *(ushort *)(local_244 + uVar11 * 2);
                  if (uVar14 == ((uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8))) {
                    printk(&_LC3,uVar11);
                  }
                  piVar10 = local_22c;
                  uVar11 = uVar11 + 1;
                  if (uVar13 <= uVar11) {
                    uVar11 = 0;
                  }
                } while (uVar7 - uVar6 != iVar3);
                printk(&_LC4);
              }
            }
          }
          else {
            printk("bppe bp %d invalid\n",uVar14);
          }
          uVar4 = uVar4 + 1;
          iVar16 = iVar16 + 1;
          if (uVar13 <= uVar4) {
            uVar4 = 0;
          }
        } while (iVar16 != uVar7 - uVar6);
      }
      local_244 = iVar9;
      if (param_1 == 0) {
        puVar8 = (uint *)(tm_base + 0x8088);
      }
      else {
        puVar8 = (uint *)(tm_base + 0x808c);
      }
      uVar4 = *puVar8 & 0x1ff;
      printk("bppi cnt 0x%x\n",uVar4);
      if (uVar4 != 0) {
        puVar17 = (ushort *)((int)&local_22c + 2);
        uVar7 = 0;
        puVar15 = puVar17;
        do {
          if (param_1 == 0) {
            iVar9 = pon_tm_bmu_alloc_bp();
          }
          else {
            iVar9 = pon_tm_bmu_alloc_jumbo_bp();
          }
          if (iVar9 < 0) {
            printk("alloc bp failed\n");
            if (uVar7 == 0) goto LAB_00018bd4;
            break;
          }
          uVar7 = uVar7 + 1;
          puVar15 = puVar15 + 1;
          *puVar15 = (ushort)iVar9;
        } while (uVar4 != uVar7);
        uVar4 = 0;
        do {
          puVar17 = puVar17 + 1;
          uVar6 = (uint)*puVar17;
          if (uVar6 < uVar13) {
            iVar9 = _test_and_set_bit(uVar6,puVar2);
            if (iVar9 != 0) {
              local_244 = local_244 + 1;
              printk("bppi bp %d : repeat\n",uVar6);
            }
          }
          else {
            printk("bppi bp %d invalid\n",uVar6);
          }
          uVar4 = uVar4 + 1;
          pp_bmu_free_bp(uVar6,0,param_1);
        } while (uVar4 != uVar7);
      }
LAB_00018bd4:
      if (local_23c == 0) {
        iVar9 = 0;
      }
      else {
        iVar9 = 0;
        iVar16 = 0;
        puVar8 = puVar2;
        do {
          puVar12 = puVar8 + 1;
          uVar4 = *puVar8;
          if (uVar4 == 0xfffffff) {
            iVar9 = iVar9 + 0x20;
          }
          else {
            uVar7 = 0;
            while( true ) {
              if ((uVar4 & 1 << (uVar7 & 0xff)) == 0) {
                printk("bp %u miss\n",iVar16 + uVar7);
              }
              else {
                iVar9 = iVar9 + 1;
              }
              uVar7 = uVar7 + 1;
              if (uVar7 == 0x20) break;
              uVar4 = *puVar8;
            }
          }
          iVar16 = iVar16 + 0x20;
          puVar8 = puVar12;
        } while (puVar12 != puVar2 + local_23c);
      }
      if (param_1 == 0) {
        printk("%s bp total %u miss %d repeat %d\n","normal",iVar9,uVar13 - iVar9,local_244);
        iVar9 = piVar10[0x11];
      }
      else {
        printk("%s bp total %u miss %d repeat %d\n","jumbo",iVar9,uVar13 - iVar9,local_244);
        iVar9 = piVar10[0x10];
      }
      kfree(iVar9);
      return;
    }
  }
  return;
}


/* ============= FUNCTION: dump_bmu_reg @ 00018de8 ============= */

void dump_bmu_reg(void)

{
  printk("bmu cfg\t\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8000));
  printk("bpp cfg\t\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8004));
  printk("sw alloc bp\t: 0x%x\n",*(undefined4 *)(tm_base + 0x800c));
  printk("sw free bp\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8010));
  printk("sw alloc cfg: 0x%x\n",*(undefined4 *)(tm_base + 0x8014));
  printk("bppi ptr\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8040));
  printk("bppe ptr\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8048));
  printk("pool size\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8058));
  printk("bppe bpcnt\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8080));
  printk("bppi bpcnt\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8088));
  printk("alloc bpcnt\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8090));
  printk("rls bpcnt\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8098));
  printk("bp initsat\t: 0x%x\n",*(undefined4 *)(tm_base + 0x80a0));
  printk("bp stat\t\t: 0x%x\n",*(undefined4 *)(tm_base + 0x80dc));
  printk("bp base\t\t: 0x%x\n",*(undefined4 *)(tm_base + 0xe8));
  printk("bp buf base\t: 0x%x\n",*(undefined4 *)(tm_base + 0xf4));
  return;
}


/* ============= FUNCTION: dump_bmu_status @ 00018fa4 ============= */

void dump_bmu_status(void)

{
  printk("sw alloc cnt \t: 0x%x\n",bmu_status._8_4_);
  printk("hw alloc cnt \t: 0x%x\n",bmu_status._20_4_);
  printk("alloc repeat    : 0x%x\n",bmu_status._32_4_);
  printk("sw free cnt     : 0x%x\n",bmu_status._12_4_);
  printk("hw free cnt     : 0x%x\n",bmu_status._24_4_);
  printk("free repeat   \t: 0x%x\n",bmu_status._28_4_);
  printk("alloc_bp_fail \t: 0x%x\n",bmu_status._0_4_);
  printk("free_bp_fail \t: 0x%x\n",bmu_status._4_4_);
  printk("timeout alloc   : 0x%x\n",bmu_status._36_4_);
  printk("sw free jumbo_c : 0x%x\n",bmu_status._16_4_);
  return;
}


/* ============= FUNCTION: check_bppe @ 00019054 ============= */

void check_bppe(void)

{
  _check_bppe(0);
  return;
}


/* ============= FUNCTION: check_jumbo_bppe @ 0001905c ============= */

void check_jumbo_bppe(void)

{
  _check_bppe(1);
  return;
}


/* ============= FUNCTION: dma_cfg_byteorder @ 00019064 ============= */

void dma_cfg_byteorder(int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(tm_base + 0x10000) & 0xfff0ffff;
  if (param_1 == 0) {
    uVar1 = uVar1 | 0x200000;
  }
  else {
    uVar1 = uVar1 | 0x2f0000;
  }
  *(uint *)(tm_base + 0x10000) = uVar1;
  return;
}


/* ============= FUNCTION: dma_ram_get @ 00019098 ============= */

undefined4 dma_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0x14;
  do {
    if ((*(uint *)(tm_base + 0x10018) & 1) != 0) {
      *(uint *)(tm_base + 0x10014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar2 = 0x14;
      do {
        if ((*(uint *)(tm_base + 0x10018) & 1) != 0) {
          *param_2 = *(undefined4 *)(tm_base + 0x1001c);
          return 0;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("get dma ram %d/%d failed\n",param_3,param_1);
  return 0xfffffff5;
}


/* ============= FUNCTION: dma_tx_free @ 00019138 ============= */

undefined4 dma_tx_free(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(tm_base + 0x1004c) & 0x200000) == 0) {
      *(uint *)(tm_base + 0x1004c) = param_3 | 0x200000 | param_2 << 0xc | param_1 << 0x14;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("tx free %d/%d/%d failed\n",param_1,param_2,param_3,param_4);
  return 0xfffffff5;
}


/* ============= FUNCTION: soft_insert_tx_1desc @ 000191ac ============= */

void soft_insert_tx_1desc(undefined4 param_1,int param_2)

{
  dma_cache_maint(param_1,0x10,1);
  if (param_2 == 0) {
    *(undefined4 *)(tm_base + 0x10054) = 1;
    return;
  }
  *(undefined4 *)(tm_base + 0x10064) = 1;
  return;
}


/* ============= FUNCTION: soft_insert_tx_multidesc @ 000191ec ============= */

void soft_insert_tx_multidesc(int *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = param_1[1];
  uVar3 = param_1[2];
  uVar2 = 0x400 - (iVar1 - *param_1 >> 4);
  if (uVar2 < uVar3) {
    dma_cache_maint(iVar1,uVar2 * 0x10,1);
    dma_cache_maint(*param_1,(uVar3 - uVar2) * 0x10,1);
  }
  else {
    dma_cache_maint(iVar1,uVar3 << 4,1);
  }
  if (param_1[5] == 0) {
    *(uint *)(tm_base + 0x10054) = uVar3;
  }
  else {
    *(uint *)(tm_base + 0x10064) = uVar3;
  }
  param_1[6] = param_1[6] + uVar3;
  return;
}


/* ============= FUNCTION: pon_tm_dma_init @ 0001927c ============= */

undefined4 pon_tm_dma_init(void)

{
  *(uint *)(tm_base + 0x10000) = *(uint *)(tm_base + 0x10000) | 0x2f0000;
  *(undefined4 *)(tm_base + 0x10028) = 1;
  *(undefined4 *)(tm_base + 0x1002c) = 1;
  *(undefined4 *)(tm_base + 0x10030) = 50000;
  *(undefined4 *)(tm_base + 0x10034) = 0x40;
  *(undefined4 *)(tm_set_onu_mac + tm_base + 4) = 0x7f;
  *(undefined4 *)(tm_base + 0x10020) = 0x20;
  *(undefined4 *)(tm_base + 0x10024) = 0x20;
  *(int *)(tm_base + 0x10050) =
       u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
       u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405e0000 +
       ZX_RESERVE_MEM_SIZE * -0x100000;
  *(int *)(tm_base + 0x10060) =
       u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
       u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405f0000 +
       ZX_RESERVE_MEM_SIZE * -0x100000;
  *(undefined4 *)(tm_base + 0x10388) = 0x131217;
  *(undefined4 *)(tm_base + 0x1003c) = 0x400040;
  return 0;
}


/* ============= FUNCTION: zx_pon_tm_int @ 000193dc ============= */

undefined4 zx_pon_tm_int(undefined4 param_1,undefined4 *param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(tm_base + 0x100) & 3 & ~*(uint *)(tm_base + 0x104);
  if (uVar1 != 0) {
    pon_tm_net_int(*param_2,uVar1);
    param_2[1] = param_2[1] + 1;
    return 1;
  }
  return 1;
}


/* ============= FUNCTION: set_pon_tm_int_info @ 00019430 ============= */

void set_pon_tm_int_info(undefined4 param_1)

{
  pon_tm_int_info = param_1;
  return;
}


/* ============= FUNCTION: pon_tm_int_init @ 00019440 ============= */

int pon_tm_int_init(void)

{
  int iVar1;
  
  *(undefined4 *)(tm_base + 0x104) = 0xffffffff;
  iVar1 = request_threaded_irq(g_tm_irq,zx_pon_tm_int,0,0,"pon_tm",&pon_tm_int_info);
  if (iVar1 < 0) {
    printk("request pon_tm irq failed\n");
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}


/* ============= FUNCTION: register_omci_oam_handle @ 000194bc ============= */

void register_omci_oam_handle(undefined4 param_1)

{
  omci_oam_rx = param_1;
  return;
}


/* ============= FUNCTION: pon_tm_check_tx_done_nolock @ 000194cc ============= */

void pon_tm_check_tx_done_nolock(int param_1)

{
  if (param_1 != 1) {
    net_txq._16_4_ = net_txq._16_4_ - (*(uint *)(tm_base + 0x10058) & 0xffff);
    return;
  }
  net_txq._44_4_ = net_txq._44_4_ - (*(uint *)(tm_base + 0x10068) & 0xffff);
  return;
}


/* ============= FUNCTION: pon_tm_eth_get_stats @ 00019524 ============= */

int pon_tm_eth_get_stats(int param_1)

{
  return param_1 + 0x4d0;
}


/* ============= FUNCTION: pon_tm_net_register @ 0001952c ============= */

char * pon_tm_net_register(undefined4 param_1,char *param_2)

{
  char *__dest;
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  __dest = (char *)alloc_etherdev_mqs(0xf8,1,1);
  if (__dest == (char *)0x0) {
    return (char *)0x0;
  }
  *(char **)(__dest + 0x4c0) = __dest;
  *(undefined4 *)(__dest + 0x4c8) = param_1;
  *(undefined1 **)(__dest + 300) = &pon_tm_net_netdev_ops;
  uVar1 = msecs_to_jiffies(5000);
  *(undefined4 *)(__dest + 600) = uVar1;
  strcpy(__dest,param_2);
  iVar2 = strncmp(__dest,"omci",4);
  uVar1 = default_mac;
  puVar3 = *(undefined4 **)(__dest + 0x1dc);
  if (iVar2 == 0) {
    __dest[0x14c] = -0x30;
    __dest[0x14d] = '\a';
    __dest[0x14e] = '\0';
    __dest[0x14f] = '\0';
  }
  *puVar3 = uVar1;
  net_lock_tx = 0;
  net_lock_stack = 0;
  *(undefined2 *)(puVar3 + 1) = DAT_00021888;
  iVar2 = register_netdev(__dest);
  if (iVar2 < 0) {
    free_netdev(__dest);
    return (char *)0x0;
  }
  return __dest;
}


/* ============= FUNCTION: pon_tm_net_timeout @ 000195f8 ============= */

void pon_tm_net_timeout(int param_1)

{
  netif_tx_wake_queue(*(undefined4 *)(param_1 + 0x240));
  *(undefined4 *)(param_1 + 0x260) = jiffies;
  return;
}


/* ============= FUNCTION: pon_tm_timer_func @ 0001961c ============= */

void pon_tm_timer_func(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  
  iVar2 = 0;
  iVar1 = DAT_000196f0;
  do {
    if (*(int *)(iVar1 + 0x10) != 0) {
      uVar3 = 0;
      if ((*(uint *)(((uint)&stack0xffffffe8 & 0xffffe000) + 4) & 0x1fff00) == 0) {
        uVar3 = _raw_spin_lock_irqsave();
      }
      else {
        _raw_spin_lock(DAT_000196f4);
      }
      pon_tm_check_tx_done_nolock(iVar2);
      if ((*(uint *)(((uint)&stack0xffffffe8 & 0xffffe000) + 4) & 0x1fff00) == 0) {
        _raw_spin_unlock_irqrestore();
      }
      else {
        _raw_spin_unlock(DAT_000196f4,uVar3);
      }
    }
    bVar4 = iVar2 != 1;
    iVar1 = iVar1 + 0x1c;
    iVar2 = 1;
  } while (bVar4);
  pon_tm_timer._8_4_ = jiffies + 1;
  pon_tm_poll_cnt = pon_tm_poll_cnt + 1;
  add_timer(pon_tm_timer);
  return;
}


/* ============= FUNCTION: pon_tm_net_stop @ 000196f8 ============= */

undefined4 pon_tm_net_stop(char *param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x240) == 0) {
    warn_slowpath_null("include/linux/netdevice.h",0xa06);
    printk(&_LC2);
  }
  else {
    _set_bit(0,*(int *)(param_1 + 0x240) + 0x50);
  }
  netif_carrier_off(param_1);
  iVar1 = strcmp(param_1,"pon");
  if (iVar1 == 0) {
    napi_disable(param_1 + 0x530);
    *(uint *)(tm_base + 0x104) = *(uint *)(tm_base + 0x104) | 7;
  }
  return 0;
}


/* ============= FUNCTION: pon_tm_net_open @ 00019784 ============= */

undefined4 pon_tm_net_open(char *param_1)

{
  code *pcVar1;
  int iVar2;
  
  _clear_bit(0,*(int *)(param_1 + 0x240) + 0x50);
  netif_carrier_on(param_1);
  iVar2 = strcmp(param_1,"pon");
  if (iVar2 == 0) {
    if ((*(uint *)(param_1 + 0x538) & 1) == 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)software_udf(0x12,0x197fc);
      (*pcVar1)();
    }
    DataMemoryBarrier(0xb);
    _clear_bit(0,param_1 + 0x538);
    *(uint *)(tm_base + 0x104) = *(uint *)(tm_base + 0x104) & 0xfffffffc;
  }
  return 0;
}


/* ============= FUNCTION: net_invalid_cache @ 00019800 ============= */

void net_invalid_cache(uint param_1,int param_2)

{
  dma_cache_maint(param_1 & 0xffffffe0,
                  (param_2 + 0x1f + param_1 & 0xffffffe0) - (param_1 & 0xffffffe0),2);
  return;
}


/* ============= FUNCTION: dump_net_data @ 0001981c ============= */

void dump_net_data(undefined1 *param_1,uint param_2)

{
  uint uVar1;
  
  if (0x7f < param_2) {
    param_2 = 0x80;
  }
  if (param_2 != 0) {
    uVar1 = 0;
    printk("%.2x ",*param_1);
    while (uVar1 = uVar1 + 1, uVar1 != param_2) {
      printk("%.2x ",param_1[uVar1]);
      if ((uVar1 & 0xf) == 0xf) {
        printk(&_LC4);
      }
    }
  }
  printk(&_LC4);
  return;
}


/* ============= FUNCTION: dump_desc @ 00019894 ============= */

void dump_desc(undefined4 *param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *(byte *)((int)param_1 + 7);
  bVar2 = *(byte *)(param_1 + 2);
  printk("0x%.8x 0x%.8x 0x%.8x 0x%.8x 0x%.8x\n",param_1,*param_1,param_1[1],param_1[2],param_1[3]);
  printk("bp %u gem %u len %u \n",(uint)(bVar1 >> 1) | (uint)bVar2 << 7,
         *(ushort *)(param_1 + 1) & 0xfff,*(ushort *)(param_1 + 3) >> 2);
  return;
}


/* ============= FUNCTION: dump_desc_tx @ 000198f8 ============= */

void dump_desc_tx(undefined4 *param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *(byte *)((int)param_1 + 7);
  bVar2 = *(byte *)(param_1 + 2);
  printk("0x%.8x:0x%.8x 0x%.8x 0x%.8x 0x%.8x\n",param_1,*param_1,param_1[1],param_1[2],param_1[3]);
  printk("bp %u gem %u len %u oam_omci_Flag %u\n",(uint)(bVar1 >> 1) | (uint)bVar2 << 7,
         *(undefined2 *)(param_1 + 1),*(ushort *)(param_1 + 3) >> 2,
         ((uint)*(byte *)((int)param_1 + 6) << 0x1d) >> 0x1f);
  return;
}


/* ============= FUNCTION: pon_tm_data_raw_send @ 00019964 ============= */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 pon_tm_data_raw_send(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  byte bVar6;
  size_t __n;
  void *__dest;
  uint uVar7;
  
  __n = *(size_t *)(param_1 + 100);
  uVar3 = pon_tm_bmu_alloc_bp();
  if ((int)uVar3 < 0) {
    printk("alloc bp failed\n");
    return 0xffffffff;
  }
  if (*(uint *)((int)&bp_max_number + (*(byte *)(param_2 + 9) & 1) * 4) <= uVar3) {
    printk("invalid bp %d\n",uVar3);
    return 0xffffffff;
  }
  __dest = (void *)(u32_BP_SIZE * uVar3 +
                   pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000);
  memcpy(__dest,*(void **)(param_1 + 0xcc),__n);
  *(byte *)(param_2 + 0xb) = *(byte *)(param_2 + 0xb) & 1 | 0x20;
  uVar1 = (undefined1)((int)uVar3 >> 7);
  uVar7 = __n;
  if (param_3 == 0) {
    if ((*(byte *)(param_2 + 6) & 4) != 0) {
      uVar5 = __n & 0x3fff;
      bVar6 = *(byte *)(param_2 + 0xe) & 1;
      goto LAB_00019a14;
    }
    bVar6 = *(byte *)(param_2 + 0xe) & 1;
    bVar4 = bVar6 ^ 1;
    if (0x3f < (int)__n) {
      bVar4 = 0;
    }
    if (bVar4 == 0) {
      uVar5 = __n & 0x3fff;
      goto LAB_00019a14;
    }
    if (__n != 0x40) {
      __memzero((int)__dest + __n);
      uVar5 = 0x40;
      bVar6 = *(byte *)(param_2 + 0xe) & 1;
      uVar7 = 0x40;
      goto LAB_00019a14;
    }
    uVar5 = 0x40;
    *(byte *)(param_2 + 7) = *(byte *)(param_2 + 7) & 1 | (byte)((uVar3 & 0x7f) << 1);
    *(undefined1 *)(param_2 + 8) = uVar1;
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 3 | 0x100;
    uVar7 = uVar5;
  }
  else {
    uVar5 = __n & 0x3fff;
    bVar6 = *(byte *)(param_2 + 0xe) & 1;
LAB_00019a14:
    *(undefined1 *)(param_2 + 8) = uVar1;
    *(byte *)(param_2 + 7) = *(byte *)(param_2 + 7) & 1 | (byte)((uVar3 & 0x7f) << 1);
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 3 | (ushort)(uVar5 << 2);
    if (bVar6 != 0) goto LAB_00019a48;
  }
  *(uint *)(param_2 + 8) = *(uint *)(param_2 + 8) & 0xff8001ff | uVar5 << 9;
LAB_00019a48:
  if (0 < pon_tm_net_debug) {
    printk("Send skb %x data %x,len %u buf size %u, BP %d \naddr %x,off %x,c %d,que %x,pri %x,f %x\n"
           ,param_1,*(undefined4 *)(param_1 + 0xcc),uVar7,
           *(int *)(param_1 + 0xc4) - *(int *)(param_1 + 200),uVar3,__dest,
           *(byte *)(param_2 + 0xb) >> 1,*(byte *)(param_1 + 0x72) & 1,0,0);
    dump_desc_tx(param_2);
    dump_net_data(__dest,uVar7);
    pon_tm_net_debug = pon_tm_net_debug + -1;
  }
  iVar2 = param_3 * 0x1c;
  *(int *)(net_txq + iVar2 + 0x10) = *(int *)(net_txq + iVar2 + 0x10) + 1;
  dma_cache_maint(__dest,__n);
  soft_insert_tx_1desc(param_2,param_3);
  *(int *)(net_txq + iVar2 + 0x18) = *(int *)(net_txq + iVar2 + 0x18) + 1;
  bmu_status._24_4_ = bmu_status._24_4_ + 1;
  return 0;
}


/* ============= FUNCTION: pon_tm_get_next_txdesc @ 00019bf0 ============= */

int pon_tm_get_next_txdesc(uint param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if ((0x1ff < *(uint *)(net_txq + param_1 * 0x1c + 0x10)) &&
     (uVar3 = pon_tm_check_tx_done_nolock(param_1 & 0xff),
     0x3ff < *(uint *)(net_txq + param_1 * 0x1c + 0x10))) {
    iVar1 = param_1 * 4;
    if (uVar3 < 0x4000000) {
      *(int *)((int)&pon_tm_tx_sw_full + iVar1) = *(int *)((int)&pon_tm_tx_sw_full + iVar1) + 1;
    }
    else {
      *(int *)((int)&pon_tm_tx_full + iVar1) = *(int *)((int)&pon_tm_tx_full + iVar1) + 1;
    }
    return 0;
  }
  iVar1 = param_1 * 0x1c;
  iVar2 = *(int *)(net_txq + iVar1 + 0xc);
  uVar3 = iVar2 + 1;
  *(uint *)(net_txq + iVar1 + 0xc) = uVar3;
  if (0x3ff < uVar3) {
    *(undefined4 *)(net_txq + iVar1 + 0xc) = 0;
  }
  return *(int *)(net_txq + iVar1) + iVar2 * 0x10;
}


/* ============= FUNCTION: pon_tm_net_tx @ 00019c80 ============= */

undefined4 pon_tm_net_tx(int param_1,int param_2)

{
  code *pcVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined1 auStack_28 [4];
  undefined4 local_24 [2];
  
  if (*(int *)(param_2 + 0x4c8) == 0) {
    ffe_learn_skb(param_1,3);
  }
  if ((*(uint *)(((uint)auStack_28 & 0xffffe000) + 4) & 0x1fff00) == 0) {
    uVar7 = _raw_spin_lock_irqsave(DAT_0001a0e4);
    iVar6 = *(int *)(param_2 + 0x4c8);
    if (iVar6 != 0) goto LAB_00019cd8;
LAB_00019d3c:
    local_24[0] = 0;
    iVar6 = pon_is_registered();
    if (iVar6 != 0) {
      puVar3 = (undefined4 *)pon_tm_get_next_txdesc(0);
      if (puVar3 == (undefined4 *)0x0) {
        __dev_kfree_skb_any(param_1,1);
        *(int *)(param_2 + 0x4ec) = *(int *)(param_2 + 0x4ec) + 1;
        printk("get up tx desc failed\n");
        goto LAB_00019cec;
      }
      *puVar3 = 0x80;
      *(undefined1 *)puVar3 = 0xc9;
      pcVar1 = dev_qos_get_queue;
      puVar3[3] = 0;
      puVar3[1] = 0x10000;
      puVar3[2] = 0x1000000;
      if (pcVar1 != (code *)0x0) {
        (*pcVar1)(*(undefined4 *)(param_1 + 0x80),local_24);
      }
      uVar5 = *(ushort *)(*(int *)(param_1 + 0xcc) + 0xc);
      uVar5 = uVar5 << 8 | uVar5 >> 8;
      if (uVar5 == 0x884c || uVar5 == 0x8899) {
        if (uVar5 != 0x8899 && uVar5 != 0x884c) goto LAB_00019e8c;
      }
      else {
        iVar6 = dev_get_by_name(&init_net,&_LC17);
        if (iVar6 != 0) {
          if ((*(uint *)(iVar6 + 0x138) & 1) != 0) {
            disableIRQinterrupts();
            iVar4 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
            *(int *)(iVar4 + *(int *)(iVar6 + 0x280)) =
                 *(int *)(iVar4 + *(int *)(iVar6 + 0x280)) + -1;
            if (dev_qos_select_queue == (code *)0x0) {
              *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f;
            }
            else {
              cVar2 = (*dev_qos_select_queue)(param_1,param_2);
              *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f | cVar2 << 5;
            }
            goto LAB_00019ea0;
          }
          disableIRQinterrupts();
          iVar4 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar4 + *(int *)(iVar6 + 0x280)) = *(int *)(iVar4 + *(int *)(iVar6 + 0x280)) + -1
          ;
        }
LAB_00019e8c:
        pcVar1 = dev_qos_select_queue;
        if (lan_up == 1) {
          *(undefined2 *)(puVar3 + 1) = 0;
          if (pcVar1 == (code *)0x0) {
            *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f;
          }
          else {
            cVar2 = (*pcVar1)(param_1,param_2);
            *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f | cVar2 << 5;
          }
          *(ushort *)((int)puVar3 + 2) =
               *(ushort *)((int)puVar3 + 2) & 0xfc0f | (ushort)((lan_up_port + 0x28U & 0x3f) << 4);
        }
      }
LAB_00019ea0:
      if (*(char *)(param_1 + 0xb5) != '\0') {
        *(byte *)((int)puVar3 + 0xe) = *(byte *)((int)puVar3 + 0xe) | 1;
        *(ushort *)((int)puVar3 + 0xe) =
             *(ushort *)((int)puVar3 + 0xe) & 1 | *(short *)(param_1 + 0xba) << 1;
        puVar3[2] = puVar3[2] & 0xff8001ff | (uint)*(byte *)(param_1 + 0xb6) << 9;
      }
      iVar6 = pon_tm_data_raw_send(param_1,puVar3,0);
      if (iVar6 == 0) {
LAB_00019ef0:
        *(int *)(param_2 + 0x4d4) = *(int *)(param_2 + 0x4d4) + 1;
        *(int *)(param_2 + 0x4dc) = *(int *)(param_2 + 0x4dc) + *(int *)(param_1 + 100);
        goto LAB_00019ce0;
      }
      if (net_txq._12_4_ == 0) {
        net_txq._12_4_ = 0x3ff;
      }
      else {
        net_txq._12_4_ = net_txq._12_4_ + -1;
      }
    }
LAB_00019d4c:
    *(int *)(param_2 + 0x4ec) = *(int *)(param_2 + 0x4ec) + 1;
  }
  else {
    _raw_spin_lock();
    iVar6 = *(int *)(param_2 + 0x4c8);
    uVar7 = 0;
    if (iVar6 == 0) goto LAB_00019d3c;
LAB_00019cd8:
    if (iVar6 == 1) {
      puVar3 = (undefined4 *)pon_tm_get_next_txdesc(1);
      if (puVar3 == (undefined4 *)0x0) {
        __dev_kfree_skb_any(param_1,1);
        *(int *)(param_2 + 0x4ec) = *(int *)(param_2 + 0x4ec) + 1;
        printk("get dn tx desc failed\n");
        goto LAB_00019cec;
      }
      *puVar3 = 0x80;
      iVar6 = test_da_unknown;
      puVar3[2] = 0x1000000;
      puVar3[1] = 0x10000;
      if (iVar6 == 0) {
        puVar3[3] = 3;
        *(ushort *)((int)puVar3 + 2) =
             *(ushort *)((int)puVar3 + 2) & 0xfc0f | (*(byte *)(param_1 + 0xb4) + 0x28 & 0x3f) << 4;
      }
      else {
        puVar3[3] = 2;
      }
      if (dev_qos_select_queue == (code *)0x0) {
        *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f;
      }
      else {
        *(byte *)((int)puVar3 + 3) =
             *(byte *)((int)puVar3 + 3) & 0x1f | (byte)((*(ushort *)(param_1 + 0x78) & 7) << 5);
      }
      if (*(char *)(param_1 + 0xb5) != '\0') {
        *(byte *)((int)puVar3 + 0xe) = *(byte *)((int)puVar3 + 0xe) | 1;
        *(ushort *)((int)puVar3 + 0xe) =
             *(ushort *)((int)puVar3 + 0xe) & 1 | *(short *)(param_1 + 0xba) << 1;
        puVar3[2] = puVar3[2] & 0xff8001ff | (uint)*(byte *)(param_1 + 0xb6) << 9;
      }
      iVar6 = pon_tm_data_raw_send(param_1,puVar3,1);
      if (iVar6 != 0) {
        if (net_txq._40_4_ == 0) {
          net_txq._40_4_ = 0x3ff;
        }
        else {
          net_txq._40_4_ = net_txq._40_4_ + -1;
        }
        goto LAB_00019d4c;
      }
      goto LAB_00019ef0;
    }
  }
LAB_00019ce0:
  __dev_kfree_skb_any(param_1,1);
LAB_00019cec:
  if ((*(uint *)(((uint)auStack_28 & 0xffffe000) + 4) & 0x1fff00) != 0) {
    _raw_spin_unlock(DAT_0001a0e4);
    return 0;
  }
  _raw_spin_unlock_irqrestore(DAT_0001a0e4,uVar7);
  return 0;
}


/* ============= FUNCTION: pon_tm_net_int @ 0001a0e8 ============= */

void pon_tm_net_int(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = tm_base;
  *(int *)(param_1 + 0xe0) = *(int *)(param_1 + 0xe0) + 1;
  *(uint *)(tm_base + 0x104) = *(uint *)(iVar1 + 0x104) | 7;
  *(undefined4 *)(param_1 + 0xc) = param_2;
  if (-1 < *(int *)(param_1 + 0x78) << 0x1e) {
    iVar1 = _test_and_set_bit(0,param_1 + 0x78);
    if (iVar1 == 0) {
      __napi_schedule(param_1 + 0x70);
      return;
    }
  }
  *(int *)(param_1 + 0xe4) = *(int *)(param_1 + 0xe4) + 1;
  return;
}


/* ============= FUNCTION: pon_tm_queue_init @ 0001a15c ============= */

void pon_tm_queue_init(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar4 = u32_BP_SIZE * u32_BPPE_POOL_SIZE + u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
          pdt_mem_size + ZX_RESERVE_MEM_SIZE * -0x100000;
  iVar2 = iVar4 + -0x3fae0000;
  puVar3 = DAT_0001a254;
  do {
    iVar1 = iVar2 + 0x20000;
    puVar3[-1] = iVar2;
    iVar2 = iVar2 + 0x4000;
    puVar3[0xf] = iVar1;
    *puVar3 = 0;
    puVar3[0x10] = 0;
    puVar3 = puVar3 + 2;
  } while (iVar2 != iVar4 + -0x3fac0000);
  net_txq._28_4_ = iVar4 + -0x3fa10000;
  net_txq._20_4_ = 0;
  net_txq._0_4_ = iVar4 + -0x3fa20000;
  net_txq._48_4_ = 1;
  printk("DMA_DN_DESC_CNT = 0x%x\n",*(undefined4 *)(tm_base + 0x10068));
  printk("DMA_UP_DESC_CNT = 0x%x\n",*(undefined4 *)(tm_base + 0x10058));
  return;
}


/* ============= FUNCTION: pon_tm_net_init @ 0001a258 ============= */

undefined4
pon_tm_net_init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  pon_tm_netdev._4_4_ = pon_tm_net_register(1,&_LC21,param_3,param_4,param_4);
  if (pon_tm_netdev._4_4_ == 0) {
    printk("failed to register sw net\n");
    return 0xffffffff;
  }
  iVar1 = pon_tm_net_register(0,&_LC3);
  pon_tm_netdev._0_4_ = iVar1;
  if (iVar1 != 0) {
    set_pon_tm_int_info(iVar1 + 0x4c0);
    netif_napi_add(iVar1,iVar1 + 0x530,pon_tm_net_poll,0x200);
    pon_tm_queue_init();
    *(uint *)(tm_base + 0x104) = *(uint *)(tm_base + 0x104) | 7;
    init_timer_key(pon_tm_timer,0,0,0);
    pon_tm_timer._8_4_ = jiffies + 1;
    pon_tm_timer._16_4_ = pon_tm_timer_func;
    pon_tm_timer._20_4_ = 0;
    add_timer(pon_tm_timer);
    printk("pon_tm net init ok,%d/%d\n",0xd8,0xb0);
    return 0;
  }
  printk("failed to register pon net\n");
  return 0xffffffff;
}


/* ============= FUNCTION: check_pon_tm_queue @ 0001a368 ============= */

void check_pon_tm_queue(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r2;
  undefined4 in_r3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  
  if (uncache_tx_desc == 0) {
    uVar7 = __arm_ioremap(u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
                          u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405e0000 +
                          ZX_RESERVE_MEM_SIZE * -0x100000,0x20000);
    uncache_tx_desc = (int)uVar7;
    if (uncache_tx_desc == 0) {
      printk("ioremap failed\n",(int)((ulonglong)uVar7 >> 0x20),extraout_r2,in_r3);
      return;
    }
  }
  iVar2 = net_txq._52_4_;
  if (0x3ff < (uint)net_txq._52_4_) {
    iVar2 = 0x400;
  }
  if (iVar2 == 0) {
    return;
  }
  iVar3 = 0;
  uVar4 = (uint)(*(ushort *)(uncache_tx_desc + 0x1000c) >> 2);
  iVar5 = uncache_tx_desc + 0x10000;
  iVar6 = uncache_tx_desc + 0x10000;
  if (uVar4 == (uint)(*(int *)(uncache_tx_desc + 0x10008) << 9) >> 0x12) {
    do {
      iVar6 = iVar5;
      if (uVar4 < 0x20) break;
      iVar3 = iVar3 + 1;
      iVar6 = iVar5 + 0x10;
      if (iVar2 == iVar3) {
        return;
      }
      piVar1 = (int *)(iVar5 + 0x18);
      uVar4 = (uint)(*(ushort *)(iVar5 + 0x1c) >> 2);
      iVar5 = iVar6;
    } while (uVar4 == (uint)(*piVar1 << 9) >> 0x12);
  }
  printk("invalid desc index %d:\n");
  dump_desc_tx(iVar6);
  return;
}


/* ============= FUNCTION: dump_pon_tm_net_info @ 0001a484 ============= */

void dump_pon_tm_net_info(uint param_1)

{
  int iVar1;
  
  if (1 < param_1) {
    printk("invalid port %d\n");
    return;
  }
  iVar1 = *(int *)((int)&pon_tm_netdev + param_1 * 4);
  printk(&_LC28,iVar1);
  printk("irq     %u\n",*(undefined4 *)(iVar1 + 0x5a0));
  printk("irq_err %u\n",*(undefined4 *)(iVar1 + 0x5a4));
  printk("poll    %u\n",*(undefined4 *)(iVar1 + 0x5a8));
  printk("rx int  %u\n",*(undefined4 *)(iVar1 + 0x5ac));
  printk("tx int  %u\n",*(undefined4 *)(iVar1 + 0x5b0));
  return;
}


/* ============= FUNCTION: tm_pon_tm_init @ 0001a514 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int tm_pon_tm_init(void)

{
  int iVar1;
  
  printk("pon tm init\n");
  *(undefined4 *)(tm_base + 0x128) = 0x1fff;
  *(undefined4 *)(tm_base + 0x130) = 0x1fffff;
  (*_request_threaded_irq)(0x66665b0);
  pon_tm_red_init();
  pon_tm_dma_init();
  iVar1 = pon_tm_bmu_init();
  if (-1 < iVar1) {
    *(int *)(tm_base + 0xf0) =
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x40520000 +
         ZX_RESERVE_MEM_SIZE * -0x100000;
    pon_tm_bmu_enable();
    *(undefined4 *)(tm_base + 0xc008) = 0;
    pon_tm_net_init();
    pon_tm_int_init();
    return 0;
  }
  printk("init bmu moduel failed %d\n",iVar1);
  return iVar1;
}


/* ============= FUNCTION: red_set_queue_cfg @ 0001a618 ============= */

undefined4 red_set_queue_cfg(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    return 0xffffffea;
  }
  iVar1 = 0x14;
  do {
    if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
      *(uint *)(tm_base + 0x4014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(tm_base + 0x4028) = param_2[3];
      *(undefined4 *)(tm_base + 0x4024) = param_2[2];
      *(undefined4 *)(tm_base + 0x4020) = param_2[1];
      *(undefined4 *)(tm_base + 0x401c) = *param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  DAT_0002e998 = DAT_0002e998 + 1;
  return 0xfffffff5;
}


/* ============= FUNCTION: red_get_queue_cfg @ 0001a6e8 ============= */

undefined4 red_get_queue_cfg(uint param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == (undefined4 *)0x0) {
    return 0xffffffea;
  }
  iVar2 = 0x14;
  do {
    if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
      *(uint *)(tm_base + 0x4014) = param_1 | 0x8000000;
      iVar1 = tm_base;
      iVar3 = 0x14;
      do {
        if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
          param_2[3] = *(undefined4 *)(tm_base + 0x4028);
          iVar2 = tm_base;
          param_2[2] = *(undefined4 *)(iVar1 + 0x4024);
          iVar1 = tm_base;
          param_2[1] = *(undefined4 *)(iVar2 + 0x4020);
          *param_2 = *(undefined4 *)(iVar1 + 0x401c);
          return 0;
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  DAT_0002e99c = DAT_0002e99c + 1;
  return 0xfffffff5;
}


/* ============= FUNCTION: red_get_queue_status @ 0001a7e0 ============= */

undefined4 red_get_queue_status(uint param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == (undefined4 *)0x0) {
    return 0xffffffea;
  }
  iVar1 = 0x14;
  do {
    if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
      *(uint *)(tm_base + 0x4014) = param_1 | 0x8400000;
      iVar2 = 0x14;
      do {
        if ((*(uint *)(tm_base + 0x4018) & 1) != 0) {
          *param_2 = *(undefined4 *)(tm_base + 0x401c);
          return 0;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  DAT_0002e9a0 = DAT_0002e9a0 + 1;
  return 0xfffffff5;
}


/* ============= FUNCTION: is_red_alloc_bp_empty @ 0001a89c ============= */

bool is_red_alloc_bp_empty(undefined4 param_1)

{
  uint local_1c;
  uint local_18;
  
  local_1c = 0;
  local_18 = 0;
  red_get_queue_cfg();
  red_get_queue_status(param_1,&local_1c);
  return (local_18 & 0xfff) <= (local_1c & 0xfff);
}


/* ============= FUNCTION: soft_release_rx_desc @ 0001a8e8 ============= */

undefined4 soft_release_rx_desc(int param_1,uint param_2,uint param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = param_3 != 0;
  bVar2 = param_3 == 1;
  if (param_3 < 2) {
    bVar3 = 6 < param_2;
    bVar2 = param_2 == 7;
  }
  if (!bVar3 || bVar2) {
    iVar1 = 0x1e;
    do {
      if ((*(uint *)(tm_base + 0x4064) & 1) == 0) {
        *(uint *)(tm_base + 0x4068) = param_1 << 0xe | param_4 << 4 | param_2 | param_3 << 3;
        *(undefined4 *)(tm_base + 0x4064) = 1;
        return 0;
      }
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    printk("failed to rls rx desc\n");
    DAT_0002e994 = DAT_0002e994 + 1;
    return 0xfffffff5;
  }
  return 0xffffffea;
}


/* ============= FUNCTION: pon_tm_red_init @ 0001a998 ============= */

undefined4 pon_tm_red_init(void)

{
  int iVar1;
  uint uVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  uVar2 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_18 = 0x400;
  do {
    iVar1 = red_set_queue_cfg(uVar2 & 0xffff,&local_18,0);
    if (iVar1 < 0) goto LAB_0001aabc;
    uVar2 = uVar2 + 1;
  } while (uVar2 != 0x10);
  local_18 = 0x800400;
  do {
    iVar1 = red_set_queue_cfg(uVar2 & 0xffff,&local_18,0);
    if (iVar1 < 0) {
LAB_0001aabc:
      printk("red queue %d cfg failed,%d\n",uVar2);
      return 0xffffffff;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 400);
  uVar2 = 0;
  local_18 = 0x200020;
  do {
    iVar1 = red_set_queue_cfg(uVar2 & 0xffff,&local_18,2);
    if (iVar1 < 0) goto LAB_0001aaa4;
    uVar2 = uVar2 + 1;
  } while (uVar2 != 0x180);
  uVar2 = 0;
  local_14 = 0x100ff80;
  local_18 = 0xff803fff;
  local_10 = 0x100200;
  local_c = 0x20;
  while (iVar1 = red_set_queue_cfg(uVar2 & 0xffff,&local_18,4), -1 < iVar1) {
    uVar2 = uVar2 + 1;
    if (uVar2 == 0x180) {
      return 0;
    }
  }
LAB_0001aaa4:
  printk("red queue %d cfg ram 0 failed,%d\n",uVar2);
  return 0xffffffff;
}


/* ============= FUNCTION: usch_ram_set @ 0001aad4 ============= */

undefined4 usch_ram_set(uint param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(tm_base + 0x14018) & 1) != 0) {
      *(uint *)(tm_base + 0x14014) = param_1 | param_3 << 0x16;
      *(undefined4 *)(tm_base + 0x1401c) = param_2;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0xfffffff5;
}


/* ============= FUNCTION: usch_ram_get @ 0001ab34 ============= */

undefined4 usch_ram_get(uint param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(tm_base + 0x14018) & 1) != 0) {
      *(uint *)(tm_base + 0x14014) = param_1 | 0x8000000 | param_3 << 0x16;
      iVar2 = 5;
      do {
        if ((*(uint *)(tm_base + 0x14018) & 1) != 0) {
          *param_2 = *(undefined4 *)(tm_base + 0x1401c);
          return 0;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0xfffffff5;
}


/* ============= FUNCTION: usch_set_que_wrr_pos @ 0001abc0 ============= */

int usch_set_que_wrr_pos(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x1f < param_1) {
    return -0x16;
  }
  iVar1 = usch_ram_set(param_1,param_2 & 7,0,param_4,param_4);
  if (-1 < iVar1) {
    return 0;
  }
  usch_status = usch_status + 1;
  return iVar1;
}


/* ============= FUNCTION: usch_get_que_wrr_pos @ 0001ac08 ============= */

int usch_get_que_wrr_pos(uint param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x1f < param_1 || param_2 == (uint *)0x0) {
    return -0x16;
  }
  iVar1 = usch_ram_get(param_1,param_2,0,param_4,param_4);
  if (iVar1 < 0) {
    usch_status = usch_status + 1;
  }
  else {
    *param_2 = *param_2 & 7;
    iVar1 = 0;
  }
  return iVar1;
}


/* ============= FUNCTION: usch_set_que_weight @ 0001ac68 ============= */

int usch_set_que_weight(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1) {
    return -0x16;
  }
  iVar1 = usch_ram_set(param_1,param_2 & 0x3ffff,1,param_4,param_4);
  if (-1 < iVar1) {
    return 0;
  }
  DAT_0002e9ac = DAT_0002e9ac + 1;
  return iVar1;
}


/* ============= FUNCTION: usch_get_que_weight @ 0001acb0 ============= */

int usch_get_que_weight(uint param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1 || param_2 == (uint *)0x0) {
    return -0x16;
  }
  iVar1 = usch_ram_get(param_1,param_2,1,param_2 == (uint *)0x0,param_4);
  if (iVar1 < 0) {
    DAT_0002e9b0 = DAT_0002e9b0 + 1;
  }
  else {
    *param_2 = *param_2 & 0x3ffff;
    iVar1 = 0;
  }
  return iVar1;
}


/* ============= FUNCTION: usch_set_pq_shp_fill @ 0001ad10 ============= */

int usch_set_pq_shp_fill(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1) {
    return -0x16;
  }
  iVar1 = usch_ram_set(param_1,param_2 & 0x1fffff,2,param_4,param_4);
  if (-1 < iVar1) {
    return 0;
  }
  DAT_0002e9b4 = DAT_0002e9b4 + 1;
  return iVar1;
}


/* ============= FUNCTION: usch_get_pq_shp_fill @ 0001ad58 ============= */

int usch_get_pq_shp_fill(uint param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1 || param_2 == (uint *)0x0) {
    return -0x16;
  }
  iVar1 = usch_ram_get(param_1,param_2,2,param_2 == (uint *)0x0,param_4);
  if (iVar1 < 0) {
    DAT_0002e9b8 = DAT_0002e9b8 + 1;
  }
  else {
    *param_2 = *param_2 & 0x1fffff;
    iVar1 = 0;
  }
  return iVar1;
}


/* ============= FUNCTION: usch_set_pq_shp_max @ 0001adb8 ============= */

int usch_set_pq_shp_max(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1) {
    return -0x16;
  }
  iVar1 = usch_ram_set(param_1,param_2 & 0x3fffff,3,param_4,param_4);
  if (-1 < iVar1) {
    return 0;
  }
  DAT_0002e9b4 = DAT_0002e9b4 + 1;
  return iVar1;
}


/* ============= FUNCTION: usch_get_pq_shp_max @ 0001ae00 ============= */

int usch_get_pq_shp_max(uint param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0xff < param_1 || param_2 == (uint *)0x0) {
    return -0x16;
  }
  iVar1 = usch_ram_get(param_1,param_2,3,param_2 == (uint *)0x0,param_4);
  if (iVar1 < 0) {
    DAT_0002e9b8 = DAT_0002e9b8 + 1;
  }
  else {
    *param_2 = *param_2 & 0x3fffff;
    iVar1 = 0;
  }
  return iVar1;
}


/* ============= FUNCTION: pon_tm_usch_init @ 0001ae60 ============= */

undefined4 pon_tm_usch_init(void)

{
  return 0;
}


/* ============= FUNCTION: netdebug_dev_open @ 0001ae68 ============= */

undefined4 netdebug_dev_open(void)

{
  return 0;
}


/* ============= FUNCTION: netdebug_dev_release @ 0001ae70 ============= */

undefined4 netdebug_dev_release(void)

{
  return 0;
}


/* ============= FUNCTION: netdebug_dev_ioctl @ 0001ae78 ============= */

undefined4 netdebug_dev_ioctl(undefined4 param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 auStack_20 [4];
  undefined4 local_1c;
  uint local_18;
  uint local_14;
  
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  switch(param_2) {
  case 0x100:
    uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    uVar1 = param_3 + 0xc;
    uVar2 = uVar1;
    if (param_3 < 0xfffffff4) {
      uVar2 = uVar1 - (uVar3 + 1);
    }
    if (param_3 < 0xfffffff4 && uVar1 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      __copy_from_user(&local_1c,param_3,0xc);
    }
    else {
      __memzero(&local_1c,0xc,uVar2);
    }
    uVar2 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    if (param_3 < 0xfffffff4 && param_3 + 0xc <= uVar2) {
      uVar2 = 0;
    }
    local_14 = (*(uint *)(&g_netdebug_mod_tabel + (local_18 >> 5) * 4) & 1 << (local_18 & 0x1f)) >>
               (local_18 & 0x1f);
    if (uVar2 != 0) {
      return 0;
    }
    __copy_to_user(param_3,&local_1c,0xc);
    return 0;
  case 0x101:
    uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    uVar1 = param_3 + 0xc;
    uVar2 = uVar1;
    if (param_3 < 0xfffffff4) {
      uVar2 = uVar1 - (uVar3 + 1);
    }
    if (param_3 < 0xfffffff4 && uVar1 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      __copy_from_user(&local_1c,param_3,0xc);
    }
    else {
      __memzero(&local_1c,0xc,uVar2);
    }
    uVar2 = local_18 >> 5;
    if (local_14 == 0) {
      *(undefined4 *)(&g_netdebug_mod_tabel + uVar2 * 4) = 0;
    }
    else {
      *(uint *)(&g_netdebug_mod_tabel + uVar2 * 4) =
           *(uint *)(&g_netdebug_mod_tabel + uVar2 * 4) | 1 << (local_18 & 0x1f);
    }
    return 0;
  case 0x102:
    local_18 = g_netdebug_outuni;
    break;
  case 0x103:
    uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    uVar1 = param_3 + 0xc;
    uVar2 = uVar1;
    if (param_3 < 0xfffffff4) {
      uVar2 = uVar1 - (uVar3 + 1);
    }
    if (param_3 < 0xfffffff4 && uVar1 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      __copy_from_user(&local_1c,param_3,0xc);
    }
    else {
      __memzero(&local_1c,0xc,uVar2);
    }
    g_netdebug_outuni = local_18;
    return 0;
  case 0x104:
    local_18 = g_netdebug_print;
    break;
  case 0x105:
    uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    uVar1 = param_3 + 0xc;
    uVar2 = uVar1;
    if (param_3 < 0xfffffff4) {
      uVar2 = uVar1 - (uVar3 + 1);
    }
    if (param_3 < 0xfffffff4 && uVar1 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      __copy_from_user(&local_1c,param_3,0xc);
    }
    else {
      __memzero(&local_1c,0xc,uVar2);
    }
    g_netdebug_print = local_18;
    return 0;
  default:
    printk("module-netdebug: invalid cmdid\n");
    return 0;
  }
  uVar2 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
  if (param_3 < 0xfffffff4 && param_3 + 0xc <= uVar2) {
    uVar2 = 0;
  }
  if (uVar2 == 0) {
    __copy_to_user(param_3,&local_1c,0xc);
  }
  return 0;
}


/* ============= FUNCTION: zx_pon_int @ 0001b128 ============= */

undefined4 zx_pon_int(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = *(uint *)(pon_base + 0x40040) & ~*(uint *)(pon_base + 0x40044);
  if (((uVar1 & 0x40) != 0) && (lp_isr != (code *)0x0)) {
    (*lp_isr)(ZX_INT_PON,*param_2,lp_isr,&lp_isr,param_4);
    param_2[4] = param_2[4] + 1;
  }
  if ((uVar1 & 0x10) != 0) {
    rog_onu_flag = 1;
  }
  return 1;
}


/* ============= FUNCTION: register_gmac_int @ 0001b1a4 ============= */

void register_gmac_int(undefined4 param_1,undefined4 param_2)

{
  gpon_isr = param_1;
  pon_int_info._0_4_ = param_2;
  pon_int_enable(1);
  return;
}


/* ============= FUNCTION: register_emac_int @ 0001b1bc ============= */

void register_emac_int(undefined4 param_1,undefined4 param_2)

{
  pon_int_info._0_4_ = param_2;
  epon_isr = param_1;
  pon_int_enable(0x100);
  return;
}


/* ============= FUNCTION: register_lp_int @ 0001b1d4 ============= */

void register_lp_int(undefined4 param_1,undefined4 param_2)

{
  lp_isr = param_1;
  pon_int_info._0_4_ = param_2;
  pon_int_enable(0x40);
  return;
}


/* ============= FUNCTION: pon_is_registered @ 0001b1ec ============= */

undefined4 pon_is_registered(void)

{
  if ((lan_up == 0) && (pon_registered == 0)) {
    pon_registered = 1;
  }
  return 1;
}


/* ============= FUNCTION: register_pon_int @ 0001b220 ============= */

int register_pon_int(void)

{
  int iVar1;
  
  iVar1 = request_threaded_irq(g_pon_irq,zx_pon_int,0,0x80,&_LC0,DAT_0001b280);
  if (iVar1 < 0) {
    printk("request pon irq failed\n");
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}


/* ============= FUNCTION: pon_reset @ 0001b284 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void pon_reset(uint param_1)

{
  int iVar1;
  
  *(uint *)(pon_base + 8) = *(uint *)(pon_base + 8) & ~param_1;
  iVar1 = 100;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *(uint *)(pon_base + 8) = *(uint *)(pon_base + 8) | param_1;
  return;
}


/* ============= FUNCTION: pon_int_enable @ 0001b2e4 ============= */

void pon_int_enable(uint param_1)

{
  *(uint *)(pon_base + 0x40044) = *(uint *)(pon_base + 0x40044) & ~param_1;
  return;
}


/* ============= FUNCTION: reserve_mem_info @ 0001b30c ============= */

void reserve_mem_info(void)

{
  undefined4 in_r3;
  
  printk("ZX_PA_BUF_BASE0=%x\n",pdt_mem_size + 0x40000000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_BUF_BASE0=%x\n",pdt_mem_size + -0x40000000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_ACL_BASE=%x\n",pdt_mem_size + 0x40020000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_ACL_BASE=%x\n",pdt_mem_size + -0x3ffe0000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_FLOW_BASE=%x\n",pdt_mem_size + 0x40420000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_FLOW_BASE=%x\n",pdt_mem_size + -0x3fbe0000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_BP_BUFFER_BASE=%x\n",pdt_mem_size + 0x40520000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x40520000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_TX_UP_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405e0000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_TX_DN_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405f0000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_BPPE_BASE=%x\n",pdt_mem_size + -0x40000000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_BP_BUF_BASE=%x\n",pdt_mem_size + -0x3fae0000 + ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fae0000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_TX_UP_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fa20000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("ZX_VA_TX_DN_DESC_BASE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fa10000 +
         ZX_RESERVE_MEM_SIZE * -0x100000);
  printk("BPPE_POOL_SIZE=%x\n",u32_BPPE_POOL_SIZE);
  printk("NORMAL_BP_BUFFER_SIZE=%x\n",u32_BP_SIZE * u32_BPPE_POOL_SIZE);
  printk("JUMBO_BP_SIZE=%x\n",u32_JUMBO_BP_SIZE);
  printk("JUMBO_BPPE_POOL_SIZE=%x\n",u32_JUMBO_BPPE_POOL_SIZE);
  printk("BP_BUFFER_SIZE=%x\n",
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE + u32_BP_SIZE * u32_BPPE_POOL_SIZE,
         u32_JUMBO_BPPE_POOL_SIZE,in_r3);
  return;
}


/* ============= FUNCTION: serdes_set_gen_en_open @ 0001b614 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void serdes_set_gen_en_open(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0xdfffffff;
  (*_request_threaded_irq)(0xa3d6f8);
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) | 0x20000000;
  return;
}


/* ============= FUNCTION: serdes_set_gen_en_disable @ 0001b664 ============= */

void serdes_set_gen_en_disable(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0xdfffffff;
  return;
}


/* ============= FUNCTION: serdes_set_check_en_open @ 0001b684 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void serdes_set_check_en_open(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0xbfffffff;
  (*_request_threaded_irq)(0xa3d6f8);
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) | 0x40000000;
  return;
}


/* ============= FUNCTION: serdes_set_check_en_disable @ 0001b6d4 ============= */

void serdes_set_check_en_disable(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0xbfffffff;
  return;
}


/* ============= FUNCTION: serdes_set_err_cnt_en_open @ 0001b6f4 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void serdes_set_err_cnt_en_open(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0x7fffffff;
  (*_request_threaded_irq)(0xa3d6f8);
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) | 0x80000000;
  return;
}


/* ============= FUNCTION: serdes_set_err_cnt_en_disable @ 0001b744 ============= */

void serdes_set_err_cnt_en_disable(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0x7fffffff;
  return;
}


/* ============= FUNCTION: serdes_get_err_cnt @ 0001b764 ============= */

uint serdes_get_err_cnt(void)

{
  return *(uint *)(pon_serdes_base + 0x60) >> 0x10 | *(int *)(pon_serdes_base + 100) << 0x10;
}


/* ============= FUNCTION: serdes_prbs_err_ok @ 0001b788 ============= */

uint serdes_prbs_err_ok(void)

{
  return (uint)(*(int *)(pon_serdes_base + 0x68) << 0x11) >> 0x1f;
}


/* ============= FUNCTION: serdes_err_cnt_reset @ 0001b7a0 ============= */

void serdes_err_cnt_reset(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0x7fffffff;
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) | 0x80000000;
  return;
}


/* ============= FUNCTION: serdes_mode_set @ 0001b7d4 ============= */

void serdes_mode_set(int param_1)

{
  if (param_1 == 1) {
    *pon_serdes_base = *pon_serdes_base & 0xffffff00 | 0xa5;
    pon_serdes_base[2] = pon_serdes_base[2] & 0xffffff00 | 0x20;
    pon_serdes_base[5] = pon_serdes_base[5] & 0xffff00ff | 0x5800;
    pon_serdes_base[8] = pon_serdes_base[8] & 0xffffff;
    pon_serdes_base[9] = pon_serdes_base[9] & 0xffffff00 | 3;
    pon_serdes_base[9] = pon_serdes_base[9] & 0xff00ffff | 0x570000;
    pon_serdes_base[9] = pon_serdes_base[9] & 0xffffff | 0x7000000;
    return;
  }
  if (param_1 != 3) {
    return;
  }
  *pon_serdes_base = *pon_serdes_base & 0xffffff00 | 0xa5;
  pon_serdes_base[2] = pon_serdes_base[2] & 0xffffff00 | 0x20;
  pon_serdes_base[3] = pon_serdes_base[3] & 0xffffff00 | 5;
  pon_serdes_base[5] = pon_serdes_base[5] & 0xffff00ff | 0x5800;
  pon_serdes_base[8] = pon_serdes_base[8] & 0xffffff;
  pon_serdes_base[9] = pon_serdes_base[9] & 0xffffff00 | 0x83;
  return;
}


/* ============= FUNCTION: serdes_set_tx_prbs_mode @ 0001b92c ============= */

undefined4 serdes_set_tx_prbs_mode(int param_1)

{
  serdes_set_gen_en_open();
  *pon_serdes_base = *pon_serdes_base & 0xfffffff8;
  pon_serdes_base[0x11] = pon_serdes_base[0x11] & 0xfe3fffff | 0x1000000;
  if (param_1 == 1) {
    pon_serdes_base[0x11] = pon_serdes_base[0x11] & 0xfffffcff | 0x200;
    printk("\nserdes_set_tx_prbs_prbs_mode to 23\n");
    return 0;
  }
  if (param_1 != 0) {
    if (param_1 == 2) {
      pon_serdes_base[0x11] = pon_serdes_base[0x11] | 0x300;
      printk("\nserdes_set_tx_prbs_prbs_mode to 31\n");
    }
    return 0;
  }
  pon_serdes_base[0x11] = pon_serdes_base[0x11] & 0xfffffcff;
  printk("\nserdes_set_tx_prbs_prbs_mode to 7\n");
  return 0;
}


/* ============= FUNCTION: serdes_set_rx_prbs_mode @ 0001b9fc ============= */

undefined4 serdes_set_rx_prbs_mode(int param_1)

{
  *(uint *)(pon_serdes_base + 0x14) = *(uint *)(pon_serdes_base + 0x14) & 0xffff8fff;
  *(uint *)(pon_serdes_base + 0x14) = *(uint *)(pon_serdes_base + 0x14) | 0x10000000;
  if (param_1 == 1) {
    *(uint *)(pon_serdes_base + 0x44) = *(uint *)(pon_serdes_base + 0x44) & 0xfffff3ff | 0x800;
    printk("\nserdes_set_tx_prbs_prbs_mode to 23\n");
    return 0;
  }
  if (param_1 != 0) {
    if (param_1 == 2) {
      *(uint *)(pon_serdes_base + 0x44) = *(uint *)(pon_serdes_base + 0x44) | 0xc00;
      printk("\nserdes_set_tx_prbs_prbs_mode to 31\n");
    }
    return 0;
  }
  *(uint *)(pon_serdes_base + 0x44) = *(uint *)(pon_serdes_base + 0x44) & 0xfffff3ff;
  printk("\nserdes_set_tx_prbs_prbs_mode to 7\n");
  return 0;
}


/* ============= FUNCTION: serdes_rx_ready @ 0001bac0 ============= */

undefined4 serdes_rx_ready(void)

{
  if ((*(uint *)(pon_serdes_base + 0x68) & 0x10) != 0) {
    printk("serdes_rx_ready  ok  \n");
    return 1;
  }
  printk("serdes_rx_ready  failed  \n");
  return 0;
}


/* ============= FUNCTION: serdes_set_tx_eq @ 0001bb04 ============= */

undefined4 serdes_set_tx_eq(int param_1)

{
  if (param_1 != 1) {
    if (param_1 == 2) {
      *pon_serdes_base = *pon_serdes_base & 0xfff1ffff | 0x80000;
      *pon_serdes_base = *pon_serdes_base | 0x80000000;
      pon_serdes_base[1] = pon_serdes_base[1] & 0xfffffff0 | 10;
      pon_serdes_base[1] = pon_serdes_base[1] & 0xffff87ff | 0x3000;
      printk("\nset tx 6db pre and post success \n");
    }
    return 0;
  }
  *pon_serdes_base = *pon_serdes_base & 0xfff1ffff | 0x80000;
  *pon_serdes_base = *pon_serdes_base | 0x80000000;
  pon_serdes_base[1] = pon_serdes_base[1] & 0xfffffff0 | 10;
  pon_serdes_base[1] = pon_serdes_base[1] & 0xffff87ff | 0x1800;
  printk("\nset tx 3db pre and post success \n");
  return 0;
}


/* ============= FUNCTION: serdes_set_rx_eq @ 0001bc08 ============= */

undefined4 serdes_set_rx_eq(int param_1)

{
  if (param_1 != 1) {
    if (param_1 == 2) {
      *(uint *)(pon_serdes_base + 8) = *(uint *)(pon_serdes_base + 8) & 0xffffff8f;
      *(uint *)(pon_serdes_base + 8) = *(uint *)(pon_serdes_base + 8) & 0xffff8fff | 0x2000;
      printk("\nset rx 6db pre and post success \n");
    }
    return 0;
  }
  *(uint *)(pon_serdes_base + 8) = *(uint *)(pon_serdes_base + 8) & 0xffffff8f;
  *(uint *)(pon_serdes_base + 8) = *(uint *)(pon_serdes_base + 8) & 0xffff8fff;
  printk("\nset rx 3db pre and post success \n");
  return 0;
}


/* ============= FUNCTION: apb_write @ 0001bca8 ============= */

void apb_write(int param_1,undefined4 param_2)

{
  *(undefined4 *)(pon_serdes_base + param_1) = param_2;
  return;
}


/* ============= FUNCTION: apb_read @ 0001bcc0 ============= */

undefined4 apb_read(int param_1)

{
  return *(undefined4 *)(pon_serdes_base + param_1);
}


/* ============= FUNCTION: apb_bit_write @ 0001bcd8 ============= */

void apb_bit_write(int param_1,int param_2,uint param_3,uint param_4)

{
  *(uint *)(pon_serdes_base + param_1) =
       *(uint *)(pon_serdes_base + param_1) & ~(~(-1 << (param_3 & 0xff)) << (param_4 & 0xff)) |
       param_2 << (param_4 & 0xff);
  return;
}


/* ============= FUNCTION: pll_cfg_integer @ 0001bd10 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void pll_cfg_integer(uint *param_1,int param_2,uint param_3,int param_4,uint param_5)

{
  int iVar1;
  
  if (param_3 < 0x10) {
    printk("feed back divide value is %d < 16 \n",param_3);
  }
  *param_1 = *param_1 | 0x80000000;
  *param_1 = *param_1 | 0x8000000;
  *param_1 = *param_1 & 0xfeffffff;
  *param_1 = *param_1 & 0xff03ffff | param_2 << 0x12;
  *param_1 = *param_1 & 0xfffc003f | param_3 << 6;
  if (param_4 != 0) {
    *param_1 = *param_1 & 0xffffffc7 | param_4 << 3;
  }
  if (param_5 != 0) {
    *param_1 = *param_1 & 0xfffffff8 | param_5;
  }
  param_1[1] = param_1[1] & 0xf7ffffff;
  param_1[1] = param_1[1] | 0x4000000;
  param_1[1] = param_1[1] & 0xfdffffff;
  param_1[1] = param_1[1] & 0xfeffffff;
  param_1[1] = param_1[1] & 0xff000000;
  iVar1 = 100;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *param_1 = *param_1 & 0x7fffffff;
  return;
}


/* ============= FUNCTION: pll_cfg_fractional @ 0001beb4 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void pll_cfg_fractional(uint *param_1,int param_2,uint param_3,uint param_4,int param_5,uint param_6
                       )

{
  int iVar1;
  
  printk("enter pll_cfg_fractional\n");
  if (param_3 < 0x14) {
    printk("feed back divide value is %d < 20 \n",param_3);
  }
  *param_1 = *param_1 | 0x80000000;
  *param_1 = *param_1 & 0xf7ffffff;
  *param_1 = *param_1 & 0xfeffffff;
  *param_1 = *param_1 & 0xff03ffff | param_2 << 0x12;
  *param_1 = *param_1 & 0xfffc003f | param_3 << 6;
  if (param_5 != 0) {
    *param_1 = *param_1 & 0xffffffc7 | param_5 << 3;
  }
  if (param_6 != 0) {
    *param_1 = *param_1 & 0xfffffff8 | param_6;
  }
  param_1[1] = param_1[1] & 0xf7ffffff;
  param_1[1] = param_1[1] | 0x4000000;
  param_1[1] = param_1[1] & 0xfdffffff;
  param_1[1] = param_1[1] & 0xfeffffff;
  param_1[1] = param_1[1] & 0xff000000 | param_4;
  iVar1 = 100;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *param_1 = *param_1 & 0x7fffffff;
  return;
}


/* ============= FUNCTION: pll_ssc_cfg @ 0001c06c ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void pll_ssc_cfg(uint *param_1,int param_2,int param_3,uint param_4,int param_5,uint param_6)

{
  int iVar1;
  
  *param_1 = *param_1 | 0x80000000;
  param_1[2] = param_1[2] | 0x800;
  param_1[2] = param_1[2] & 0xfffffffd;
  *param_1 = *param_1 & 0xffffffc7 | param_5 << 3;
  *param_1 = *param_1 & 0xfffffff8 | param_6;
  *param_1 = *param_1 & 0xff03ffff | param_2 << 0x12;
  *param_1 = *param_1 & 0xfffc003f | param_3 << 6;
  param_1[1] = param_1[1] & 0xff000000 | param_4;
  param_1[2] = param_1[2] & 0xffffff83 | 0x10;
  param_1[2] = param_1[2] | 1;
  *param_1 = *param_1 & 0xf7ffffff;
  param_1[1] = param_1[1] & 0xf7ffffff;
  iVar1 = 10;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *param_1 = *param_1 & 0x7fffffff;
  do {
  } while ((param_1[1] & 0x10000000) == 0);
  printk("pll_ssc_cfg success!\n");
  return;
}


/* ============= FUNCTION: ref_clk_set @ 0001c200 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ref_clk_set(uint param_1)

{
  int iVar1;
  
  printk("enter ref_clk_set.. mode = %d .\n",param_1);
  *(uint *)(top_crm_base + 0x50) = *(uint *)(top_crm_base + 0x50) & 0x7fffffff;
  if ((param_1 & 0xfffffffd) == 1) {
    pll_cfg_integer(top_crm_base + 0x50,1,0x32,4,2);
  }
  else {
    pll_cfg_fractional(top_crm_base + 0x50,1,0x5d,0x4fdf3b,5,3);
  }
  iVar1 = 0x32;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("ref_clk_set success!\n");
  return;
}


/* ============= FUNCTION: reg_def_set @ 0001c2c4 ============= */

void reg_def_set(void)

{
  *pon_serdes_base = 0x800180a7;
  pon_serdes_base[1] = 0x8f;
  pon_serdes_base[2] = 0x540;
  pon_serdes_base[3] = 4;
  pon_serdes_base[4] = 0;
  pon_serdes_base[5] = 0x18a6400;
  pon_serdes_base[6] = 0xb50140;
  pon_serdes_base[7] = 0x1216000;
  pon_serdes_base[8] = 0x40000000;
  pon_serdes_base[9] = 0xb510007;
  pon_serdes_base[10] = 0;
  pon_serdes_base[0xb] = 0;
  pon_serdes_base[0xc] = 0xa02e2400;
  pon_serdes_base[0xd] = 0xc0593d44;
  pon_serdes_base[0xe] = 0xf0f;
  pon_serdes_base[0xf] = 0;
  pon_serdes_base[0x10] = 0x3c0000;
  pon_serdes_base[0x11] = 0xea00a013;
  pon_serdes_base[0x12] = 0x101038ca;
  pon_serdes_base[0x13] = 0x5a008;
  pon_serdes_base[0x14] = 0x33333333;
  pon_serdes_base[0x15] = 0x33333333;
  pon_serdes_base[0x16] = 0x3e23333;
  pon_serdes_base[0x17] = 0x40244;
  return;
}


/* ============= FUNCTION: zx_pon_clk_reset_init @ 0001c41c ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 zx_pon_clk_reset_init(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  ref_clk_set();
  *(uint *)(top_crm_base + 8) = *(uint *)(top_crm_base + 8) & 0xffffffdf;
  *(uint *)(top_crm_base + 8) = *(uint *)(top_crm_base + 8) & 0xffffffef;
  iVar3 = 10;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *(uint *)(top_crm_base + 8) = *(uint *)(top_crm_base + 8) | 0x20;
  iVar3 = 10;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  reg_def_set();
  serdes_mode_set(param_1,0,0);
  *(uint *)(top_crm_base + 8) = *(uint *)(top_crm_base + 8) | 0x10;
  do {
  } while ((*(uint *)(pon_serdes_base + 0x68) & 0x10) == 0);
  iVar3 = 0x14;
  printk("rxpll_ready\n");
  while ((*_request_threaded_irq)(0x66665b0), (*(uint *)(pon_serdes_base + 0x70) & 0x1000000) == 0)
  {
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      printk("err:pll is not ready for banding\n");
      return 0xffffffff;
    }
  }
  iVar1 = *(int *)(pon_serdes_base + 0x70);
  iVar3 = temp_ctrl_read();
  uVar2 = (uint)(iVar1 << 8) >> 0x1a;
  printk("serdes band cpu_temper:%d coarse:0x%x\n",iVar3,uVar2);
  if (iVar3 < -6) {
    uVar2 = uVar2 + 1;
LAB_0001c574:
    if (0x3f < uVar2) {
      uVar2 = 0x3f0000;
      goto LAB_0001c584;
    }
  }
  else if (0xf < iVar3 + 6U) {
    if (iVar3 - 10U < 0x31) {
      uVar2 = uVar2 - 1;
    }
    else if (iVar3 - 0x3bU < 0x21) {
      uVar2 = uVar2 - 2;
    }
    else {
      uVar2 = uVar2 - 3;
    }
    goto LAB_0001c574;
  }
  uVar2 = uVar2 << 0x10;
LAB_0001c584:
  *(uint *)(pon_serdes_base + 0x44) = *(uint *)(pon_serdes_base + 0x44) & 0xffc0ffff | uVar2;
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) | 0x4000000;
  printk("band calc fin\n");
  *(uint *)(sys_ctrl_base + 0x10) = *(uint *)(sys_ctrl_base + 0x10) & 0xfffff7ff;
  *(uint *)(top_crm_base + 0xc) = *(uint *)(top_crm_base + 0xc) | 0x1e0;
  return 0;
}


/* ============= FUNCTION: zx_pon_clk_reset @ 0001c624 ============= */

void zx_pon_clk_reset(void)

{
  *(uint *)(top_crm_base + 0xc) = *(uint *)(top_crm_base + 0xc) | 0x1e0;
  return;
}


/* ============= FUNCTION: dump_task_fd @ 0001c644 ============= */

void dump_task_fd(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  undefined1 auStack_118 [256];
  
  puVar6 = *(uint **)(*(int *)(param_1 + 0x310) + 4);
  for (iVar7 = 0; uVar5 = iVar7 << 3, uVar5 < *puVar6; iVar7 = iVar7 + 4) {
    iVar4 = iVar7 << 5;
    uVar3 = *(uint *)(puVar6[3] + iVar7);
    while (uVar3 != 0) {
      uVar1 = uVar3 & 1;
      uVar3 = uVar3 >> 1;
      if (uVar1 != 0) {
        if ((*(int *)(puVar6[1] + iVar4) != 0) &&
           (iVar2 = d_path(*(int *)(puVar6[1] + iVar4) + 8,auStack_118,0x100), iVar2 != 0)) {
          printk("fd %d : %s\n",uVar5);
        }
      }
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 4;
    }
  }
  return;
}


/* ============= FUNCTION: my_dump_vma @ 0001c6dc ============= */

void my_dump_vma(int param_1)

{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  char acStack_120 [260];
  
  iVar9 = *(int *)(param_1 + 0x18c);
  iVar8 = *(int *)(param_1 + 4);
  iVar2 = rb_last(iVar9 + 4);
  uVar4 = *(uint *)(iVar8 + 0x1fe4);
  if (uVar4 < *(uint *)(iVar2 + -0x10)) {
    bVar1 = false;
  }
  else if (uVar4 < *(uint *)(iVar2 + -0xc)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  iVar2 = rb_first(iVar9 + 4);
  do {
    if (iVar2 == 0) {
      return;
    }
    uVar4 = *(uint *)(iVar2 + 0x18);
    iVar10 = *(int *)(iVar2 + 0x40);
    if ((uVar4 & 1) == 0) {
      uVar5 = 0x2d;
    }
    else {
      uVar5 = 0x72;
    }
    if ((uVar4 & 2) == 0) {
      uVar12 = 0x2d;
    }
    else {
      uVar12 = 0x77;
    }
    if ((uVar4 & 4) == 0) {
      uVar13 = 0x2d;
    }
    else {
      uVar13 = 0x78;
    }
    if ((uVar4 & 0x80) == 0) {
      uVar11 = 0x70;
    }
    else {
      uVar11 = 0x73;
    }
    printk("vma : %.8lx-%.8lx %c%c%c%c ",*(undefined4 *)(iVar2 + -0x10),
           *(undefined4 *)(iVar2 + -0xc),uVar5,uVar12,uVar13,uVar11);
    if (iVar10 == 0) {
      uVar4 = *(uint *)(iVar2 + -0x10);
      if ((*(uint *)(iVar9 + 0x94) < uVar4) || (*(uint *)(iVar2 + -0xc) < *(uint *)(iVar9 + 0x90)))
      {
        uVar6 = *(uint *)(iVar9 + 0x98);
        if ((uVar6 < uVar4) || (*(uint *)(iVar2 + -0xc) < uVar6)) {
          if (((uVar6 ^ uVar4) & 0xf0000000) != 0) goto LAB_0001c8e8;
          uVar6 = *(uint *)(iVar8 + 0x1fe4);
          if ((uVar6 < uVar4) || (*(uint *)(iVar2 + -0xc) <= uVar6)) {
            iVar10 = param_1;
            if (!bVar1) {
              iVar10 = *(int *)(param_1 + 0x200);
            }
            for (puVar7 = *(undefined4 **)(iVar10 + 0x208); puVar7 != (undefined4 *)(iVar10 + 0x208)
                ; puVar7 = (undefined4 *)*puVar7) {
              if ((uVar4 <= *(uint *)(puVar7[-0x83] + 0x1fe4)) &&
                 (*(uint *)(puVar7[-0x83] + 0x1fe4) < *(uint *)(iVar2 + -0xc))) {
                if ((int)puVar7[-6] < 0) {
                  pcVar3 = "[stack:child]";
                }
                else {
                  sprintf(acStack_120,"[stack:%d]");
                  pcVar3 = acStack_120;
                }
                goto LAB_0001c8f0;
              }
            }
            pcVar3 = "[stack:child]";
          }
          else {
            sprintf(acStack_120,"[stack:%d]",*(undefined4 *)(param_1 + 0x1f8));
            pcVar3 = acStack_120;
          }
        }
        else {
          if (bVar1) {
            uVar5 = *(undefined4 *)(param_1 + 0x1f8);
          }
          else {
            uVar5 = *(undefined4 *)(*(int *)(param_1 + 0x200) + 0x1f8);
          }
          sprintf(acStack_120,"[stack:parent %d]",uVar5);
          pcVar3 = acStack_120;
        }
      }
      else {
        pcVar3 = "[heap]";
      }
    }
    else {
      pcVar3 = (char *)d_path(iVar10 + 8,acStack_120,0x100);
      if (pcVar3 == (char *)0x0) {
LAB_0001c8e8:
        pcVar3 = "";
      }
    }
LAB_0001c8f0:
    printk(&_LC7,pcVar3);
    iVar2 = rb_next(iVar2);
  } while( true );
}


/* ============= FUNCTION: get_usyms_lib @ 0001c924 ============= */

int get_usyms_lib(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 auStack_110 [260];
  
  iVar1 = rb_first(*(int *)(param_1 + 0x18c) + 4);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if ((*(uint *)(iVar1 + -0x10) <= param_2) && (param_2 < *(uint *)(iVar1 + -0xc))) break;
    iVar1 = rb_next(iVar1);
  }
  uVar3 = ((*(uint *)(iVar1 + 0x18) ^ 4) << 0x1d) >> 0x1f;
  if (*(int *)(iVar1 + 0x40) == 0) {
    uVar3 = 1;
  }
  if (uVar3 != 0) {
    return 0;
  }
  iVar2 = d_path(*(int *)(iVar1 + 0x40) + 8,auStack_110,0x100);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = usyms_lookup_addr(iVar2,param_2 - *(int *)(iVar1 + -0x10));
  if (iVar2 != 0) {
    *(int *)(iVar2 + 0xc) = *(int *)(iVar2 + 0xc) + *(int *)(iVar1 + -0x10);
    return iVar2;
  }
  return 0;
}


/* ============= FUNCTION: pp_skb_recycle @ 0001c9e8 ============= */

undefined4 pp_skb_recycle(void)

{
  return 0xffffffff;
}


/* ============= FUNCTION: pon_tm_net_poll @ 0001c9f0 ============= */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

int pon_tm_net_poll(int param_1,uint param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  void *pvVar12;
  int iVar13;
  bool bVar14;
  uint local_58;
  uint local_4c;
  uint local_44;
  uint local_40;
  int local_3c;
  int local_30;
  
  *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + 1;
  local_40 = param_2;
  if ((*(uint *)(param_1 + -100) & 3) == 0) {
    local_3c = 0;
LAB_0001d0d4:
    if (0 < (int)local_40) {
      napi_complete_done(param_1,0);
      disableIRQinterrupts();
      *(uint *)(tm_base + 0x104) = *(uint *)(tm_base + 0x104) & 0xfffffffc;
    }
    return local_3c;
  }
  local_30 = 4;
  *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 0x7c) + 1;
  local_3c = 0;
  local_44 = 0xff;
LAB_0001ca58:
  bVar14 = false;
  local_58 = 7;
  iVar13 = DAT_0001d324;
  do {
    if (((int)local_44 >> (local_58 & 0xff) & 1U) == 0) {
joined_r0x0001cd64:
      if (local_58 == 0) break;
    }
    else {
      uVar6 = *(uint *)(tm_base + (local_58 + 0x4040) * 4);
      uVar7 = uVar6;
      if (0 < (int)uVar6) {
        uVar7 = local_40;
      }
      if (0 < (int)uVar7) {
        iVar10 = 0x400 - *(int *)(iVar13 + 0x7c);
        iVar9 = (int)local_40 >> 1;
        if ((int)uVar6 >> 0x10 < (int)local_40 >> 1) {
          iVar9 = (int)uVar6 >> 0x10;
        }
        iVar2 = *(int *)(iVar13 + 0x78) + *(int *)(iVar13 + 0x7c) * 0x10;
        if (iVar10 < iVar9) {
          net_invalid_cache(iVar2,iVar10 * 0x10);
          net_invalid_cache(*(undefined4 *)(iVar13 + 0x78),(iVar9 - iVar10) * 0x10);
        }
        else {
          net_invalid_cache(iVar2,iVar9 << 4);
        }
        iVar10 = (int)pon_tm_netdev;
        if (iVar9 != 0) {
          iVar2 = 0;
          local_4c = 0;
          do {
            while( true ) {
              iVar4 = *(uint *)(iVar13 + 0x78) + *(int *)(iVar13 + 0x7c) * 0x10;
              HintPreloadData(iVar4);
              uVar7 = *(int *)(iVar13 + 0x7c) + 1;
              *(uint *)(iVar13 + 0x7c) = uVar7;
              if (0x3ff < uVar7) {
                *(undefined4 *)(iVar13 + 0x7c) = 0;
              }
              uVar8 = (uint)(*(byte *)(iVar4 + 7) >> 1) | (uint)*(byte *)(iVar4 + 8) << 7;
              bVar14 = (*(byte *)(iVar4 + 6) & 1) != 0;
              uVar7 = *(uint *)(iVar13 + 0x78);
              if (bVar14) {
                uVar7 = local_4c;
              }
              if (bVar14) {
                uVar7 = uVar7 + 1;
              }
              if (bVar14) {
                local_4c = uVar7;
              }
              if (*(uint *)((int)&bp_max_number + (*(byte *)(iVar4 + 9) & 1) * 4) <= uVar8) break;
              bmu_status._20_4_ = bmu_status._20_4_ + 1;
              if ((*(byte *)(iVar4 + 9) & 1) == 0) {
                pvVar12 = (void *)(u32_BP_SIZE * uVar8 +
                                  pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000);
              }
              else {
                pvVar12 = (void *)(u32_JUMBO_BP_SIZE * uVar8 +
                                  u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fadfff0 +
                                  ZX_RESERVE_MEM_SIZE * -0x100000);
              }
              uVar7 = (uint)(*(ushort *)(iVar4 + 0xc) >> 2);
              net_invalid_cache(pvVar12,uVar7);
              if (0 < pon_tm_net_debug) {
                dump_desc(iVar4);
                printk("recv gem %d,addr %x\n",*(ushort *)(iVar4 + 4) & 0xfff,pvVar12);
                dump_net_data(pvVar12,uVar7);
                pon_tm_net_debug = pon_tm_net_debug + -1;
              }
              if ((*(byte *)(iVar4 + 6) & 4) == 0) {
                iVar3 = __netdev_alloc_skb(iVar10,uVar7 + 0x12,0x20);
                if (iVar3 != 0) {
                  *(uint *)(iVar10 + 0x4d8) = *(int *)(iVar10 + 0x4d8) + uVar7;
                  *(int *)(iVar10 + 0x4d0) = *(int *)(iVar10 + 0x4d0) + 1;
                  pvVar5 = (void *)(*(int *)(iVar3 + 0xcc) + 2);
                  *(void **)(iVar3 + 0xcc) = pvVar5;
                  *(int *)(iVar3 + 0xc0) = *(int *)(iVar3 + 0xc0) + 2;
                  memcpy(pvVar5,pvVar12,uVar7);
                  skb_put(iVar3,uVar7);
                  *(int *)(iVar3 + 0x18) = iVar10;
                  if ((*(byte *)(iVar4 + 9) & 1) != 0) {
                    *(ushort *)(iVar3 + 0xbc) = *(ushort *)(iVar3 + 0xbc) | 2;
                  }
                  if (switch_skb_recv == (code *)0x0) {
                    uVar1 = eth_type_trans(iVar3,iVar10);
                    *(undefined2 *)(iVar3 + 0xa4) = uVar1;
                    netif_receive_skb_sk(*(undefined4 *)(iVar3 + 0x14),iVar3);
                  }
                  else {
                    *(ushort *)(iVar3 + 0xbc) = *(ushort *)(iVar3 + 0xbc) | 8;
                    if ((*(byte *)(iVar4 + 0xe) & 2) == 0) {
                      *(byte *)(iVar3 + 0xb4) = (*(byte *)(iVar4 + 6) >> 3) - 1;
                    }
                    (*switch_skb_recv)(iVar3);
                  }
                  goto LAB_0001cc48;
                }
                iVar4 = pp_bmu_free_bp(uVar8,0,*(byte *)(iVar4 + 9) & 1);
                if (iVar4 < 0) {
                  printk("failed to rls bp\n");
                }
                *(int *)(iVar10 + 0x4e8) = *(int *)(iVar10 + 0x4e8) + 1;
              }
              else {
LAB_0001cc48:
                iVar4 = pp_bmu_free_bp(uVar8,0,*(byte *)(iVar4 + 9) & 1);
                if (iVar4 < 0) {
                  printk("failed to rls bp\n");
                }
              }
              iVar2 = iVar2 + 1;
              if (iVar2 == iVar9) goto LAB_0001cdb4;
            }
            *(int *)(iVar10 + 0x4e0) = *(int *)(iVar10 + 0x4e0) + 1;
            iVar2 = iVar2 + 1;
            printk("rxq %d,invalid bp %u\n",local_58,uVar8);
            dump_desc(iVar4);
          } while (iVar2 != iVar9);
LAB_0001cdb4:
          if (iVar9 - local_4c != 0) {
            soft_release_rx_desc(1,local_58 & 0xff,0,iVar9 - local_4c & 0xffff);
          }
          if (local_4c != 0) {
            soft_release_rx_desc(1,local_58 & 0xff,1,local_4c & 0xffff);
          }
        }
        iVar2 = 0x400 - *(int *)(iVar13 + 0x3c);
        iVar10 = *(int *)(iVar13 + 0x38) + *(int *)(iVar13 + 0x3c) * 0x10;
        uVar7 = (int)(local_40 - iVar9) / 2;
        if ((int)(uVar6 & 0xffff) <= (int)uVar7) {
          uVar7 = uVar6 & 0xffff;
        }
        if (iVar2 < (int)uVar7) {
          net_invalid_cache(iVar10,iVar2 * 0x10);
          net_invalid_cache(*(undefined4 *)(iVar13 + 0x38),(uVar7 - iVar2) * 0x10);
          if ((int)uVar7 < 1) goto LAB_0001d16c;
LAB_0001ce24:
          iVar10 = pon_tm_netdev._4_4_;
          local_4c = 0;
          uVar6 = 0;
          do {
            iVar2 = *(uint *)(iVar13 + 0x38) + *(int *)(iVar13 + 0x3c) * 0x10;
            HintPreloadData(iVar2);
            uVar8 = *(int *)(iVar13 + 0x3c) + 1;
            *(uint *)(iVar13 + 0x3c) = uVar8;
            if (0x3ff < uVar8) {
              *(undefined4 *)(iVar13 + 0x3c) = 0;
            }
            uVar11 = (uint)(*(byte *)(iVar2 + 7) >> 1) | (uint)*(byte *)(iVar2 + 8) << 7;
            bVar14 = (*(byte *)(iVar2 + 6) & 1) != 0;
            uVar8 = *(uint *)(iVar13 + 0x38);
            if (bVar14) {
              uVar8 = local_4c;
            }
            if (bVar14) {
              uVar8 = uVar8 + 1;
            }
            if (bVar14) {
              local_4c = uVar8;
            }
            if (uVar11 < *(uint *)((int)&bp_max_number + (*(byte *)(iVar2 + 9) & 1) * 4)) {
              bmu_status._20_4_ = bmu_status._20_4_ + 1;
              if ((*(byte *)(iVar2 + 9) & 1) == 0) {
                pvVar12 = (void *)(u32_BP_SIZE * uVar11 +
                                  pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000);
              }
              else {
                pvVar12 = (void *)(u32_JUMBO_BP_SIZE * uVar11 +
                                  u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fadfff0 +
                                  ZX_RESERVE_MEM_SIZE * -0x100000);
              }
              uVar8 = (uint)(*(ushort *)(iVar2 + 0xc) >> 2);
              net_invalid_cache(pvVar12,uVar8);
              if (0 < pon_tm_net_debug) {
                dump_desc(iVar2);
                printk("recv gem %d,addr %x\n",*(ushort *)(iVar2 + 4) & 0xfff,pvVar12);
                dump_net_data(pvVar12,uVar8);
                pon_tm_net_debug = pon_tm_net_debug + -1;
              }
              if ((*(byte *)(iVar2 + 6) & 4) == 0) {
                iVar4 = __netdev_alloc_skb(iVar10,uVar8 + 0x12,0x20);
                if (iVar4 == 0) {
                  iVar2 = pp_bmu_free_bp(uVar11,0,*(byte *)(iVar2 + 9) & 1);
                  if (iVar2 < 0) {
                    printk("failed to rls bp\n");
                  }
                  *(int *)(iVar10 + 0x4e8) = *(int *)(iVar10 + 0x4e8) + 1;
                  goto LAB_0001cf8c;
                }
                *(uint *)(iVar10 + 0x4d8) = *(int *)(iVar10 + 0x4d8) + uVar8;
                *(int *)(iVar10 + 0x4d0) = *(int *)(iVar10 + 0x4d0) + 1;
                pvVar5 = (void *)(*(int *)(iVar4 + 0xcc) + 2);
                *(void **)(iVar4 + 0xcc) = pvVar5;
                *(int *)(iVar4 + 0xc0) = *(int *)(iVar4 + 0xc0) + 2;
                memcpy(pvVar5,pvVar12,uVar8);
                skb_put(iVar4,uVar8);
                *(int *)(iVar4 + 0x18) = iVar10;
                if ((*(byte *)(iVar2 + 9) & 1) != 0) {
                  *(ushort *)(iVar4 + 0xbc) = *(ushort *)(iVar4 + 0xbc) | 2;
                }
                if (switch_skb_recv == (code *)0x0) {
                  uVar1 = eth_type_trans(iVar4,iVar10);
                  *(undefined2 *)(iVar4 + 0xa4) = uVar1;
                  netif_receive_skb_sk(*(undefined4 *)(iVar4 + 0x14),iVar4);
                }
                else {
                  *(ushort *)(iVar4 + 0xbc) = *(ushort *)(iVar4 + 0xbc) | 8;
                  if ((*(byte *)(iVar2 + 0xe) & 2) == 0) {
                    *(byte *)(iVar4 + 0xb4) = (*(byte *)(iVar2 + 6) >> 3) - 1;
                  }
                  (*switch_skb_recv)(iVar4);
                }
              }
              iVar2 = pp_bmu_free_bp(uVar11,0,*(byte *)(iVar2 + 9) & 1);
              if (iVar2 < 0) {
                printk("failed to rls bp\n");
              }
            }
            else {
              *(int *)(iVar10 + 0x4e0) = *(int *)(iVar10 + 0x4e0) + 1;
              printk("rxq %d,invalid bp %u\n",local_58,uVar11);
              dump_desc(iVar2);
            }
LAB_0001cf8c:
            uVar6 = uVar6 + 1;
          } while (uVar6 != uVar7);
          uVar6 = uVar7 - local_4c;
          if (uVar7 - local_4c != 0) {
LAB_0001d178:
            soft_release_rx_desc(0,local_58 & 0xff,0,uVar6 & 0xffff);
          }
          if (local_4c != 0) {
            soft_release_rx_desc(0,local_58 & 0xff,1,local_4c & 0xffff);
          }
        }
        else {
          net_invalid_cache(iVar10,uVar7 << 4);
          if (0 < (int)uVar7) goto LAB_0001ce24;
LAB_0001d16c:
          if (uVar7 != 0) {
            local_4c = 0;
            uVar6 = uVar7;
            goto LAB_0001d178;
          }
        }
        bVar14 = true;
        local_40 = (local_40 - iVar9) - uVar7;
        local_3c = local_3c + uVar7;
        goto joined_r0x0001cd64;
      }
      if (local_58 != 7) {
        local_44 = local_44 & ~(1 << (local_58 & 0xff));
        goto joined_r0x0001cd64;
      }
    }
    iVar13 = iVar13 + -8;
    local_58 = local_58 - 1;
  } while( true );
  if ((!bVar14) || (local_30 = local_30 + -1, local_30 == 0)) goto LAB_0001d0d4;
  goto LAB_0001ca58;
}


/* ============= FUNCTION: netdebug_module_init @ 0001d328 ============= */

undefined4 netdebug_module_init(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = __register_chrdev(99,0,0x100,"netdebug_dev",&netdebug_module_fops);
  if (iVar1 < 0) {
    printk("module-netdebug: register_chrdev failed\n");
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


/* ============= FUNCTION: init_module @ 0001d378 ============= */

int init_module(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  printk("pon init\n");
  bp_max_number._0_4_ = u32_BPPE_POOL_SIZE;
  bp_max_number._4_4_ = u32_JUMBO_BPPE_POOL_SIZE;
  reserve_mem_info();
  g_pon_work_mode = zte_get_pon_mode();
  if (g_pon_work_mode == 0x10) {
    lan_up = 1;
  }
  printk("lan_up=%d, lan_up_port=%d\n",lan_up,lan_up_port);
  uVar6 = u32_BP_SIZE * u32_BPPE_POOL_SIZE;
  uVar1 = u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE + uVar6;
  if (uVar1 <= uVar6 && uVar6 - uVar1 != 0) {
    printk("bmu config error!");
  }
  if ((uint)(ZX_RESERVE_MEM_SIZE * 0x100000) <
      u32_BP_SIZE * u32_BPPE_POOL_SIZE + u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE + 0x600000U) {
    printk("error:bmu no enough reserved mem! bmutotal_size=0x%0x reserve_mem=0x%0x\n");
  }
  iVar2 = of_find_matching_node_and_match(0,&zx_pon_match,0);
  iVar5 = DAT_0001d8dc;
  do {
    if (iVar2 == 0) {
      pon_reset(0xffffffff);
      msleep(10);
      *(undefined4 *)(pon_base + 0x40018) = 2;
      zx_pon_clk_reset_init(1);
      iVar5 = register_pon_int();
      if (-1 < iVar5) {
        *(undefined4 *)(pon_base + 0x40044) = 0xffffff7f;
        *(undefined4 *)(pon_base + 0x4001c) = 0xf;
        msleep(1);
        tm_pon_tm_init();
        netdebug_module_init();
        tm_pon_pp_init();
        tm_pon_npp_init();
        iVar5 = 0;
        if (lan_up != 0) {
          *(uint *)("mac learn:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n" + pp_base + 0x2c)
               = *(uint *)("mac learn:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n" +
                          pp_base + 0x2c) | 1 << (lan_up_port + 0x19U & 0xff);
          zx_pon_clk_reset();
          iVar5 = 0;
        }
      }
      return iVar5;
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-pon");
    if (iVar3 != 0) {
      pon_base = of_iomap(iVar2,0);
      top_crm_base = of_iomap(iVar2,1);
      sys_ctrl_base = of_iomap(iVar2,2);
      pin_mux_base = of_iomap(iVar2,3);
      pon_serdes_base = of_iomap(iVar2,4);
      if (pon_base == 0) {
        printk(&_LC25);
        goto LAB_0001d808;
      }
      g_pon_irq = irq_of_parse_and_map(iVar2,0);
      if (g_pon_irq < 1) {
        printk("%s: failed to get pon irq\n",DAT_0001d8e0);
        goto LAB_0001d808;
      }
      printk("g_pon_irq=%d,%x,%x,%x,%x,%x\n",g_pon_irq,pon_base,top_crm_base,sys_ctrl_base,
             pin_mux_base,pon_serdes_base);
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-gephy");
    if (iVar3 != 0) {
      iVar3 = 0;
      do {
        iVar4 = irq_of_parse_and_map(iVar2,iVar3);
        *(int *)(iVar5 + iVar3 * 4) = iVar4;
        iVar3 = iVar3 + 1;
        if (iVar4 < 0) {
          printk("fail to get gephy irq");
          goto LAB_0001d808;
        }
      } while (iVar3 != 4);
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-npp");
    if (iVar3 != 0) {
      npp_base = of_iomap(iVar2,0);
      if (npp_base == 0) {
        printk(&_LC31);
        goto LAB_0001d808;
      }
      g_npp_irq = irq_of_parse_and_map(iVar2,0);
      g_idm_irq = irq_of_parse_and_map(iVar2,1);
      if (g_npp_irq < 1) {
        printk("%s: failed to get npp irq\n",DAT_0001d8e0);
        goto LAB_0001d808;
      }
      printk("get npp irq succeed,g_npp_irq:%d\n");
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-tm");
    if (iVar3 != 0) {
      tm_base = of_iomap(iVar2,0);
      if (tm_base == 0) {
        printk(&_LC35);
        goto LAB_0001d808;
      }
      g_tm_irq = irq_of_parse_and_map(iVar2,0);
      if (g_tm_irq < 1) {
        printk("%s: failed to get tm irq\n",DAT_0001d8e0);
        goto LAB_0001d808;
      }
      printk("get tm irq succeed,g_tm_irq:%d\n",g_tm_irq);
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-pp");
    if (iVar3 != 0) {
      pp_base = of_iomap(iVar2,0);
      if (pp_base == 0) {
        printk(&_LC39);
        goto LAB_0001d808;
      }
      g_pp_irq = irq_of_parse_and_map(iVar2,0);
      if (g_pp_irq < 1) {
        printk("%s: failed to get pp irq\n",DAT_0001d8e0);
        goto LAB_0001d808;
      }
      printk("get pp irq succeed,g_pp_irq:%d\n",g_pp_irq);
    }
    iVar3 = of_device_is_compatible(iVar2,"zte,zx279128s-idm");
    if (iVar3 != 0) {
      idm_base = of_iomap(iVar2,0);
      if (idm_base == 0) {
        printk(&_LC43);
LAB_0001d808:
        printk("get pon irq fail!\n");
        return -0x13;
      }
      g_idm_irq = irq_of_parse_and_map(iVar2,0);
      if (g_idm_irq < 1) {
        printk("%s: failed to get idm irq\n",DAT_0001d8e0);
        goto LAB_0001d808;
      }
      printk("get idm irq succeed,g_idm_irq:%d\n",g_idm_irq);
    }
    iVar2 = of_find_matching_node_and_match(iVar2,&zx_pon_match,0);
  } while( true );
}


/* ============= FUNCTION: cleanup_module @ 0001d8e4 ============= */

void cleanup_module(void)

{
  return;
}


/* ============= FUNCTION: alloc_etherdev_mqs @ 0002f000 ============= */

/* WARNING: Control flow encountered bad instruction data */

void alloc_etherdev_mqs(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: filp_open @ 0002f004 ============= */

/* WARNING: Control flow encountered bad instruction data */

void filp_open(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strcpy @ 0002f008 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strcpy(char *__dest,char *__src)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: skb_put @ 0002f014 ============= */

/* WARNING: Control flow encountered bad instruction data */

void skb_put(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _clear_bit @ 0002f018 ============= */

/* WARNING: Control flow encountered bad instruction data */

void _clear_bit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: rb_last @ 0002f01c ============= */

/* WARNING: Control flow encountered bad instruction data */

void rb_last(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kallsyms_lookup @ 0002f020 ============= */

/* WARNING: Control flow encountered bad instruction data */

void kallsyms_lookup(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _test_and_set_bit @ 0002f024 ============= */

/* WARNING: Control flow encountered bad instruction data */

void _test_and_set_bit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _set_bit @ 0002f028 ============= */

/* WARNING: Control flow encountered bad instruction data */

void _set_bit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __arm_ioremap @ 0002f030 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __arm_ioremap(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: rb_next @ 0002f034 ============= */

/* WARNING: Control flow encountered bad instruction data */

void rb_next(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: memcpy @ 0002f03c ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memcpy(void *__dest,void *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kfree @ 0002f040 ============= */

/* WARNING: Control flow encountered bad instruction data */

void kfree(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: proc_create_data @ 0002f04c ============= */

/* WARNING: Control flow encountered bad instruction data */

void proc_create_data(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: free_pages @ 0002f050 ============= */

/* WARNING: Control flow encountered bad instruction data */

void free_pages(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: rb_insert_color @ 0002f054 ============= */

/* WARNING: Control flow encountered bad instruction data */

void rb_insert_color(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _raw_spin_lock_irqsave @ 0002f058 ============= */

/* WARNING: Control flow encountered bad instruction data */

void _raw_spin_lock_irqsave(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _raw_spin_lock @ 0002f05c ============= */

/* WARNING: Control flow encountered bad instruction data */

void _raw_spin_lock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: full_name_hash @ 0002f060 ============= */

/* WARNING: Control flow encountered bad instruction data */

void full_name_hash(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: eth_type_trans @ 0002f064 ============= */

/* WARNING: Control flow encountered bad instruction data */

void eth_type_trans(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: napi_complete_done @ 0002f068 ============= */

/* WARNING: Control flow encountered bad instruction data */

void napi_complete_done(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: msecs_to_jiffies @ 0002f06c ============= */

/* WARNING: Control flow encountered bad instruction data */

void msecs_to_jiffies(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _raw_spin_unlock_bh @ 0002f070 ============= */

/* WARNING: Control flow encountered bad instruction data */

void _raw_spin_unlock_bh(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __get_free_pages @ 0002f074 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __get_free_pages(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zx_mdio_write @ 0002f078 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zx_mdio_write(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __alloc_skbuff @ 0002f07c ============= */

/* WARNING: Control flow encountered bad instruction data */

void __alloc_skbuff(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __napi_schedule @ 0002f080 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __napi_schedule(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: netif_receive_skb_sk @ 0002f084 ============= */

/* WARNING: Control flow encountered bad instruction data */

void netif_receive_skb_sk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: find_vma @ 0002f088 ============= */

/* WARNING: Control flow encountered bad instruction data */

void find_vma(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __aeabi_idiv @ 0002f08c ============= */

/* WARNING: Control flow encountered bad instruction data */

void __aeabi_idiv(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kallsyms_lookup_name @ 0002f098 ============= */

/* WARNING: Control flow encountered bad instruction data */

void kallsyms_lookup_name(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: request_threaded_irq @ 0002f0a0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void request_threaded_irq(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: add_timer @ 0002f0a4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void add_timer(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: netif_napi_add @ 0002f0a8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void netif_napi_add(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: warn_slowpath_null @ 0002f0b0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void warn_slowpath_null(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strncmp @ 0002f0b4 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strncmp(char *__s1,char *__s2,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zte_get_pon_mode @ 0002f0b8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zte_get_pon_mode(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: register_netdev @ 0002f0bc ============= */

/* WARNING: Control flow encountered bad instruction data */

void register_netdev(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strncpy @ 0002f0c0 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strncpy(char *__dest,char *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: free_netdev @ 0002f0c4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void free_netdev(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: of_iomap @ 0002f0c8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void of_iomap(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sscanf @ 0002f0cc ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sscanf(char *__s,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: printk @ 0002f0d0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void printk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kmalloc_order @ 0002f0d4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void kmalloc_order(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _raw_spin_unlock_irqrestore @ 0002f0d8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void _raw_spin_unlock_irqrestore(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __print_symbol @ 0002f0e0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __print_symbol(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: netif_tx_wake_queue @ 0002f0e4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void netif_tx_wake_queue(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: proc_mkdir @ 0002f0e8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void proc_mkdir(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __memzero @ 0002f0ec ============= */

/* WARNING: Control flow encountered bad instruction data */

void __memzero(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __aeabi_uidiv @ 0002f0f4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __aeabi_uidiv(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: rb_first @ 0002f0f8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void rb_first(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __netdev_alloc_skb @ 0002f0fc ============= */

/* WARNING: Control flow encountered bad instruction data */

void __netdev_alloc_skb(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strcmp @ 0002f100 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strcmp(char *__s1,char *__s2)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sprintf @ 0002f110 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sprintf(char *__s,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: dma_cache_maint @ 0002f114 ============= */

/* WARNING: Control flow encountered bad instruction data */

void dma_cache_maint(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: of_device_is_compatible @ 0002f118 ============= */

/* WARNING: Control flow encountered bad instruction data */

void of_device_is_compatible(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: init_timer_key @ 0002f11c ============= */

/* WARNING: Control flow encountered bad instruction data */

void init_timer_key(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __dev_kfree_skb_any @ 0002f120 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __dev_kfree_skb_any(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: filp_close @ 0002f124 ============= */

/* WARNING: Control flow encountered bad instruction data */

void filp_close(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: ffe_learn_skb @ 0002f128 ============= */

/* WARNING: Control flow encountered bad instruction data */

void ffe_learn_skb(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __register_chrdev @ 0002f12c ============= */

/* WARNING: Control flow encountered bad instruction data */

void __register_chrdev(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: netif_carrier_off @ 0002f130 ============= */

/* WARNING: Control flow encountered bad instruction data */

void netif_carrier_off(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: seq_printf @ 0002f134 ============= */

/* WARNING: Control flow encountered bad instruction data */

void seq_printf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: simple_strtoul @ 0002f13c ============= */

/* WARNING: Control flow encountered bad instruction data */

void simple_strtoul(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: dev_get_by_name @ 0002f140 ============= */

/* WARNING: Control flow encountered bad instruction data */

void dev_get_by_name(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _raw_spin_lock_bh @ 0002f144 ============= */

/* WARNING: Control flow encountered bad instruction data */

void _raw_spin_lock_bh(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: netif_carrier_on @ 0002f148 ============= */

/* WARNING: Control flow encountered bad instruction data */

void netif_carrier_on(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __tasklet_hi_schedule @ 0002f150 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __tasklet_hi_schedule(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: temp_ctrl_read @ 0002f160 ============= */

/* WARNING: Control flow encountered bad instruction data */

void temp_ctrl_read(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: irq_to_desc @ 0002f164 ============= */

/* WARNING: Control flow encountered bad instruction data */

void irq_to_desc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: zx_mdio_read @ 0002f168 ============= */

/* WARNING: Control flow encountered bad instruction data */

void zx_mdio_read(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: irq_of_parse_and_map @ 0002f16c ============= */

/* WARNING: Control flow encountered bad instruction data */

void irq_of_parse_and_map(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strlen @ 0002f170 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t strlen(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: napi_disable @ 0002f174 ============= */

/* WARNING: Control flow encountered bad instruction data */

void napi_disable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: del_timer @ 0002f178 ============= */

/* WARNING: Control flow encountered bad instruction data */

void del_timer(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __copy_to_user @ 0002f180 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __copy_to_user(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: single_open @ 0002f184 ============= */

/* WARNING: Control flow encountered bad instruction data */

void single_open(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strchr @ 0002f188 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strchr(char *__s,int __c)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: skb_recycle @ 0002f18c ============= */

/* WARNING: Control flow encountered bad instruction data */

void skb_recycle(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: _raw_spin_unlock @ 0002f190 ============= */

/* WARNING: Control flow encountered bad instruction data */

void _raw_spin_unlock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: of_find_matching_node_and_match @ 0002f194 ============= */

/* WARNING: Control flow encountered bad instruction data */

void of_find_matching_node_and_match(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __copy_from_user @ 0002f198 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __copy_from_user(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: show_stack @ 0002f19c ============= */

/* WARNING: Control flow encountered bad instruction data */

void show_stack(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: msleep @ 0002f1a0 ============= */

/* WARNING: Control flow encountered bad instruction data */

void msleep(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __kmalloc @ 0002f1a4 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __kmalloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: d_path @ 0002f1a8 ============= */

/* WARNING: Control flow encountered bad instruction data */

void d_path(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: find_task_by_vpid @ 0002f1ac ============= */

/* WARNING: Control flow encountered bad instruction data */

void find_task_by_vpid(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



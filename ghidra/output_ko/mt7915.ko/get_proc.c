// module: mt7915.ko
// function: get_proc @ 0x351fc
// size: 1800 bytes
//

/* WARNING: Type propagation algorithm not settling */

int get_proc(int *param_1,char *param_2,int param_3,int param_4)

{
  size_t sVar1;
  int iVar2;
  char *__s2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int local_230;
  uint local_228 [64];
  char local_128 [4];
  char acStack_124 [4];
  char acStack_120 [4];
  uint local_11c;
  undefined1 local_118;
  
  iVar5 = *param_1;
  memset(local_228,0,0x100);
  memset(local_128,0,0x100);
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    piVar3 = *(int **)(iVar5 + 0x3c);
    if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) <= (int)piVar3) {
      return 0;
    }
    piVar4 = param_1 + (int)piVar3 * 0x160d + 0xadc92;
  }
  else if (*(char *)((int)param_1 + 0x286285) == '\0') {
    piVar3 = (int *)0x0;
    piVar4 = param_1 + 0xdb6d6;
  }
  else {
    piVar3 = (int *)0x0;
    piVar4 = piVar3;
  }
  local_230 = HcGetBandByWdev(piVar4);
  sVar1 = strlen(param_2);
  if (0xff < sVar1) {
    return -1;
  }
  strncpy(local_128,param_2,0xff);
  if (*(int *)(iVar5 + 0x38) == 0x400) {
    iVar2 = strcmp(local_128,"WscConfMode");
    if (iVar2 == 0) {
      local_128[0] = 'A';
      local_128[1] = 'p';
      local_128[2] = 'C';
      local_128[3] = 'l';
      acStack_124[0] = 'i';
      acStack_124[1] = 'W';
      acStack_124[2] = 's';
      acStack_124[3] = 'c';
      acStack_120[0] = 'C';
      acStack_120[1] = 'o';
      acStack_120[2] = 'n';
      acStack_120[3] = 'f';
      local_11c._0_1_ = 'M';
      local_11c._1_1_ = 'o';
      local_11c._2_1_ = 'd';
      local_11c._3_1_ = 'e';
      local_118 = 0;
    }
    iVar2 = strcmp(local_128,"WscMode");
    if (iVar2 == 0) {
      local_128[0] = 'A';
      local_128[1] = 'p';
      local_128[2] = 'C';
      local_128[3] = 'l';
      acStack_124[0] = 'i';
      acStack_124[1] = 'W';
      acStack_124[2] = 's';
      acStack_124[3] = 'c';
      acStack_120[0] = 'M';
      acStack_120[1] = 'o';
      acStack_120[2] = 'd';
      acStack_120[3] = 'e';
      local_11c = local_11c & 0xffffff00;
    }
  }
  __s2 = s_CountryRegion_0032aa04;
  while (iVar2 = strcmp(local_128,__s2), iVar2 != 0) {
    __s2 = __s2 + 0x2c;
    if (__s2 == (char *)&DAT_0032b924) {
      return -0x16;
    }
  }
  if (__s2 == (char *)0x0) {
    return -0x16;
  }
  if (2 < DebugLevel) {
    printk("type=%d,offset=%ld,len=%d,apidx=%d,BandIdx=%d\n",*(undefined4 *)(__s2 + 0x20),
           *(undefined4 *)(__s2 + 0x24),*(undefined4 *)(__s2 + 0x28),piVar3,local_230);
  }
  if (param_4 == 0) {
    if (param_3 <= DebugLevel) {
      printk("%s set value: ",local_128);
    }
  }
  else if (param_3 <= DebugLevel) {
    printk("%s original value: ",local_128);
  }
  switch(*(undefined4 *)(__s2 + 0x20)) {
  case 1:
    local_228[0] = CONCAT31(local_228[0]._1_3_,*(undefined1 *)((int)param_1 + *(int *)(__s2 + 0x24))
                           );
    if (param_3 <= DebugLevel) {
      printk(&_LC569);
      return 0;
    }
    break;
  case 2:
    if (param_3 <= DebugLevel) {
      local_230 = 0;
    }
    local_228[0] = CONCAT22(local_228[0]._2_2_,*(undefined2 *)((int)param_1 + *(int *)(__s2 + 0x24))
                           );
    goto joined_r0x000357b0;
  case 3:
  case 5:
    local_228[0] = *(uint *)((int)param_1 + *(int *)(__s2 + 0x24));
    if (DebugLevel < param_3) {
      return 0;
    }
    goto LAB_000357e4;
  case 4:
    local_228[0] = *(uint *)((int)param_1 + *(int *)(__s2 + 0x24));
    goto joined_r0x000353ec;
  case 6:
    iVar5 = *(int *)(__s2 + 0x24);
    sVar1 = *(size_t *)(__s2 + 0x28);
    goto LAB_00035570;
  default:
    if (-1 < DebugLevel) {
      printk("unsupport type: %d\n");
      return 0;
    }
    break;
  case 8:
    dumpBndStrgInfo((int)param_1 + local_230 * 0x1094 + *(int *)(__s2 + 0x24),param_3);
    return 0;
  case 9:
    sVar1 = *(size_t *)(__s2 + 0x28);
    iVar5 = (short)local_230 * 0x24 + *(int *)(__s2 + 0x24);
    goto LAB_000355e8;
  case 10:
    sVar1 = *(size_t *)(__s2 + 0x28);
    iVar5 = local_230 * sVar1 + *(int *)(__s2 + 0x24);
LAB_000355e8:
    memcpy(local_228,(void *)((int)param_1 + iVar5),sVar1);
    if (param_3 <= DebugLevel) {
LAB_00035604:
      printk(&_LC569,local_228[0] & 0xff);
      return 0;
    }
    break;
  case 0xb:
    memcpy(local_228,
           (void *)((int)param_1 + local_230 * *(size_t *)(__s2 + 0x28) + *(int *)(__s2 + 0x24)),
           *(size_t *)(__s2 + 0x28));
    goto joined_r0x000357e0;
  case 0xc:
    memcpy(local_228,(void *)((int)param_1 + (int)piVar3 * 0x5834 + *(int *)(__s2 + 0x24)),
           *(size_t *)(__s2 + 0x28));
    if (param_3 <= DebugLevel) {
      printk(&_LC569,(int)(char)local_228[0]);
      return 0;
    }
    break;
  case 0xd:
    memcpy(local_228,(void *)((int)param_1 + (int)piVar3 * 0x5834 + *(int *)(__s2 + 0x24)),
           *(size_t *)(__s2 + 0x28));
    if (DebugLevel < param_3) {
      return 0;
    }
    goto LAB_00035604;
  case 0xe:
    memcpy(local_228,(void *)((int)param_1 + (int)piVar3 * 0x5834 + *(int *)(__s2 + 0x24)),
           *(size_t *)(__s2 + 0x28));
    local_230 = 0;
joined_r0x000357b0:
    if (param_3 <= DebugLevel) {
      printk(&_LC569,local_228[0] & 0xffff);
      return local_230;
    }
    break;
  case 0xf:
    memcpy(local_228,(void *)((int)param_1 + (int)piVar3 * 0x5834 + *(int *)(__s2 + 0x24)),
           *(size_t *)(__s2 + 0x28));
joined_r0x000357e0:
    if (param_3 <= DebugLevel) {
LAB_000357e4:
      printk(&_LC569,local_228[0]);
      return 0;
    }
    break;
  case 0x10:
    memcpy(local_228,(void *)((int)param_1 + (int)piVar3 * 0x5834 + *(int *)(__s2 + 0x24)),
           *(size_t *)(__s2 + 0x28));
joined_r0x000353ec:
    if (param_3 <= DebugLevel) {
      printk(&_LC570,local_228[0]);
      return 0;
    }
    break;
  case 0x11:
    sVar1 = *(size_t *)(__s2 + 0x28);
    iVar5 = (int)piVar3 * 0x5834 + *(int *)(__s2 + 0x24);
LAB_00035570:
    memcpy(local_228,(void *)((int)param_1 + iVar5),sVar1);
    if (param_3 <= DebugLevel) {
      printk(&_LC241,local_228);
      return 0;
    }
    break;
  case 0x12:
    dumpWlanOp(piVar4,param_3);
    return 0;
  case 0x13:
    dumpWlanCfg(piVar4,param_3);
    return 0;
  case 0x14:
    if (*(int *)(iVar5 + 0x40) != 0) {
      dumpSecurityCfg(*(int *)(iVar5 + 0x40),param_3);
      return 0;
    }
    break;
  case 0x15:
    memcpy(local_228,(void *)((int)param_1 + *(int *)(__s2 + 0x24)),*(size_t *)(__s2 + 0x28));
    dumpEDCAParm(local_228,0,param_3);
    return 0;
  case 0x16:
    memcpy(local_228,(void *)((int)param_1 + *(int *)(__s2 + 0x24)),*(size_t *)(__s2 + 0x28));
    dumpEDCAParm(local_228,1,param_3);
    return 0;
  case 0x17:
    memcpy(local_228,(void *)((int)param_1 + *(int *)(__s2 + 0x24)),*(size_t *)(__s2 + 0x28));
    dumpEDCAParm(local_228,2,param_3);
    return 0;
  case 0x18:
    memcpy(local_228,(void *)((int)param_1 + *(int *)(__s2 + 0x24)),*(size_t *)(__s2 + 0x28));
    dumpEDCAParm(local_228,3,param_3);
    return 0;
  case 0x19:
    sVar1 = *(size_t *)(__s2 + 0x28);
    memcpy(local_228,(void *)((int)param_1 + *(int *)(__s2 + 0x24)),sVar1);
    iVar5 = DebugLevel;
    if (0 < (int)sVar1) {
      iVar2 = 0;
      do {
        if (param_3 <= iVar5) {
          printk(&_LC571,*(undefined1 *)((int)param_1 + *(int *)(__s2 + 0x24) + iVar2));
          iVar5 = DebugLevel;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < *(int *)(__s2 + 0x28));
    }
    if (param_3 <= iVar5) {
      printk(&_LC220);
      return 0;
    }
  }
  return 0;
}


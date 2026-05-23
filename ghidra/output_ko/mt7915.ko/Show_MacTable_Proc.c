// module: mt7915.ko
// function: Show_MacTable_Proc @ 0xe4f54
// size: 712 bytes
//

undefined4 Show_MacTable_Proc(undefined4 param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  char *__s;
  char *__s_00;
  undefined4 uVar3;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_2c = 0;
  if (DebugLevel < 1) {
    if (param_2 == (char *)0x0) {
      uVar3 = 0x20001;
      goto LAB_000e4fb0;
    }
LAB_000e4f90:
    if (*param_2 == '\0') goto LAB_000e4f9c;
    iVar1 = rtstrcasecmp(param_2,&_LC463);
    if (iVar1 == 1) {
      uVar3 = 0x20001;
    }
    else {
      iVar1 = rtstrcasecmp(param_2,&_LC464);
      if (iVar1 == 1) {
        uVar3 = 2;
      }
      else {
        uVar3 = 0;
      }
    }
    pcVar2 = strstr(param_2,"rate:");
    __s = strstr(param_2,"psm:");
    __s_00 = strstr(param_2,"bss:");
    if (pcVar2 != (char *)0x0) {
      pcVar2 = strchr(pcVar2,0x3a);
      local_2c = os_str_tol(pcVar2 + 1,0,10);
      if (0 < DebugLevel) {
        printk("%s check_aid:%d RATE\n","Show_MacTable_Proc");
      }
      if (local_2c != 0) {
        uVar3 = entrytb_traversal(param_1,traversal_func_dump_entry_rate_by_aid,&local_2c);
        return uVar3;
      }
      return 1;
    }
    if (__s != (char *)0x0) {
      pcVar2 = strchr(__s,0x3a);
      local_2c = os_str_tol(pcVar2 + 1,0,10);
      if (0 < DebugLevel) {
        printk("%s check_aid:%d PSM\n","Show_MacTable_Proc");
      }
      if (local_2c != 0) {
        uVar3 = entrytb_traversal(param_1,traversal_func_dump_entry_psm_by_aid,&local_2c);
        return uVar3;
      }
      return 1;
    }
    if (__s_00 != (char *)0x0) {
      os_zero_mem(&local_28);
      pcVar2 = strchr(__s_00,0x3a);
      if (pcVar2 != (char *)0x0) {
        local_28 = os_str_tol(pcVar2 + 1,0,10);
        local_24 = 1;
        if (0 < DebugLevel) {
          printk("%s check_bssidx:%d associated entries\n","Show_MacTable_Proc",local_28);
        }
        uVar3 = entrytb_traversal(param_1,traversal_func_dump_entry_associated_to_bss,&local_28);
        return uVar3;
      }
      if (-1 < DebugLevel) {
        printk("%s bss_str parse fail\n","Show_MacTable_Proc");
        return 1;
      }
      return 1;
    }
  }
  else {
    if (param_2 != (char *)0x0) {
      printk("%s(): arg=%s\n","Show_MacTable_Proc",param_2);
      goto LAB_000e4f90;
    }
    printk("%s(): arg=%s\n","Show_MacTable_Proc",&_LC461);
LAB_000e4f9c:
    uVar3 = 0x20001;
  }
  if (0 < DebugLevel) {
    printk("Dump MacTable entries info, EntType=0x%x\n",uVar3);
  }
LAB_000e4fb0:
  uVar3 = FUN_000e3ee8(param_1,uVar3);
  return uVar3;
}


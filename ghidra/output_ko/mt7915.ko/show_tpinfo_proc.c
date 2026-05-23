// module: mt7915.ko
// function: show_tpinfo_proc @ 0xe24c0
// size: 1108 bytes
//

undefined4 show_tpinfo_proc(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if ((param_2 == (char *)0x0) || (*param_2 == 0)) goto LAB_000e24d8;
  iVar2 = rstrtok(param_2,&_LC547,(int)*param_2,param_2,param_4);
  if (iVar2 == 0) {
    uVar5 = 0;
    uVar4 = 0;
    goto LAB_000e25d8;
  }
  iVar2 = os_str_tol(iVar2,0,10);
  iVar3 = rstrtok(0,&_LC547);
  if (iVar3 == 0) {
    uVar1 = 0xffff;
    uVar5 = 0;
    uVar4 = 0;
  }
  else {
    uVar4 = os_str_toul(iVar3,0,10);
    iVar3 = rstrtok(0,&_LC547);
    uVar5 = 0;
    if (iVar3 != 0) {
      uVar5 = os_str_tol(iVar3,0,10);
      iVar3 = rstrtok(0,&_LC547);
      if (iVar3 != 0) {
        uVar1 = os_str_tol(iVar3,0,10);
        goto LAB_000e2598;
      }
    }
    uVar1 = 0xffff;
  }
LAB_000e2598:
  if (iVar2 == 0) {
LAB_000e25d8:
    show_tpinfo_host(param_1,uVar4,uVar5);
    return 1;
  }
  if (iVar2 != 1) {
    if (iVar2 == 2) {
      switch(uVar4) {
      case 0:
        goto switchD_000e25b4_caseD_0;
      case 1:
        mt_cmd_wo_query(param_1,6,uVar1);
        return 1;
      case 2:
        mt_cmd_wo_query(param_1,7,uVar1);
        return 1;
      case 3:
        mt_cmd_wo_query(param_1,8,uVar1);
        return 1;
      case 4:
        mt_cmd_wo_query(param_1,9,uVar1);
        return 1;
      case 5:
        mt_cmd_wo_query(param_1,10,uVar1);
        return 1;
      default:
        if (0 < DebugLevel) {
          printk("%sunknown option = %d\n","show_tpinfo_wocpu",uVar4);
          return 1;
        }
        return 1;
      }
    }
LAB_000e24d8:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("\tiwpriv $(inf_name) show tpinfo=[cpu]-[option]-[debug_level]-[idx]\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("\t[cpu] 0: host, 1: wacpu, 2: wocpu\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("\t[idx] wocpu: could be wlan_idx/bss_idx/dev_idx\n");
    return 1;
  }
  MtCmdFwLog2Host(param_1,1,2);
  switch(uVar4) {
  case 0:
    if (DebugLevel < 1) break;
    printk("\t0: help\n");
    if (DebugLevel < 1) {
LAB_000e2860:
      if ((DebugLevel < 1) || (printk("\t5: tx free notify info\n"), DebugLevel < 1)) break;
      printk("\t6: ctxd info\n");
    }
    else {
      printk("\t1: msdu drop info\n");
      if (DebugLevel < 1) break;
      printk("\t2: ac tail drop info\n");
      if (0 < DebugLevel) {
        printk("\t3: bss table info\n");
        if (DebugLevel < 1) break;
        printk("\t4: sta record info\n");
        goto LAB_000e2860;
      }
    }
    if (0 < DebugLevel) {
      printk("\t7: igmp info\n");
    }
    break;
  case 1:
    MtCmdCr4Query(param_1,0x16,0,0);
    break;
  case 2:
    MtCmdCr4Query(param_1,0x17,0,0);
    break;
  case 3:
    MtCmdCr4Query(param_1,0x20,0,0);
    break;
  case 4:
    MtCmdCr4Query(param_1,0x21,0,0);
    break;
  case 5:
    MtCmdCr4Query(param_1,0x19,0,0);
    break;
  case 6:
    MtCmdCr4Query(param_1,0x18,0,0);
    break;
  case 7:
    MtCmdCr4Query(param_1,0x1a,0,0);
    break;
  default:
    if (0 < DebugLevel) {
      printk("%sunknown option = %d\n","show_tpinfo_wacpu",uVar4);
    }
  }
  MtCmdFwLog2Host(param_1,1,0);
  return 1;
switchD_000e25b4_caseD_0:
  if (DebugLevel < 1) {
    return 1;
  }
  printk("\t0: help\n");
  if (0 < DebugLevel) {
    printk("\t1: dev info\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("\t2: bss info\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("\t3: sta rec info\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("\t4: ba info\n");
  }
  if (0 < DebugLevel) {
    printk("\t5: fbcmd ring info\n");
    return 1;
  }
  return 1;
}


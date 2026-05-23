// module: mt7915.ko
// function: Set_Scan_DwellTime_Proc @ 0x2a458
// size: 428 bytes
//

undefined4 Set_Scan_DwellTime_Proc(int *param_1,char *param_2)

{
  undefined2 uVar1;
  char *__s1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  bool bVar7;
  char *local_14;
  
  iVar5 = *param_1;
  iVar3 = *(int *)(iVar5 + 0x38);
  uVar4 = iVar3 - 0x100U & 0xfffffeff;
  if (iVar3 != 0x400 && uVar4 != 0) {
    return 0;
  }
  uVar6 = (uint)*(byte *)(iVar5 + 0x3c);
  local_14 = param_2;
  if (uVar4 == 0) {
    uVar4 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
    bVar7 = 0x1e < uVar6;
    if (uVar6 < 0x20) {
      bVar7 = uVar4 <= uVar6;
    }
    if (bVar7) {
      iVar3 = *(int *)(iVar5 + 0x38);
      goto LAB_0002a4ac;
    }
  }
  else {
LAB_0002a4ac:
    bVar7 = uVar6 == 1;
    if (uVar6 < 2) {
      bVar7 = iVar3 == 0x400;
    }
    if (!bVar7) {
      return 0;
    }
  }
  if (param_1 + uVar6 * 0x160d == (int *)0xffd48db8) {
    return 0;
  }
  iVar3 = get_scan_ctrl_by_wdev(param_1);
  __s1 = strsep(&local_14,":");
  pcVar2 = strsep(&local_14,":");
  if (pcVar2 != (char *)0x0 && __s1 != (char *)0x0) {
    iVar5 = strcmp(__s1,"2");
    if (iVar5 == 0) {
      uVar1 = os_str_tol(pcVar2,0,10);
      *(undefined2 *)(iVar3 + 0x1c4) = uVar1;
    }
    else {
      iVar5 = strcmp(__s1,"5");
      if (iVar5 != 0) goto LAB_0002a514;
      uVar1 = os_str_tol(pcVar2,0,10);
      *(undefined2 *)(iVar3 + 0x1c2) = uVar1;
    }
    *(undefined1 *)(iVar3 + 0x1c0) = 1;
    if ((0 < DebugLevel) &&
       (printk("5G Dwell Time : %d (msec)\n",*(undefined2 *)(iVar3 + 0x1c2)), 0 < DebugLevel)) {
      printk("2G Dwell Time : %d (msec)\n",*(undefined2 *)(iVar3 + 0x1c4));
      return 1;
    }
    return 1;
  }
LAB_0002a514:
  *(undefined1 *)(iVar3 + 0x1c0) = 0;
  return 0;
}


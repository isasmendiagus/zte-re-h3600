// module: mt7915.ko
// function: ApSiteSurvey_by_wdev @ 0x1447a0
// size: 596 bytes
//

void ApSiteSurvey_by_wdev
               (int param_1,size_t *param_2,undefined1 param_3,undefined1 param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  size_t __n;
  undefined1 auStack_51 [6];
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined1 auStack_48 [36];
  
  iVar1 = get_scan_ctrl_by_wdev(param_1,param_5);
  uVar2 = get_scan_tab_by_wdev(param_1,param_5);
  iVar3 = HcIsRfSupport(param_1,2);
  if (param_5 == 0) {
    return;
  }
  iVar4 = HcGetBandByWdev(param_5);
  if ((((iVar3 != 0) && (*(char *)(param_1 + 0x795074) == '\x01')) &&
      (*(char *)(param_1 + 0x7953ef) == '\x01')) &&
     ((*(char *)(param_1 + (iVar4 + 0x51bb9) * 0x20 + 8) == '\x02' &&
      (*(int *)(param_5 + 0x14) != 2)))) {
    if (DebugLevel < 0) {
      return;
    }
    printk("INFO::AP is in Silent Mode.DFS CAC is under process!\n");
    return;
  }
  iVar3 = scan_in_run_state(param_1,param_5);
  if (iVar3 != 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s::Failed!!!Scan is running, please try again after scan done!\n",
           "ApSiteSurvey_by_wdev");
    return;
  }
  if (((*(byte *)(param_5 + 0xe) < 2) && ((&DAT_0036da53)[param_1] == '\0')) &&
     ((*(uint *)(s_OTH__d__d_N_A__0037170c +
                param_1 + (uint)*(byte *)(param_5 + 0xe) * 0x2137b0 + 0x14) & 2) != 0)) {
    if (DebugLevel < 3) {
      (&DAT_0036b824)[param_1 + iVar4] = param_4;
      goto LAB_0014487c;
    }
    printk(&_LC4);
  }
  else {
    cVar5 = *(char *)(iVar1 + 0x17c);
    if (cVar5 == '\x01') {
      cVar5 = *(char *)(iVar1 + 2);
    }
    if (cVar5 == '\0') {
      BssTableInit(uVar2);
    }
  }
  iVar1 = DebugLevel;
  (&DAT_0036b824)[param_1 + iVar4] = param_4;
  if (2 < iVar1) {
    printk("INFO::reset ChannelInfo! band_idx=%d\n",iVar4);
  }
LAB_0014487c:
  ChannelInfoResetNew(param_1,iVar4);
  RTMPZeroMemory(auStack_51,0x29);
  if ((param_2 != (size_t *)0x0) && (__n = *param_2, __n - 1 < 0x20)) {
    local_49 = (undefined1)__n;
    memcpy(auStack_48,param_2 + 1,__n);
  }
  local_4b = 2;
  local_4a = param_3;
  cntl_scan_request(param_5,auStack_51);
  return;
}


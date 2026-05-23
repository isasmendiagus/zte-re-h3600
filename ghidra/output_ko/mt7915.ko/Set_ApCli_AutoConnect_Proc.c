// module: mt7915.ko
// function: Set_ApCli_AutoConnect_Proc @ 0x30fe8
// size: 816 bytes
//

undefined4 Set_ApCli_AutoConnect_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  undefined1 auStack_4c [40];
  
  iVar4 = *param_1;
  iVar1 = simple_strtol(param_2,0,10);
  if (*(int *)(iVar4 + 0x38) == 0x400) {
    uVar6 = (uint)*(byte *)(iVar4 + 0x3c);
    piVar5 = param_1 + uVar6 * 0x84dec + 0xdb6d6;
    __memzero(auStack_4c,0x24);
    iVar4 = get_scan_ctrl_by_wdev(param_1,piVar5);
    iVar3 = cntl_idle(piVar5);
    if (iVar3 == 0) {
      if (-1 < DebugLevel) {
        printk("CNTL in reset SYNC\n");
      }
      Set_ApCli_Enable_Proc(param_1,&_LC38);
      sync_fsm_reset(param_1,piVar5);
      cntl_fsm_reset(piVar5);
    }
    if (iVar1 == 0) {
      *(undefined1 *)((int)param_1 + uVar6 * 0x2137b0 + 0x580eae) = 0;
      *(undefined1 *)(param_1 + uVar6 * 0x84dec + 0x1603ba) = 0;
      param_1[uVar6 * 0x84dec + 0x1603b9] = 0;
      return 1;
    }
    iVar3 = RtmpOSNetDevIsUp(param_1[uVar6 * 0x84dec + 0xdb6d6]);
    if (iVar3 == 1) {
      *(undefined1 *)((int)param_1 + uVar6 * 0x2137b0 + 0x580eae) = 1;
      Set_ApCli_Enable_Proc(param_1,&_LC38);
      iVar3 = DebugLevel;
      *(undefined1 *)(param_1 + uVar6 * 0x84dec + 0x1603ba) = 1;
      if (2 < iVar3) {
        printk("I/F(apcli%d) Set_ApCli_AutoConnect_Proc::(Len=%d,Ssid=%s)\n",uVar6,
               *(undefined1 *)((int)param_1 + uVar6 * 0x2137b0 + 0x580e5a),
               (int)param_1 + uVar6 * 0x2137b0 + 0x580e3a);
      }
      if (iVar1 == 3) {
        param_1[uVar6 * 0x84dec + 0x1603b9] = 1;
        ApSiteSurvey_by_wdev(param_1,auStack_4c,0,0,piVar5);
        uVar2 = 1;
      }
      else if (iVar1 == 4) {
        *(undefined1 *)((int)param_1 + uVar6 * 0x2137b0 + 0x580eae) = 0;
        *(undefined1 *)(param_1 + uVar6 * 0x84dec + 0x1603ba) = 0;
        param_1[uVar6 * 0x84dec + 0x1603b9] = 1;
        ApSiteSurvey_by_wdev(param_1,auStack_4c,0,0,piVar5);
        uVar2 = 1;
      }
      else if (iVar1 == 2) {
        uVar2 = 1;
        *(undefined1 *)(iVar4 + 0x17c) = 1;
        *(int **)(iVar4 + 0x1bc) = piVar5;
        param_1[uVar6 * 0x84dec + 0x1603b9] = 0;
      }
      else {
        param_1[uVar6 * 0x84dec + 0x1603b9] = 0;
        ApSiteSurvey_by_wdev(param_1,auStack_4c,0,0,piVar5);
        uVar2 = 1;
      }
    }
    else if (DebugLevel < 0) {
      uVar2 = 1;
    }
    else {
      printk("%s : [%s Abort] is not Enabled, please do ifconfig %s up first\n",
             "Set_ApCli_AutoConnect_Proc",param_1[uVar6 * 0x84dec + 0xdb6d6],
             param_1[uVar6 * 0x84dec + 0xdb6d6]);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


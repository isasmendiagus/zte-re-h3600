// module: mt7915.ko
// function: Set_AutoChannelSel_Proc @ 0x2d8f4
// size: 704 bytes
//

undefined4 Set_AutoChannelSel_Proc(int *param_1,char *param_2)

{
  size_t __n;
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  size_t local_44;
  undefined1 auStack_40 [36];
  
  iVar3 = *param_1;
  __memzero(&local_44,0x24);
  local_44 = 0;
  if (((*(int *)(iVar3 + 0x38) - 0x100U & 0xfffffeff) != 0) ||
     (piVar4 = param_1 + (uint)*(byte *)(iVar3 + 0x3c) * 0x160d + 0xadc92, piVar4 == (int *)0x0)) {
    return 0;
  }
  iVar3 = HcGetBandByWdev(piVar4);
  __n = strlen(param_2);
  if (__n < 0x21) {
    if (*param_2 == '\0') {
      local_44 = 0;
    }
    else {
      memcpy(auStack_40,param_2,__n);
      local_44 = __n;
    }
  }
  iVar1 = strcmp(param_2,"1");
  if (iVar1 == 0) {
    param_1[iVar3 + 0xdae0a] = 1;
LAB_0002d9a8:
    if (DebugLevel < 3) goto LAB_0002d9bc;
  }
  else {
    iVar1 = strcmp(param_2,"2");
    if (iVar1 == 0) {
      param_1[iVar3 + 0xdae0a] = 2;
      goto LAB_0002d9a8;
    }
    iVar1 = strcmp(param_2,"3");
    if (iVar1 == 0) {
      param_1[iVar3 + 0xdae0a] = 3;
    }
    else {
      iVar1 = strcmp(param_2,"5");
      if (iVar1 != 0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("Set_AutoChannelSel_Proc Alg isn\'t defined\n");
        return 0;
      }
      param_1[iVar3 + 0xdae0a] = 4;
    }
    if (DebugLevel < 3) goto LAB_0002da58;
  }
  printk("Set_AutoChannelSel_Proc Alg=%d\n",param_1[(short)iVar3 + 0xdae0a]);
  if (param_1[(short)iVar3 + 0xdae0a] - 3U < 2) {
LAB_0002da58:
    *(undefined1 *)(param_1 + 0xdae11) = 1;
    AutoChSelScanStart(param_1,piVar4);
    iVar1 = wait_for_completion_timeout(param_1 + 0xdae0d,0x4b0);
    if (iVar1 == 0) {
      if (0 < DebugLevel) {
        printk("%s() wait channel setting timeout.\n","Set_AutoChannelSel_Proc");
      }
      *(undefined1 *)(param_1 + 0xdae0c) = 0;
      iVar3 = HcGetAutoChCtrlbyBandIdx(param_1,iVar3);
      if (iVar3 != 0) {
        *(undefined4 *)(iVar3 + 0x58) = 0;
      }
    }
    else if (0 < DebugLevel) {
      printk("%s() wait channel setting success.\n","Set_AutoChannelSel_Proc");
    }
    *(undefined1 *)(param_1 + 0xdae11) = 0;
    return 1;
  }
LAB_0002d9bc:
  if (local_44 == 0) {
    uVar2 = 0x80;
  }
  else {
    uVar2 = 0;
  }
  ApSiteSurvey_by_wdev(param_1,&local_44,uVar2,1,piVar4);
  return 1;
}


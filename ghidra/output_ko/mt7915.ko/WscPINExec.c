// module: mt7915.ko
// function: WscPINExec @ 0x1e898c
// size: 804 bytes
//

char WscPINExec(int param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  char cVar3;
  undefined *puVar4;
  bool bVar5;
  
  if (param_3 == (undefined4 *)0x0) {
    return '\0';
  }
  if (*(char *)(param_1 + 0x286285) == '\0') {
    bVar5 = *(char *)(param_3 + 0x715) == '\0';
  }
  else {
    bVar5 = false;
  }
  if (0 < DebugLevel) {
    printk("-----> WscPINExec !!!\n");
  }
  WscPINBssTableSort(param_1,param_3);
  cVar3 = *(char *)((int)param_3 + 99);
  if (cVar3 == '\x01') {
    if (param_2 == 0) {
      puVar4 = &DAT_0036db58 + param_1;
      (&DAT_0057f9a0)[param_1] = 0;
      iVar2 = cntl_idle(puVar4);
      if ((iVar2 == 0) && (MlmeRestartStateMachine(param_1,puVar4), 0 < DebugLevel)) {
        printk("!!! WscPINExec --> MLME busy, reset MLME state machine !!!\n");
      }
      iVar2 = DebugLevel;
      if (bVar5) {
        param_3[4] = 2;
        param_3[3] = 0x27;
        if (0 < iVar2) {
          printk("wsc_state=start !!!\n");
        }
        uVar1 = HcGetBandByWdev(param_3[0xa7b]);
        RTMPSetLED(param_1,8,uVar1);
        if (s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] == '\x01') {
          MlmeEnqueueWithWdev(param_1,5,0x50a,6,(int)param_3 + 0x4d,0,puVar4);
        }
        else {
          MlmeEnqueueWithWdev(param_1,5,0x509,0x24,param_3 + 10,0,puVar4);
        }
      }
      else {
        uVar1 = HcGetBandByWdev(param_3[0xa7b]);
        RTMPSetLED(param_1,8,uVar1);
      }
      if (0 < DebugLevel) {
        printk("<----- WscPINExec !!!\n");
      }
    }
    else if (0 < DebugLevel) {
      printk("bfromM2\n");
    }
  }
  else {
    param_3[4] = 3;
    if (cVar3 == '\0') {
      param_3[3] = 0x102;
      uVar1 = HcGetBandByWdev(param_3[0xa7b]);
      RTMPSetLED(param_1,9,uVar1);
      if (0 < DebugLevel) {
        printk("WscPINExec --> AP list is %d, wait for next time\n",
               *(undefined1 *)((int)param_3 + 99));
      }
      if (s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] != '\x01') {
        return '\0';
      }
      RTMPSetTimer(param_3 + 0xa10,1000);
      *(undefined1 *)(param_3 + 0xa0f) = 1;
    }
    else {
      param_3[3] = 0x101;
      uVar1 = HcGetBandByWdev(param_3[0xa7b]);
      RTMPSetLED(param_1,10,uVar1);
      if (2 < DebugLevel) {
        printk("WscPINExec --> AP list is %d, stop WPS process!\n",
               *(undefined1 *)((int)param_3 + 99));
      }
      cVar3 = '\0';
      _WscStop(param_1,0,param_3,0);
      *param_3 = 0;
      RTMPZeroMemory(param_1 + 0x371c98,0x20);
      (&DAT_00371cb8)[param_1] = (&DAT_0057ff7e)[param_1];
      RTMPMoveMemory(param_1 + 0x371c98,param_1 + 0x57ff5e);
    }
  }
  return cVar3;
}


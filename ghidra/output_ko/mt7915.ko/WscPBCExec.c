// module: mt7915.ko
// function: WscPBCExec @ 0x1e82f4
// size: 704 bytes
//

undefined1 WscPBCExec(int param_1,int param_2,undefined4 *param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 local_2c [2];
  
  if (param_3 != (undefined4 *)0x0) {
    iVar5 = param_3[0xa7b];
    iVar2 = GetStaCfgByWdev(param_1,iVar5);
    if (iVar2 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = 2;
    }
    if (0 < DebugLevel) {
      printk("-----> WscPBCExec (CurOpMode=%d) !!!\n",iVar4);
    }
    WscPBCBssTableSort(param_1,param_3);
    if (*(char *)(param_3 + 0x13) == '\x01') {
      if (param_2 != 0) {
        return 1;
      }
      if (iVar2 != 0) {
        BN_mod_lshift1[iVar2] = (code)0x0;
      }
      iVar2 = cntl_idle(iVar5);
      if ((iVar2 == 0) && (MlmeRestartStateMachine(param_1,iVar5), 0 < DebugLevel)) {
        printk("!!! WscPBCExec --> MLME busy, reset MLME state machine !!!\n");
      }
      uVar3 = HcGetBandByWdev(param_3[0xa7b]);
      RTMPSetLED(param_1,8,uVar3);
      if (iVar4 != 2) {
        if (DebugLevel < 1) {
          return 1;
        }
        printk("<----- WscPBCExec !!!\n");
        return 1;
      }
      bVar1 = *(byte *)(param_3 + 0x715);
      local_2c[0] = CONCAT31(local_2c[0]._1_3_,(char)(bVar1 & 0xf));
      memmove((void *)((int)param_3 + 0x82),(void *)(iVar5 + 0x1b),6);
      (&DAT_00580e8d)[param_1 + (bVar1 & 0xf) * 0x2137b0] = 1;
      RTEnqueueInternalCmd(param_1,8,local_2c,1);
      return 1;
    }
    param_3[4] = 3;
    iVar5 = DebugLevel;
    if (*(char *)(param_3 + 0x13) == '\0') {
      param_3[3] = 0x102;
      if (0 < iVar5) {
        printk("WscPBCExec --> AP list is %d, wait for next time\n",0);
      }
      if ((iVar2 != 0) && (*(char *)(iVar2 + 0x4060) == '\x01')) {
        RTMPSetTimer(param_3 + 0xa10,1000);
        *(undefined1 *)(param_3 + 0xa0f) = 1;
        return 0;
      }
    }
    else {
      param_3[3] = 0x101;
      uVar3 = HcGetBandByWdev(param_3[0xa7b]);
      RTMPSetLED(param_1,10,uVar3);
      if (2 < DebugLevel) {
        printk("WscPBCExec --> AP list is %d, stop WPS process!\n",*(undefined1 *)(param_3 + 0x13));
      }
      _WscStop(param_1,0,param_3,0);
      __memzero(local_2c,4);
      local_2c[0] = 0x80;
      Kernel_ASEND("cspd.wlan_manage.wlan_mgr",0xa277,local_2c,4,0,0);
      *param_3 = 0;
      if (iVar2 != 0) {
        RTMPZeroMemory(iVar2 + 0x4140,0x20);
        *(undefined1 *)(iVar2 + 0x4160) = *(undefined1 *)(iVar2 + 0x212426);
        RTMPMoveMemory(iVar2 + 0x4140,iVar2 + 0x212406);
        return 0;
      }
    }
  }
  return 0;
}


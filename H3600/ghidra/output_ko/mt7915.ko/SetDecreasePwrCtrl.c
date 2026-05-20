// module: mt7915.ko
// function: SetDecreasePwrCtrl @ 0xbf65c
// size: 276 bytes
//

bool SetDecreasePwrCtrl(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    uVar3 = HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
    if (*(char *)((int)param_1 + 0x286285) == '\0') goto LAB_000bf708;
  }
  else {
    if (*(char *)((int)param_1 + 0x286285) != '\0') {
      uVar3 = 0;
      goto LAB_000bf688;
    }
LAB_000bf708:
    uVar3 = HcGetBandByWdev(param_1 + 0xdb6d6);
  }
  if (1 < uVar3) {
    return false;
  }
LAB_000bf688:
  if (param_2 != 0) {
    cVar1 = simple_strtol(param_2,0,10);
    if (0 < DebugLevel) {
      printk("%s: cPowerDropLevel (0.5 dBm) = %d\n","SetDecreasePwrCtrl",(int)cVar1,DebugLevel,
             param_4);
    }
    iVar2 = MtCmdTxPowerDropCtrl(param_1,(int)cVar1,uVar3);
    return iVar2 == 0;
  }
  if (DebugLevel < 0) {
    return false;
  }
  printk("%s: No parameters!!\n","SetDecreasePwrCtrl");
  return false;
}


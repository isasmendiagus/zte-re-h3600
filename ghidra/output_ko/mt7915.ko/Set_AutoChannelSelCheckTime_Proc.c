// module: mt7915.ko
// function: Set_AutoChannelSelCheckTime_Proc @ 0x2968c
// size: 200 bytes
//

undefined4
Set_AutoChannelSelCheckTime_Proc
          (int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(*param_1 + 0x38);
  if ((iVar3 - 0x100U & 0xfffffeff) == 0) {
    uVar1 = HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
    iVar2 = simple_strtol(param_2,0,10);
    iVar3 = DebugLevel;
    param_1[(short)uVar1 + 0xdae14] = 0;
    param_1[(short)uVar1 + 0xdae12] = iVar2;
    if (0 < iVar3) {
      printk(&_LC137,"Set_AutoChannelSelCheckTime_Proc",uVar1,iVar2,param_4);
    }
  }
  else if (-1 < DebugLevel) {
    printk(&_LC138,"Set_AutoChannelSelCheckTime_Proc",iVar3,DebugLevel,param_4);
  }
  return 1;
}


// module: mt7915.ko
// function: Set_SCSCfg_Proc @ 0xbea68
// size: 600 bytes
//

int * Set_SCSCfg_Proc(int *param_1,char *param_2)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  undefined1 local_80 [4];
  undefined1 local_7c [4];
  undefined2 local_78 [2];
  undefined2 auStack_74 [2];
  undefined2 auStack_70 [2];
  undefined1 local_6c [4];
  undefined2 local_68 [2];
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  uint local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  pbVar1 = (byte *)((int)param_1 + 0x2b7242);
  local_50 = 0;
  local_4c = 0;
  uVar4 = *(uint *)(*param_1 + 0x3c) & 0xff;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  if (*pbVar1 <= uVar4) {
    param_1 = (int *)0x0;
  }
  local_30 = 0;
  local_2c = 0;
  local_58 = 2;
  if (uVar4 < *pbVar1) {
    iVar2 = HcGetBandByWdev(param_1 + uVar4 * 0x160d + 0xadc92);
    iVar3 = sscanf(param_2,"%d-%d-%d-%d-%d-%d-%d-%d-%d-%d",local_7c,local_80,&local_64,local_6c,
                   &local_60,&local_5c,local_78,auStack_74,auStack_70,local_68);
    bVar5 = iVar2 == 1;
    if (iVar2 < 2) {
      bVar5 = iVar3 == 10;
    }
    if (bVar5) {
      local_34 = local_64;
      local_40 = CONCAT13(local_6c[0],CONCAT12(local_7c[0],CONCAT11(local_80[0],(char)iVar2)));
      local_30 = local_60;
      local_2c = local_5c;
      local_3c = CONCAT22(auStack_74[0],local_78[0]);
      local_38 = CONCAT22(local_68[0],auStack_70[0]);
    }
    else if (((-1 < DebugLevel) &&
             (printk("Max supported bands = %d (Supported Band Number is out of range)\n",2),
             -1 < DebugLevel)) && (printk("Format Error!\n"), -1 < DebugLevel)) {
      printk(
            "iwpriv ra0 set SCSCfg=[MinRssiTolerance]-[ThTolerance]-[TrafficThreshold]-[OfdmSupport]-[CckUpBoundary]-[CckLowBoundary]-[OfdmUpBoundary]-[OfdmLowBoundary]-[FixedCckBoundary]-[FixedOfdmBoundary]"
            );
    }
    iVar2 = AndesAllocCmdMsg(param_1,0x1c);
    if (iVar2 != 0) {
      local_48 = 0;
      local_44 = 0;
      local_50 = CONCAT31(local_50._1_3_,10);
      local_4c = local_4c & 0xffff0000;
      local_50 = local_50 & 0xffff;
      local_54 = 0x82ed0000;
      AndesInitCmdMsg(iVar2,0x82ed0000,local_50,local_4c,0,0);
      AndesAppendCmdMsg(iVar2,&local_58,4);
      AndesAppendCmdMsg(iVar2,&local_40,0x18);
      AndesSendCmdMsg(param_1,iVar2);
    }
    param_1 = (int *)(uint)(iVar2 != 0);
    if (3 < DebugLevel) {
      printk("%s:(Ret = %d_\n","Set_SCSCfg_Proc",param_1);
    }
  }
  return param_1;
}


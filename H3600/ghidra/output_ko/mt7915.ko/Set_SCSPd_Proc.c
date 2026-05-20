// module: mt7915.ko
// function: Set_SCSPd_Proc @ 0xbecc4
// size: 608 bytes
//

/* WARNING: Type propagation algorithm not settling */

int * Set_SCSPd_Proc(int *param_1,char *param_2)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  int local_3c;
  int local_38;
  int local_34 [2];
  undefined2 local_2a;
  undefined2 local_28;
  short local_26;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  pbVar1 = (byte *)((int)param_1 + 0x2b7242);
  uVar3 = (uint)*(byte *)(*param_1 + 0x3c);
  local_3c = 0;
  local_38 = 0;
  local_34[0] = 0;
  local_24 = 0;
  if (*pbVar1 <= uVar3) {
    param_1 = (int *)0x0;
  }
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_2a = 0;
  local_28 = 0;
  local_26 = 0;
  local_34[1] = 1;
  if (uVar3 < *pbVar1) {
    local_3c = HcGetBandByWdev(param_1 + uVar3 * 0x160d + 0xadc92);
    iVar2 = sscanf(param_2,"%d-%d-%d",&local_3c,&local_38,local_34);
    if ((((iVar2 == 3) && (local_38 - 0x1eU < 0x51)) && (local_34[0] - 0x1eU < 0x45)) &&
       (local_3c < 2)) {
      local_26 = (0x100 - (short)local_34[0]) * 2;
      local_28 = CONCAT11(local_28._1_1_,-(char)local_38);
      local_2a = CONCAT11(2,(char)local_3c);
      iVar2 = AndesAllocCmdMsg(param_1,10);
      if (iVar2 == 0) {
        param_1 = (int *)0x0;
      }
      else {
        local_24 = CONCAT13(0x82,CONCAT12(0xed,(undefined2)local_24));
        local_20 = CONCAT31(local_20._1_3_,10);
        AndesInitCmdMsg(iVar2,local_24,local_20,local_1c,local_18,local_14);
        AndesAppendCmdMsg(iVar2,local_34 + 1,4);
        AndesAppendCmdMsg(iVar2,&local_2a,6);
        AndesSendCmdMsg(param_1,iVar2);
        param_1 = (int *)0x1;
      }
    }
    else {
      if (DebugLevel < 0) {
        return (int *)0x1;
      }
      printk("Format Error or Out of range\n");
      if (DebugLevel < 0) {
        param_1 = (int *)0x1;
      }
      else {
        printk("iwpriv ra0 set SCSCfg=[CckPdBlkTh]-[OfdmPdBlkTh]\n");
        if (DebugLevel < 0) {
          return (int *)0x1;
        }
        printk("CckPdBlkTh  Range: 30~110 dBm (Represents a negative number)\n");
        if (DebugLevel < 0) {
          return (int *)0x1;
        }
        printk("OfdmPdBlkTh Range: 30~98\tdBm (Represents a negative number)\n");
        if (DebugLevel < 0) {
          return (int *)0x1;
        }
        printk("Max supported bands = %d (Supported Band Number is out of range)\n",2);
        param_1 = (int *)0x1;
      }
    }
    if (3 < DebugLevel) {
      printk("%s:(Ret = %d_\n","Set_SCSPd_Proc",param_1);
    }
  }
  return param_1;
}


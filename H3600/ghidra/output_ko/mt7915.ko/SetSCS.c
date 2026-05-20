// module: mt7915.ko
// function: SetSCS @ 0x23897c
// size: 260 bytes
//

void SetSCS(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  undefined2 local_12;
  
  local_12._1_1_ = 0;
  if (0 < DebugLevel) {
    printk("%s(): BandIdx=%d, SCSEnable=%d\n","SetSCS",param_2,param_3);
  }
  if (param_3 < 0x1f5) {
    if (param_3 == 0) {
      uVar1 = 0;
      (&DAT_00a7c241)[param_1 + param_2] = 0;
      *(undefined1 *)(param_1 + param_2 + 0xa7c243) = 0;
    }
    else {
      if (param_3 != 1) {
        return;
      }
      local_12._1_1_ = 1;
      (&DAT_00a7c241)[param_1 + param_2] = 1;
      uVar1 = 0x100;
    }
    SCS_Set_FW_Offload(param_1,uVar1);
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      local_12 = CONCAT11(local_12._1_1_,1);
      SCS_Set_FW_Offload(param_1,local_12);
    }
    return;
  }
  *(uint *)(param_1 + (int)("CmdHeRaMuMetricInfo" + param_2 + 6) * 4) = param_3;
  return;
}


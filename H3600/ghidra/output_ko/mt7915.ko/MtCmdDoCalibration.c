// module: mt7915.ko
// function: MtCmdDoCalibration @ 0x1aea38
// size: 372 bytes
//

void MtCmdDoCalibration(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  undefined4 unaff_r10;
  undefined4 local_c8 [18];
  undefined4 local_80;
  undefined4 local_74;
  int local_70;
  undefined4 local_6c;
  undefined1 auStack_68 [72];
  
  os_zero_mem(&local_74,0x54);
  uVar4 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  bVar1 = uVar4 == 0x7615;
  bVar2 = uVar4 == 0x7626;
  bVar3 = uVar4 == 0x6867;
  local_74 = param_2;
  local_70 = param_3;
  if (uVar4 == 0x7915 || (bVar3 || (bVar2 || (uVar4 == 0x7663 || bVar1)))) {
    if (!bVar3 && (!bVar2 && !bVar1)) {
      unaff_r10 = 8;
    }
    if (bVar3 || (bVar2 || bVar1)) {
      if (param_3 == -0x80000000) {
        unaff_r10 = 0x70;
      }
      else {
        unaff_r10 = 8;
      }
    }
    local_6c = CONCAT31(local_6c._1_3_,(char)param_4);
    if (2 < DebugLevel) {
      local_c8[0] = param_4;
      printk("%s, func_idx:%x, func_data:%x, band_idx:%x\n","MtCmdDoCalibration",param_2,param_3);
    }
  }
  else {
    if (DebugLevel < 0) {
      unaff_r10 = 8;
      goto LAB_001aeaf0;
    }
    unaff_r10 = 8;
    printk("%s: else case\n","MtCmdDoCalibration");
  }
  if (-1 < DebugLevel) {
    printk("%s: Call RfTest\n","MtCmdDoCalibration");
  }
LAB_001aeaf0:
  local_80 = unaff_r10;
  memcpy(local_c8,auStack_68,0x48);
  FUN_001ac150(param_1,local_74,local_70,local_6c);
  return;
}


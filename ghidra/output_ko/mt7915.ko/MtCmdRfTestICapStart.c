// module: mt7915.ko
// function: MtCmdRfTestICapStart @ 0x1adb78
// size: 548 bytes
//

undefined4 MtCmdRfTestICapStart(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  uint local_74;
  int local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_34;
  
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdRfTestICapStart");
  }
  *(undefined4 *)(param_1 + 0xa78a7c) = param_2[4];
  *(undefined4 *)(param_1 + 0xa78a80) = param_2[3];
  *(undefined4 *)(param_1 + 0xa78a84) = param_2[0x11];
  os_zero_mem(&local_80,0x58);
  local_90 = param_2[10];
  local_70 = param_2[2];
  local_4c = 1;
  local_6c = param_2[3];
  local_68 = param_2[4];
  local_64 = param_2[5];
  local_78 = *param_2;
  local_8c = param_2[6];
  local_88 = param_2[7];
  local_84 = param_2[8];
  local_54 = param_2[9];
  local_44 = param_2[0xd];
  local_34 = param_2[0x11];
  local_80 = CONCAT31(local_80._1_3_,1);
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7626) {
    local_4c = 2;
  }
  local_48 = 0;
  local_74 = (uint)(local_70 != 0);
  local_7c = 0xb;
  local_60 = local_8c;
  local_5c = local_88;
  local_58 = local_84;
  local_50 = local_90;
  if (2 < DebugLevel) {
    local_b8 = 0;
    local_e8 = local_70;
    local_e4 = local_6c;
    local_e0 = local_68;
    local_dc = local_64;
    local_d8 = local_90;
    local_d4 = local_8c;
    local_d0 = local_88;
    local_cc = local_84;
    local_c8 = local_54;
    local_c4 = local_44;
    local_c0 = local_34;
    local_bc = local_4c;
    printk("%s :\n prICapInfo->fgTrigger = 0x%08x\n prICapInfo->fgRingCapEn = 0x%08x\n prICapInfo->u4TriggerEvent = 0x%08x\n prICapInfo->u4CaptureNode = 0x%08x\n prICapInfo->u4CaptureLen = 0x%08x\n prICapInfo->u4CapStopCycle = 0x%08x\n prICapInfo->ucBW = 0x%08x\n prICapInfo->u4MACTriggerEvent = 0x%08x\n prICapInfo->u4SourceAddressLSB = 0x%08x\n prICapInfo->u4SourceAddressMSB = 0x%08x\n prICapInfo->u4BandIdx = 0x%08x\n prICapInfo->u4PhyIdx = 0x%08x\n prICapInfo->u4CapSource = 0x%08x\n prICapInfo->u4EnBitWidth = 0x%08x\n prICapInfo->u4Architech = 0x%08x\n"
           ,"MtCmdRfTestICapStart",local_78,local_74);
  }
  local_9c = 0;
  local_98 = 8;
  memcpy(&local_e8,&local_74,0x4c);
  uVar1 = FUN_001abb34(param_1,local_80,local_7c,local_78);
  if ((0 < DebugLevel) &&
     (printk("%s:(Status = %d)\n","MtCmdRfTestICapStart",uVar1), 2 < DebugLevel)) {
    printk("%s<-----------------\n","MtCmdRfTestICapStart");
  }
  return uVar1;
}


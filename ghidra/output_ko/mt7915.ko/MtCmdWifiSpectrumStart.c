// module: mt7915.ko
// function: MtCmdWifiSpectrumStart @ 0x1ad3a0
// size: 440 bytes
//

undefined4 MtCmdWifiSpectrumStart(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdWifiSpectrumStart");
  }
  *(undefined4 *)(param_1 + 0xa78a60) = param_2[3];
  os_zero_mem(&local_ac,0x84);
  local_bc = param_2[10];
  local_a4 = param_2[1];
  local_a0 = param_2[2];
  local_9c = param_2[3];
  local_98 = param_2[4];
  local_94 = param_2[5];
  local_a8 = *param_2;
  local_b8 = param_2[6];
  local_b4 = param_2[7];
  local_88 = param_2[8];
  local_84 = param_2[9];
  local_ac = 0;
  local_78 = 0;
  local_7c = 1;
  local_90 = local_b8;
  local_8c = local_b4;
  local_80 = local_bc;
  if (2 < DebugLevel) {
    local_150 = local_a0;
    local_14c = local_9c;
    local_148 = local_98;
    local_144 = local_94;
    local_140 = local_bc;
    local_13c = local_b8;
    local_138 = local_b4;
    local_134 = local_88;
    local_130 = local_84;
    printk("%s :\n pSpectrumInfo->fgTrigger = 0x%08x\n pSpectrumInfo->fgRingCapEn = 0x%08x\n pSpectrumInfo->u4TriggerEvent = 0x%08x\n pSpectrumInfo->u4CaptureNode = 0x%08x\n pSpectrumInfo->u4CaptureLen = 0x%08x\n pSpectrumInfo->u4CapStopCycle = 0x%08x\n pSpectrumInfo->ucBW = 0x%08x\n pSpectrumInfo->u4MACTriggerEvent = 0x%08x\n pSpectrumInfo->u4SourceAddressLSB = 0x%08x\n pSpectrumInfo->u4SourceAddressMSB = 0x%08x\n pSpectrumInfo->u4BandIdx = 0x%08x\n"
           ,"MtCmdWifiSpectrumStart");
  }
  local_d4 = 0;
  local_d8 = 8;
  local_d0 = 0;
  local_cc = 0;
  local_c8 = 0;
  memcpy(&local_150,&local_a0,0x78);
  uVar1 = FUN_001abc64(param_1,local_ac,local_a8,local_a4);
  if (0 < DebugLevel) {
    printk("%s:(Status = %d)\n","MtCmdWifiSpectrumStart",uVar1);
    if (2 < DebugLevel) {
      printk("%s<-----------------\n","MtCmdWifiSpectrumStart");
    }
  }
  return uVar1;
}


// module: mt7915.ko
// function: RTMPIoctlWifiSpectrumSetParameter @ 0x36e94
// size: 372 bytes
//

void RTMPIoctlWifiSpectrumSetParameter(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 *local_1c [2];
  
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  os_alloc_mem(param_1,local_1c,*(undefined2 *)(param_2 + 0x14));
  if (local_1c[0] == (undefined4 *)0x0) {
    return;
  }
  uVar4 = (uint)*(ushort *)(param_2 + 0x14);
  uVar5 = *(uint *)(((uint)&local_48 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar4) && *(uint *)(param_2 + 0x10) + uVar4 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    __copy_from_user(local_1c[0]);
  }
  else if (uVar4 != 0) {
    __memzero(local_1c[0],uVar4);
  }
  puVar1 = local_1c[0];
  uVar3 = Get_System_Bw_Info(param_1,local_1c[0][3]);
  puVar1[10] = uVar3;
  if (*(code **)(iVar2 + 0x1a4) == (code *)0x0) {
    if (DebugLevel < 0) goto LAB_00036f40;
    printk("%s : The function is not hooked !!\n","RTMPIoctlWifiSpectrumSetParameter");
  }
  else {
    (**(code **)(iVar2 + 0x1a4))(param_1);
  }
  if (2 < DebugLevel) {
    local_48 = local_1c[0][2];
    local_44 = local_1c[0][3];
    local_40 = local_1c[0][4];
    local_3c = local_1c[0][5];
    local_38 = local_1c[0][10];
    local_34 = local_1c[0][6];
    local_30 = local_1c[0][7];
    local_2c = local_1c[0][8];
    local_28 = local_1c[0][9];
    printk("%s :\n Trigger = 0x%08x\n RingCapEn  = 0x%08x\n TriggerEvent  = 0x%08x\n CaptureNode = 0x%08x\n CaptureLen = 0x%08x\n CapStopCycle = 0x%08x\n BW = 0x%08x\n MACTriggerEvent = 0x%08x\n SourceAddrLSB = 0x%08x\n SourceAddrMSB = 0x%08x\n BandIdx = 0x%08x\n"
           ,"RTMPIoctlWifiSpectrumSetParameter",*local_1c[0],local_1c[0][1]);
  }
LAB_00036f40:
  os_free_mem(local_1c[0]);
  return;
}


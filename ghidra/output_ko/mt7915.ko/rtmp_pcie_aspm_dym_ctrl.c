// module: mt7915.ko
// function: rtmp_pcie_aspm_dym_ctrl @ 0xb101c
// size: 156 bytes
//

void rtmp_pcie_aspm_dym_ctrl
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  local_13 = (undefined1)param_2;
  local_12 = (undefined1)param_3;
  local_11 = (undefined1)param_4;
  if (2 < DebugLevel) {
    printk("%s::b(%d),L1(%d),L0s(%d)\n","rtmp_pcie_aspm_dym_ctrl",param_2,param_3,param_4);
  }
  iVar1 = FUN_000b0a74(param_1,4,0x3a,3,&local_13);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s::Failed to enqueue cmd\n","rtmp_pcie_aspm_dym_ctrl");
  }
  return;
}


// module: mt7915.ko
// function: MtCmdWifiSpectrumUnSolicitCapStatus @ 0x1b038c
// size: 408 bytes
//

undefined4 MtCmdWifiSpectrumUnSolicitCapStatus(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *local_18;
  undefined4 *local_14 [2];
  
  local_18 = (undefined4 *)0x0;
  local_14[0] = (undefined4 *)0x0;
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdWifiSpectrumUnSolicitCapStatus");
  }
  iVar1 = os_alloc_mem(param_1,&local_18,8);
  if (iVar1 == 0) {
    os_zero_mem(local_18,8);
    iVar1 = os_alloc_mem(param_1,local_14,8);
    if (iVar1 == 0) {
      os_zero_mem(local_14[0],8);
      *local_18 = 0x810c0090;
      MtCmdMultipleMacRegAccessRead(param_1,local_18,1);
      if ((local_18[1] & 2) == 0) {
        *local_14[0] = 0x810c00b8;
        local_14[0][1] = local_14[0][1] & 0xe3ffffff;
        MtCmdMultipleMacRegAccessWrite(param_1,local_14[0],1);
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
      goto LAB_001b03e4;
    }
  }
  if (DebugLevel < 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = 1;
    printk("%s : Not enough memory for dynamic allocating !!\n",
           "MtCmdWifiSpectrumUnSolicitCapStatus");
  }
LAB_001b03e4:
  if (local_18 != (undefined4 *)0x0) {
    os_free_mem();
  }
  if (local_14[0] != (undefined4 *)0x0) {
    os_free_mem();
  }
  if ((0 < DebugLevel) &&
     (printk("%s:(Status = %d)\n","MtCmdWifiSpectrumUnSolicitCapStatus",uVar2), 2 < DebugLevel)) {
    printk("%s<-----------------\n","MtCmdWifiSpectrumUnSolicitCapStatus");
  }
  return uVar2;
}


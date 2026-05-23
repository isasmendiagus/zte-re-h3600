// module: mt7915.ko
// function: MtCmdWifiSpectrumSolicitCapStatus @ 0x1ad55c
// size: 244 bytes
//

bool MtCmdWifiSpectrumSolicitCapStatus(undefined4 param_1)

{
  undefined1 auStack_138 [120];
  undefined4 local_c0;
  undefined4 local_bc;
  code *local_b8;
  int *local_b4;
  undefined4 local_b0;
  int local_a8;
  undefined4 local_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined1 auStack_98 [124];
  
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdWifiSpectrumSolicitCapStatus");
  }
  os_zero_mem(&local_a4,0x84);
  local_a4 = 1;
  local_b4 = &local_a8;
  local_b8 = MtCmdWifiSpectrumResp;
  local_b0 = 0x44;
  local_c0 = 0xf;
  local_bc = 10000;
  memcpy(auStack_138,auStack_98,0x78);
  FUN_001abc64(param_1,local_a4,uStack_a0,uStack_9c);
  if (0 < DebugLevel) {
    printk("%s:(Status = %d)\n","MtCmdWifiSpectrumSolicitCapStatus",local_a8 == 0);
    if (2 < DebugLevel) {
      printk("%s<-----------------\n","MtCmdWifiSpectrumSolicitCapStatus");
    }
  }
  return local_a8 == 0;
}


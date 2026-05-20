// module: mt7915.ko
// function: RtmpOSNetDeviceRefPut @ 0x244258
// size: 44 bytes
//

void RtmpOSNetDeviceRefPut(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    return;
  }
  disableIRQinterrupts();
  iVar1 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
  *(int *)(iVar1 + *(int *)(param_1 + 0x280)) = *(int *)(iVar1 + *(int *)(param_1 + 0x280)) + -1;
  return;
}


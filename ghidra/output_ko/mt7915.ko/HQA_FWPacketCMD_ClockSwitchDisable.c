// module: mt7915.ko
// function: HQA_FWPacketCMD_ClockSwitchDisable @ 0x276874
// size: 156 bytes
//

undefined4 HQA_FWPacketCMD_ClockSwitchDisable(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint local_20;
  int local_1c [2];
  
  iVar1 = *(int *)(param_1 + 0xa39fd4);
  local_1c[0] = param_3 + 0xc;
  local_20 = 0;
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_FWPacketCMD_ClockSwitchDisable");
  }
  FUN_00276034(1,4,local_1c,&local_20);
  (**(code **)(iVar1 + 0x118))(param_1,local_20 & 0xff);
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}


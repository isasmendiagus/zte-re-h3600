// module: mt7915.ko
// function: HwCtrlGetTemperature @ 0xaf220
// size: 76 bytes
//

undefined4 HwCtrlGetTemperature(undefined4 param_1,int param_2)

{
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  MtCmdGetThermalSensorResult(param_1,0,**(undefined1 **)(param_2 + 8),local_14);
  if (*(void **)(param_2 + 0x24) != (void *)0x0) {
    os_move_mem(*(void **)(param_2 + 0x24),local_14,*(size_t *)(param_2 + 0x28));
  }
  return 0;
}


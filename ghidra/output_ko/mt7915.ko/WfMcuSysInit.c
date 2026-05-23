// module: mt7915.ko
// function: WfMcuSysInit @ 0x13a210
// size: 60 bytes
//

undefined4 WfMcuSysInit(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xa8) != (code *)0x0) {
    (**(code **)(iVar1 + 0xa8))(param_1);
  }
  chip_fw_init(param_1);
  return 0;
}


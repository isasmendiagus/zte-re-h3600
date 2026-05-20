// module: mt7915.ko
// function: HWCtrlOpsReg @ 0xb2904
// size: 72 bytes
//

undefined4 HWCtrlOpsReg(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(iVar1 + 0x15e) != '\x01') {
    hw_ctrl_ops_v1_register();
    return 0;
  }
  hw_ctrl_ops_v2_register(param_1 + 0x285ce0);
  return 0;
}


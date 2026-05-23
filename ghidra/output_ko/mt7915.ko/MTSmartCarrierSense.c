// module: mt7915.ko
// function: MTSmartCarrierSense @ 0x1c84a8
// size: 52 bytes
//

undefined4 MTSmartCarrierSense(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x180) != (code *)0x0) {
    (**(code **)(iVar1 + 0x180))(param_1);
  }
  return 0;
}


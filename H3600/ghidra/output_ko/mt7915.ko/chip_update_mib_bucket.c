// module: mt7915.ko
// function: chip_update_mib_bucket @ 0x136dc0
// size: 52 bytes
//

undefined4 chip_update_mib_bucket(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x2f0) != (code *)0x0) {
    (**(code **)(iVar1 + 0x2f0))(param_1);
  }
  return 0;
}


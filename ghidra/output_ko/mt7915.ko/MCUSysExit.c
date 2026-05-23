// module: mt7915.ko
// function: MCUSysExit @ 0x1a3f78
// size: 80 bytes
//

undefined4 MCUSysExit(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xb4) != (code *)0x0) {
    (**(code **)(iVar1 + 0xb4))(param_1);
  }
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xac) != (code *)0x0) {
    (**(code **)(iVar1 + 0xac))(param_1);
  }
  return 0;
}


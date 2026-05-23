// module: mt7915.ko
// function: MTBbpInit @ 0x1c84dc
// size: 96 bytes
//

undefined4 MTBbpInit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s(): Init BBP Registers\n","MTBbpInit",extraout_r2,DebugLevel,param_4);
  }
  if (*(code **)(iVar1 + 0x2c) != (code *)0x0) {
    (**(code **)(iVar1 + 0x2c))(param_1);
  }
  return 0;
}


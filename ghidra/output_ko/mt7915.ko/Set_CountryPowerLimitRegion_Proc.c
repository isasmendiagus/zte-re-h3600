// module: mt7915.ko
// function: Set_CountryPowerLimitRegion_Proc @ 0xd85ac
// size: 104 bytes
//

undefined4 Set_CountryPowerLimitRegion_Proc(int param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = simple_strtol(param_2,0,10);
  if (uVar1 < 7) {
    *(char *)(param_1 + 0x794c46) = (char)uVar1;
  }
  else {
    *(undefined1 *)(param_1 + 0x794c46) = 0;
  }
  if (2 < DebugLevel) {
    printk("Set_CountryPowerLimitRegion_Proc::(CountryPowerLimitRegion=%d)\n",
           *(undefined1 *)(param_1 + 0x794c46));
  }
  return 1;
}


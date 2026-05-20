// module: mt7915.ko
// function: Set_CountryPowerLimitRegionABand_Proc @ 0xd8614
// size: 104 bytes
//

undefined4 Set_CountryPowerLimitRegionABand_Proc(int param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = simple_strtol(param_2,0,10);
  if (uVar1 < 0x10) {
    *(char *)(param_1 + 0x794c47) = (char)uVar1;
  }
  else {
    *(undefined1 *)(param_1 + 0x794c47) = 0;
  }
  if (2 < DebugLevel) {
    printk("Set_CountryPowerLimitRegionABand_Proc::(CountryPowerLimitRegionABand=%d)\n",
           *(undefined1 *)(param_1 + 0x794c47));
  }
  return 1;
}


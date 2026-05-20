// module: mt7915.ko
// function: DriverOwn @ 0x19b3ac
// size: 64 bytes
//

undefined4 DriverOwn(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if ((iVar1 != 0) && (*(code **)(iVar1 + 0x26c) != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0019b3e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x26c))(param_1);
    return uVar2;
  }
  return 0;
}


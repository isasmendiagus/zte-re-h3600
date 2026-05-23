// module: mt7915.ko
// function: chip_pa_lna_set @ 0x137364
// size: 64 bytes
//

undefined4 chip_pa_lna_set(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x278) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00137398. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x278))(param_1,param_2);
    return uVar2;
  }
  return 0;
}


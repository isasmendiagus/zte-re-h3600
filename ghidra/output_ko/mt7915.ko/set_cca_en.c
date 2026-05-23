// module: mt7915.ko
// function: set_cca_en @ 0xec518
// size: 60 bytes
//

undefined4 set_cca_en(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x34) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ec548. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x34))(*(undefined4 *)(param_1 + 0xa797a0),param_2);
    return uVar2;
  }
  return 0;
}


// module: mt7915.ko
// function: AsicTxBfHwEnStatusUpdate @ 0x1371d4
// size: 84 bytes
//

undefined4 AsicTxBfHwEnStatusUpdate(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x118) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00137214. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x118))(param_1,param_2,param_3);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicTxBfHwEnStatusUpdate");
  return 0;
}


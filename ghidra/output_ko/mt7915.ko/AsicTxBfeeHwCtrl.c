// module: mt7915.ko
// function: AsicTxBfeeHwCtrl @ 0x1370d4
// size: 76 bytes
//

undefined4 AsicTxBfeeHwCtrl(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 300) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0013710c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 300))(param_1,param_2);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicTxBfeeHwCtrl");
  return 0;
}


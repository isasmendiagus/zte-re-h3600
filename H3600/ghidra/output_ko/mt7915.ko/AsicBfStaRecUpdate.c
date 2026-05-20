// module: mt7915.ko
// function: AsicBfStaRecUpdate @ 0x136e9c
// size: 100 bytes
//

undefined4 AsicBfStaRecUpdate(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x104) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00136ee4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x104))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicBfStaRecUpdate");
  return 0;
}


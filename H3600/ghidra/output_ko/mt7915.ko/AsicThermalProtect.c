// module: mt7915.ko
// function: AsicThermalProtect @ 0x135224
// size: 156 bytes
//

undefined4 AsicThermalProtect(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    AsicNotSupportFunc(param_1,"AsicThermalProtect");
    return 0;
  }
  uVar2 = MtCmdThermalProtect(param_1,param_2,param_3,param_4);
  return uVar2;
}


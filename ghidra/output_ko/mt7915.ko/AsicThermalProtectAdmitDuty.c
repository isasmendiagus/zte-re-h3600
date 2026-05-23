// module: mt7915.ko
// function: AsicThermalProtectAdmitDuty @ 0x1352c4
// size: 104 bytes
//

undefined4
AsicThermalProtectAdmitDuty(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    AsicNotSupportFunc(param_1,"AsicThermalProtectAdmitDuty");
    return 0;
  }
  uVar2 = MtCmdThermalProtectAdmitDuty(param_1,param_2,param_3,param_4);
  return uVar2;
}


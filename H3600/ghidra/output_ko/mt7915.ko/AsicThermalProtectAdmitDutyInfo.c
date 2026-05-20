// module: mt7915.ko
// function: AsicThermalProtectAdmitDutyInfo @ 0x135330
// size: 64 bytes
//

undefined1 AsicThermalProtectAdmitDutyInfo(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 != 2) {
    AsicNotSupportFunc(param_1,"AsicThermalProtectAdmitDutyInfo");
    return 0;
  }
  uVar1 = MtCmdThermalProtectAdmitDutyInfo(param_1);
  return uVar1;
}


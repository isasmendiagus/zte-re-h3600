// module: mt7915.ko
// function: get_thermal_protection_admin_ctrl_duty_proc @ 0xbd670
// size: 4 bytes
//

undefined1 get_thermal_protection_admin_ctrl_duty_proc(int param_1)

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


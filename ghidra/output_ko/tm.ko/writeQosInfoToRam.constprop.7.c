// module: tm.ko
// function: writeQosInfoToRam.constprop.7 @ 0x58bb8
// size: 120 bytes
//

undefined4 writeQosInfoToRam_constprop_7(undefined1 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined1 local_14;
  byte local_13;
  
  if (param_2 == -1 || param_1 == (undefined1 *)0x0) {
    printk("ERROR:invalid addr\n");
    uVar1 = 0xfffffff4;
  }
  else {
    __memzero(&local_14);
    local_14 = *param_1;
    local_13 = local_13 & 0xe0 | param_1[1] & 1 | (param_1[2] & 7) << 1 | (param_1[3] & 1) << 4;
    uVar1 = pp_pm_set_e8_qos_info(param_2,&local_14);
  }
  return uVar1;
}


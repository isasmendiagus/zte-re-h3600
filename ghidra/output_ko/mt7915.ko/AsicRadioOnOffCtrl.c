// module: mt7915.ko
// function: AsicRadioOnOffCtrl @ 0x134dc0
// size: 244 bytes
//

undefined4 AsicRadioOnOffCtrl(int param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_24;
  int local_14;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    AsicNotSupportFunc(param_1,"AsicRadioOnOffCtrl");
    return 0;
  }
  local_14 = (param_2 & 0xff) << 0x10;
  if (param_3 == 1) {
    local_24 = 0x205;
    if (0 < DebugLevel) {
      printk("%s(): DbdcIdx=%d RadioOn\n","AsicRadioOnOffCtrl",param_2);
    }
  }
  else {
    local_24 = 0x105;
    if (0 < DebugLevel) {
      printk("%s(): DbdcIdx=%d RadioOff\n","AsicRadioOnOffCtrl",param_2);
    }
  }
  uVar2 = MtCmdExtPmStateCtrl(param_1,local_24,0,0,0,local_14);
  return uVar2;
}


// module: mt7915.ko
// function: mt_WrapSetETxBFCap @ 0x8a41c
// size: 164 bytes
//

void mt_WrapSetETxBFCap(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_48 [5];
  byte local_43;
  undefined4 local_34;
  undefined4 local_20;
  undefined1 local_1c;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  local_34 = param_3;
  local_20 = wlan_config_get_etxbf(param_2);
  local_1c = *(undefined1 *)(param_1 + 0x7959a4);
  local_43 = (byte)(((uint)(byte)"SetPartProfileParameters"[param_1 + 0x18] << 0x1c) >> 0x1c);
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    iVar2 = HcGetBandByWdev(param_2);
    if (iVar2 == 0) {
      local_43 = "SetPartProfileParameters"[param_1 + 0x1b];
    }
    else {
      local_43 = "rtmp_read_vow_parms_from_file"[param_1 + 1];
    }
  }
  if (*(code **)(iVar1 + 0xf4) != (code *)0x0) {
    (**(code **)(iVar1 + 0xf4))(param_1,auStack_48);
  }
  return;
}


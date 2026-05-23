// module: mt7915.ko
// function: mt_WrapSetVHTETxBFCap @ 0x8a4c0
// size: 332 bytes
//

void mt_WrapSetVHTETxBFCap(int param_1,undefined4 *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_50 [4];
  byte local_4c;
  int local_38;
  undefined4 local_28;
  
  bVar1 = "SetPartProfileParameters"[param_1 + 0x18];
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  local_4c = bVar1 >> 4;
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    iVar3 = HcGetBandByWdev(param_2);
    if (iVar3 == 0) {
      local_4c = "SetPartProfileParameters"[param_1 + 0x1a];
    }
    else {
      local_4c = "rtmp_read_vow_parms_from_file"[param_1];
    }
  }
  local_38 = param_3;
  local_28 = wlan_config_get_etxbf(param_2);
  if (param_2[5] == 2) {
    *(byte *)(local_38 + 1) = *(byte *)(local_38 + 1) & 0x1f;
    iVar3 = GetStaCfgByWdev(param_1,param_2);
    if (((iVar3 != 0) && ((*(byte *)(iVar3 + 0x41cd) & 8) != 0)) &&
       (*(byte *)(local_38 + 1) = *(byte *)(local_38 + 1) & 0x1f | *(char *)(iVar3 + 0x41ce) << 5,
       2 < DebugLevel)) {
      printk("%s: %s num_snd_dimension=%d, bfee_sts_cap=%d, bfer=%d, bfee=%d\n",
             "mt_WrapSetVHTETxBFCap",*param_2,*(byte *)(iVar3 + 0x41ce) & 7,
             *(byte *)(iVar3 + 0x41cd) >> 5,((uint)*(byte *)(iVar3 + 0x41cd) << 0x1c) >> 0x1f,
             ((uint)*(byte *)(iVar3 + 0x41cd) << 0x1b) >> 0x1f);
    }
  }
  if (*(code **)(iVar2 + 0xfc) != (code *)0x0) {
    (**(code **)(iVar2 + 0xfc))(param_1,auStack_50);
  }
  return;
}


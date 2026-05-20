// module: mt7915.ko
// function: SetCommonHT @ 0x138618
// size: 352 bytes
//

uint SetCommonHT(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  uint local_38;
  byte local_34;
  byte local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  
  uVar1 = wlan_operate_get_ht_bw(param_2);
  uVar2 = wlan_operate_get_ext_cha(param_2);
  iVar3 = HcGetBandByWdev(param_2);
  local_38 = (uint)*(ushort *)(param_2 + 0x18);
  if ((*(ushort *)(param_2 + 0x18) & 0x18) == 0) {
    RTMPZeroMemory(param_2 + 0x891,0x1c);
    return local_38 & 0x18;
  }
  local_34 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    iVar4 = HcGetBandByWdev(param_2);
    if (iVar4 == 0) {
      local_34 = "SetPartProfileParameters"[param_1 + 0x1a];
    }
    else {
      local_34 = "rtmp_read_vow_parms_from_file"[param_1];
    }
  }
  local_31 = 0x21;
  local_33 = (byte)(((uint)*(byte *)(param_1 + 0x794cce) << 0x1f) >> 0x1f);
  local_32 = uVar2;
  local_30 = uVar1;
  local_2f = wlan_config_get_ht_stbc(param_2);
  local_2e = wlan_config_get_ht_gi(param_2);
  local_2d = *(undefined1 *)(param_2 + 0x1a);
  local_2c = 0;
  RTMPSetHT(param_1,&local_38,param_2);
  if ((*(char *)(param_1 + 0x79564e) != '\0') && (*(char *)(param_1 + iVar3 + 0x795688) != '\0')) {
    zte_wlan_operate_set_ht_bw(param_2,0,0);
    *(byte *)(param_1 + 0x7956b4) = *(byte *)(param_1 + 0x7956b4) | 4;
    *(byte *)(param_1 + 0x795652) = *(byte *)(param_1 + 0x795652) | 2;
    return 1;
  }
  return 1;
}


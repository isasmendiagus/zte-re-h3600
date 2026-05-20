// module: mt7915.ko
// function: wlan_operate_update_ht_stbc @ 0x107f8c
// size: 212 bytes
//

void wlan_operate_update_ht_stbc(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *(int *)(param_1 + 8);
  iVar5 = *(int *)(param_1 + 0xb14);
  bVar3 = "SetPartProfileParameters"[iVar4 + 0x18] & 0xf;
  bVar1 = (byte)"SetPartProfileParameters"[iVar4 + 0x18] >> 4;
  if (*(char *)(iVar4 + 0x79504d) == '\0') {
    if (iVar5 == 0) {
      return;
    }
  }
  else {
    iVar2 = HcGetBandByWdev();
    if (iVar2 == 0) {
      bVar1 = "SetPartProfileParameters"[iVar4 + 0x1a];
      bVar3 = "SetPartProfileParameters"[iVar4 + 0x1b];
    }
    else {
      bVar1 = "rtmp_read_vow_parms_from_file"[iVar4];
      bVar3 = "rtmp_read_vow_parms_from_file"[iVar4 + 1];
    }
    if (iVar5 == 0) {
      return;
    }
  }
  if (param_2 == 1) {
    if (bVar1 < 2) {
      if (bVar3 == 0) {
        bVar1 = 0;
        param_2 = 0;
        goto LAB_00107fdc;
      }
      bVar1 = 0;
    }
    else {
      bVar1 = 1;
      if (bVar3 == 0) goto LAB_00107fdc;
    }
    bVar3 = 1;
  }
  else {
    bVar1 = 0;
    bVar3 = bVar1;
  }
LAB_00107fdc:
  *(char *)(iVar5 + 10) = (char)param_2;
  *(byte *)(iVar5 + 0x36) = *(byte *)(iVar5 + 0x36) & 0x7f | bVar1 << 7;
  *(byte *)(iVar5 + 0x37) = *(byte *)(iVar5 + 0x37) & 0xfc | bVar3 & 3;
  return;
}


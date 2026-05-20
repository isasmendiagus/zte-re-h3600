// module: mt7915.ko
// function: operate_loader_trx_stream @ 0x1077f4
// size: 148 bytes
//

void operate_loader_trx_stream(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 8);
  if (*(char *)(iVar3 + 0x79504d) != '\0') {
    iVar2 = HcGetBandByWdev();
    if (iVar2 == 0) {
      bVar1 = "SetPartProfileParameters"[iVar3 + 0x1b];
    }
    else {
      bVar1 = "rtmp_read_vow_parms_from_file"[iVar3 + 1];
    }
    if (bVar1 <= param_4) {
      param_4 = (uint)bVar1;
    }
  }
  __memzero(param_2 + 0x39,0x10);
  if (param_4 == 3) {
LAB_00107850:
    *(undefined1 *)(param_2 + 0x3b) = 0xff;
  }
  else {
    if (param_4 == 4) {
      *(undefined1 *)(param_2 + 0x3c) = 0xff;
      goto LAB_00107850;
    }
    if (param_4 != 2) goto LAB_0010783c;
  }
  *(undefined1 *)(param_2 + 0x3a) = 0xff;
LAB_0010783c:
  *(undefined1 *)(param_2 + 0x39) = 0xff;
  return;
}


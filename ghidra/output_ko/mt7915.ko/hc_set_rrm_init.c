// module: mt7915.ko
// function: hc_set_rrm_init @ 0xaa350
// size: 144 bytes
//

void hc_set_rrm_init(int param_1)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  undefined8 uVar5;
  
  iVar4 = *(int *)(param_1 + 8);
  uVar5 = HcGetBandByWdev();
  bVar3 = "SetPartProfileParameters"[iVar4 + 0x18] & 0xf;
  bVar2 = (byte)"SetPartProfileParameters"[iVar4 + 0x18] >> 4;
  if (*(char *)(iVar4 + 0x79504d) != '\0') {
    iVar1 = HcGetBandByWdev(param_1,(int)((ulonglong)uVar5 >> 0x20));
    if (iVar1 == 0) {
      bVar2 = "SetPartProfileParameters"[iVar4 + 0x1a];
      bVar3 = "SetPartProfileParameters"[iVar4 + 0x1b];
    }
    else {
      bVar2 = "rtmp_read_vow_parms_from_file"[iVar4];
      bVar3 = "rtmp_read_vow_parms_from_file"[iVar4 + 1];
    }
  }
  AsicSetTxStream(*(undefined4 *)(param_1 + 8),bVar2,1,1,(int)uVar5);
  AsicSetRxStream(*(undefined4 *)(param_1 + 8),bVar3,(int)uVar5);
  return;
}


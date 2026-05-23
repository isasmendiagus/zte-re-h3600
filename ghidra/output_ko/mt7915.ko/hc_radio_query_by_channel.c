// module: mt7915.ko
// function: hc_radio_query_by_channel @ 0xaa490
// size: 176 bytes
//

undefined4 hc_radio_query_by_channel(int param_1,uint param_2,int param_3)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0xa797a0);
  if (*(byte *)(iVar4 + 0x32d8) == 0) {
    return 1;
  }
  if (*(byte *)(iVar4 + 0x16a0) == param_2) {
    iVar3 = 0;
  }
  else {
    if (*(byte *)(iVar4 + 0x32d8) < 2) {
      return 1;
    }
    if (*(byte *)(iVar4 + 0x19f4) != param_2) {
      return 1;
    }
    iVar3 = 1;
  }
  iVar4 = iVar3 * 0x354 + iVar4 + 0x1000;
  cVar1 = *(char *)(iVar4 + 0x6a3);
  *(char *)(param_3 + 3) = cVar1;
  *(undefined1 *)(param_3 + 6) = *(undefined1 *)(iVar4 + 0x6a2);
  *(undefined1 *)(param_3 + 7) = *(undefined1 *)(iVar4 + 0x6a1);
  *(undefined1 *)(param_3 + 4) = *(undefined1 *)(iVar4 + 0x6a4);
  uVar2 = *(undefined1 *)(iVar4 + 0x6a0);
  *(bool *)(param_3 + 1) = cVar1 != '\0';
  *(undefined1 *)(param_3 + 5) = uVar2;
  uVar2 = rf_bw_2_vht_bw();
  *(undefined1 *)(param_3 + 2) = uVar2;
  return 0;
}


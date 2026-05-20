// module: mt7915.ko
// function: hc_radio_query_by_rf @ 0xaa5ac
// size: 204 bytes
//

undefined4 hc_radio_query_by_rf(int param_1,uint param_2,int param_3)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = *(int *)(param_1 + 0xa797a0);
  if (*(char *)(iVar5 + 0x32d8) != '\0') {
    uVar4 = 0;
    do {
      iVar6 = uVar4 * 0x354;
      uVar4 = uVar4 + 1 & 0xff;
      uVar3 = wmode_2_rfic(*(undefined2 *)(iVar5 + iVar6 + 0x169e));
      if ((uVar3 & param_2) != 0) {
        iVar6 = iVar5 + 0x1000 + iVar6;
        cVar1 = *(char *)(iVar6 + 0x6a3);
        *(char *)(param_3 + 3) = cVar1;
        *(undefined1 *)(param_3 + 6) = *(undefined1 *)(iVar6 + 0x6a2);
        *(undefined1 *)(param_3 + 7) = *(undefined1 *)(iVar6 + 0x6a1);
        *(undefined1 *)(param_3 + 4) = *(undefined1 *)(iVar6 + 0x6a4);
        uVar2 = *(undefined1 *)(iVar6 + 0x6a0);
        *(bool *)(param_3 + 1) = cVar1 != '\0';
        *(undefined1 *)(param_3 + 5) = uVar2;
        uVar2 = rf_bw_2_vht_bw();
        *(undefined1 *)(param_3 + 2) = uVar2;
        return 0;
      }
    } while (uVar4 < *(byte *)(iVar5 + 0x32d8));
  }
  return 1;
}


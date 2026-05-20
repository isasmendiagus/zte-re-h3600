// module: mt7915.ko
// function: wdev_sync_prim_ch @ 0x14e43c
// size: 228 bytes
//

void wdev_sync_prim_ch(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  iVar1 = HcGetBandByWdev(param_2);
  piVar4 = (int *)(param_1 + 8);
  do {
    while( true ) {
      piVar4 = piVar4 + 1;
      iVar3 = *piVar4;
      if (iVar3 != 0) break;
LAB_0014e494:
      if (piVar4 == (int *)(param_1 + 0x1a8)) {
        return;
      }
    }
    iVar2 = HcIsRadioAcq(iVar3);
    if ((iVar2 == 0) || (iVar2 = HcGetBandByWdev(iVar3), iVar2 != iVar1)) {
      iVar2 = *(int *)(param_2 + 0x14);
      if (iVar2 == 1) {
        iVar2 = HcGetBandByWdev(iVar3);
        if ((iVar2 == iVar1) && (*(short *)(iVar3 + 0x18) == *(short *)(param_2 + 0x18))) {
          *(undefined1 *)(iVar3 + 0x1a) = *(undefined1 *)(param_2 + 0x1a);
          goto LAB_0014e4d0;
        }
        iVar2 = *(int *)(param_2 + 0x14);
      }
      if ((((iVar2 != 2) || (*(int *)(iVar3 + 0x14) != 1)) || (*(char *)(iVar3 + 0x28) != '\0')) ||
         (*(short *)(iVar3 + 0x18) != *(short *)(param_2 + 0x18))) goto LAB_0014e494;
      *(undefined1 *)(iVar3 + 0x1a) = *(undefined1 *)(param_2 + 0x1a);
    }
    else {
      *(undefined1 *)(iVar3 + 0x1a) = *(undefined1 *)(param_2 + 0x1a);
    }
LAB_0014e4d0:
    if (piVar4 == (int *)(param_1 + 0x1a8)) {
      return;
    }
  } while( true );
}


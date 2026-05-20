// module: mt7915.ko
// function: wdev_sync_ch_by_rfic @ 0x14e52c
// size: 72 bytes
//

void wdev_sync_ch_by_rfic(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)(param_1 + 8);
  do {
    piVar3 = piVar3 + 1;
    iVar2 = *piVar3;
    if (((iVar2 != 0) &&
        (uVar1 = wmode_2_rfic(*(undefined2 *)(iVar2 + 0x18)), (uVar1 & param_2) != 0)) &&
       (*(byte *)(iVar2 + 0x1a) != param_3)) {
      *(char *)(iVar2 + 0x1a) = (char)param_3;
    }
  } while (piVar3 != (int *)(param_1 + 0x1a8));
  return;
}


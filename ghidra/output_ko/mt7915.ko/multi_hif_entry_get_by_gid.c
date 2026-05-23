// module: mt7915.ko
// function: multi_hif_entry_get_by_gid @ 0x14e904
// size: 136 bytes
//

void multi_hif_entry_get_by_gid(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  OS_SPIN_LOCK(&DAT_005f3d24);
  *(int *)param_2 = param_2;
  *(int *)(param_2 + 4) = param_2;
  puVar3 = DAT_005f3d1c;
  if ((undefined4 **)DAT_005f3d1c != &DAT_005f3d1c) {
    do {
      while (puVar3[5] != param_1) {
        puVar3 = (undefined4 *)*puVar3;
        if ((undefined4 **)puVar3 == &DAT_005f3d1c) goto LAB_0014e980;
      }
      piVar2 = *(int **)(param_2 + 4);
      iVar1 = *piVar2;
      puVar3[3] = piVar2;
      puVar3[2] = iVar1;
      *(undefined4 **)(*piVar2 + 4) = puVar3 + 2;
      *piVar2 = (int)(puVar3 + 2);
      puVar3 = (undefined4 *)*puVar3;
    } while ((undefined4 **)puVar3 != &DAT_005f3d1c);
  }
LAB_0014e980:
  OS_SPIN_UNLOCK(&DAT_005f3d24);
  return;
}


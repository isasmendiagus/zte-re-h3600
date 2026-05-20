// module: mt7915.ko
// function: multi_hif_entry_get_by_id @ 0x14e884
// size: 124 bytes
//

undefined4 * multi_hif_entry_get_by_id(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  OS_SPIN_LOCK(&DAT_005f3d24);
  if ((undefined4 **)DAT_005f3d1c != &DAT_005f3d1c) {
    iVar4 = DAT_005f3d1c[4];
    puVar3 = (undefined4 *)*DAT_005f3d1c;
    puVar2 = DAT_005f3d1c;
    while( true ) {
      puVar1 = puVar3;
      if (iVar4 == param_1) {
        OS_SPIN_UNLOCK(&DAT_005f3d24);
        return puVar2 + 8;
      }
      if ((undefined4 **)puVar1 == &DAT_005f3d1c) break;
      iVar4 = puVar1[4];
      puVar3 = (undefined4 *)*puVar1;
      puVar2 = puVar1;
    }
  }
  OS_SPIN_UNLOCK(&DAT_005f3d24);
  return (undefined4 *)0x0;
}


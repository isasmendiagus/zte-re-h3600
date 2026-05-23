// module: mt7915.ko
// function: get_starec_by_wcid @ 0x104420
// size: 116 bytes
//

int get_starec_by_wcid(int param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  
  _raw_spin_lock_bh(param_1 + 0xa7bf00);
  for (piVar1 = *(int **)(param_1 + 0xa7bef0); (int *)(param_1 + 0xa7bef0) != piVar1;
      piVar1 = (int *)*piVar1) {
    iVar2 = (int)(piVar1 + -0x34);
    if (*(ushort *)((int)piVar1 + -0xce) == param_2) goto LAB_0010447c;
  }
  iVar2 = 0;
LAB_0010447c:
  _raw_spin_unlock_bh(param_1 + 0xa7bf00);
  return iVar2;
}


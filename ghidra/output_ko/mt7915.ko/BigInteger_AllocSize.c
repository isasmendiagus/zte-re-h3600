// module: mt7915.ko
// function: BigInteger_AllocSize @ 0x1fb168
// size: 420 bytes
//

void BigInteger_AllocSize(int *param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((int)param_2 < 1) {
    return;
  }
  iVar2 = *param_1;
  iVar3 = (int)param_2 >> 2;
  if (iVar2 == 0) {
    BigInteger_Init();
    iVar2 = *param_1;
    if ((param_2 & 3) != 0) goto LAB_001fb194;
LAB_001fb198:
    if (iVar2 == 0) {
      return;
    }
  }
  else if ((param_2 & 3) != 0) {
LAB_001fb194:
    iVar3 = iVar3 + 1;
    goto LAB_001fb198;
  }
  iVar1 = *(int *)(iVar2 + 0xc);
  if (iVar1 != 0) {
    if ((uint)(iVar3 << 2) <= *(uint *)(iVar2 + 0x10)) goto LAB_001fb1bc;
    BigInteger_Free_AllocSize(param_1);
    iVar2 = *param_1;
    iVar1 = *(int *)(iVar2 + 0xc);
    if (iVar1 != 0) goto LAB_001fb1bc;
  }
  iVar2 = iVar3 << 2;
  if (is_time_rec != '\0') {
    alloc_cnt = alloc_cnt + 1;
  }
  if (is_add_alloc_rec != '\0') {
    alloc_cnt_add = alloc_cnt_add + 1;
  }
  if (is_sub_alloc_rec != '\0') {
    alloc_cnt_sub = alloc_cnt_sub + 1;
  }
  if (is_mul_alloc_rec != '\0') {
    alloc_cnt_mul = alloc_cnt_mul + 1;
  }
  if (is_div_alloc_rec != '\0') {
    alloc_cnt_div = alloc_cnt_div + 1;
  }
  if (is_mod_alloc_rec != '\0') {
    alloc_cnt_mod = alloc_cnt_mod + 1;
  }
  os_alloc_mem(0,*param_1 + 0xc,iVar2);
  if (*(int *)(*param_1 + 0xc) == 0) {
    printk("BigInteger_AllocSize: allocate %zu bytes memory failure.\n",iVar2,0,param_4);
    return;
  }
  *(int *)(*param_1 + 0x10) = iVar2;
  iVar2 = *param_1;
  iVar1 = *(int *)(iVar2 + 0xc);
LAB_001fb1bc:
  if (*(int *)(iVar2 + 0x10) != 0) {
    __memzero(iVar1);
    iVar2 = *param_1;
  }
  *(int *)(iVar2 + 0x14) = iVar3;
  *(uint *)(*param_1 + 0x18) = param_2;
  return;
}


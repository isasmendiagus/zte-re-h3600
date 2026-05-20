// module: mt7915.ko
// function: ecc_point_copy @ 0x2174c0
// size: 144 bytes
//

void ecc_point_copy(int *param_1,int *param_2)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    return;
  }
  iVar1 = *param_2;
  if (iVar1 == 0) {
    FUN_0021705c(param_2);
    iVar1 = *param_2;
    if (iVar1 == 0) {
                    /* WARNING: Subroutine does not return */
      panic("ecc_point_init alloc fail\n");
    }
  }
  if (*param_1 != 0) {
    Bignum_Copy();
    iVar1 = *param_2;
  }
  if (param_1[1] != 0) {
    Bignum_Copy(param_1[1],iVar1 + 4);
    iVar1 = *param_2;
  }
  if (param_1[2] != 0) {
    Bignum_Copy(param_1[2],iVar1 + 8);
    iVar1 = *param_2;
  }
  *(char *)(iVar1 + 0xc) = (char)param_1[3];
  return;
}


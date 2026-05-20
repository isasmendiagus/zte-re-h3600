// module: mt7915.ko
// function: ecc_point_mul_wNAF @ 0x2186bc
// size: 628 bytes
//

void ecc_point_mul_wNAF(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 local_54;
  undefined4 local_50;
  int local_4c;
  undefined4 local_48 [9];
  
  local_48[0] = 0;
  local_48[1] = 0;
  local_48[2] = 0;
  local_48[3] = 0;
  local_48[4] = 0;
  local_48[5] = 0;
  local_48[6] = 0;
  local_48[7] = 0;
  local_54 = 0;
  local_50 = 0;
  BigInteger_record_time_begin(0x5f4af4);
  ecc_point_copy(param_1,local_48);
  ecc_point_double(local_48[0],param_3,local_48 + 7);
  puVar5 = local_48;
  do {
    puVar8 = puVar5 + 1;
    ecc_point_add(*puVar5,local_48[7],param_3,puVar8);
    puVar5 = puVar8;
  } while (puVar8 != local_48 + 3);
  puVar5 = local_48 + 7;
  puVar8 = local_48;
  do {
    puVar6 = puVar5 + -1;
    ecc_point_copy(*puVar8,puVar5);
    ecc_point_inverse(*puVar5,*(undefined4 *)(param_3 + 4),puVar5);
    puVar5 = puVar6;
    puVar8 = puVar8 + 1;
  } while (local_48 + 3 != puVar6);
  iVar2 = Bignum_getlen(param_2);
  os_alloc_mem(0,&local_4c,iVar2 << 5);
  iVar2 = local_4c;
  if (local_4c == 0) {
    iVar2 = 0;
  }
  else {
    uVar3 = Bignum_getlen(param_2);
    if ((uVar3 & 0x7ffffff) != 0) {
      __memzero(iVar2);
    }
    iVar2 = 0;
    Bignum_Copy(param_2,&local_50);
    while (iVar4 = Bignum_is_zero(local_50), iVar4 == 0) {
      iVar4 = Bignum_is_odd(local_50);
      if (iVar4 == 0) {
        *(undefined4 *)(local_4c + iVar2) = 0;
      }
      else {
        Bignum_Mod_DW(local_50,0x10,local_4c + iVar2);
        if (7 < *(uint *)(local_4c + iVar2)) {
          Bignum_Add_DW(local_50,0x10);
        }
      }
      Bignum_Shift_Right1(local_50,&local_50);
      iVar2 = iVar2 + 4;
    }
    iVar4 = Bignum_getlen(param_2);
    iVar2 = 0;
    ecc_point_copy(param_1,&local_54);
    iVar7 = iVar4 * 8 + -1;
    iVar4 = (iVar4 * 8 + 0x3fffffff) * 4;
    do {
      ecc_point_double(local_54,param_3,&local_54);
      piVar1 = (int *)(local_4c + iVar4);
      iVar4 = iVar4 + -4;
      if (*piVar1 != 0) {
        iVar2 = iVar2 + 1;
        ecc_point_add(local_54,local_48[*piVar1],param_3,&local_54);
      }
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    ecc_point_copy(local_54,param_4);
    os_free_mem(local_4c);
  }
  puVar5 = local_48;
  do {
    puVar8 = puVar5 + 1;
    ecc_point_free(puVar5);
    puVar5 = puVar8;
  } while (puVar8 != local_48 + 8);
  ecc_point_free(&local_54);
  BigInteger_record_time_end(0x5f4af4);
  if (0 < DebugLevel) {
    printk("total cnt = %d!!!!!!\n",iVar2 + 8);
  }
  return;
}


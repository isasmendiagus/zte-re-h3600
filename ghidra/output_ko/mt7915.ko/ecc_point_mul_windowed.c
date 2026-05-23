// module: mt7915.ko
// function: ecc_point_mul_windowed @ 0x2183dc
// size: 572 bytes
//

void ecc_point_mul_windowed
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44;
  undefined4 local_40 [8];
  undefined4 *puVar5;
  
  local_40[0] = 0;
  local_40[1] = 0;
  local_40[2] = 0;
  local_40[3] = 0;
  local_40[4] = 0;
  local_40[5] = 0;
  local_40[6] = 0;
  local_40[7] = 0;
  local_4c = 0;
  local_48 = 0;
  BigInteger_record_time_begin(0x5f4af4);
  if (3 < DebugLevel) {
    printk("==> %s()\n","ecc_point_mul_windowed");
  }
  ecc_point_copy(param_1);
  ecc_point_double(local_40[0],param_3,local_40 + 7);
  puVar4 = local_40;
  do {
    puVar5 = puVar4 + 1;
    ecc_point_add(*puVar4,local_40[7],param_3,puVar5);
    puVar4 = puVar5;
  } while (puVar5 != local_40 + 7);
  iVar2 = Bignum_getlen(param_2);
  os_alloc_mem(0,&local_44,iVar2 << 5);
  iVar2 = local_44;
  if (local_44 != 0) {
    uVar3 = Bignum_getlen(param_2);
    if ((uVar3 & 0x7ffffff) != 0) {
      __memzero(iVar2);
    }
    sVar1 = 0;
    Bignum_Copy(param_2,&local_48);
    while (iVar2 = Bignum_is_zero(local_48), iVar2 == 0) {
      iVar2 = Bignum_is_odd(local_48);
      if (iVar2 == 0) {
        *(undefined4 *)(local_44 + sVar1 * 4) = 0;
      }
      else {
        Bignum_Mod_DW(local_48,0x10,local_44 + sVar1 * 4);
      }
      Bignum_Shift_Right1(local_48,&local_48);
      sVar1 = sVar1 + 1;
    }
    sVar1 = Bignum_getlen(param_2);
    sVar1 = sVar1 * 8 + -1;
    iVar2 = (int)sVar1;
    do {
      ecc_point_double(local_4c,param_3,&local_4c);
      iVar2 = *(int *)(local_44 + iVar2 * 4);
      if (iVar2 != 0) {
        ecc_point_add(local_4c,local_40[iVar2 - 1U >> 1],param_3,&local_4c);
      }
      sVar1 = sVar1 + -1;
      iVar2 = (int)sVar1;
    } while (-1 < iVar2);
    ecc_point_copy(local_4c,param_4);
    os_free_mem(local_44);
  }
  puVar4 = local_40;
  do {
    puVar5 = puVar4 + 1;
    ecc_point_free(puVar4);
    puVar4 = puVar5;
  } while (puVar5 != (undefined4 *)&stack0xffffffe0);
  ecc_point_free(&local_4c);
  Bignum_Free(&local_48);
  BigInteger_record_time_end(0x5f4af4);
  return;
}


// module: mt7915.ko
// function: BigInteger_Montgomery_ExpMod_with_mont @ 0x1fd850
// size: 1104 bytes
//

/* WARNING: Type propagation algorithm not settling */

void BigInteger_Montgomery_ExpMod_with_mont
               (int param_1,int param_2,int param_3,ushort *param_4,undefined4 param_5)

{
  int *piVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 **local_58;
  uint local_50;
  uint local_4c;
  int local_48 [7];
  undefined1 *local_2c [2];
  
  bi_op_ti_rec._88_4_ = jiffies;
  local_48[0] = 0;
  local_48[1] = 0;
  local_48[2] = 0;
  local_48[3] = 0;
  local_48[4] = 0;
  local_48[5] = 0;
  local_48[6] = 0;
  if (param_1 == 0 || (param_3 == 0 || param_2 == 0)) {
    return;
  }
  iVar2 = *(int *)(param_1 + 0x18) + *(int *)(param_2 + 0x18) + 0x32 + *(int *)(param_3 + 0x18);
  BigInteger_AllocSize(local_48,iVar2);
  BigInteger_AllocSize(local_48 + 1,iVar2);
  if (*(int *)(param_1 + 0x18) == 1) {
    if (**(int **)(param_1 + 0xc) == 0) {
      BigInteger_Bin2BI(&DAT_005f4a1c,1,param_5);
      goto LAB_001fdb64;
    }
    if (**(int **)(param_1 + 0xc) != 1) goto LAB_001fd908;
LAB_001fdbe0:
    BigInteger_Div(param_1,param_3,local_48,param_5);
  }
  else {
LAB_001fd908:
    if (*(int *)(param_2 + 0x18) == 1) {
      if (**(int **)(param_2 + 0xc) == 1) goto LAB_001fdbe0;
      if (**(int **)(param_2 + 0xc) == 2) {
        FUN_001fc024(param_1,local_48);
        BigInteger_Div(local_48[0],param_3,local_48 + 1,param_5);
        goto LAB_001fdb64;
      }
    }
    piVar1 = local_48 + 3;
    BigInteger_Init(local_48 + 2);
    BigInteger_Init(piVar1);
    BigInteger_Init(local_48 + 4);
    BigInteger_Init(local_48 + 6);
    BigInteger_Bin2BI(&_LANCHOR1,1,local_48 + 5);
    BigInteger_AllocSize(piVar1,iVar2);
    BigInteger_Bin2BI(WPS_DH_P_VALUE,0xc0,local_48);
    if (param_4 != (ushort *)0x0) {
      BigInteger_Copy(*(undefined4 *)(param_4 + 2),piVar1);
      BigInteger_Copy(*(undefined4 *)(param_4 + 4),local_48 + 4);
      BigInteger_Copy(*(undefined4 *)(param_4 + 6),local_48 + 6);
      local_4c = (uint)*param_4;
    }
    if ((local_48[0] == 0) ||
       (iVar2 = memcmp(*(void **)(param_3 + 0xc),*(void **)(local_48[0] + 0xc),
                       *(size_t *)(param_3 + 0x18)), iVar2 != 0)) {
      local_2c[0] = (undefined1 *)0x0;
      BigInteger_BitsOfBI(param_3,&local_50);
      iVar2 = *(int *)(param_3 + 0x18);
      if ((local_50 & 7) == 0) {
        iVar2 = iVar2 + 1;
      }
      os_alloc_mem(0,local_2c,iVar2);
      if (local_2c[0] != (undefined1 *)0x0) {
        if (iVar2 != 0) {
          __memzero(local_2c[0],iVar2);
        }
        *local_2c[0] = (char)(1 << (local_50 & 7));
        BigInteger_Bin2BI(local_2c[0],iVar2,local_48 + 4);
        os_free_mem(local_2c[0]);
      }
      FUN_001fced0(local_48[4],param_3,local_48,local_48 + 6);
      BigInteger_Div(local_48[4],param_3,local_48 + 1,piVar1);
      BigInteger_BitsOfBI(local_48[4],&local_4c);
    }
    else {
      BigInteger_Bin2BI(&DAT_005dfad8,0xb8,piVar1);
      BigInteger_Bin2BI(&DAT_005dfb90,0xc1,local_48 + 4);
      BigInteger_Bin2BI(&DAT_005dfc54,0xc0,local_48 + 6);
      BigInteger_BitsOfBI(local_48[4],&local_4c);
    }
    local_58 = local_2c;
    BigInteger_Mul(param_1,local_48[4],local_48);
    BigInteger_Div(local_48[0],param_3,local_48 + 1,local_48 + 2);
    BigInteger_BitsOfBI(param_2,local_58);
    puVar3 = local_2c[0];
    while (puVar3 != (undefined1 *)0x0) {
      while( true ) {
        puVar3 = puVar3 + -1;
        BigInteger_Montgomery_MulMod_with_mont(local_48[3],local_48[3],param_3,param_4,local_48);
        if ((*(uint *)(param_2 + 0x14) < (uint)puVar3 >> 5) ||
           ((*(uint *)(*(int *)(param_2 + 0xc) + ((uint)puVar3 >> 5) * 4) >> ((uint)puVar3 & 0x1f) &
            1) == 0)) break;
        BigInteger_Montgomery_MulMod_with_mont(local_48[2],local_48[0],param_3,param_4,piVar1);
        if (puVar3 == (undefined1 *)0x0) goto LAB_001fdb24;
      }
      BigInteger_Copy(local_48[0],piVar1,param_3,param_4);
    }
LAB_001fdb24:
    BigInteger_Montgomery_MulMod_with_mont(local_48[3],local_48[5],param_3,param_4,param_5);
    release_temporal_usage_big_interger(local_48 + 2);
    release_temporal_usage_big_interger(piVar1);
    release_temporal_usage_big_interger(local_48 + 4);
    release_temporal_usage_big_interger(local_48 + 6);
    release_temporal_usage_big_interger(local_48 + 5);
  }
LAB_001fdb64:
  release_temporal_usage_big_interger(local_48);
  release_temporal_usage_big_interger(local_48 + 1);
  bi_op_ti_rec._88_4_ = jiffies - bi_op_ti_rec._88_4_;
  if (bi_op_ti_rec._92_4_ != -1) {
    iVar2 = bi_op_ti_rec._92_4_ + 1;
    bi_op_ti_rec._84_4_ =
         __aeabi_uidiv(bi_op_ti_rec._84_4_ * bi_op_ti_rec._92_4_ + bi_op_ti_rec._88_4_,iVar2);
    bi_op_ti_rec._92_4_ = iVar2;
  }
  return;
}


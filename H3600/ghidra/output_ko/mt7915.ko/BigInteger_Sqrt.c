// module: mt7915.ko
// function: BigInteger_Sqrt @ 0x1fe8c8
// size: 760 bytes
//

undefined4 BigInteger_Sqrt(int param_1,int *param_2)

{
  uint uVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  char cVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined8 uVar9;
  undefined4 local_40;
  char *local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  local_40 = 0;
  bi_op_ti_rec._76_4_ = jiffies;
  local_3c = (char *)0x0;
  local_38 = 0;
  if (param_1 == 0) {
    BigInteger_Bin2BI(&testa,8,&local_38);
  }
  else {
    BigInteger_Copy(param_1,&local_38);
  }
  uVar7 = 0;
  if (local_38 != 0) {
    uVar1 = *(int *)(local_38 + 0x18) + 1U >> 1;
    os_alloc_mem(0,&local_3c,uVar1);
    if (local_3c == (char *)0x0) {
      uVar7 = 0;
    }
    else {
      if (uVar1 != 0) {
        __memzero(local_3c,uVar1);
      }
      pcVar2 = local_3c;
      uVar6 = *(uint *)(local_38 + 0x18);
      uVar3 = BigInteger_GetByteValue(local_38,uVar6);
      iVar8 = 0;
      if (uVar3 < 0x11) {
        cVar5 = '\x02';
      }
      else {
        cVar5 = '\a';
      }
      if ((uVar6 & 1) == 0) {
        cVar5 = cVar5 << 4;
      }
      *pcVar2 = cVar5;
      BigInteger_Bin2BI(local_3c,uVar1,&local_40);
      BigInteger_is_one(local_40);
      while( true ) {
        local_34 = 0;
        iVar8 = iVar8 + 1;
        local_30 = 0;
        local_2c[0] = 0;
        BigInteger_Div(local_38,local_40,&local_34,&local_30);
        iVar4 = BigInteger_UnsignedCompare(local_40,local_34);
        if (iVar4 == 0) break;
        uVar9 = BigInteger_UnsignedCompare(local_40,local_30);
        if ((int)uVar9 != 1) {
          BigInteger_Free(&local_34,(int)((ulonglong)uVar9 >> 0x20),local_2c);
          BigInteger_Free(&local_30);
          printk("%s: div fail!!!\n","BigInteger_Sqrt");
          goto LAB_001feaec;
        }
        BigInteger_Add(local_40,local_34);
        BigInteger_Shift_Right1(local_2c[0],&local_34);
        iVar4 = BigInteger_UnsignedCompare(local_40,local_34);
        if (iVar4 == 0) {
          printk("diff == 1\n",&local_40);
          BigInteger_Free(&local_34);
          BigInteger_Free(&local_30);
          BigInteger_Free(local_2c);
          goto LAB_001feaec;
        }
        BigInteger_Copy(local_34);
        BigInteger_Free(&local_34);
        BigInteger_Free(&local_30);
        BigInteger_Free(local_2c);
      }
      iVar4 = BigInteger_is_zero(local_30);
      if (iVar4 == 0) {
        BigInteger_Free(&local_34);
        BigInteger_Free(&local_30);
LAB_001feaec:
        printk("%s: total loop %d\n","BigInteger_Sqrt",iVar8);
        uVar7 = 0;
        BigInteger_Free(param_2);
      }
      else {
        printk(&_LC19,"BigInteger_Sqrt");
        BigInteger_Free(&local_34);
        BigInteger_Free(&local_30);
        printk("%s: total loop %d\n","BigInteger_Sqrt",iVar8);
        if (*param_2 == 0) {
          BigInteger_Init(param_2);
        }
        BigInteger_Copy(local_40,param_2);
        uVar7 = 1;
      }
      os_free_mem(local_3c);
    }
    BigInteger_Free(&local_38);
    BigInteger_Free(&local_40);
    bi_op_ti_rec._76_4_ = jiffies - bi_op_ti_rec._76_4_;
    if (bi_op_ti_rec._80_4_ != -1) {
      iVar8 = bi_op_ti_rec._80_4_ + 1;
      bi_op_ti_rec._72_4_ =
           __aeabi_uidiv(bi_op_ti_rec._72_4_ * bi_op_ti_rec._80_4_ + bi_op_ti_rec._76_4_,iVar8);
      bi_op_ti_rec._80_4_ = iVar8;
    }
  }
  return uVar7;
}


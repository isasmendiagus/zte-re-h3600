// module: mt7915.ko
// function: BigInteger_rand_range @ 0x1fe250
// size: 404 bytes
//

undefined4 BigInteger_rand_range(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  byte *pbVar8;
  bool bVar9;
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  
  local_28 = 0;
  uVar2 = 0;
  if (param_1 != 0) {
    iVar4 = *(int *)(param_1 + 0x18);
    local_24 = 0;
    local_2c = param_2;
    os_alloc_mem(0,&local_28,iVar4);
    if (local_28 == 0) {
      printk("==> %s(), fail\n","BigInteger_rand_range");
      return 0;
    }
    iVar5 = 100;
    while( true ) {
      if (iVar4 != 0) {
        iVar6 = 0;
        do {
          pbVar8 = (byte *)(local_28 + iVar6);
          iVar3 = 8;
          bVar7 = 0;
          if (DAT_005f4ab8 == 0) {
            DAT_005f4ab8 = jiffies;
          }
          do {
            bVar9 = (DAT_005f4ab8 & 1) != 0;
            if (bVar9) {
              DAT_005f4ab8 = DAT_005f4ab8 ^ 0x80000057;
            }
            DAT_005f4ab8 = DAT_005f4ab8 >> 1;
            bVar1 = bVar7 << 1;
            if (bVar9) {
              DAT_005f4ab8 = DAT_005f4ab8 | 0x80000000;
            }
            iVar3 = iVar3 + -1;
            bVar7 = bVar9 | bVar1;
          } while (iVar3 != 0);
          iVar6 = iVar6 + 1;
          *pbVar8 = bVar9 | bVar1;
        } while (iVar6 != iVar4);
      }
      hex_dump_with_lvl("rand:",local_28,iVar4,4);
      BigInteger_Bin2BI(local_28,iVar4,&local_24);
      iVar6 = BigInteger_is_zero(local_24);
      if (((iVar6 == 0) && (iVar6 = BigInteger_is_one(local_24), iVar6 == 0)) &&
         (iVar6 = BigInteger_UnsignedCompare(local_24,param_1), iVar6 < 0)) break;
      iVar5 = iVar5 + -1;
      if (iVar5 == 0) {
        BigInteger_Free(&local_24);
        os_free_mem(local_28);
        return 0;
      }
    }
    BigInteger_Copy(local_24,&local_2c);
    BigInteger_Free(&local_24);
    os_free_mem(local_28);
    uVar2 = 1;
  }
  return uVar2;
}


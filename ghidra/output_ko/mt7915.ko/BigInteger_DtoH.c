// module: mt7915.ko
// function: BigInteger_DtoH @ 0x1ff8d4
// size: 284 bytes
//

void BigInteger_DtoH(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int local_34 [2];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  local_1c[0] = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_34[0] = param_1;
  BigInteger_DWtoBI(100,local_1c);
  BigInteger_DWtoBI(1,&local_24);
  BigInteger_DWtoBI(0,&local_2c);
  uVar2 = 1;
  if (*(int *)(local_34[0] + 0x18) != 0) {
    do {
      uVar3 = uVar2 + 1;
      uVar1 = BigInteger_GetByteValue(local_34[0],uVar2);
      BigInteger_DWtoBI(uVar1,&local_28);
      BigInteger_Mul(local_28,local_24,&local_20);
      BigInteger_Copy(local_20,&local_28);
      BigInteger_Add(local_2c,local_28,&local_20);
      BigInteger_Copy(local_20,&local_2c);
      BigInteger_Mul(local_24,local_1c[0],&local_28);
      BigInteger_Copy(local_28,&local_24);
      uVar2 = uVar3;
    } while (uVar3 <= *(uint *)(local_34[0] + 0x18));
  }
  BigInteger_Copy(local_2c,local_34);
  BigInteger_Free(&local_2c);
  BigInteger_Free(&local_28);
  BigInteger_Free(&local_24);
  BigInteger_Free(&local_20);
  BigInteger_Free(local_1c);
  return;
}


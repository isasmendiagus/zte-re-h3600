// module: mt7915.ko
// function: get_ecc_group_info_bi @ 0x2170f0
// size: 472 bytes
//

undefined4 * get_ecc_group_info_bi(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  undefined4 uVar7;
  undefined1 local_21;
  BIGNUM *local_20;
  BIGNUM *local_1c [2];
  
  if (_LANCHOR0 == param_1) {
    puVar4 = (undefined4 *)0x5dffc0;
    puVar5 = &_LANCHOR0;
  }
  else {
    puVar4 = (undefined4 *)0x0;
    puVar5 = puVar4;
  }
  if (DAT_005dff40 == param_1) {
    puVar5 = &DAT_005dff40;
    puVar4 = (undefined4 *)&DAT_005dffe8;
  }
  if (DAT_005dff80 == param_1) {
    puVar5 = &DAT_005dff80;
    puVar4 = (undefined4 *)&DAT_005e0010;
  }
  if (puVar5 == (undefined4 *)0x0 || puVar4 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  local_20 = (BIGNUM *)(uint)*(byte *)((int)puVar4 + 0x25);
  if (local_20 != (BIGNUM *)0x0) {
    return puVar4;
  }
  local_21 = 3;
  local_1c[0] = local_20;
  Bignum_Bin2BI(puVar5[1],puVar5[2],puVar4 + 1);
  Bignum_Bin2BI(puVar5[3],puVar5[4],puVar4 + 2);
  Bignum_Bin2BI(puVar5[5],puVar5[6],puVar4 + 3);
  Bignum_Bin2BI(puVar5[7],puVar5[8],puVar4 + 4);
  if (param_1 == 0x13) {
    uVar7 = 0x20;
    puVar6 = &_LANCHOR1;
    puVar3 = &DAT_002a2060;
  }
  else if (param_1 == 0x14) {
    puVar6 = &UNK_002a2080;
    uVar7 = 0x30;
    puVar3 = &DAT_002a20b0;
  }
  else {
    if (param_1 != 0x15) goto LAB_002171c8;
    puVar6 = &DAT_002a20e0;
    uVar7 = 0x42;
    puVar3 = &DAT_002a2124;
  }
  if (puVar6 != (undefined *)0x0 && puVar3 != (undefined *)0x0) {
    Bignum_Bin2BI(puVar3,uVar7,puVar4 + 5);
    Bignum_Bin2BI(puVar6,uVar7,puVar4 + 6);
  }
LAB_002171c8:
  *(undefined1 *)((int)puVar4 + 0x25) = 1;
  Bignum_Bin2BI(&local_21,1,local_1c);
  Bignum_Init(&local_20);
  Bignum_Add(puVar4[3],local_1c[0],&local_20);
  iVar2 = Bignum_UnsignedCompare(local_20,(BIGNUM *)puVar4[1]);
  if (iVar2 == 0) {
    *(undefined1 *)(puVar4 + 9) = 1;
  }
  Bignum_Free(&local_20);
  Bignum_Free(local_1c);
  os_alloc_mem(0,puVar4 + 8,0x10);
  puVar1 = (undefined4 *)0x0;
  if ((undefined2 *)puVar4[8] != (undefined2 *)0x0) {
    *(undefined2 *)puVar4[8] = *(undefined2 *)(puVar5 + 0xf);
    *(undefined4 *)(puVar4[8] + 4) = 0;
    *(undefined4 *)(puVar4[8] + 8) = 0;
    *(undefined4 *)(puVar4[8] + 0xc) = 0;
    puVar1 = puVar4;
  }
  return puVar1;
}


// module: mt7915.ko
// function: calc_mldv2_gen_query_chksum @ 0x242ebc
// size: 564 bytes
//

void calc_mldv2_gen_query_chksum(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar6;
  undefined2 local_c2;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined4 local_6c;
  undefined4 uStack_68;
  uint uStack_64;
  undefined4 uStack_60;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 *puVar5;
  
  iVar2 = DebugLevel;
  local_b8 = CONCAT13(0xff,(uint3)*(ushort *)(param_2 + 0x1c) << 8);
  local_b8 = CONCAT31(local_b8._1_3_,*(undefined1 *)(param_2 + 0x1b)) ^ 2;
  uStack_b4 = CONCAT13(*(undefined1 *)(param_2 + 0x20),
                       CONCAT12(*(undefined1 *)(param_2 + 0x1f),
                                CONCAT11(*(undefined1 *)(param_2 + 0x1e),0xfe)));
  *(undefined4 *)(param_2 + 0x5052) = 0x80fe;
  *(undefined4 *)(param_2 + 0x5056) = 0;
  *(uint *)(param_2 + 0x505a) = local_b8;
  *(undefined4 *)(param_2 + 0x505e) = uStack_b4;
  if (3 < iVar2) {
    printk("calc_mldv2_gen_query_chksum -->");
  }
  __memzero(&local_6c,0x44);
  local_6c = 0x80fe;
  uStack_68 = 0;
  uStack_64 = local_b8;
  uStack_60 = uStack_b4;
  uVar6 = 0;
  local_5c = 0x2ff;
  uStack_58 = 0;
  uStack_54 = 0;
  uStack_50 = 0x1000000;
  local_4c = 0x1c000000;
  uStack_48 = 0x3a000000;
  local_44 = 0x82;
  uStack_40 = 0xe803;
  uStack_3c = 0;
  uStack_38 = 0;
  local_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  puVar5 = &local_6c;
  do {
    puVar4 = (undefined4 *)((int)puVar5 + 2);
    uVar6 = uVar6 + CONCAT11(*(undefined1 *)puVar5,*(undefined1 *)((int)puVar5 + 1));
    puVar5 = puVar4;
  } while (puVar4 != &uStack_28);
  uVar3 = uVar6 >> 0x10;
  uVar1 = uVar3;
  while (uVar1 != 0) {
    uVar6 = uVar3 + (uVar6 & 0xffff);
    uVar3 = 1;
    uVar1 = uVar6 >> 0x10;
  }
  uVar6 = ~(uVar6 & 0xffff);
  if ((uVar6 & 0xffff) == 0) {
    local_c2 = 0xffff;
  }
  else {
    local_c2 = (undefined2)uVar6;
  }
  if (DebugLevel < 4) {
    *(undefined2 *)(param_2 + 0x5062) = local_c2;
  }
  else {
    printk("ChkSum Done: chksum: %04x \n",local_c2);
    iVar2 = DebugLevel;
    *(undefined2 *)(param_2 + 0x5062) = local_c2;
    if (3 < iVar2) {
      printk("<----- calc_mldv2_gen_query_chksum\n");
    }
  }
  return;
}


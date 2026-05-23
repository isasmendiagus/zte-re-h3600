// module: tm.ko
// function: tm_acl_3tuple_fast_init @ 0x5ff3c
// size: 1340 bytes
//

void tm_acl_3tuple_fast_init(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_bc [16];
  ushort local_ac;
  undefined4 local_a8;
  byte local_a4;
  uint local_98;
  undefined4 local_94;
  uint local_90;
  ushort local_6e;
  ushort local_6c;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined2 local_58;
  byte local_56;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  ushort local_2a;
  undefined4 local_28;
  undefined2 local_24;
  byte local_22;
  
  memset(&local_a8,0,0x44);
  local_6c = CONCAT11(local_6c._1_1_,0x12);
  local_90 = CONCAT22(local_90._2_2_,0xffff);
  local_6c = local_6c & 0x803f | 0x2480;
  local_94 = 0xffffffff;
  local_a8 = 0x22038608;
  local_90 = local_90 & 0xf0000fff | 0xffff000;
  local_a4 = local_a4 & 0xf8 | 1;
  local_98 = CONCAT13(0xf0,(int3)local_98) & 0xff000fff | 0xff000;
  local_6e = local_6e & 0xfe0f | 0x50;
  memset(&local_64,0,0x44);
  uVar2 = local_54 & 0xf0000fff | 0xff00000;
  iVar4 = 0x14;
  local_64 = 0xe1828406;
  local_5c = 0x1e3868c;
  local_54 = CONCAT13(~((byte)~(byte)(((uVar2 >> 0x18) << 0x1c) >> 0x18) >> 4),(int3)uVar2);
  local_58 = 0x4889;
  local_56 = local_56 & 0x80 | 0x26;
  local_60 = 0x16284880;
  local_50 = 0xffffffff;
  local_4c = 0xffffffff;
  local_44 = 0xffffffff;
  local_40 = 0xffffffff;
  local_3c = 0xffffffff;
  local_48 = 0xffffffff;
  local_34 = CONCAT22(local_34._2_2_,0xffff);
  local_34 = local_34 & 0xf0000fff | 0xffff000;
  local_38 = 0xffffffff;
  local_22 = local_22 & 0xf8 | 3;
  local_2a = local_2a & 0xfe0f | 0x110;
  local_28 = 0xdb6db6db;
  local_24 = 0x6db6;
  iVar3 = 1;
  do {
    local_6e = local_6e & 0xfdff;
    cla_set_extra_rule_table(iVar4,&local_a8);
    local_6e = local_6e | 0x200;
    cla_set_extra_rule_table(iVar4 + 1,&local_a8);
    cla_get_extra_index_table(iVar3,auStack_bc);
    local_ac = local_ac | 0x10;
    cla_set_extra_index_table(iVar3,auStack_bc);
    local_2a = local_2a & 0xfdff;
    cla_set_extra_rule_table(iVar4 + 2,&local_64);
    iVar1 = iVar4 + 3;
    iVar4 = iVar4 + 0x10;
    local_2a = local_2a | 0x200;
    cla_set_extra_rule_table(iVar1,&local_64);
    cla_get_extra_index_table(iVar3,auStack_bc);
    iVar1 = iVar3 + 1;
    local_ac = local_ac | 0x40;
    cla_set_extra_index_table(iVar3,auStack_bc);
    iVar3 = iVar1;
  } while (iVar1 != 10);
  return;
}


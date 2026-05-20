// module: tm.ko
// function: tm_acl_l2_fast_init @ 0x57e10
// size: 1560 bytes
//

void tm_acl_l2_fast_init(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_c4 [16];
  ushort local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  uint local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  uint local_94;
  ushort local_76;
  uint local_74;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined2 local_60;
  undefined2 local_5e;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  ushort local_32;
  undefined4 local_30;
  undefined2 local_2c;
  ushort local_2a;
  
  memset(&local_b0,0,0x44);
  local_94 = CONCAT22(local_94._2_2_,0xffff);
  local_9c = 0xffffffff;
  local_b0 = 0x22038608;
  local_98 = 0xffffffff;
  local_a0 = CONCAT13(0xf0,(int3)local_a0) & 0xff000fff | 0xff000;
  local_ac = CONCAT22(local_ac._2_2_,1) & 0xfffe0007 | 0x58a0;
  local_76 = local_76 & 0xfe0f | 0x70;
  local_94 = local_94 & 0xf0000fff | 0xffff000;
  iVar4 = 0x11;
  local_74 = CONCAT22(local_74._2_2_,0x2492);
  local_74 = local_74 & 0xffe07fff | 0x90000;
  memset(&local_6c,0,0x44);
  local_6c = 0xe1828406;
  local_68 = 0x16284880;
  local_64 = 0x1e3868c;
  local_5e = 0x9426;
  local_60 = 0x4889;
  uVar1 = local_5c & 0xf0000fe0 | 0xff0000a;
  local_58 = 0xffffffff;
  local_54 = 0xffffffff;
  local_50 = 0xffffffff;
  local_4c = 0xffffffff;
  local_48 = 0xffffffff;
  local_5c = CONCAT13(~((byte)~(byte)(((uVar1 >> 0x18) << 0x1c) >> 0x18) >> 4),(int3)uVar1);
  local_38 = CONCAT22(local_38._2_2_,0xffff);
  local_44 = 0xffffffff;
  local_2a = CONCAT11(local_2a._1_1_,0x1b);
  local_2c = 0x6db6;
  local_30 = 0xdb6db6db;
  local_38 = local_38 & 0xf0000fff | 0xffff000;
  local_32 = local_32 & 0xfe0f | 0x130;
  local_40 = 0xffffffff;
  local_3c = 0xffffffff;
  local_2a = local_2a & 0xfe3f | 0xc0;
  iVar3 = 1;
  do {
    local_76 = local_76 & 0xfdff;
    cla_set_extra_rule_table(iVar3 << 4,&local_b0);
    local_76 = local_76 | 0x200;
    cla_set_extra_rule_table(iVar4,&local_b0);
    cla_get_extra_index_table(iVar3,auStack_c4);
    local_b4 = local_b4 | 1;
    cla_set_extra_index_table(iVar3,auStack_c4);
    local_32 = local_32 & 0xfdff;
    cla_set_extra_rule_table(iVar4 + 1,&local_6c);
    iVar2 = iVar4 + 2;
    iVar4 = iVar4 + 0x10;
    local_32 = local_32 | 0x200;
    cla_set_extra_rule_table(iVar2,&local_6c);
    cla_get_extra_index_table(iVar3,auStack_c4);
    iVar2 = iVar3 + 1;
    local_b4 = local_b4 | 4;
    cla_set_extra_index_table(iVar3,auStack_c4);
    iVar3 = iVar2;
  } while (iVar2 != 9);
  return;
}


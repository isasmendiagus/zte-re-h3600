// module: tm.ko
// function: tm_acl_fast_init @ 0x5edfc
// size: 1340 bytes
//

undefined4 tm_acl_fast_init(void)

{
  uint3 uVar1;
  undefined1 auStack_c4 [16];
  ushort local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  uint3 local_a0;
  undefined1 uStack_9d;
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
  uint local_5c;
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
  uVar1 = (uint3)_local_a0;
  local_94 = local_94 & 0xf0000fff | 0xfffffff;
  local_b0 = 0x22038608;
  local_ac = CONCAT22(local_ac._2_2_,1) & 0xfffe0007 | 0x58a0;
  local_9c = 0xffffffff;
  local_98 = 0xffffffff;
  _local_a0 = CONCAT13(0xf0,uVar1 & 0xfff | 0xff000);
  local_76 = local_76 & 0xfe0f | 0x70;
  local_74 = CONCAT22(local_74._2_2_,0x2492);
  local_74 = local_74 & 0xffe07fff | 0x90000;
  memset(&local_6c,0,0x44);
  local_6c = 0xe1828406;
  local_68 = 0x16284880;
  local_60 = 0x4889;
  local_64 = 0x1e3868c;
  local_5e = 0x9426;
  local_54 = 0xffffffff;
  local_4c = 0xffffffff;
  local_5c = local_5c & 0xf0000fe0 | 0xfff0000a;
  local_58 = 0xffffffff;
  local_50 = 0xffffffff;
  local_48 = 0xffffffff;
  local_44 = 0xffffffff;
  local_30 = 0xdb6db6db;
  local_38 = local_38 & 0xf0000fff | 0xfffffff;
  local_2a = CONCAT11(local_2a._1_1_,0x1b);
  local_2c = 0x6db6;
  local_40 = 0xffffffff;
  local_3c = 0xffffffff;
  local_32 = local_32 & 0xfe0f | 0x130;
  local_2a = local_2a & 0xfe3f | 0xc0;
  cla_set_extra_rule_table(0x90,&local_b0);
  local_76 = local_76 | 0x200;
  cla_set_extra_rule_table(0x91,&local_b0);
  cla_get_extra_index_table(9,auStack_c4);
  local_b4 = local_b4 | 1;
  cla_set_extra_index_table(9,auStack_c4);
  cla_set_extra_rule_table(2,&local_6c);
  local_32 = local_32 | 0x200;
  cla_set_extra_rule_table(3,&local_6c);
  cla_get_extra_index_table(10,auStack_c4);
  local_b4 = local_b4 | 4;
  cla_set_extra_index_table(10,auStack_c4);
  return 1;
}


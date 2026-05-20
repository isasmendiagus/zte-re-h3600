// module: mt7915.ko
// function: send_mldv2_gen_query_pkt @ 0x242c90
// size: 552 bytes
//

void send_mldv2_gen_query_pkt(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 local_c6;
  undefined2 local_c2;
  undefined4 local_c0;
  undefined2 local_bc;
  undefined2 local_ba;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 uStack_90;
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  local_c2 = 0;
  local_c0 = 0;
  local_bc = 0;
  local_ba = 0;
  iVar2 = (uint)*(byte *)(*(int *)(param_2 + 8) + 0xe) * 0x5834;
  iVar3 = param_1 + iVar2;
  local_9c = 0x60;
  local_98 = 0x1002400;
  local_78 = 0x1000000;
  local_c6 = 0;
  local_80 = 0;
  local_7c = 0;
  local_b8 = 0;
  local_b4 = 0;
  local_b0 = 0;
  local_ac = 0;
  local_84 = 0x2ff;
  local_94 = *(undefined4 *)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar3 + 0xe);
  uVar1 = *(undefined2 *)
           ("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + param_1 + iVar2 + 0x1e);
  uStack_90 = *(undefined4 *)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar3 + 0x12);
  uStack_88 = *(undefined4 *)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar3 + 0x1a);
  local_8c = *(undefined4 *)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar3 + 0x16);
  local_a8 = 0;
  local_a4 = 0;
  local_a0 = 0;
  if (3 < DebugLevel) {
    printk("send_mldv2_gen_query_pkt---->\n");
  }
  __memzero(&local_c6,0xe);
  local_c0 = *(undefined4 *)(*(int *)(param_2 + 8) + 0x1b);
  local_bc = *(undefined2 *)(*(int *)(param_2 + 8) + 0x1f);
  local_ba = TYPEIPV6;
  local_c6 = 0x3333;
  local_c2 = 0x100;
  __memzero(&local_74,0x4c);
  local_b8 = CONCAT13((char)uVar1,CONCAT12((char)((ushort)uVar1 >> 8),(undefined2)local_b8));
  local_b8 = CONCAT31(local_b8._1_3_,0x82);
  local_74 = local_9c;
  uStack_70 = local_98;
  uStack_6c = local_94;
  uStack_68 = uStack_90;
  local_b4 = CONCAT22(local_b4._2_2_,0xe803);
  local_64 = local_8c;
  uStack_60 = uStack_88;
  uStack_5c = local_84;
  uStack_58 = local_80;
  local_54 = local_7c;
  uStack_50 = local_78;
  local_44 = local_b8;
  uStack_40 = local_b4;
  uStack_3c = local_b0;
  uStack_38 = local_ac;
  local_34 = local_a8;
  uStack_30 = local_a4;
  uStack_2c = local_a0;
  uStack_4c = 0x205003a;
  uStack_48 = 0x10000;
  RTMPToWirelessSta(param_1,param_2,&local_c6,0xe,&local_74,0x4c,0);
  if (3 < DebugLevel) {
    printk("<----- send_mldv2_gen_query_pkt\n");
  }
  return;
}


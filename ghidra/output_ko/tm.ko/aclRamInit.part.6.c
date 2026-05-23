// module: tm.ko
// function: aclRamInit.part.6 @ 0x60478
// size: 600 bytes
//

undefined4 aclRamInit_part_6(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  char cVar5;
  int iVar6;
  undefined1 local_2c;
  char local_2b;
  char local_2a;
  char local_29;
  char local_28;
  char local_27;
  char local_26;
  char local_25;
  char local_24;
  char local_23;
  char local_22;
  char local_21;
  char local_20;
  char local_1f;
  char local_1e;
  char local_1d;
  undefined2 local_1c;
  byte local_1a;
  
  __memzero(&local_2c,0x14);
  __memzero(0xf1020000,0x400000);
  __memzero(0xf1420000,0x100000);
  iVar6 = 1;
  cVar5 = '\x11';
  do {
    local_2a = cVar5 + '\x01';
    local_1c = 0;
    if (iVar6 == 10) {
      local_29 = '\x03';
      local_28 = '\x04';
      local_27 = '\x05';
      local_26 = '\x06';
      local_25 = '\a';
      local_24 = '\b';
      local_23 = '\t';
      local_21 = '\v';
      local_2c = 0;
      local_2b = '\x01';
      local_2a = '\x02';
      local_22 = '\n';
      local_20 = '\f';
      local_1f = '\r';
      local_1e = '\x0e';
      local_1d = '\x0f';
LAB_000606c0:
      local_1a = local_1a & 0xf3 | 0x15;
    }
    else {
      local_29 = cVar5 + '\x02';
      local_28 = cVar5 + '\x03';
      local_27 = cVar5 + '\x04';
      local_26 = cVar5 + '\x05';
      local_25 = cVar5 + '\x06';
      local_24 = cVar5 + '\a';
      local_23 = cVar5 + '\b';
      local_22 = cVar5 + '\t';
      local_21 = cVar5 + '\n';
      local_20 = cVar5 + '\v';
      local_1f = cVar5 + '\f';
      local_1e = cVar5 + '\r';
      local_2c = (undefined1)(iVar6 << 4);
      local_1d = cVar5 + '\x0e';
      local_2b = cVar5;
      if (iVar6 - 9U < 2) goto LAB_000606c0;
      local_1a = local_1a & 0xf3 | 0x19;
    }
    iVar1 = cla_set_extra_index_table(iVar6,&local_2c);
    cVar5 = cVar5 + '\x10';
    iVar6 = iVar6 + 1;
    if (iVar1 != 0) {
      printk("ERROR:(%s:%d)","tm_acl_v2.c",0x2a5);
      printk("cla_set_extra_index_table fail\n");
      return 0xfffffff4;
    }
    if (iVar6 == 0xb) {
      puVar3 = sa_rulesRecord;
      do {
        puVar2 = (undefined4 *)((int)puVar3 + 0x100);
        puVar4 = (undefined4 *)puVar3;
        do {
          *puVar4 = 0;
          puVar3 = (undefined1 *)(puVar4 + 4);
          puVar4[1] = 0;
          puVar4[2] = 0;
          puVar4[3] = 0;
          puVar4 = (undefined4 *)puVar3;
        } while ((undefined4 *)puVar3 != puVar2);
      } while (puVar3 != g_v4OutUsed);
      __memzero(s_aclHashUsedCnt,0x10208);
      if (g_fast_opti != 0) {
        tm_acl_3tuple_fast_init();
        tm_acl_fast_init();
      }
      cla_get_outspace_cfg(&ACL_OUT_HASH_NUM,&ACL_OUT_SPACE_SEL);
      g_aclRamInited = 1;
      return 0;
    }
  } while( true );
}


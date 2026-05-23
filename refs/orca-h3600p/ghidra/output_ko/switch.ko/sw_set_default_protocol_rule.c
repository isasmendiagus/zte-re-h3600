// module: switch.ko
// function: sw_set_default_protocol_rule @ 0x13460
// size: 704 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_set_default_protocol_rule(void)

{
  sbyte sVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  uint uVar6;
  sbyte *local_38;
  undefined1 auStack_30 [12];
  
  puVar2 = (undefined1 *)kmem_cache_alloc(_DAT_0002c350,0x20);
  if (puVar2 == (undefined1 *)0x0) {
    printk("switch ERR: sw_set_default_protocol_rule alloc mem failed\n");
  }
  else {
    puVar5 = puVar2 + 0x1f;
    __memzero(puVar2,0x49c);
    __memzero(auStack_30,8);
    *(undefined2 *)(puVar2 + 2) = 0;
    puVar2[600] = 0;
    *puVar2 = 100;
    puVar2[1] = 0x2f;
    *(undefined4 *)(puVar2 + 0x24c) = 3;
    puVar2[8] = 1;
    *(undefined4 *)(puVar2 + 4) = 1;
    *(undefined4 *)(puVar2 + 0x250) = 1;
    puVar2[0x256] = 3;
    *(undefined4 *)(puVar2 + 0xc) = 2;
    puVar4 = puVar5;
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar2 + 0x2f);
    puVar2[0x1a] = 1;
    puVar2[0x2a] = 0xff;
    puVar2[0x1c] = 0xc2;
    puVar2[0x2b] = 0xff;
    puVar2[0x2c] = 0xff;
    puVar2[0x1b] = 0x80;
    iVar3 = zte_api_sw_qos_add_port_streamselect(puVar2,auStack_30);
    if (iVar3 == 0) {
      *(undefined4 *)(puVar2 + 0xc) = 0xd;
      do {
        puVar5 = puVar5 + 1;
        *puVar5 = 0;
      } while (puVar5 != puVar2 + 0x2f);
      puVar2[0x1d] = 0;
      puVar2[0x1e] = 0;
      puVar2[0x1f] = 0;
      puVar2[0x2f] = 0;
      puVar2[0x1c] = 0xe0;
      puVar2[0x2c] = 0xff;
      puVar2[0x2d] = 0xff;
      puVar2[0x2e] = 0xff;
      iVar3 = zte_api_sw_qos_add_port_streamselect(puVar2,auStack_30);
      if (iVar3 == 0) {
        puVar2[8] = 2;
        puVar2[0x256] = 2;
        *(undefined4 *)(puVar2 + 4) = 0;
        puVar2[600] = 0;
        *(undefined4 *)(puVar2 + 0x250) = 0;
        *(undefined4 *)(puVar2 + 0x24c) = 3;
        __memzero(puVar2 + 0xc,0x240);
        uVar6 = _tm_port_unknwn_multicast_floodport_set;
        *(undefined4 *)(puVar2 + 0xc) = 0;
        if (uVar6 != 0) {
          local_38 = (sbyte *)((int)&proc_create_data + 3);
          uVar6 = 0;
          do {
            local_38 = local_38 + 1;
            sVar1 = *local_38;
            puVar2[0x2f] = 0xff;
            puVar2[0x1f] = (char)(1 << sVar1);
            *(undefined4 *)(puVar2 + 0x30) = 2;
            puVar4 = puVar2 + 0x43;
            do {
              puVar4 = puVar4 + 1;
              *puVar4 = 0;
            } while (puVar4 != puVar2 + 0x53);
            puVar2[0x3f] = 0x80;
            puVar2[0x3e] = 1;
            puVar2[0x4e] = 0xff;
            puVar2[0x4f] = 0xff;
            puVar2[0x50] = 0xff;
            puVar2[0x40] = 0xc2;
            iVar3 = zte_api_sw_qos_add_port_streamselect(puVar2,auStack_30);
            if (iVar3 != 0) {
              printk("sw_set_default_protocol_rule failed!\n");
              kfree(puVar2);
              return 0xffffffff;
            }
            *(undefined4 *)(puVar2 + 0x30) = 0xd;
            puVar4 = puVar2 + 0x43;
            do {
              puVar4 = puVar4 + 1;
              *puVar4 = 0;
            } while (puVar4 != puVar2 + 0x53);
            puVar2[0x41] = 0;
            puVar2[0x42] = 0;
            puVar2[0x43] = 0;
            puVar2[0x53] = 0;
            puVar2[0x40] = 0xe0;
            puVar2[0x50] = 0xff;
            puVar2[0x51] = 0xff;
            puVar2[0x52] = 0xff;
            iVar3 = zte_api_sw_qos_add_port_streamselect(puVar2,auStack_30);
            if (iVar3 != 0) goto LAB_000136e8;
            uVar6 = uVar6 + 1;
          } while (uVar6 < _tm_port_unknwn_multicast_floodport_set);
        }
        kfree(puVar2);
        return 0;
      }
    }
LAB_000136e8:
    printk("sw_set_default_protocol_rule failed!\n");
    kfree(puVar2);
  }
  return 0xffffffff;
}


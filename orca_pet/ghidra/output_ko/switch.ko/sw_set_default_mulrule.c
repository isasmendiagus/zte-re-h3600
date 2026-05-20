// module: switch.ko
// function: sw_set_default_mulrule @ 0x1329c
// size: 452 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_set_default_mulrule(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 auStack_28 [12];
  
  puVar1 = (undefined1 *)kmem_cache_alloc(_DAT_0002c350,0x20);
  if (puVar1 == (undefined1 *)0x0) {
    printk("switch ERR: sw_set_default_mulrule alloc mem failed\n");
    uVar3 = 0xffffffff;
  }
  else {
    puVar5 = puVar1 + 0x1f;
    __memzero(puVar1,0x49c);
    __memzero(auStack_28,8);
    puVar1[1] = 0;
    *(undefined2 *)(puVar1 + 2) = 0;
    *puVar1 = 100;
    *(undefined4 *)(puVar1 + 4) = 1;
    puVar1[8] = 1;
    *(undefined4 *)(puVar1 + 0xc) = 2;
    puVar4 = puVar5;
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar1 + 0x2f);
    puVar1[0x1b] = 0;
    puVar1[600] = 0;
    puVar1[0x1a] = 1;
    *(undefined4 *)(puVar1 + 0x250) = 1;
    puVar1[0x2a] = 0xff;
    puVar1[0x2b] = 0xff;
    puVar1[0x2c] = 0xff;
    puVar1[0x1c] = 0x5e;
    *(undefined4 *)(puVar1 + 0x24c) = 3;
    puVar1[0x256] = 5;
    iVar2 = zte_api_sw_qos_add_port_streamselect(puVar1,auStack_28);
    if (iVar2 == 0) {
      __memzero(puVar1,0x49c);
      __memzero(auStack_28,8);
      puVar1[1] = 0;
      *(undefined2 *)(puVar1 + 2) = 0;
      *(undefined4 *)(puVar1 + 4) = 1;
      puVar1[8] = 1;
      *puVar1 = 100;
      *(undefined4 *)(puVar1 + 0xc) = 2;
      do {
        puVar5 = puVar5 + 1;
        *puVar5 = 0;
      } while (puVar5 != puVar1 + 0x2f);
      puVar1[600] = 0;
      puVar1[0x1a] = 0x33;
      puVar1[0x1b] = 0x33;
      puVar1[0x2a] = 0xff;
      puVar1[0x2b] = 0xff;
      *(undefined4 *)(puVar1 + 0x24c) = 3;
      *(undefined4 *)(puVar1 + 0x250) = 1;
      puVar1[0x256] = 5;
      iVar2 = zte_api_sw_qos_add_port_streamselect(puVar1,auStack_28);
      if (iVar2 == 0) {
        kfree(puVar1);
        uVar3 = 0;
      }
      else {
        printk("sw_set_default_ipv6_mulrule failed!\n");
        kfree(puVar1);
        uVar3 = 0xffffffff;
      }
    }
    else {
      printk("sw_set_default_ipv4_mulrule failed!\n");
      kfree(puVar1);
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}


// module: switch.ko
// function: sw_igmp_mulrule_deal @ 0x1f7b4
// size: 440 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_igmp_mulrule_deal(undefined4 param_1,int param_2,int param_3)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 auStack_20 [12];
  
  puVar1 = (undefined1 *)kmem_cache_alloc(_DAT_0002c340,0x20);
  if (puVar1 == (undefined1 *)0x0) {
    printk("switch ERR: sw_set_default_mulrule alloc mem failed\n");
    uVar3 = 0xffffffff;
  }
  else {
    __memzero(puVar1,0x49c);
    __memzero(auStack_20,8);
    puVar4 = puVar1 + 0x1f;
    *(undefined2 *)(puVar1 + 2) = 0;
    puVar1[1] = 0xf;
    *puVar1 = 100;
    puVar1[8] = 3;
    *(undefined4 *)(puVar1 + 4) = 1;
    *(undefined4 *)(puVar1 + 0xc) = 0xd;
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar1 + 0x2f);
    puVar4 = puVar1 + 0x43;
    puVar1[0x1f] = (char)param_1;
    puVar1[0x1c] = (char)((uint)param_1 >> 0x18);
    puVar1[0x2c] = 0xff;
    puVar1[0x2d] = 0xff;
    puVar1[0x2e] = 0xff;
    puVar1[0x2f] = 0xff;
    puVar1[0x1d] = (char)((uint)param_1 >> 0x10);
    puVar1[0x1e] = (char)((uint)param_1 >> 8);
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar1 + 0x53);
    puVar1[0x43] = (char)param_2;
    if (param_2 != 0) {
      *(undefined4 *)(puVar1 + 0x30) = 6;
    }
    puVar1[0x53] = 0xff;
    puVar4 = puVar1 + 0x67;
    if (param_2 != 0) {
      puVar1[0x42] = (char)((uint)param_2 >> 8);
    }
    else {
      *(undefined4 *)(puVar1 + 0x30) = 4;
    }
    do {
      puVar4 = puVar4 + 1;
      *puVar4 = 0;
    } while (puVar4 != puVar1 + 0x77);
    puVar1[600] = 0;
    *(undefined4 *)(puVar1 + 0x54) = 2;
    puVar1[0x72] = 0xff;
    puVar1[0x62] = 1;
    *(undefined4 *)(puVar1 + 0x24c) = 1;
    *(undefined4 *)(puVar1 + 0x250) = 1;
    puVar1[0x256] = 5;
    if (param_3 == 1) {
      iVar2 = zte_api_sw_qos_add_port_streamselect(puVar1,auStack_20);
    }
    else {
      iVar2 = zte_api_sw_qos_del_port_streamselect();
    }
    if (iVar2 == 0) {
      kfree(puVar1);
      uVar3 = 0;
    }
    else {
      printk("zte_api_sw_qos_add_port_streamselect failed!\n");
      kfree(puVar1);
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}


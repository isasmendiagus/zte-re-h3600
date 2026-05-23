// module: plat-zxylzb_9128S.ko
// function: pon_tm_net_register @ 0x19144
// size: 204 bytes
//

char * pon_tm_net_register(undefined4 param_1,char *param_2)

{
  char *__dest;
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  __dest = (char *)alloc_etherdev_mqs(0xf8,1,1);
  if (__dest == (char *)0x0) {
    return (char *)0x0;
  }
  *(char **)(__dest + 0x4c0) = __dest;
  *(undefined4 *)(__dest + 0x4c8) = param_1;
  *(undefined1 **)(__dest + 300) = &pon_tm_net_netdev_ops;
  uVar1 = msecs_to_jiffies(5000);
  *(undefined4 *)(__dest + 600) = uVar1;
  strcpy(__dest,param_2);
  iVar2 = strncmp(__dest,"omci",4);
  uVar1 = default_mac;
  puVar3 = *(undefined4 **)(__dest + 0x1dc);
  if (iVar2 == 0) {
    __dest[0x14c] = -0x30;
    __dest[0x14d] = '\a';
    __dest[0x14e] = '\0';
    __dest[0x14f] = '\0';
  }
  *puVar3 = uVar1;
  net_lock_tx = 0;
  net_lock_stack = 0;
  *(undefined2 *)(puVar3 + 1) = DAT_00021ee8;
  iVar2 = register_netdev(__dest);
  if (iVar2 < 0) {
    free_netdev(__dest);
    return (char *)0x0;
  }
  return __dest;
}


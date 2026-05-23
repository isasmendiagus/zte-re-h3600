// module: plat-zxylzb_9128S.ko
// function: idm_net_register @ 0x14f2c
// size: 196 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * idm_net_register(undefined4 param_1,char *param_2)

{
  char *__dest;
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  __dest = (char *)alloc_etherdev_mqs(0xf0,1,1);
  if (__dest == (char *)0x0) {
    return (char *)0x0;
  }
  *(char **)(__dest + 0x4c0) = __dest;
  *(undefined4 *)(__dest + 0x4c4) = param_1;
  *(undefined1 **)(__dest + 300) = &idm_net_netdev_ops;
  uVar1 = msecs_to_jiffies(5000);
  *(undefined4 *)(__dest + 600) = uVar1;
  strcpy(__dest,param_2);
  puVar3 = *(undefined4 **)(__dest + 0x1dc);
  _DAT_00021d84 = CONCAT11((char)param_1,DAT_00021d84);
  *puVar3 = idm_mac;
  idm_lock_stack = 0;
  idm_lock_tx = 0;
  *(undefined2 *)(puVar3 + 1) = _DAT_00021d84;
  DAT_00028c28 = 0;
  DAT_00028c2c = 0;
  idm_lock_tx_done = 0;
  iVar2 = register_netdev(__dest);
  if (-1 < iVar2) {
    return __dest;
  }
  free_netdev(__dest);
  return (char *)0x0;
}


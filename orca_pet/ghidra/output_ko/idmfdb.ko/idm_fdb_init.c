// module: idmfdb.ko
// function: idm_fdb_init @ 0x12760
// size: 104 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 idm_fdb_init(void)

{
  undefined4 in_r3;
  
  idm_skb_recv = idm_fdb_forward;
  __memzero(&idm_flood_cnt,0x210,idm_fdb_forward,&idm_skb_recv,in_r3);
  register_netdevice_notifier(&idm_netdev_notifier);
  ___dev_kfree_skb_any = idm_fdb_hook_xmit;
  _WlanIndex2WlanIdmMap = 0x10000;
  SUB_0001907c = register_idm_fdb_node_bydev;
  return 0;
}


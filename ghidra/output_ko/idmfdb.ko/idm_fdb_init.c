// module: idmfdb.ko
// function: idm_fdb_init @ 0x1261c
// size: 60 bytes
//

undefined4 idm_fdb_init(void)

{
  undefined4 in_r3;
  
  idm_skb_recv = idm_fdb_forward;
  __memzero(&idm_flood_cnt,0x210,idm_fdb_forward,&idm_skb_recv,in_r3);
  register_netdevice_notifier(&idm_netdev_notifier);
  return 0;
}


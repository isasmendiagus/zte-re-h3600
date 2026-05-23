// module: idmfdb.ko
// function: idm_fdb_exit @ 0x10d38
// size: 20 bytes
//

void idm_fdb_exit(void)

{
  idm_skb_recv = 0;
  return;
}


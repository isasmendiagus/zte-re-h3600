// module: idmfdb.ko
// function: idm_fdb_exit @ 0x10e10
// size: 40 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void idm_fdb_exit(void)

{
  idm_skb_recv = 0;
  ___dev_kfree_skb_any = 0;
  _WlanIndex2WlanIdmMap = 0;
  SUB_0001907c = 0;
  return;
}


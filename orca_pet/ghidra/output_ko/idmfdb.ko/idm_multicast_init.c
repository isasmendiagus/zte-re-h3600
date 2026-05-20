// module: idmfdb.ko
// function: idm_multicast_init @ 0x11aa0
// size: 28 bytes
//

undefined4
idm_multicast_init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  __memzero(&g_mtrans_dbg_cnt,0x2400,param_3,param_4,param_4);
  return 0;
}


// module: idmfdb.ko
// function: cleanup_module @ 0x126f8
// size: 24 bytes
//

void cleanup_module(void)

{
  idm_fdb_exit();
  idm_proc_exit();
  idm_multicast_exit();
  idm_led_exit();
  return;
}


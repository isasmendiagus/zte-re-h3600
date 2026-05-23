// module: idmfdb.ko
// function: init_module @ 0x12744
// size: 28 bytes
//

undefined4 init_module(void)

{
  idm_fdb_init();
  idm_proc_init();
  idm_multicast_init();
  idm_led_init();
  return 0;
}


// module: tm.ko
// function: api_lock_init @ 0x65184
// size: 24 bytes
//

void api_lock_init(void)

{
  fast_api_busy_lock = 0;
  acl_api_lock = 0;
  return;
}


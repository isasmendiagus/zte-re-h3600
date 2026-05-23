// module: plat-zxylzb_9128S.ko
// function: is_red_alloc_bp_empty @ 0x1a89c
// size: 76 bytes
//

bool is_red_alloc_bp_empty(undefined4 param_1)

{
  uint local_1c;
  uint local_18;
  
  local_1c = 0;
  local_18 = 0;
  red_get_queue_cfg();
  red_get_queue_status(param_1,&local_1c);
  return (local_18 & 0xfff) <= (local_1c & 0xfff);
}


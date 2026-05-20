// module: switch.ko
// function: l3_hardfastReg @ 0x12404
// size: 108 bytes
//

void l3_hardfastReg(void)

{
  code *local_28;
  code *local_24;
  code *local_20;
  code *local_1c;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;
  
  local_28 = hf_set_l3_entry;
  local_24 = hf_del_l3_entry;
  local_20 = hf_query_l3_status;
  local_1c = hf_entry_police2;
  __memzero(&local_18,0x10);
  local_18 = 0x14;
  local_16 = 0x14;
  local_14 = 0x14;
  local_12 = 0x14;
  npu_hff_register(&local_28,&local_18);
  return;
}


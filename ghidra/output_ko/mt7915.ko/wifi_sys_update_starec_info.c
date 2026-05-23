// module: mt7915.ko
// function: wifi_sys_update_starec_info @ 0x104de0
// size: 76 bytes
//

undefined4 wifi_sys_update_starec_info(undefined4 param_1,void *param_2)

{
  int iVar1;
  int local_10;
  int local_c;
  
  iVar1 = *(int *)((int)param_2 + 0xcc);
  os_move_mem((void *)(iVar1 + 0x3e0),param_2,0xd0);
  local_10 = *(int *)(iVar1 + 4);
  local_c = iVar1;
  mt_notify_call_chain(*(int *)(local_10 + 8) + 0xa7bef8,6,&local_10);
  return 0;
}


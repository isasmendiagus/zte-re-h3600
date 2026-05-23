// module: mt7915.ko
// function: sae_send_auth_confirm @ 0x20a440
// size: 344 bytes
//

undefined4 sae_send_auth_confirm(undefined4 param_1,int param_2)

{
  void *pvVar1;
  void *__dest;
  void *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_3c = (void *)0x0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_send_auth_confirm");
  }
  os_alloc_mem(param_1,&local_3c,0x402);
  pvVar1 = local_3c;
  if (local_3c == (void *)0x0) {
    return 0;
  }
  if (*(short *)(param_2 + 4) != -1) {
    *(short *)(param_2 + 4) = *(short *)(param_2 + 4) + 1;
  }
  __dest = (void *)((int)local_3c + 2);
  memmove(local_3c,(void *)(param_2 + 4),2);
  if (*(int *)(param_2 + 0x98) != 0) {
    (**(code **)(*(int *)(param_2 + 0x98) + 8))(param_2,1,&local_38);
  }
  memmove(__dest,&local_38,0x20);
  hex_dump_with_lvl("confirm(pos):",__dest,0x20,SAE_DEBUG_LEVEL);
  sae_send_auth(param_1,param_2 + 0x160,param_2 + 0x166,param_2 + 0x16c,3,2,0,local_3c,
                (int)pvVar1 + (0x22 - (int)local_3c));
  os_free_mem(local_3c);
  return 1;
}


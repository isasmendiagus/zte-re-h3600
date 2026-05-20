// module: mt7915.ko
// function: wext_send_btm_query_event_newapi @ 0x22473c
// size: 196 bytes
//

void wext_send_btm_query_event_newapi
               (undefined4 param_1,undefined4 *param_2,void *param_3,size_t param_4)

{
  undefined2 uVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 *local_24;
  
  uVar4 = param_4 + 0x13 & 0xffff;
  os_alloc_mem(0,&local_24,uVar4);
  if (local_24 != (undefined1 *)0x0) {
    if (uVar4 != 0) {
      __memzero(local_24,uVar4);
    }
    puVar2 = local_24;
    *(size_t *)(local_24 + 1) = param_4 + 0xe;
    *local_24 = 1;
    uVar3 = RtmpOsGetNetIfIndex(param_1);
    *(undefined4 *)(puVar2 + 5) = uVar3;
    *(undefined4 *)(puVar2 + 9) = *param_2;
    uVar1 = *(undefined2 *)(param_2 + 1);
    *(size_t *)(puVar2 + 0xf) = param_4;
    *(undefined2 *)(puVar2 + 0xd) = uVar1;
    memcpy(puVar2 + 0x13,param_3,param_4);
    RtmpOSWrielessEventSend(param_1,1,0x94b,0,local_24,uVar4);
    os_free_mem(local_24);
  }
  return;
}


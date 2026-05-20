// module: mt7915.ko
// function: wext_send_anqp_req_event @ 0x22bac8
// size: 188 bytes
//

void wext_send_anqp_req_event(undefined4 param_1,undefined4 *param_2,void *param_3,size_t param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *local_24 [2];
  
  uVar3 = param_4 + 0x10 & 0xffff;
  os_alloc_mem(0,local_24,uVar3);
  if (local_24[0] != (undefined4 *)0x0) {
    if (uVar3 != 0) {
      __memzero(local_24[0],uVar3);
    }
    puVar1 = local_24[0];
    uVar2 = RtmpOsGetNetIfIndex(param_1);
    *puVar1 = uVar2;
    puVar1[1] = *param_2;
    *(undefined2 *)(puVar1 + 2) = *(undefined2 *)(param_2 + 1);
    puVar1[3] = param_4;
    memcpy(puVar1 + 4,param_3,param_4);
    RtmpOSWrielessEventSend(param_1,1,0x923,0,local_24[0],uVar3);
    os_free_mem(local_24[0]);
  }
  return;
}


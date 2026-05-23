// module: mt7915.ko
// function: wext_send_nr_req_event @ 0x221898
// size: 180 bytes
//

void wext_send_nr_req_event(undefined4 param_1,undefined4 *param_2,void *param_3,size_t param_4)

{
  undefined2 uVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 *local_24 [2];
  
  iVar4 = param_4 + 0x13;
  os_alloc_mem(0,local_24,iVar4);
  if (local_24[0] != (undefined1 *)0x0) {
    __memzero(local_24[0],iVar4);
    puVar2 = local_24[0];
    *local_24[0] = 2;
    *(size_t *)(local_24[0] + 1) = param_4 + 0xe;
    uVar3 = RtmpOsGetNetIfIndex(param_1);
    *(undefined4 *)(puVar2 + 5) = uVar3;
    *(undefined4 *)(puVar2 + 9) = *param_2;
    uVar1 = *(undefined2 *)(param_2 + 1);
    *(size_t *)(puVar2 + 0xf) = param_4;
    *(undefined2 *)(puVar2 + 0xd) = uVar1;
    memcpy(puVar2 + 0x13,param_3,param_4);
    RtmpOSWrielessEventSend(param_1,1,0x94d,0,local_24[0],iVar4);
    os_free_mem(local_24[0]);
  }
  return;
}


// module: mt7915.ko
// function: wext_send_btm_cfm_event @ 0x224f50
// size: 184 bytes
//

void wext_send_btm_cfm_event(undefined4 param_1,undefined4 *param_2,void *param_3,size_t param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *local_24 [2];
  
  uVar3 = param_4 + 0xe & 0xffff;
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
    *(size_t *)((int)puVar1 + 10) = param_4;
    memcpy((void *)((int)puVar1 + 0xe),param_3,param_4);
    RtmpOSWrielessEventSend(param_1,1,0x93a,0,local_24[0],uVar3);
    os_free_mem(local_24[0]);
  }
  return;
}


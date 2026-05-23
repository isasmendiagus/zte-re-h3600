// module: mt7915.ko
// function: wext_send_bcn_rsp_event @ 0x222764
// size: 244 bytes
//

void wext_send_bcn_rsp_event
               (undefined4 param_1,undefined4 *param_2,void *param_3,size_t param_4,
               undefined1 param_5)

{
  undefined2 uVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 *local_24;
  
  if (2 < DebugLevel) {
    printk(&_LC50,"wext_send_bcn_rsp_event");
  }
  iVar4 = param_4 + 0x14;
  os_alloc_mem(0,&local_24,iVar4);
  if (local_24 != (undefined1 *)0x0) {
    if (iVar4 != 0) {
      __memzero(local_24,iVar4);
    }
    puVar2 = local_24;
    local_24[5] = param_5;
    *(size_t *)(local_24 + 1) = param_4 + 0xf;
    *local_24 = 1;
    uVar3 = RtmpOsGetNetIfIndex(param_1);
    *(undefined4 *)(puVar2 + 6) = uVar3;
    *(undefined4 *)(puVar2 + 10) = *param_2;
    uVar1 = *(undefined2 *)(param_2 + 1);
    *(size_t *)(puVar2 + 0x10) = param_4;
    *(undefined2 *)(puVar2 + 0xe) = uVar1;
    memcpy(puVar2 + 0x14,param_3,param_4);
    RtmpOSWrielessEventSend(param_1,1,0x94d,0,local_24,iVar4);
    os_free_mem(local_24);
  }
  return;
}


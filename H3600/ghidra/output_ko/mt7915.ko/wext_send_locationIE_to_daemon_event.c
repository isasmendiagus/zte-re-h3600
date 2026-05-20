// module: mt7915.ko
// function: wext_send_locationIE_to_daemon_event @ 0x22ba24
// size: 160 bytes
//

void wext_send_locationIE_to_daemon_event
               (undefined4 param_1,void *param_2,size_t param_3,undefined2 param_4)

{
  uint uVar1;
  undefined2 *local_1c;
  
  uVar1 = param_3 + 4 & 0xffff;
  os_alloc_mem(0,&local_1c,uVar1);
  if (local_1c != (undefined2 *)0x0) {
    if (uVar1 != 0) {
      __memzero(local_1c,uVar1);
    }
    *(char *)(local_1c + 1) = (char)param_3;
    *local_1c = param_4;
    memcpy((void *)((int)local_1c + 3),param_2,param_3);
    RtmpOSWrielessEventSend(param_1,1,0x948,0,local_1c,uVar1);
    os_free_mem(local_1c);
  }
  return;
}


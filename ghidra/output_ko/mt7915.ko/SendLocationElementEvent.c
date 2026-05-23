// module: mt7915.ko
// function: SendLocationElementEvent @ 0x22bac4
// size: 4 bytes
//

void SendLocationElementEvent(undefined4 param_1,void *param_2,size_t param_3,undefined2 param_4)

{
  uint uVar1;
  undefined2 *puStack_1c;
  
  uVar1 = param_3 + 4 & 0xffff;
  os_alloc_mem(0,&puStack_1c,uVar1);
  if (puStack_1c != (undefined2 *)0x0) {
    if (uVar1 != 0) {
      __memzero(puStack_1c,uVar1);
    }
    *(char *)(puStack_1c + 1) = (char)param_3;
    *puStack_1c = param_4;
    memcpy((void *)((int)puStack_1c + 3),param_2,param_3);
    RtmpOSWrielessEventSend(param_1,1,0x948,0,puStack_1c,uVar1);
    os_free_mem(puStack_1c);
  }
  return;
}


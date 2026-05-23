// module: mt7915.ko
// function: PeerBAAction @ 0xa179c
// size: 116 bytes
//

void PeerBAAction(undefined4 param_1,int param_2)

{
  char cVar1;
  
  if ((*(byte *)(param_2 + 1) & 0x80) != 0) {
    memmove((void *)(param_2 + 0x18),(void *)(param_2 + 0x1c),*(int *)(param_2 + 0x908) - 4);
  }
  cVar1 = *(char *)(param_2 + 0x19);
  if (cVar1 == '\x01') {
    peer_addba_rsp_action(param_1,param_2);
    return;
  }
  if (cVar1 == '\0') {
    peer_addba_req_action(param_1,param_2);
    return;
  }
  if (cVar1 != '\x02') {
    return;
  }
  peer_delba_action(param_1,param_2);
  return;
}


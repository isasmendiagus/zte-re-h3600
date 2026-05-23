// module: mt7915.ko
// function: WaitPeerBTMReqTimeout @ 0x227500
// size: 168 bytes
//

void WaitPeerBTMReqTimeout(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined1 local_24;
  undefined1 auStack_23 [8];
  undefined1 local_1b;
  
  if (0 < DebugLevel) {
    printk(&_LC6,"WaitPeerBTMReqTimeout");
  }
  iVar1 = *(int *)(param_2 + 0x14);
  if ((*(uint *)(iVar1 + 0xa39f84) & 0x140) != 0) {
    return;
  }
  os_zero_mem(&local_24,0xc);
  os_move_mem(auStack_23,(void *)(param_2 + 0xd),6);
  local_24 = *(undefined1 *)(param_2 + 0xc);
  local_1b = *(undefined1 *)(param_2 + 0x13);
  MlmeEnqueue(iVar1,0x28,8,0xc,&local_24,0);
  return;
}


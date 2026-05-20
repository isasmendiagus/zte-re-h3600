// module: mt7915.ko
// function: WaitPeerBCNRepTimeout @ 0x223290
// size: 136 bytes
//

void WaitPeerBCNRepTimeout(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined1 uStack_1a;
  undefined1 local_19;
  undefined1 auStack_18 [6];
  undefined2 local_12;
  
  if (2 < DebugLevel) {
    printk(&_LC50,"WaitPeerBCNRepTimeout");
  }
  uVar1 = *(undefined4 *)(param_2 + 0x10);
  __memzero(&uStack_1a,10);
  local_19 = *(undefined1 *)(param_2 + 9);
  RTMPMoveMemory(auStack_18,param_2 + 0x48,6);
  local_12 = 0;
  MlmeEnqueue(uVar1,0x31,2,10,&uStack_1a,0);
  return;
}


// module: mt7915.ko
// function: MtAndesAppendCmdMsg @ 0x1aca60
// size: 4 bytes
//

void MtAndesAppendCmdMsg(int param_1,void *param_2,size_t param_3,undefined4 param_4)

{
  void *__dest;
  
  if (param_1 == 0) {
    return;
  }
  if (param_2 == (void *)0x0) {
    return;
  }
  __dest = (void *)skb_put(*(undefined4 *)(param_1 + 0x20),param_3,param_3,param_4,param_4);
  memcpy(__dest,param_2,param_3);
  return;
}


// module: mt7915.ko
// function: AndesAppendHeadCmdMsg @ 0x1a42b0
// size: 48 bytes
//

void AndesAppendHeadCmdMsg(int param_1,void *param_2,size_t param_3,undefined4 param_4)

{
  void *__dest;
  
  if (param_2 == (void *)0x0) {
    return;
  }
  __dest = (void *)skb_push(*(undefined4 *)(param_1 + 0x20),param_3,param_3,param_4,param_4);
  memcpy(__dest,param_2,param_3);
  return;
}


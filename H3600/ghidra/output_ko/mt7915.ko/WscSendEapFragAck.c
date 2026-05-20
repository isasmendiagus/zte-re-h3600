// module: mt7915.ko
// function: WscSendEapFragAck @ 0x2017a8
// size: 288 bytes
//

void WscSendEapFragAck(int param_1,int *param_2,int *param_3)

{
  if (param_3 == (int *)0x0) {
    printk(&_LC6,0x165);
    dump_stack();
    return;
  }
  if (*param_3 == 0x20001) {
    *(undefined1 *)(param_2 + 0xafe) = 1;
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      WscSendMessage(param_1,6,0,0,param_2,0,1);
    }
    else {
      if (((*(uint *)(param_1 + 0x795124) & 2) == 0) || (*param_2 != 4)) {
        WscSendMessage(param_1,6,0,0,param_2,2,2);
        return;
      }
      WscSendMessage(param_1,6,0,0,param_2,2,1);
    }
  }
  else if (*param_3 == 2) {
    WscSendMessage(param_1,6,0,0,param_2,1,2);
    return;
  }
  return;
}


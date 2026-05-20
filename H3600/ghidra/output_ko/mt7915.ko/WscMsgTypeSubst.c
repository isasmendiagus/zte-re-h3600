// module: mt7915.ko
// function: WscMsgTypeSubst @ 0x1e12c0
// size: 100 bytes
//

undefined4 WscMsgTypeSubst(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  if (param_1 == 0) {
    *param_3 = 0x22;
    return 1;
  }
  if (param_1 != 1) {
    if (DebugLevel < 3) {
      return 0;
    }
    printk("WscMsgTypeSubst : unsupported EAP Type(%d);\n",param_1,param_3,DebugLevel,param_4);
    return 0;
  }
  *param_3 = 0x23;
  return 1;
}


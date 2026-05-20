// module: mt7915.ko
// function: MtAsicSetWdevIfAddr @ 0x19af7c
// size: 132 bytes
//

void MtAsicSetWdevIfAddr(int param_1,int param_2,int param_3)

{
  if (param_3 == 1) {
    if ((*(int *)(&DAT_003678e8 + param_1) == 0) && (*(int *)(&DAT_003678ec + param_1) == 0)) {
      MtAsicSetMbssWdevIfAddrGen2();
      return;
    }
    MtAsicSetMbssWdevIfAddrGen3(param_1,param_2);
    return;
  }
  if (param_3 == 0) {
    MtAsicSetApcliWdevIfAddr();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: wdev(%d) non-supported opmode(%d)\n","MtAsicSetWdevIfAddr",
         *(undefined1 *)(param_2 + 0xc));
  return;
}


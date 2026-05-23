// module: mt7915.ko
// function: Show_MATTable_Proc @ 0x34480
// size: 156 bytes
//

undefined4 Show_MATTable_Proc(int param_1)

{
  param_1 = param_1 + 0x794b28;
  dumpIPMacTb(param_1,0xffffffff);
  dumpSesMacTb(param_1,0xffffffff);
  dumpUidMacTb(param_1,0xffffffff);
  dumpIPv6MacTb(param_1,0xffffffff);
  if (2 < DebugLevel) {
    printk("Default BroadCast Address=%02x:%02x:%02x:%02x:%02x:%02x!\n",(undefined1)BROADCAST_ADDR,
           BROADCAST_ADDR._1_1_,BROADCAST_ADDR._2_1_,BROADCAST_ADDR._3_1_,BROADCAST_ADDR._4_1_,
           BROADCAST_ADDR._5_1_);
  }
  return 1;
}


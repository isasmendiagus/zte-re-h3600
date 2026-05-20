// module: mt7915.ko
// function: WtblTlvBufferFree @ 0x1c506c
// size: 100 bytes
//

void WtblTlvBufferFree(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s::Fail to free buffer(%p)\n","WtblTlvBufferFree");
    return;
  }
  RTMPFreeNdisPacket();
  if (DebugLevel < 3) {
    return;
  }
  printk("%s::Free buffer(%p)\n","WtblTlvBufferFree",param_2);
  return;
}


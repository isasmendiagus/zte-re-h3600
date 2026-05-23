// module: mt7915.ko
// function: WtblTlvBufferAlloc @ 0x1c4f6c
// size: 96 bytes
//

int WtblTlvBufferAlloc(void)

{
  int iVar1;
  
  iVar1 = RTMP_AllocateFragPacketBuffer();
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s::Can not allocate net_pkt\n","WtblTlvBufferAlloc");
    }
  }
  else if (2 < DebugLevel) {
    printk("%s::Allocate(%p)\n","WtblTlvBufferAlloc",iVar1);
  }
  return iVar1;
}


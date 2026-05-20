// module: mt7915.ko
// function: RtmpOSFileRead @ 0x243d90
// size: 72 bytes
//

undefined4 RtmpOSFileRead(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x24) & 0x20000) != 0) {
    uVar1 = __vfs_read();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 0xffffffff;
  }
  printk("no file read method\n");
  return 0xffffffff;
}


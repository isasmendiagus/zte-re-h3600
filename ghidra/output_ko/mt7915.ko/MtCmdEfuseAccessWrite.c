// module: mt7915.ko
// function: MtCmdEfuseAccessWrite @ 0x1acb88
// size: 52 bytes
//

void MtCmdEfuseAccessWrite(void)

{
  if (-1 < DebugLevel) {
    printk("%s: error  set efuse failed!!!!!!\n","MtCmdEfuseAccessWrite");
  }
  dump_stack();
  return;
}


// module: mt7915.ko
// function: ShowSerProc @ 0xedb24
// size: 96 bytes
//

undefined4 ShowSerProc(int param_1)

{
  undefined4 uVar1;
  
  if (0 < DebugLevel) {
    uVar1 = ErrRecoveryCurStat(param_1 + 0xa7bf04);
    printk("%s,::E R , stat=0x%08X\n","ShowSerProc",uVar1);
  }
  chip_dump_ser_stat(param_1,1);
  SerTimeLogDump(param_1);
  return 1;
}


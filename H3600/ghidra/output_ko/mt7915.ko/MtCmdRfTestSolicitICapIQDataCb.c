// module: mt7915.ko
// function: MtCmdRfTestSolicitICapIQDataCb @ 0x1ae5a8
// size: 100 bytes
//

void MtCmdRfTestSolicitICapIQDataCb(int param_1,void *param_2)

{
  void *__dest;
  
  __dest = *(void **)(param_1 + 0xc);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdRfTestSolicitICapIQDataCb");
  }
  os_move_mem(__dest,param_2,0x430);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s<-----------------\n","MtCmdRfTestSolicitICapIQDataCb");
  return;
}


// module: mt7915.ko
// function: MonitorTimeout_Band0 @ 0x15a120
// size: 28 bytes
//

void MonitorTimeout_Band0(void)

{
  queue_work_on(2,system_wq,&_LANCHOR1);
  return;
}


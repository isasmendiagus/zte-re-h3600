// module: mt7915.ko
// function: MonitorTimeout_Band1 @ 0x15a13c
// size: 24 bytes
//

void MonitorTimeout_Band1(void)

{
  queue_work_on(2,system_wq,&DAT_0034d508);
  return;
}


// module: mt7915.ko
// function: ZTE_Temperature_Protection_Work_Schedule @ 0x15ffbc
// size: 24 bytes
//

void ZTE_Temperature_Protection_Work_Schedule(void)

{
  queue_work_on(2,system_wq,&DAT_0034d540);
  return;
}


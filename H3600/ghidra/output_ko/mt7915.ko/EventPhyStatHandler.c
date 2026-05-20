// module: mt7915.ko
// function: EventPhyStatHandler @ 0x153464
// size: 120 bytes
//

void EventPhyStatHandler(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  cVar1 = *param_2;
  if (3 < DebugLevel) {
    printk("%s: u1PhyStateEventId = %d\n","EventPhyStatHandler",cVar1);
  }
  if (cVar1 != '\0') {
    if (cVar1 != '\x01') {
      return;
    }
    EventPhyStatRxRate(param_1,param_2,param_3,param_4);
    return;
  }
  EventPhyStatTxRate(param_1,param_2,param_3,param_4);
  return;
}


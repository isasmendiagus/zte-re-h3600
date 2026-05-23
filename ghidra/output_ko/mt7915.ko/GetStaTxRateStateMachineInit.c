// module: mt7915.ko
// function: GetStaTxRateStateMachineInit @ 0x157f60
// size: 136 bytes
//

void GetStaTxRateStateMachineInit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (2 < DebugLevel) {
    printk("%s===>\n","GetStaTxRateStateMachineInit");
  }
  StateMachineInit(param_2,param_3,2,1,Drop,0,0);
  StateMachineSetAction(param_2,0,0,GetStaTxRateStart);
  return;
}


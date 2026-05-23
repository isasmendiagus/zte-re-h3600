// module: mt7915.ko
// function: DedicatedZeroWaitStartAction @ 0x22cec0
// size: 132 bytes
//

void DedicatedZeroWaitStartAction(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("[%s]\n","DedicatedZeroWaitStartAction");
  }
  *(undefined4 *)(param_1 + 0xa79184) = 2;
  if (*(code **)(iVar1 + 0x280) != (code *)0x0) {
    (**(code **)(iVar1 + 0x280))(param_1,6,1);
  }
  DfsDedicatedOutBandRDDStart(param_1);
  *(undefined4 *)(param_1 + 0x79540c) = 1;
  return;
}


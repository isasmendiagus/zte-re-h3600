// module: mt7915.ko
// function: WaitNRRspTimeout @ 0x221c38
// size: 188 bytes
//

void WaitNRRspTimeout(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined1 local_22;
  undefined1 local_21;
  undefined4 local_20;
  undefined2 local_1c;
  undefined2 local_1a;
  
  if (2 < DebugLevel) {
    printk(&_LC50,"WaitNRRspTimeout");
  }
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: MeasureReq Entry doesn\'t exist\n","WaitNRRspTimeout");
    }
  }
  else {
    uVar1 = *(undefined4 *)(param_2 + 0x10);
    __memzero(&local_22,10);
    local_20 = *(undefined4 *)(param_2 + 0x48);
    local_21 = *(undefined1 *)(param_2 + 9);
    local_22 = *(undefined1 *)(param_2 + 0x4e);
    local_1c = *(undefined2 *)(param_2 + 0x4c);
    local_1a = 0;
    MlmeEnqueue(uVar1,0x30,2,10,&local_22,0);
  }
  return;
}


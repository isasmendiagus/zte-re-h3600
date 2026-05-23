// module: mt7915.ko
// function: SetATETxBfLnaGain @ 0x2671b8
// size: 108 bytes
//

bool SetATETxBfLnaGain(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  
  if (param_2 != 0) {
    uVar1 = simple_strtol(param_2,0,10,param_4,param_4);
    if (-1 < DebugLevel) {
      printk(&_LC324,"SetATETxBfLnaGain");
    }
    iVar2 = CmdTxBfLnaGain(param_1,uVar1);
    return iVar2 == 0;
  }
  return false;
}


// module: mt7915.ko
// function: SetATETxFreqOffset @ 0x261ba8
// size: 112 bytes
//

bool SetATETxFreqOffset(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (0 < DebugLevel) {
    printk("%s: FreqOffset = %s\n","SetATETxFreqOffset",param_2);
  }
  uVar1 = simple_strtol(param_2,0,10);
  iVar2 = (**(code **)(iVar2 + 0x4c))(param_1,uVar1);
  return iVar2 == 0;
}


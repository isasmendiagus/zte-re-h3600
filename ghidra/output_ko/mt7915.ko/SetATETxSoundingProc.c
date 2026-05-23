// module: mt7915.ko
// function: SetATETxSoundingProc @ 0x2680d8
// size: 112 bytes
//

bool SetATETxSoundingProc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (0 < DebugLevel) {
    printk("%s: SoundingMode = %s\n","SetATETxSoundingProc",param_2);
  }
  uVar1 = simple_strtol(param_2,0,10);
  iVar2 = (**(code **)(iVar2 + 0xc0))(param_1,uVar1);
  return iVar2 == 0;
}


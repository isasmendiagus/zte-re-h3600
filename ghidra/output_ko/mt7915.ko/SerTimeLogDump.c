// module: mt7915.ko
// function: SerTimeLogDump @ 0xaf92c
// size: 236 bytes
//

void SerTimeLogDump(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  if (param_1 == 0) {
    return;
  }
  piVar3 = (int *)(param_1 + 0x285d38);
  iVar2 = 0;
  iVar1 = DebugLevel;
  do {
    if (0 < iVar1) {
      printk("%s,::E  R  , Time[%d](us)=%u\n","SerTimeLogDump",iVar2,piVar3[iVar2]);
      iVar1 = DebugLevel;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 8);
  iVar2 = 1;
  do {
    if (0 < iVar1) {
      printk("%s,::E  R  , T%d - T%d(us)=%u\n","SerTimeLogDump",iVar2,iVar2 + -1,piVar3[1] - *piVar3
            );
      iVar1 = DebugLevel;
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 != 8);
  if (iVar1 < 1) {
    return;
  }
  printk("%s,::E  R  , Total Time(us)=%u\n","SerTimeLogDump",
         *(int *)(param_1 + 0x285d54) - *(int *)(param_1 + 0x285d38));
  return;
}


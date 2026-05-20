// module: mt7915.ko
// function: ThermalTaskCtrl @ 0xed880
// size: 44 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool ThermalTaskCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdThermalTaskCtrl();
  return iVar1 != 0;
}


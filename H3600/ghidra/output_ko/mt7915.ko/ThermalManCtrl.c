// module: mt7915.ko
// function: ThermalManCtrl @ 0xed86c
// size: 20 bytes
//

bool ThermalManCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdThermalManCtrl();
  return iVar1 != 0;
}


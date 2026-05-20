// module: mt7915.ko
// function: ThermoCompCtrl @ 0xed7b4
// size: 20 bytes
//

bool ThermoCompCtrl(void)

{
  int iVar1;
  
  iVar1 = MtCmdThermoCompCtrl();
  return iVar1 == 0;
}


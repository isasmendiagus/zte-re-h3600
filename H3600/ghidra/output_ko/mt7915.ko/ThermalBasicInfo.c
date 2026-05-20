// module: mt7915.ko
// function: ThermalBasicInfo @ 0xed8ac
// size: 20 bytes
//

bool ThermalBasicInfo(void)

{
  int iVar1;
  
  iVar1 = MtCmdThermalBasicInfo();
  return iVar1 != 0;
}


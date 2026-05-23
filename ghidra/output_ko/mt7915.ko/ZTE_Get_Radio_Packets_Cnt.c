// module: mt7915.ko
// function: ZTE_Get_Radio_Packets_Cnt @ 0x157ae0
// size: 24 bytes
//

undefined4 ZTE_Get_Radio_Packets_Cnt(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_005f3d38;
  if (param_1 != 0) {
    uVar1 = DAT_005f3d3c;
  }
  return uVar1;
}


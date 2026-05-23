// module: mt7915.ko
// function: DfsStopWifiCheck @ 0x232820
// size: 48 bytes
//

bool DfsStopWifiCheck(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = HcGetBandByWdev(param_2);
  return *(char *)(param_1 + iVar1 + 0x7953eb) == '\x01';
}


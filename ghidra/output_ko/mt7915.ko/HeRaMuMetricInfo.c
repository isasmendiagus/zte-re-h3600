// module: mt7915.ko
// function: HeRaMuMetricInfo @ 0x87120
// size: 20 bytes
//

bool HeRaMuMetricInfo(void)

{
  int iVar1;
  
  iVar1 = CmdHeRaMuMetricInfo();
  return iVar1 == 0;
}


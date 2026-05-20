// module: mt7915.ko
// function: VhtBw2Str @ 0x201bfc
// size: 32 bytes
//

char * VhtBw2Str(int param_1)

{
  char *pcVar1;
  
  if (param_1 < 4) {
    pcVar1 = (&PTR_s_20_40_002a1518)[param_1];
  }
  else {
    pcVar1 = "invalid";
  }
  return pcVar1;
}


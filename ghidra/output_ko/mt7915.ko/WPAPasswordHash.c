// module: mt7915.ko
// function: WPAPasswordHash @ 0x119ce4
// size: 136 bytes
//

undefined4 WPAPasswordHash(char *param_1,undefined4 param_2,int param_3,int param_4)

{
  size_t sVar1;
  
  sVar1 = strlen(param_1);
  if (sVar1 < 0x40 && param_3 < 0x21) {
    FUN_001186b0(param_1,param_2,param_3,1,param_4);
    FUN_001186b0(param_1,param_2,param_3,2,param_4 + 0x14);
    return 1;
  }
  return 0;
}


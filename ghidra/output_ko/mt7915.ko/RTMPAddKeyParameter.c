// module: mt7915.ko
// function: RTMPAddKeyParameter @ 0xeee50
// size: 56 bytes
//

undefined4
RTMPAddKeyParameter(undefined4 param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  size_t sVar1;
  
  sVar1 = strlen(param_4);
  sprintf(param_4 + sVar1,"%s=%s\n",param_1,param_2);
  return 1;
}


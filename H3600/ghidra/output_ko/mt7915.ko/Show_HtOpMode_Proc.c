// module: mt7915.ko
// function: Show_HtOpMode_Proc @ 0xd5d44
// size: 68 bytes
//

undefined4 Show_HtOpMode_Proc(int param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  char *__format;
  
  if ((*(byte *)(param_1 + 0x794cce) & 1) == 0) {
    __format = "\tMM";
  }
  else {
    __format = "\tGF";
  }
  snprintf(param_2,param_3,__format,(uint)*(byte *)(param_1 + 0x794cce),param_4);
  return 0;
}


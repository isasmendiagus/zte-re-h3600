// module: mt7915.ko
// function: Show_CountryCode_Proc @ 0xd5f64
// size: 44 bytes
//

undefined4 Show_CountryCode_Proc(int param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  snprintf(param_2,param_3,"\t%s",param_1 + 0x794c31,param_4);
  return 0;
}


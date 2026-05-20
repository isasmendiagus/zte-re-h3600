// module: mt7915.ko
// function: Show_CountryRegion_Proc @ 0xd5f0c
// size: 44 bytes
//

undefined4 Show_CountryRegion_Proc(int param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  snprintf(param_2,param_3,"\t%d",(uint)*(byte *)(param_1 + 0x794c44),param_4);
  return 0;
}


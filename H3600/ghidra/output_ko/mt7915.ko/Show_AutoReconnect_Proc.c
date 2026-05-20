// module: mt7915.ko
// function: Show_AutoReconnect_Proc @ 0xd6308
// size: 76 bytes
//

undefined4 Show_AutoReconnect_Proc(int *param_1,char *param_2,size_t param_3)

{
  snprintf(param_2,param_3,"\tAutoReconnect = %d",
           (uint)*(byte *)((int)param_1 + *(int *)(*param_1 + 0x3c) * 0x2137b0 + 0x580cc9));
  return 0;
}


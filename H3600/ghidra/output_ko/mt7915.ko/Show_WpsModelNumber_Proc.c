// module: mt7915.ko
// function: Show_WpsModelNumber_Proc @ 0xd5554
// size: 68 bytes
//

undefined4
Show_WpsModelNumber_Proc(int *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  sprintf(param_2,"\tModelNumber = %s",
          (int)(param_1 + *(int *)(*param_1 + 0x3c) * 0x84dec) + 0x36ef67,
          param_1 + *(int *)(*param_1 + 0x3c) * 0x84dec,param_4);
  return 0;
}


// module: mt7915.ko
// function: RRM_InsertBcnRepIE @ 0x21cc0c
// size: 60 bytes
//

void RRM_InsertBcnRepIE(undefined4 param_1,undefined4 param_2,int *param_3,undefined4 param_4)

{
  int local_c;
  
  MakeOutgoingFrame(param_2,&local_c,0x1a,param_4,0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}


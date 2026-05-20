// module: mt7915.ko
// function: RRM_InsertBcnReqSsidSubIE @ 0x21ccfc
// size: 100 bytes
//

void RRM_InsertBcnReqSsidSubIE
               (undefined4 param_1,undefined4 param_2,int *param_3,undefined4 param_4,
               undefined1 param_5)

{
  undefined1 local_d;
  int local_c;
  
  local_d = 0;
  MakeOutgoingFrame(param_2,&local_c,1,&local_d,1,&param_5,param_5,param_4,0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}


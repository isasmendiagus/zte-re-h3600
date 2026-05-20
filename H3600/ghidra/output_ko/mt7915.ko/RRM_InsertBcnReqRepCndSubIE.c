// module: mt7915.ko
// function: RRM_InsertBcnReqRepCndSubIE @ 0x21cd60
// size: 120 bytes
//

void RRM_InsertBcnReqRepCndSubIE
               (undefined4 param_1,undefined4 param_2,int *param_3,undefined1 param_4)

{
  undefined1 local_11 [3];
  undefined1 local_e;
  undefined1 local_d;
  int local_c;
  
  local_d = 1;
  local_e = 2;
  local_11[0] = param_4;
  MakeOutgoingFrame(param_2,&local_c,1,&local_d,1,&local_e,1,local_11,1,&stack0x00000000,0xffffffff)
  ;
  *param_3 = *param_3 + local_c;
  return;
}


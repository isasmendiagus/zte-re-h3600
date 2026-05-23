// module: mt7915.ko
// function: RRM_InsertBcnReqRepDetailSubIE @ 0x21cdd8
// size: 108 bytes
//

void RRM_InsertBcnReqRepDetailSubIE
               (undefined4 param_1,undefined4 param_2,int *param_3,undefined1 param_4)

{
  undefined1 local_11 [3];
  undefined1 local_e;
  undefined1 local_d;
  int local_c;
  
  local_e = 1;
  local_d = 2;
  local_11[0] = param_4;
  MakeOutgoingFrame(param_2,&local_c,1,&local_d,1,&local_e,1,local_11,0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}


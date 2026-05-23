// module: mt7915.ko
// function: WNM_InsertBSSTerminationSubIE @ 0x228e30
// size: 132 bytes
//

void WNM_InsertBSSTerminationSubIE(undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined1 local_e;
  undefined1 local_d;
  int local_c;
  
  local_c = 0;
  local_e = 10;
  local_d = 4;
  MakeOutgoingFrame(param_2,&local_c,1,&local_d,1,&local_e,8,&stack0x00000000,2,&stack0x00000008,
                    0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}


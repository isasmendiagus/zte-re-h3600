// module: mt7915.ko
// function: RRM_InsertTxStreamReqTriggerReportSubIE @ 0x21d340
// size: 100 bytes
//

/* WARNING: Type propagation algorithm not settling */

void RRM_InsertTxStreamReqTriggerReportSubIE
               (undefined4 param_1,undefined4 param_2,int *param_3,undefined4 param_4)

{
  undefined1 local_11;
  int local_10 [2];
  
  local_11 = 1;
  local_10[1] = 6;
  MakeOutgoingFrame(param_2,local_10,1,&local_11,1,local_10 + 1,6,param_4,0xffffffff);
  *param_3 = *param_3 + local_10[0];
  return;
}


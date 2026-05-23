// module: mt7915.ko
// function: call_traffic_notifieriers @ 0xc62c0
// size: 56 bytes
//

void call_traffic_notifieriers(undefined4 param_1,int param_2,undefined4 param_3)

{
  int local_10;
  undefined4 local_c;
  
  local_10 = param_2;
  local_c = param_3;
  mt_notify_call_chain(param_2 + 0xa18fc,param_1,&local_10);
  return;
}


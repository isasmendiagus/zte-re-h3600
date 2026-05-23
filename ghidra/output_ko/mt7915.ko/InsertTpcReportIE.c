// module: mt7915.ko
// function: InsertTpcReportIE @ 0x13ed84
// size: 116 bytes
//

void InsertTpcReportIE(undefined4 param_1,undefined4 param_2,int *param_3,undefined1 param_4,
                      undefined1 param_5)

{
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  int local_c;
  
  local_d = param_5;
  local_10 = 2;
  local_f = 0x23;
  local_e = param_4;
  MakeOutgoingFrame(param_2,&local_c,1,&local_f,1,&local_10,2,&local_e,0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}


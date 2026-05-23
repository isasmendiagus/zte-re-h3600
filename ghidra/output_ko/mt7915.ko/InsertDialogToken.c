// module: mt7915.ko
// function: InsertDialogToken @ 0x13ed40
// size: 68 bytes
//

void InsertDialogToken(undefined4 param_1,undefined4 param_2,int *param_3,undefined1 param_4)

{
  undefined1 local_11 [5];
  int local_c;
  
  local_11[0] = param_4;
  MakeOutgoingFrame(param_2,&local_c,1,local_11,0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}


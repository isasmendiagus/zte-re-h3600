// module: mt7915.ko
// function: InsertActField @ 0xa40d0
// size: 84 bytes
//

void InsertActField(undefined4 param_1,undefined4 param_2,int *param_3,undefined1 param_4)

{
  undefined1 local_11 [5];
  int local_c;
  
  local_11[0] = param_4;
  MakeOutgoingFrame(param_2,&local_c,1,local_11,1,&stack0x00000000,0xffffffff);
  *param_3 = *param_3 + local_c;
  return;
}


// module: mt7915.ko
// function: Set_DumpSta_Proc @ 0x156c00
// size: 68 bytes
//

undefined4 Set_DumpSta_Proc(int param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = simple_strtol(param_2,0,10);
  if (cVar1 == '\x01') {
    *(undefined1 *)(param_1 + 0xa7d164) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0xa7d164) = 0;
  }
  return 1;
}


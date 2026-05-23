// module: mt7915.ko
// function: Set_bufferMode_Proc @ 0x128504
// size: 44 bytes
//

undefined4 Set_bufferMode_Proc(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  
  uVar1 = os_str_tol(param_2,0,10);
  MtCmdEfusBufferModeSet(param_1,uVar1);
  return 1;
}


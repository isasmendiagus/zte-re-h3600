// module: mt7915.ko
// function: Show_TmrCalResult_Proc @ 0x33c78
// size: 104 bytes
//

undefined4
Show_TmrCalResult_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) == 0) {
    if (0 < DebugLevel) {
      printk("%s(): (X) pTmrCtrlStruct is NULL\n","Show_TmrCalResult_Proc",0,DebugLevel,param_4);
    }
  }
  else if (0 < DebugLevel) {
    printk("%s(): TmrCalResult=0x%X\n","Show_TmrCalResult_Proc",
           *(undefined4 *)(*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) + 4),DebugLevel,
           param_4);
  }
  return 1;
}


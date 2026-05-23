// module: mt7915.ko
// function: Set_LinkMeasureReq_Proc @ 0x21fcd8
// size: 56 bytes
//

undefined4
Set_LinkMeasureReq_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined2 uVar2;
  
  uVar1 = *(undefined1 *)(*param_1 + 0x3c);
  uVar2 = os_str_tol(param_2,0,10,*param_1,param_4);
  RRM_EnqueueLinkMeasureReq(param_1,uVar2,uVar1);
  return 1;
}


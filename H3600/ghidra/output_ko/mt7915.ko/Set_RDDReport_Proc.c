// module: mt7915.ko
// function: Set_RDDReport_Proc @ 0x235140
// size: 84 bytes
//

undefined4 Set_RDDReport_Proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  
  uVar1 = os_str_tol(param_2,0,10);
  *(undefined1 *)(param_1 + 0x795439) = 1;
  mtRddControl(param_1,3,uVar1,0,0);
  return 1;
}


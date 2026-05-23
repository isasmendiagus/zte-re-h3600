// module: mt7915.ko
// function: Set_ErrDetectOn_Proc @ 0x13deec
// size: 48 bytes
//

undefined4 Set_ErrDetectOn_Proc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  CmdExtGeneralTestOn(param_1,iVar1 != 0);
  return 1;
}


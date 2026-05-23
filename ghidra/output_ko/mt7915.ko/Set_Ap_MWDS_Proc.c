// module: mt7915.ko
// function: Set_Ap_MWDS_Proc @ 0x9ecbc
// size: 44 bytes
//

void Set_Ap_MWDS_Proc(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  
  uVar1 = simple_strtol(param_2,0,10);
  Set_Enable_MWDS_Proc(param_1,uVar1,1);
  return;
}


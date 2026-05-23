// module: mt7915.ko
// function: Set_ErrDetectMode_Proc @ 0x13df1c
// size: 124 bytes
//

undefined4 Set_ErrDetectMode_Proc(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  char *pcVar3;
  char *local_14;
  
  local_14 = param_2;
  pcVar3 = strsep(&local_14,"_");
  uVar1 = 0;
  if (pcVar3 != (char *)0x0) {
    uVar1 = os_str_tol(pcVar3,0,10);
  }
  pcVar3 = strsep(&local_14,"_");
  uVar2 = 0;
  if (pcVar3 != (char *)0x0) {
    uVar2 = os_str_tol(pcVar3,0,10);
  }
  CmdExtGeneralTestMode(param_1,uVar1,uVar2);
  return 1;
}


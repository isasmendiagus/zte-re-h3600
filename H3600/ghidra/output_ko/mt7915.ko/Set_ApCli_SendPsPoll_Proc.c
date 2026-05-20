// module: mt7915.ko
// function: Set_ApCli_SendPsPoll_Proc @ 0x2feec
// size: 88 bytes
//

undefined4
Set_ApCli_SendPsPoll_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *param_1;
  if (*(int *)(iVar1 + 0x38) != 0x400) {
    return 0;
  }
  uVar2 = *(uint *)(iVar1 + 0x3c);
  iVar1 = os_str_tol(param_2,0,0x10,iVar1,param_4);
  if (iVar1 == 0) {
    return 1;
  }
  ApCliRTMPSendPsPollFrame(param_1,uVar2 & 0xff);
  return 1;
}


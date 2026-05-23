// module: mt7915.ko
// function: SetMuruSuTx @ 0x23a320
// size: 276 bytes
//

undefined4 SetMuruSuTx(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_34 [2];
  undefined1 local_29;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_29 = 0;
  local_28 = 0x10;
  local_34[0] = param_2;
  pcVar1 = strsep(local_34,"-");
  if (pcVar1 != (char *)0x0) {
    local_29 = os_str_tol(pcVar1,0,10);
    iVar2 = AndesAllocCmdMsg(param_1,5);
    if (iVar2 != 0) {
      local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
      local_20 = CONCAT31(local_20._1_3_,10);
      uVar3 = 1;
      AndesInitCmdMsg(iVar2,local_24,local_20,local_1c,local_18,local_14);
      AndesAppendCmdMsg(iVar2,&local_28,4);
      AndesAppendCmdMsg(iVar2,&local_29,1);
      AndesSendCmdMsg(param_1,iVar2);
      goto LAB_0023a3fc;
    }
  }
  uVar3 = 0;
LAB_0023a3fc:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuruSuTx",uVar3);
  }
  return uVar3;
}


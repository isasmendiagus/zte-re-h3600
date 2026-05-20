// module: mt7915.ko
// function: SetMuruProtFrameThr @ 0x23a550
// size: 272 bytes
//

undefined4 SetMuruProtFrameThr(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_34 [2];
  undefined4 local_2c;
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
  local_2c = 0xcc;
  local_34[0] = param_2;
  pcVar1 = strsep(local_34,"-");
  if (pcVar1 != (char *)0x0) {
    local_28 = os_str_tol(pcVar1,0,10);
    iVar2 = AndesAllocCmdMsg(param_1,8);
    if (iVar2 != 0) {
      local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
      local_20 = CONCAT31(local_20._1_3_,10);
      uVar3 = 1;
      AndesInitCmdMsg(iVar2,local_24,local_20,local_1c,local_18,local_14);
      AndesAppendCmdMsg(iVar2,&local_2c,4);
      AndesAppendCmdMsg(iVar2,&local_28,4);
      AndesSendCmdMsg(param_1,iVar2);
      goto LAB_0023a628;
    }
  }
  uVar3 = 0;
LAB_0023a628:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuruProtFrameThr",uVar3);
  }
  return uVar3;
}


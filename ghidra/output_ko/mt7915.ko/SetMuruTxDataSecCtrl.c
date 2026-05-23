// module: mt7915.ko
// function: SetMuruTxDataSecCtrl @ 0x239ee8
// size: 332 bytes
//

undefined4 SetMuruTxDataSecCtrl(undefined4 param_1,char *param_2)

{
  byte bVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  char *local_34 [2];
  undefined4 local_2c;
  uint local_28;
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
  local_28 = 0;
  local_2c = 3;
  local_34[0] = param_2;
  pcVar2 = strsep(local_34,"-");
  if (pcVar2 != (char *)0x0) {
    bVar1 = os_str_tol(pcVar2,0,10);
    local_28 = CONCAT31(local_28._1_3_,(byte)local_28 & 0xf8 | bVar1 & 7);
    pcVar2 = strsep(local_34,"-");
    if (pcVar2 != (char *)0x0) {
      uVar3 = os_str_tol(pcVar2,0,10);
      local_28 = local_28 & 0xfffe0007 | (uVar3 & 0x3fff) << 3;
      iVar4 = AndesAllocCmdMsg(param_1,8);
      if (iVar4 != 0) {
        local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
        local_20 = CONCAT31(local_20._1_3_,10);
        uVar5 = 1;
        AndesInitCmdMsg(iVar4,local_24,local_20,local_1c,local_18,local_14);
        AndesAppendCmdMsg(iVar4,&local_2c,4);
        AndesAppendCmdMsg(iVar4,&local_28,4);
        AndesSendCmdMsg(param_1,iVar4);
        goto LAB_00239ffc;
      }
    }
  }
  uVar5 = 0;
LAB_00239ffc:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuruTxDataSecCtrl",uVar5);
  }
  return uVar5;
}


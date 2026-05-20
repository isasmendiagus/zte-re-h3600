// module: mt7915.ko
// function: SetMuruTrigDataSecCtrl @ 0x23a038
// size: 380 bytes
//

undefined4 SetMuruTrigDataSecCtrl(undefined4 param_1,char *param_2)

{
  byte bVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  char *local_3c [2];
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 0;
  local_34 = 4;
  local_3c[0] = param_2;
  pcVar2 = strsep(local_3c,"-");
  if (pcVar2 != (char *)0x0) {
    bVar1 = os_str_tol(pcVar2,0,10);
    local_30 = CONCAT31(local_30._1_3_,(byte)local_30 & 0xfc | bVar1 & 3);
    pcVar2 = strsep(local_3c,"-");
    if (pcVar2 != (char *)0x0) {
      bVar1 = os_str_tol(pcVar2,0,10);
      local_30 = CONCAT31(local_30._1_3_,(byte)local_30 & 0xe3 | (bVar1 & 7) << 2);
      pcVar2 = strsep(local_3c,"-");
      if (pcVar2 != (char *)0x0) {
        uVar3 = os_str_tol(pcVar2,0,10);
        local_30 = local_30 & 0xfff8001f | (uVar3 & 0x3fff) << 5;
        iVar4 = AndesAllocCmdMsg(param_1,8);
        if (iVar4 != 0) {
          local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
          local_28 = CONCAT31(local_28._1_3_,10);
          uVar5 = 1;
          AndesInitCmdMsg(iVar4,local_2c,local_28,local_24,local_20,local_1c);
          AndesAppendCmdMsg(iVar4,&local_34,4);
          AndesAppendCmdMsg(iVar4,&local_30,4);
          AndesSendCmdMsg(param_1,iVar4);
          goto LAB_0023a17c;
        }
      }
    }
  }
  uVar5 = 0;
LAB_0023a17c:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuruTrigDataSecCtrl",uVar5);
  }
  return uVar5;
}


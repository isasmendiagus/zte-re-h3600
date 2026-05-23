// module: mt7915.ko
// function: SetMuruGlobalProtSecCtrl @ 0x239c40
// size: 676 bytes
//

undefined4 SetMuruGlobalProtSecCtrl(undefined4 param_1,char *param_2)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  char *local_34 [2];
  byte local_2b;
  byte local_2a;
  byte local_29;
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
  local_2b = 0;
  local_2a = 0;
  local_29 = 0;
  local_28 = 2;
  local_34[0] = param_2;
  pcVar3 = strsep(local_34,"-");
  if (pcVar3 != (char *)0x0) {
    bVar1 = os_str_tol(pcVar3,0,10);
    local_2b = local_2b & 0xfe | bVar1 & 1;
    pcVar3 = strsep(local_34,"-");
    if (pcVar3 != (char *)0x0) {
      bVar1 = os_str_tol(pcVar3,0,10);
      local_2b = local_2b & 0xfd | (bVar1 & 1) << 1;
      pcVar3 = strsep(local_34,"-");
      if (pcVar3 != (char *)0x0) {
        bVar1 = os_str_tol(pcVar3,0,10);
        local_2b = local_2b & 0xe3 | (bVar1 & 7) << 2;
        pcVar3 = strsep(local_34,"-");
        if (pcVar3 != (char *)0x0) {
          bVar1 = os_str_tol(pcVar3,0,10);
          local_2b = local_2b & 0x9f | (bVar1 & 3) << 5;
          pcVar3 = strsep(local_34,"-");
          if (pcVar3 != (char *)0x0) {
            bVar1 = os_str_tol(pcVar3,0,10);
            local_2a = local_2a & 0xf8 | bVar1 & 7;
            pcVar3 = strsep(local_34,"-");
            if (pcVar3 != (char *)0x0) {
              bVar1 = os_str_tol(pcVar3,0,10);
              local_2a = local_2a & 0xf7 | (bVar1 & 1) << 3;
              pcVar3 = strsep(local_34,"-");
              if (pcVar3 != (char *)0x0) {
                bVar1 = os_str_tol(pcVar3,0,10);
                local_2a = local_2a & 0xef | (bVar1 & 1) << 4;
                pcVar3 = strsep(local_34,"-");
                if (pcVar3 != (char *)0x0) {
                  cVar2 = os_str_tol(pcVar3,0,10);
                  local_2a = local_2a & 0x1f | cVar2 << 5;
                  pcVar3 = strsep(local_34,"-");
                  if (pcVar3 != (char *)0x0) {
                    bVar1 = os_str_tol(pcVar3,0,10);
                    local_29 = local_29 & 0xfe | bVar1 & 1;
                    iVar4 = AndesAllocCmdMsg(param_1,7);
                    if (iVar4 != 0) {
                      local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
                      local_20 = CONCAT31(local_20._1_3_,10);
                      uVar5 = 1;
                      AndesInitCmdMsg(iVar4,local_24,local_20,local_1c,local_18,local_14);
                      AndesAppendCmdMsg(iVar4,&local_28,4);
                      AndesAppendCmdMsg(iVar4,&local_2b,3);
                      AndesSendCmdMsg(param_1,iVar4);
                      goto LAB_00239eac;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  uVar5 = 0;
LAB_00239eac:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuruGlobalProtSecCtrl",uVar5);
  }
  return uVar5;
}


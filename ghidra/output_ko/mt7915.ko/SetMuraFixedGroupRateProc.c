// module: mt7915.ko
// function: SetMuraFixedGroupRateProc @ 0x958fc
// size: 1076 bytes
//

undefined4 SetMuraFixedGroupRateProc(int param_1,char *param_2)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  byte bVar8;
  undefined4 uVar9;
  char *local_34;
  undefined4 local_30;
  byte local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  undefined1 local_28;
  undefined1 local_27;
  byte local_26;
  byte local_25;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar7 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_2b = 0;
  local_2a = 0;
  local_29 = 0;
  local_28 = 0;
  local_27 = 0;
  local_26 = 0;
  local_25 = 0;
  local_30 = 5;
  local_34 = param_2;
  if (uVar7 != 0x7626 && (uVar7 != 0x7663 && uVar7 != 0x7615)) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Not Supported (Ret = %d_\n","SetMuraFixedGroupRateProc",0);
    return 0;
  }
  pcVar5 = strsep(&local_34,"-");
  if (pcVar5 != (char *)0x0) {
    cVar2 = os_str_tol(pcVar5,0,10);
    local_2b = local_2b & 0xfc | cVar2 - 1U & 3;
    pcVar5 = strsep(&local_34,"-");
    if (pcVar5 != (char *)0x0) {
      bVar3 = os_str_tol(pcVar5,0,10);
      bVar3 = local_2b & 0xf3 | (bVar3 & 3) << 2;
      bVar4 = local_2b & 3;
      local_2b = bVar3;
      if (bVar4 == 0) goto LAB_00095c64;
      pcVar5 = strsep(&local_34,"-");
      if (pcVar5 != (char *)0x0) {
        local_2a = os_str_tol(pcVar5,0,10);
        pcVar5 = strsep(&local_34,"-");
        if (pcVar5 != (char *)0x0) {
          bVar3 = os_str_tol(pcVar5,0,10);
          local_2b = local_2b & 0xef | (10 < bVar3) << 4;
          if (10 < bVar3) {
            bVar3 = bVar3 - 10;
          }
          local_26 = local_26 & 0xf0 | bVar3 & 0xf;
          pcVar5 = strsep(&local_34,"-");
          if (pcVar5 != (char *)0x0) {
            local_29 = os_str_tol(pcVar5,0,10);
            if ((local_2b & 3) == 1) {
              pcVar5 = "";
            }
            else {
              pcVar5 = "-";
            }
            pcVar5 = strsep(&local_34,pcVar5);
            if (pcVar5 != (char *)0x0) {
              bVar4 = os_str_tol(pcVar5,0,10);
              bVar3 = local_2b & 0xdf | (10 < bVar4) << 5;
              if (10 < bVar4) {
                bVar4 = bVar4 - 10;
              }
              bVar8 = local_2b & 3;
              local_26 = local_26 & 0xf | bVar4 << 4;
              local_2b = bVar3;
              if (bVar8 < 2) {
LAB_00095bdc:
                if (bVar8 == 3) {
                  pcVar5 = strsep(&local_34,"-");
                  if (pcVar5 != (char *)0x0) {
                    local_27 = os_str_tol(pcVar5,0,10);
                    pcVar5 = strsep(&local_34,"");
                    if (pcVar5 != (char *)0x0) {
                      bVar3 = os_str_tol(pcVar5,0,10);
                      local_2b = local_2b & 0x7f | (10 < bVar3) << 7;
                      if (10 < bVar3) {
                        bVar3 = bVar3 - 10;
                      }
                      local_25 = local_25 & 0xf | bVar3 << 4;
                      goto LAB_00095c64;
                    }
                  }
                }
                else {
LAB_00095c64:
                  iVar6 = AndesAllocCmdMsg(param_1,0xb);
                  if (iVar6 != 0) {
                    local_24 = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_24));
                    local_20 = CONCAT31(local_20._1_3_,10);
                    uVar9 = 1;
                    AndesInitCmdMsg(iVar6,local_24,local_20,local_1c,local_18,local_14);
                    AndesAppendCmdMsg(iVar6,&local_30,4);
                    AndesAppendCmdMsg(iVar6,&local_2b,7);
                    AndesSendCmdMsg(param_1,iVar6);
                    goto LAB_00095ce4;
                  }
                }
              }
              else {
                pcVar5 = strsep(&local_34,"-");
                if (pcVar5 != (char *)0x0) {
                  local_28 = os_str_tol(pcVar5,0,10);
                  if ((local_2b & 3) == 2) {
                    pcVar5 = "";
                  }
                  else {
                    pcVar5 = "-";
                  }
                  pcVar5 = strsep(&local_34,pcVar5);
                  if (pcVar5 != (char *)0x0) {
                    bVar3 = os_str_tol(pcVar5,0,10);
                    bVar1 = 10 < bVar3;
                    if (bVar1) {
                      bVar3 = bVar3 - 10;
                    }
                    bVar8 = local_2b & 3;
                    local_25 = local_25 & 0xf0 | bVar3 & 0xf;
                    local_2b = local_2b & 0xbf | bVar1 << 6;
                    goto LAB_00095bdc;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  uVar9 = 0;
LAB_00095ce4:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuraFixedGroupRateProc",uVar9);
  }
  return uVar9;
}


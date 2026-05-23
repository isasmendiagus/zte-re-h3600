// module: mt7915.ko
// function: SetHeraProtectionPerPpduDis @ 0x1be3d0
// size: 540 bytes
//

undefined4 SetHeraProtectionPerPpduDis(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_3c [2];
  undefined4 local_34;
  undefined1 local_30;
  byte local_2f;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  uVar3 = 0;
  local_2c = 0;
  local_34 = 7;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_3c[0] = param_2;
  os_zero_mem(&local_30,4);
  pcVar1 = strsep(local_3c,":");
  if (pcVar1 == (char *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Empty Band Index !!\n","SetHeraProtectionPerPpduDis");
    uVar3 = 0;
  }
  else {
    local_2f = os_str_toul(pcVar1,0,10);
    if (local_2f < 2) {
      pcVar1 = strsep(local_3c,"");
      if (pcVar1 == (char *)0x0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: Empty ProtectionPerPpduDis !!\n","SetHeraProtectionPerPpduDis");
        uVar3 = 0;
      }
      else {
        iVar2 = os_str_toul(pcVar1,0,10);
        local_30 = iVar2 != 0;
        if (-1 < DebugLevel) {
          printk("%s: BandIdx:%d ProtectionPerPpduDis:%d !!\n","SetHeraProtectionPerPpduDis",
                 local_2f);
        }
        iVar2 = AndesAllocCmdMsg(param_1,8);
        if (iVar2 == 0) {
          uVar3 = 0;
        }
        else {
          local_2c = CONCAT13(0x87,CONCAT12(0xed,(undefined2)local_2c));
          local_28 = CONCAT31(local_28._1_3_,10);
          uVar3 = 1;
          AndesInitCmdMsg(iVar2,local_2c,local_28,local_24,local_20,local_1c);
          AndesAppendCmdMsg(iVar2,&local_34,4);
          AndesAppendCmdMsg(iVar2,&local_30,4);
          AndesSendCmdMsg(param_1,iVar2);
        }
      }
    }
    else {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: Invalid Band Index !!\n","SetHeraProtectionPerPpduDis");
    }
  }
  if (0 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetHeraProtectionPerPpduDis",uVar3);
  }
  return uVar3;
}


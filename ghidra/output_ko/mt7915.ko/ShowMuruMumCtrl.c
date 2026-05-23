// module: mt7915.ko
// function: ShowMuruMumCtrl @ 0x23ad34
// size: 496 bytes
//

undefined4 ShowMuruMumCtrl(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  size_t __n;
  int iVar2;
  undefined4 uVar3;
  undefined2 local_66;
  char *local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined1 *local_50;
  code *local_4c;
  undefined1 auStack_48 [56];
  
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_64 = param_2;
  pcVar1 = strsep(&local_64,"-");
  if (pcVar1 != (char *)0x0) {
    __n = strlen(pcVar1);
    iVar2 = strncmp(pcVar1,"grouptbl",__n);
    if (iVar2 == 0) {
      local_60 = 5;
    }
    else {
      iVar2 = strncmp(pcVar1,"profile",__n);
      if (iVar2 == 0) {
        local_60 = 3;
      }
      else {
        iVar2 = strncmp(pcVar1,"clustertbl",__n);
        if (iVar2 == 0) {
          local_60 = 7;
        }
        else {
          iVar2 = strncmp(pcVar1,"dlac",__n);
          if (iVar2 == 0) {
            local_60 = 8;
          }
          else {
            iVar2 = strncmp(pcVar1,"ultid",__n);
            if (iVar2 != 0) goto LAB_0023ae20;
            local_60 = 9;
          }
        }
      }
    }
    pcVar1 = strsep(&local_64,"-");
    if (pcVar1 != (char *)0x0) {
      local_66 = simple_strtol(pcVar1,0,10);
      iVar2 = AndesAllocCmdMsg(param_1,6);
      if (iVar2 != 0) {
        local_50 = auStack_48;
        local_4c = muruEventDispatcher;
        local_5c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_5c));
        local_58 = CONCAT31(local_58._1_3_,5);
        uVar3 = 1;
        local_58 = CONCAT22(0x38,(undefined2)local_58);
        AndesInitCmdMsg(iVar2,local_5c,local_58,local_54,local_50,muruEventDispatcher);
        AndesAppendCmdMsg(iVar2,&local_60,4);
        AndesAppendCmdMsg(iVar2,&local_66,2);
        AndesSendCmdMsg(param_1,iVar2);
        goto LAB_0023ae24;
      }
    }
  }
LAB_0023ae20:
  uVar3 = 0;
LAB_0023ae24:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","ShowMuruMumCtrl",uVar3);
  }
  return uVar3;
}


// module: mt7915.ko
// function: SetTpcDlAlgoCtrl @ 0xc1b68
// size: 636 bytes
//

undefined4 SetTpcDlAlgoCtrl(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  char cVar8;
  ushort uVar9;
  undefined4 local_18;
  uint local_14;
  
  uVar7 = 0;
  local_18 = 0;
  local_14 = 0;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: No parameters!!\n","SetTpcDlAlgoCtrl");
    return 0;
  }
  iVar3 = rstrtok(param_2,&_LC156);
  if (iVar3 == 0) {
LAB_000c1cb0:
    if (local_18 >> 0x10 < 2) {
      uVar5 = 0;
      uVar7 = local_18 >> 0x10 & 0xff;
      sVar2 = 0;
      uVar9 = 0;
      cVar8 = '\0';
      uVar6 = 0;
LAB_000c1d48:
      uVar4 = TpcDlAlgoCtrl(param_1,uVar5,uVar7,uVar6,(int)cVar8,uVar9,(int)sVar2);
      return uVar4;
    }
    if (-1 < DebugLevel) {
      printk("%s: Set wrong parameters! Enable command control enable=1, disable=0.\n",
             "SetTpcDlAlgoCtrl");
    }
  }
  else {
    do {
      uVar1 = os_str_tol(iVar3,0,10);
      uVar5 = uVar7 & 0xff;
      uVar7 = uVar7 + 1;
      *(undefined2 *)((int)&local_18 + uVar5 * 2) = uVar1;
      iVar3 = rstrtok(0,&_LC156);
    } while (iVar3 != 0);
    uVar5 = local_18 & 0xff;
    uVar7 = 0;
    if (uVar5 == 1) {
      if (local_18._2_2_ < 2) {
        if (0xff < ((local_14 & 0xffff) + 0x80 & 0xffff)) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: Set wrong parameters! Down-link Tx Power should between -127~128. \n",
                 "SetTpcDlAlgoCtrl");
          return 0;
        }
        uVar6 = local_18._2_2_ & 0xff;
        cVar8 = (char)local_14;
        sVar2 = 0;
        uVar9 = 0;
        goto LAB_000c1d48;
      }
    }
    else {
      if (uVar5 == 0) goto LAB_000c1cb0;
      if (uVar5 != 2) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: set wrong parameters\n","SetTpcDlAlgoCtrl");
        return 0;
      }
      if (0x1f < local_18._2_2_) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: Set wrong parameters! Entry index should be between 0~31 .\n","SetTpcDlAlgoCtrl"
              );
        return 0;
      }
      if ((local_14 & 0xffff) < 2) {
        sVar2 = (short)(local_14 >> 0x10);
        if (0x1ff < ((local_14 >> 0x10) + 0x100 & 0xffff)) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: Set wrong parameters! Down-link Tx Alpha Power should between -256~255. \n",
                 "SetTpcDlAlgoCtrl");
          return 0;
        }
        uVar9 = local_18._2_2_ & 0xff;
        uVar6 = local_14 & 0xff;
        cVar8 = '\0';
        goto LAB_000c1d48;
      }
    }
    if (-1 < DebugLevel) {
      printk("%s: Set wrong parameters! Down-link Tx Type 0: MU-MIMO, 1: OFDMA. \n",
             "SetTpcDlAlgoCtrl");
      return 0;
    }
  }
  return 0;
}


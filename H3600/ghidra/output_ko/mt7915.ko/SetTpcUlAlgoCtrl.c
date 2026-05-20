// module: mt7915.ko
// function: SetTpcUlAlgoCtrl @ 0xc1948
// size: 540 bytes
//

undefined4 SetTpcUlAlgoCtrl(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  byte bVar9;
  undefined4 local_14;
  
  uVar7 = 0;
  local_14 = 0;
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: No parameters!!\n","SetTpcUlAlgoCtrl");
    return 0;
  }
  iVar3 = rstrtok(param_2,&_LC156);
  if (iVar3 == 0) {
LAB_000c1aa0:
    uVar7 = local_14 >> 8 & 0xff;
    if (uVar7 < 0x3d) {
      uVar5 = 0;
      uVar8 = 0;
      bVar9 = 0;
      bVar6 = 0;
      bVar2 = 0;
LAB_000c1b14:
      uVar4 = TpcUlAlgoCtrl(param_1,uVar5,uVar7,bVar6,bVar2,bVar9,uVar8);
      return uVar4;
    }
    if (-1 < DebugLevel) {
      printk("%s: Set wrong parameters! Ap Tx Power should be between 0~60. \n","SetTpcUlAlgoCtrl");
    }
  }
  else {
    do {
      uVar1 = os_str_tol(iVar3,0,10);
      uVar5 = uVar7 & 0xff;
      uVar7 = uVar7 + 1;
      *(undefined1 *)((int)&local_14 + uVar5) = uVar1;
      iVar3 = rstrtok(0,&_LC156);
    } while (iVar3 != 0);
    uVar5 = local_14 & 0xff;
    uVar7 = 0;
    bVar6 = local_14._1_1_;
    if (uVar5 == 1) {
      if (local_14._1_1_ < 0x20) {
        if (0x5a < local_14._2_1_) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: Set wrong parameters! Target TSSI be between 0~90. \n","SetTpcUlAlgoCtrl");
          return 0;
        }
        uVar8 = 0;
        bVar9 = 0;
        bVar2 = local_14._2_1_;
        goto LAB_000c1b14;
      }
    }
    else {
      if (uVar5 == 0) goto LAB_000c1aa0;
      if (uVar5 != 2) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: set wrong parameters\n","SetTpcUlAlgoCtrl");
        return 0;
      }
      if (local_14._1_1_ < 0x20) {
        if (0x1f < local_14._2_1_) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: Set wrong parameters! Uplink Power Headroom should be between 0~31.\n",
                 "SetTpcUlAlgoCtrl");
          return 0;
        }
        uVar8 = local_14 >> 0x18;
        bVar9 = local_14._2_1_;
        bVar2 = 0;
        goto LAB_000c1b14;
      }
    }
    if (-1 < DebugLevel) {
      printk("%s: Set wrong parameters! Entry index should be between 0~31 .\n","SetTpcUlAlgoCtrl");
    }
  }
  return 0;
}


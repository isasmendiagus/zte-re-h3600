// module: mt7915.ko
// function: SetGroupTblEntryProc @ 0x8c6fc
// size: 1688 bytes
//

undefined4 SetGroupTblEntryProc(undefined4 param_1,char *param_2)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  char *pcVar12;
  char *pcVar13;
  char *pcVar14;
  char *pcVar15;
  char *pcVar16;
  char *pcVar17;
  char *pcVar18;
  char *pcVar19;
  char *pcVar20;
  char *pcVar21;
  char *pcVar22;
  char *pcVar23;
  char *pcVar24;
  char *pcVar25;
  int iVar26;
  uint uVar27;
  undefined4 uVar28;
  char *local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_50 = 4;
  local_54 = param_2;
  pcVar4 = strsep(&local_54,"_");
  if (((((pcVar4 != (char *)0x0) && (pcVar5 = strsep(&local_54,"_"), pcVar5 != (char *)0x0)) &&
       (pcVar6 = strsep(&local_54,"_"), pcVar6 != (char *)0x0)) &&
      ((pcVar7 = strsep(&local_54,"_"), pcVar7 != (char *)0x0 &&
       (pcVar8 = strsep(&local_54,"_"), pcVar8 != (char *)0x0)))) &&
     ((pcVar9 = strsep(&local_54,"_"), pcVar9 != (char *)0x0 &&
      (pcVar10 = strsep(&local_54,"_"), pcVar10 != (char *)0x0)))) {
    pcVar11 = strsep(&local_54,"_");
    if (pcVar11 != (char *)0x0) {
      pcVar12 = strsep(&local_54,"_");
      if (pcVar12 != (char *)0x0) {
        pcVar13 = strsep(&local_54,"_");
        if (pcVar13 != (char *)0x0) {
          pcVar14 = strsep(&local_54,"_");
          if (pcVar14 != (char *)0x0) {
            pcVar15 = strsep(&local_54,"_");
            if (pcVar15 != (char *)0x0) {
              pcVar16 = strsep(&local_54,"_");
              if (pcVar16 != (char *)0x0) {
                pcVar17 = strsep(&local_54,"_");
                if (pcVar17 != (char *)0x0) {
                  pcVar18 = strsep(&local_54,"_");
                  if (pcVar18 != (char *)0x0) {
                    pcVar19 = strsep(&local_54,"_");
                    if (pcVar19 != (char *)0x0) {
                      pcVar20 = strsep(&local_54,"_");
                      if (pcVar20 != (char *)0x0) {
                        pcVar21 = strsep(&local_54,"_");
                        if (pcVar21 != (char *)0x0) {
                          pcVar22 = strsep(&local_54,"_");
                          if (pcVar22 != (char *)0x0) {
                            pcVar23 = strsep(&local_54,"_");
                            if (pcVar23 != (char *)0x0) {
                              pcVar24 = strsep(&local_54,"_");
                              if (pcVar24 != (char *)0x0) {
                                pcVar25 = strsep(&local_54,"");
                                if (pcVar25 != (char *)0x0) {
                                  local_4c = os_str_tol(pcVar4,0,10);
                                  bVar1 = os_str_tol(pcVar5,0,10);
                                  local_48._0_1_ = (byte)local_48 & 0xfc | bVar1 & 3;
                                  bVar1 = os_str_tol(pcVar6,0,10);
                                  local_48 = CONCAT31(local_48._1_3_,
                                                      (byte)local_48 & 0xf3 | (bVar1 & 3) << 2);
                                  uVar2 = os_str_tol(pcVar11,0,10);
                                  local_48._0_2_ = CONCAT11(uVar2,(byte)local_48);
                                  uVar2 = os_str_tol(pcVar12,0,10);
                                  local_48._0_3_ = CONCAT12(uVar2,(undefined2)local_48);
                                  uVar2 = os_str_tol(pcVar13,0,10);
                                  local_48 = CONCAT13(uVar2,(undefined3)local_48);
                                  uVar2 = os_str_tol(pcVar14,0,10);
                                  local_44 = CONCAT31(local_44._1_3_,uVar2);
                                  uVar2 = os_str_tol(pcVar15,0,10);
                                  local_44._0_2_ = CONCAT11(uVar2,(undefined1)local_44);
                                  uVar2 = os_str_tol(pcVar16,0,10);
                                  local_44._0_3_ = CONCAT12(uVar2,(undefined2)local_44);
                                  uVar2 = os_str_tol(pcVar17,0,10);
                                  local_44 = CONCAT13(uVar2,(undefined3)local_44);
                                  bVar1 = os_str_tol(pcVar18,0,10);
                                  local_40._0_1_ = (byte)local_40 & 0xf0 | bVar1 & 0xf;
                                  cVar3 = os_str_tol(pcVar19,0,10);
                                  local_40 = CONCAT31(local_40._1_3_,
                                                      (byte)local_40 & 0xf | cVar3 << 4);
                                  bVar1 = os_str_tol(pcVar20,0,10);
                                  local_40._0_2_ =
                                       CONCAT11(local_40._1_1_ & 0xf0 | bVar1 & 0xf,(byte)local_40);
                                  cVar3 = os_str_tol(pcVar21,0,10);
                                  local_40._0_2_ =
                                       CONCAT11(local_40._1_1_ & 0xf | cVar3 << 4,(byte)local_40);
                                  bVar1 = os_str_tol(pcVar22,0,10);
                                  local_40._0_3_ =
                                       CONCAT12(local_40._2_1_ & 0xf0 | bVar1 & 0xf,
                                                (undefined2)local_40);
                                  cVar3 = os_str_tol(pcVar23,0,10);
                                  local_40._0_3_ =
                                       CONCAT12(local_40._2_1_ & 0xf | cVar3 << 4,
                                                (undefined2)local_40);
                                  bVar1 = os_str_tol(pcVar24,0,10);
                                  local_40._3_1_ = local_40._3_1_ & 0xf0 | bVar1 & 0xf;
                                  cVar3 = os_str_tol(pcVar25,0,10);
                                  local_40 = CONCAT13(local_40._3_1_ & 0xf | cVar3 << 4,
                                                      (undefined3)local_40);
                                  bVar1 = os_str_tol(pcVar7,0,10);
                                  local_48._0_1_ = (byte)local_48 & 0xef | (bVar1 & 1) << 4;
                                  bVar1 = os_str_tol(pcVar8,0,10);
                                  local_48._0_1_ = (byte)local_48 & 0xdf | (bVar1 & 1) << 5;
                                  bVar1 = os_str_tol(pcVar9,0,10);
                                  local_48._0_1_ = (byte)local_48 & 0xbf | (bVar1 & 1) << 6;
                                  cVar3 = os_str_tol(pcVar10,0,10);
                                  local_48 = CONCAT31(local_48._1_3_,
                                                      (byte)local_48 & 0x7f | cVar3 << 7);
                                  if ((3 < DebugLevel) &&
                                     (printk(&_LC0,"SetGroupTblEntryProc"), 3 < DebugLevel)) {
                                    uVar27 = local_48 & 0xff;
                                    printk("Index:%d NumUser:%d BW:%d NS(0~3):%d %d %d %d\n",
                                           local_4c,local_48 & 3,(uVar27 << 0x1c) >> 0x1e,
                                           (uVar27 << 0x1b) >> 0x1f,(uVar27 << 0x1a) >> 0x1f,
                                           (uVar27 << 0x19) >> 0x1f,local_48 >> 7 & 1);
                                    if (3 < DebugLevel) {
                                      printk("PFID(0~3):%d %d %d %d SGI:%d IsUsed:%d IsDisable:%d\n"
                                             ,local_48._1_1_,local_48._2_1_,local_48._3_1_,
                                             local_44 & 0xff,local_44 >> 8 & 0xff,
                                             local_44 >> 0x10 & 0xff,local_44 >> 0x18);
                                      if (3 < DebugLevel) {
                                        printk("InitMCS(0~3):%d %d %d %d DMCS(0~3):%d %d %d %d\n",
                                               local_40 & 0xf,(byte)local_40 >> 4,
                                               local_40._1_1_ & 0xf,local_40._1_1_ >> 4,
                                               local_40._2_1_ & 0xf,local_40._2_1_ >> 4,
                                               local_40._3_1_ & 0xf,local_40._3_1_ >> 4);
                                      }
                                    }
                                  }
                                  iVar26 = AndesAllocCmdMsg(param_1,0x14);
                                  if (iVar26 != 0) {
                                    local_3c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_3c));
                                    local_38 = CONCAT31(local_38._1_3_,10);
                                    uVar28 = 1;
                                    AndesInitCmdMsg(iVar26,local_3c,local_38,local_34,local_30,
                                                    local_2c);
                                    AndesAppendCmdMsg(iVar26,&local_50,4);
                                    AndesAppendCmdMsg(iVar26,&local_4c,0x10);
                                    AndesSendCmdMsg(param_1,iVar26);
                                    goto LAB_0008cc64;
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
              }
            }
          }
        }
      }
    }
  }
  uVar28 = 0;
LAB_0008cc64:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetGroupTblEntryProc",uVar28);
  }
  return uVar28;
}


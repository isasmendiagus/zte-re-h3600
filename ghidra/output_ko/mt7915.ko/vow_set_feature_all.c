// module: mt7915.ko
// function: vow_set_feature_all @ 0x4133c
// size: 952 bytes
//

undefined4 vow_set_feature_all(int param_1)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  byte *pbVar7;
  undefined2 local_48;
  byte local_46;
  byte local_45;
  undefined2 local_44;
  undefined2 local_40;
  undefined2 local_34;
  byte local_32;
  byte local_31;
  ushort local_30;
  ushort local_2c;
  undefined4 local_28;
  byte local_24;
  
  __memzero(&local_48,0x28);
  uVar5 = local_28;
  local_34 = *(undefined2 *)(param_1 + 0xa7a2f0);
  uVar4 = (uint)local_30;
  local_31 = local_31 & 0xd | (*(byte *)(param_1 + 0xa7a32c) & 1) << 1 |
             (*(byte *)(param_1 + 0xa7a2eb) & 1) << 4 | (*(byte *)(param_1 + 0xa7a2ea) & 1) << 5 |
             (*(byte *)(param_1 + 0xa7a2e9) & 1) << 6 | *(char *)(param_1 + 0xa7a2e8) << 7;
  uVar6 = 0;
  local_32 = local_32 & 200 | *(byte *)(param_1 + 0xa7a2ee) & 7 |
             (*(byte *)(param_1 + 0xa7a2ed) & 1) << 4 | (*(byte *)(param_1 + 0xa7a2ec) & 1) << 5;
  local_45 = local_45 | 0xf2;
  local_46 = local_46 | 0x31;
  local_48 = 0xffff;
  local_44 = 0xffff;
  local_40 = 0xffff;
  pbVar7 = (byte *)(param_1 + 0xa79842);
  do {
    uVar1 = (uint)*pbVar7 << (uVar6 & 0xff);
    local_30 = (ushort)uVar4 | (ushort)uVar1;
    uVar6 = uVar6 + 1;
    uVar4 = uVar4 | uVar1 & 0xffff;
    pbVar7 = pbVar7 + 0x1c;
  } while (uVar6 != 0x10);
  uVar6 = (uint)local_2c;
  uVar4 = 0;
  pbVar7 = (byte *)(param_1 + 0xa79841);
  do {
    uVar1 = (uint)*pbVar7 << (uVar4 & 0xff);
    local_2c = (ushort)uVar6 | (ushort)uVar1;
    uVar4 = uVar4 + 1;
    uVar6 = uVar6 | uVar1 & 0xffff;
    pbVar7 = pbVar7 + 0x1c;
  } while (uVar4 != 0x10);
  if (*(byte *)(param_1 + 0xa797a4) - 1 < 2) {
    bVar3 = (byte)local_28;
    bVar2 = (*(byte *)(param_1 + 0xa7a308) & 1) << 1;
    local_28 = CONCAT31(local_28._1_3_,(byte)local_28 & 0xfd | 1 | bVar2);
    if ((*(uint *)(param_1 + 0xa7a2e8) & 0xff00ff) != 0) {
      uVar4 = CONCAT31(local_28._1_3_,
                       bVar3 & 0xf5 | 1 | bVar2 | 4 | (*(byte *)(param_1 + 0xa7a309) & 1) << 3) &
              0xfe1f | 0x10 | (*(byte *)(param_1 + 0xa7a30a) & 0xf) << 5;
      local_28._2_2_ = SUB42(uVar5,2);
      local_28._0_1_ = (byte)uVar4;
      local_28._0_2_ =
           CONCAT11((byte)(uVar4 >> 8) & 0xeb | 2 | (*(byte *)(param_1 + 0xa7a30b) & 1) << 2 | 8 |
                    (*(byte *)(param_1 + 0xa7a30c) & 1) << 4,(byte)local_28);
      uVar4 = local_28 & 0xfffc1fff;
      uVar6 = uVar4 | (*(byte *)(param_1 + 0xa7a30d) & 0x1f) << 0xd;
      local_24 = local_24 & 0xf1 | 1 | (*(byte *)(param_1 + 0xa7a319) & 7) << 1;
      local_28._0_2_ = (undefined2)uVar6;
      local_28 = CONCAT13((byte)(uVar4 >> 0x18) & 0x81 | 1 |
                          (*(byte *)(param_1 + 0xa7a311) & 1) << 1 |
                          (*(byte *)(param_1 + 0xa7a318) & 0x1f) << 2,
                          CONCAT12((byte)(uVar6 >> 0x10) & 0x57 | 4 |
                                   (*(byte *)(param_1 + 0xa7a30e) & 1) << 3 | 0x10 |
                                   (*(byte *)(param_1 + 0xa7a30f) & 1) << 5 | 0x40 |
                                   *(char *)(param_1 + 0xa7a310) << 7,(undefined2)local_28));
    }
  }
  if (2 < DebugLevel) {
    printk("%s:(u2Bss_0_to_16_CtrlValue  = 0x%x)\n","vow_set_feature_all");
    if (2 < DebugLevel) {
      printk("%s:(u2RefillPerildValue = 0x%x)\n","vow_set_feature_all",
             *(undefined1 *)(param_1 + 0xa7a2ee));
      if (2 < DebugLevel) {
        printk("%s:(u2Dbdc1SearchRuleValue = 0x%x)\n","vow_set_feature_all",
               *(undefined1 *)(param_1 + 0xa7a2ed));
        if (2 < DebugLevel) {
          printk("%s:(u2Dbdc0SearchRuleValue = 0x%x)\n","vow_set_feature_all",
                 *(undefined1 *)(param_1 + 0xa7a2ec));
          if (2 < DebugLevel) {
            printk("%s:(u2EnTxopNoChangeBssValue = 0x%x)\n","vow_set_feature_all",
                   *(undefined1 *)(param_1 + 0xa7a2eb));
            if (2 < DebugLevel) {
              printk("%s:(u2AirTimeFairnessValue = 0x%x)\n","vow_set_feature_all",
                     *(undefined1 *)(param_1 + 0xa7a2ea));
              if (2 < DebugLevel) {
                printk("%s:(u2EnbwrefillValue = 0x%x)\n","vow_set_feature_all",
                       *(undefined1 *)(param_1 + 0xa7a2e9));
                if (2 < DebugLevel) {
                  printk("%s:(u2EnbwCtrlValue = 0x%x)\n","vow_set_feature_all",
                         *(undefined1 *)(param_1 + 0xa7a2e8));
                  if (2 < DebugLevel) {
                    printk("%s:(u2WeightedAirTimeFairnessValue = 0x%x)\n","vow_set_feature_all",
                           *(undefined1 *)(param_1 + 0xa7a32c));
                    if (2 < DebugLevel) {
                      printk("%s:(u2BssCheckTimeToken_0_to_16_CtrlValue = 0x%x)\n",
                             "vow_set_feature_all",local_30);
                      if (2 < DebugLevel) {
                        printk("%s:(u2BssCheckLengthToken_0_to_16_CtrlValue = 0x%x)\n",
                               "vow_set_feature_all",local_2c);
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
  uVar5 = MtCmdSetVoWFeatureCtrl(param_1,&local_48);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_feature_all",uVar5,0x28);
  }
  return uVar5;
}


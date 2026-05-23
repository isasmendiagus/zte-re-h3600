// module: mt7915.ko
// function: MtCmdSetVoWFeatureCtrlRsp @ 0x1ac1d8
// size: 904 bytes
//

void MtCmdSetVoWFeatureCtrlRsp(int param_1,short *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  byte bVar4;
  short *psVar5;
  short *psVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  puVar1 = *(undefined4 **)(param_1 + 0xc);
  psVar6 = param_2;
  do {
    psVar5 = psVar6;
    puVar3 = puVar1;
    psVar6 = psVar5 + 8;
    uVar9 = *(undefined4 *)(psVar5 + 2);
    uVar8 = *(undefined4 *)(psVar5 + 4);
    uVar2 = *(undefined4 *)(psVar5 + 6);
    *puVar3 = *(undefined4 *)psVar5;
    puVar3[1] = uVar9;
    puVar3[2] = uVar8;
    puVar3[3] = uVar2;
    puVar1 = puVar3 + 4;
  } while (psVar6 != param_2 + 0x10);
  uVar2 = *(undefined4 *)(psVar5 + 10);
  puVar3[4] = *(undefined4 *)psVar6;
  puVar3[5] = uVar2;
  if (3 < DebugLevel) {
    printk("%s: ExtCmd = 0x%x\n","MtCmdSetVoWFeatureCtrlRsp",*(undefined1 *)(param_1 + 3));
    if ((*(byte *)(param_1 + 4) & 8) == 0) goto LAB_001ac250;
    if (DebugLevel < 4) goto LAB_001ac258;
    printk("%s: Get fail!\n","MtCmdSetVoWFeatureCtrlRsp");
LAB_001ac4ac:
    if (*param_2 == 0) {
LAB_001ac4fc:
      bVar4 = *(byte *)(param_2 + 1);
      if ((bVar4 & 1) != 0) {
        if (DebugLevel < 4) {
          if ((bVar4 & 0x20) != 0) goto LAB_001ac274;
          goto LAB_001ac518;
        }
        printk("%s: u2RefillPerildValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",
               *(byte *)(param_2 + 0xb) & 7);
        bVar4 = *(byte *)(param_2 + 1);
      }
      goto LAB_001ac2d8;
    }
    if (3 < DebugLevel) {
      printk("%s: u2Bss_0_to_16_CtrlValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",param_2[10]);
      goto LAB_001ac4fc;
    }
    if ((*(byte *)(param_2 + 1) & 0x10) == 0) {
      if ((*(byte *)(param_2 + 1) & 0x20) != 0) goto LAB_001ac274;
      goto LAB_001ac420;
    }
LAB_001ac518:
    uVar7 = (uint)*(byte *)((int)param_2 + 3);
    if ((*(byte *)((int)param_2 + 3) & 0x10) != 0) goto LAB_001ac434;
    goto LAB_001ac360;
  }
  if ((*(byte *)(param_1 + 4) & 8) == 0) {
LAB_001ac250:
    if (3 < DebugLevel) {
      printk("%s: Set fail!\n","MtCmdSetVoWFeatureCtrlRsp");
      goto LAB_001ac4ac;
    }
  }
LAB_001ac258:
  bVar4 = *(byte *)(param_2 + 1);
  if ((bVar4 & 1) == 0) {
LAB_001ac2d8:
    if ((bVar4 & 0x10) == 0) goto LAB_001ac264;
    if (3 < DebugLevel) {
      printk("%s: u2Dbdc1SearchRuleValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",
             ((uint)*(byte *)(param_2 + 0xb) << 0x1b) >> 0x1f);
      bVar4 = *(byte *)(param_2 + 1);
      goto LAB_001ac264;
    }
    bVar4 = *(byte *)((int)param_2 + 3);
    uVar7 = (uint)bVar4;
    if ((bVar4 & 0x10) != 0) goto LAB_001ac440;
    if ((bVar4 & 0x20) != 0) goto LAB_001ac370;
    goto LAB_001ac2fc;
  }
LAB_001ac264:
  if ((bVar4 & 0x20) == 0) {
LAB_001ac420:
    uVar7 = (uint)*(byte *)((int)param_2 + 3);
    if ((*(byte *)((int)param_2 + 3) & 0x10) == 0) {
LAB_001ac360:
      if ((uVar7 & 0x20) != 0) {
        if (3 < DebugLevel) {
          printk("%s: u2AirTimeFairnessValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",
                 ((uint)*(byte *)((int)param_2 + 0x17) << 0x1a) >> 0x1f);
          uVar7 = (uint)*(byte *)((int)param_2 + 3);
          goto LAB_001ac2fc;
        }
LAB_001ac370:
        if ((uVar7 & 0x80) == 0) goto LAB_001ac378;
LAB_001ac318:
        if (param_2[4] != 0) {
          return;
        }
        goto LAB_001ac324;
      }
LAB_001ac2fc:
      if ((uVar7 & 0x40) != 0) {
        if (DebugLevel < 4) goto LAB_001ac30c;
        printk("%s: u2EnbwrefillValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",
               ((uint)*(byte *)((int)param_2 + 0x17) << 0x19) >> 0x1f);
        uVar7 = (uint)*(byte *)((int)param_2 + 3);
      }
LAB_001ac3d4:
      if (uVar7 >> 7 != 0) {
        if (DebugLevel < 4) {
          return;
        }
        printk("%s: u2EnbwCtrlValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",
               *(byte *)((int)param_2 + 0x17) >> 7);
      }
      goto LAB_001ac288;
    }
    if (3 < DebugLevel) {
      printk("%s: u2EnTxopNoChangeBssValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",
             ((uint)*(byte *)((int)param_2 + 0x17) << 0x1b) >> 0x1f);
      uVar7 = (uint)*(byte *)((int)param_2 + 3);
      goto LAB_001ac360;
    }
LAB_001ac434:
    if ((uVar7 & 0x40) == 0) goto LAB_001ac280;
LAB_001ac378:
    if (param_2[2] != 0) {
      return;
    }
  }
  else {
    if (3 < DebugLevel) {
      printk("%s: u2Dbdc0SearchRuleValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",
             ((uint)*(byte *)(param_2 + 0xb) << 0x1a) >> 0x1f);
      goto LAB_001ac420;
    }
LAB_001ac274:
    uVar7 = (uint)*(byte *)((int)param_2 + 3);
    if ((*(byte *)((int)param_2 + 3) & 0x20) == 0) {
LAB_001ac440:
      if ((uVar7 & 0x40) != 0) {
LAB_001ac30c:
        if (param_2[2] != 0) {
          return;
        }
        goto LAB_001ac318;
      }
      goto LAB_001ac3d4;
    }
LAB_001ac280:
    if ((uVar7 & 0x80) != 0) {
      return;
    }
LAB_001ac288:
    if (param_2[2] != 0) {
      if (DebugLevel < 4) {
        return;
      }
      printk("%s: u2BssCheckTimeToken_0_to_16_CtrlValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",
             param_2[0xc]);
    }
  }
  if (param_2[4] != 0) {
    if (DebugLevel < 4) {
      return;
    }
    printk("%s: u2BssCheckLengthToken_0_to_16_CtrlValue = 0x%0x\n","MtCmdSetVoWFeatureCtrlRsp",
           param_2[0xe]);
  }
LAB_001ac324:
  if (3 < DebugLevel) {
    printk("%s: i am here~\n","MtCmdSetVoWFeatureCtrlRsp");
    return;
  }
  return;
}


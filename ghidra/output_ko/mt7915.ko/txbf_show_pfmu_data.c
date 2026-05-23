// module: mt7915.ko
// function: txbf_show_pfmu_data @ 0x176f40
// size: 2520 bytes
//

void txbf_show_pfmu_data(int *param_1,undefined4 param_2,void *param_3)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  undefined2 local_ac;
  undefined2 local_aa;
  undefined2 local_a8;
  undefined2 local_a6;
  undefined2 local_a4;
  undefined2 local_a2;
  undefined2 local_a0;
  undefined2 local_9e;
  undefined2 local_9c;
  undefined2 local_9a;
  undefined2 local_98;
  undefined2 local_96;
  undefined2 local_94;
  undefined2 local_92;
  undefined2 local_90;
  undefined2 local_8e;
  undefined2 local_8c;
  undefined2 local_8a;
  undefined2 local_88;
  undefined2 local_86;
  undefined2 local_84;
  undefined2 local_82;
  undefined2 local_80;
  undefined2 local_7e;
  undefined2 local_7c;
  undefined2 local_7a;
  undefined2 local_78;
  undefined2 local_76;
  undefined2 local_74;
  undefined2 local_72;
  undefined2 local_70;
  undefined2 local_6e;
  undefined2 local_6c;
  undefined2 local_6a;
  undefined2 local_68;
  undefined2 local_66;
  undefined2 local_64;
  undefined2 local_62;
  undefined2 local_60;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_52;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_42;
  undefined2 local_40;
  undefined2 local_3e;
  byte local_3c;
  byte local_3b;
  byte local_3a;
  byte local_39;
  byte local_38;
  byte local_37;
  byte local_36;
  byte local_35;
  
  uVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  cVar1 = wlan_config_get_he_bw();
  uVar3 = wlan_config_get_tx_stream(uVar2);
  memcpy(&local_ac,param_3,0x84);
  if (uVar3 < 5) {
    if (DebugLevel < 3) {
      return;
    }
    uVar3 = (uint)(local_aa._1_1_ >> 1);
    uVar9 = (uint)(local_ac._1_1_ >> 1);
    uVar11 = (uint)(local_92._1_1_ >> 1);
    uVar12 = (uint)(local_9c._1_1_ >> 1);
    uVar13 = (uint)(local_9e._1_1_ >> 1);
    uVar8 = local_aa & 0x1ff;
    uVar7 = local_ac & 0x1ff;
    uVar6 = local_92 & 0x1ff;
    uVar5 = local_9c & 0x1ff;
    uVar10 = local_9e & 0x1ff;
    printk("================= TxBf profile Data - Subcarrier Idx = %d(0x%03x) ===================\n================================= Low Seg Angles ====================================\nPsi41 = 0x%02x, Phi31 = 0x%03x, Psi31 = 0x%02x, Phi21 = 0x%03x Psi21 = 0x%02x, Phi11 = 0x%03x,\nPsi43 = 0x%02x, Phi33 = 0x%03x, Psi42 = 0x%02x, Phi32 = 0x%03x Psi32 = 0x%02x, Phi22 = 0x%03x,\n"
           ,param_2,param_2,local_a8._1_1_ >> 1,local_a8 & 0x1ff,uVar3,uVar8,uVar9,uVar7,uVar11,
           uVar6,uVar12,uVar5,uVar13,uVar10);
    if ((byte)(cVar1 - 3U) < 2) {
      if (DebugLevel < 3) {
        return;
      }
      uVar6 = local_64 & 0x1ff;
      uVar3 = (uint)(local_74._1_1_ >> 1);
      uVar5 = local_66 & 0x1ff;
      uVar9 = (uint)(local_5a._1_1_ >> 1);
      uVar11 = (uint)(local_64._1_1_ >> 1);
      uVar12 = (uint)(local_66._1_1_ >> 1);
      uVar8 = local_74 & 0x1ff;
      uVar7 = local_5a & 0x1ff;
      printk("================================== High Seg Angles ====================================\nPsi41 = 0x%02x, Phi31 = 0x%03x, Psi31 = 0x%02x, Phi21 = 0x%03x Psi21 = 0x%02x, Phi11 = 0x%03x,\nPsi43 = 0x%02x, Phi33 = 0x%03x, Psi42 = 0x%02x, Phi32 = 0x%03x Psi32 = 0x%02x, Phi22 = 0x%03x,\n"
             ,local_70._1_1_ >> 1,local_70 & 0x1ff,local_72._1_1_ >> 1,local_72 & 0x1ff,uVar3,uVar8,
             uVar9,uVar7,uVar11,uVar6,uVar12,uVar5,uVar13,uVar10);
      if (DebugLevel < 3) {
        return;
      }
      printk("================================= Low Seg SNRs ===================================\nSNR00 = 0x%01x, SNR01 = 0x%01x, SNR02 = 0x%01x, SNR03 = 0x%01x\n"
             ,local_3c & 0xf,local_3c >> 4,local_3b & 0xf,local_3b >> 4,uVar3,uVar8,uVar9,uVar7,
             uVar11,uVar6,uVar12,uVar5,uVar13,uVar10);
      if (DebugLevel < 3) {
        return;
      }
      pcVar4 = 
      "================================ High Seg SNRs ===================================\nSNR00 = 0x%01x, SNR01 = 0x%01x, SNR02 = 0x%01x, SNR03 = 0x%01x\n"
      ;
      local_3b = local_37;
      local_3c = local_38;
    }
    else {
      if (DebugLevel < 3) {
        return;
      }
      pcVar4 = 
      "================================= Low Seg SNRs ===================================\nSNR00 = 0x%01x, SNR01 = 0x%01x, SNR02 = 0x%01x, SNR03 = 0x%01x\n"
      ;
    }
    printk(pcVar4,local_3c & 0xf,local_3c >> 4,local_3b & 0xf,local_3b >> 4,uVar3,uVar8,uVar9,uVar7,
           uVar11,uVar6,uVar12,uVar5,uVar13,uVar10);
  }
  else {
    if (DebugLevel < 3) {
      if ((byte)(cVar1 - 3U) < 2) {
        return;
      }
    }
    else {
      uVar3 = (uint)(local_78._1_1_ >> 1);
      uVar9 = local_78 & 0x1ff;
      printk("================ TxBf profile Data - Subcarrier Idx = %d(0x%03x) =================\n=============================== Low Seg Angles ==================================\nPsi31 = 0x%02x, Phi21 = 0x%03x, Psi21 = 0x%02x, Phi11 = 0x%03x\nPsi51 = 0x%02x, Phi41 = 0x%03x, Psi41 = 0x%02x, Phi31 = 0x%03x\nPsi71 = 0x%02x, Phi61 = 0x%03x, Psi61 = 0x%02x, Phi51 = 0x%03x\nPsi32 = 0x%02x, Phi22 = 0x%03x, Psi81 = 0x%02x, Phi71 = 0x%03x\nPsi52 = 0x%02x, Phi42 = 0x%03x, Psi42 = 0x%02x, Phi32 = 0x%03x\nPsi72 = 0x%02x, Phi62 = 0x%03x, Psi62 = 0x%02x, Phi52 = 0x%03x\nPsi43 = 0x%02x, Phi33 = 0x%03x, Psi82 = 0x%02x, Phi72 = 0x%03x\nPsi63 = 0x%02x, Phi53 = 0x%03x, Psi53 = 0x%02x, Phi43 = 0x%03x\nPsi83 = 0x%02x, Phi73 = 0x%03x, Psi73 = 0x%02x, Phi63 = 0x%03x\nPsi64 = 0x%02x, Phi54 = 0x%03x, Psi54 = 0x%02x, Phi44 = 0x%03x\nPsi84 = 0x%02x, Phi74 = 0x%03x, Psi74 = 0x%02x, Phi64 = 0x%03x\nPsi75 = 0x%02x, Phi65 = 0x%03x, Psi65 = 0x%02x, Phi55 = 0x%03x\nPsi76 = 0x%02x, Phi66 = 0x%03x, Psi85 = 0x%02x, Phi75 = 0x%03x\nPsi87 = 0x%02x, Phi77 = 0x%03x, Psi86 = 0x%02x, Phi76 = 0x%03x\n"
             ,param_2,param_2,local_aa._1_1_ >> 1,local_aa & 0x1ff,local_ac._1_1_ >> 1,
             local_ac & 0x1ff,local_a6._1_1_ >> 1,local_a6 & 0x1ff,local_a8._1_1_ >> 1,
             local_a8 & 0x1ff,local_a2._1_1_ >> 1,local_a2 & 0x1ff,local_a4._1_1_ >> 1,
             local_a4 & 0x1ff,local_9e._1_1_ >> 1,local_9e & 0x1ff,local_a0._1_1_ >> 1,
             local_a0 & 0x1ff,local_9a._1_1_ >> 1,local_9a & 0x1ff,local_9c._1_1_ >> 1,
             local_9c & 0x1ff,local_96._1_1_ >> 1,local_96 & 0x1ff,local_98._1_1_ >> 1,
             local_98 & 0x1ff,local_92._1_1_ >> 1,local_92 & 0x1ff,local_94._1_1_ >> 1,
             local_94 & 0x1ff,local_8e._1_1_ >> 1,local_8e & 0x1ff,local_90._1_1_ >> 1,
             local_90 & 0x1ff,local_8a._1_1_ >> 1,local_8a & 0x1ff,local_8c._1_1_ >> 1,
             local_8c & 0x1ff,local_86._1_1_ >> 1,local_86 & 0x1ff,local_88._1_1_ >> 1,
             local_88 & 0x1ff,local_82._1_1_ >> 1,local_82 & 0x1ff,local_84._1_1_ >> 1,
             local_84 & 0x1ff,local_7e._1_1_ >> 1,local_7e & 0x1ff,local_80._1_1_ >> 1,
             local_80 & 0x1ff,local_7a._1_1_ >> 1,local_7a & 0x1ff,local_7c._1_1_ >> 1,
             local_7c & 0x1ff,local_76._1_1_ >> 1,local_76 & 0x1ff,uVar3,uVar9);
      if ((byte)(cVar1 - 3U) < 2) {
        if (DebugLevel < 3) {
          return;
        }
        printk("=============================== High Seg Angles =================================\nPsi31 = 0x%02x, Phi21 = 0x%03x, Psi21 = 0x%02x, Phi11 = 0x%03x\nPsi51 = 0x%02x, Phi41 = 0x%03x, Psi41 = 0x%02x, Phi31 = 0x%03x\nPsi71 = 0x%02x, Phi61 = 0x%03x, Psi61 = 0x%02x, Phi51 = 0x%03x\nPsi32 = 0x%02x, Phi22 = 0x%03x, Psi81 = 0x%02x, Phi71 = 0x%03x\nPsi52 = 0x%02x, Phi42 = 0x%03x, Psi42 = 0x%02x, Phi32 = 0x%03x\nPsi72 = 0x%02x, Phi62 = 0x%03x, Psi62 = 0x%02x, Phi52 = 0x%03x\nPsi43 = 0x%02x, Phi33 = 0x%03x, Psi82 = 0x%02x, Phi72 = 0x%03x\nPsi63 = 0x%02x, Phi53 = 0x%03x, Psi53 = 0x%02x, Phi43 = 0x%03x\nPsi83 = 0x%02x, Phi73 = 0x%03x, Psi73 = 0x%02x, Phi63 = 0x%03x\nPsi64 = 0x%02x, Phi54 = 0x%03x, Psi54 = 0x%02x, Phi44 = 0x%03x\nPsi84 = 0x%02x, Phi74 = 0x%03x, Psi74 = 0x%02x, Phi64 = 0x%03x\nPsi75 = 0x%02x, Phi65 = 0x%03x, Psi65 = 0x%02x, Phi55 = 0x%03x\nPsi76 = 0x%02x, Phi66 = 0x%03x, Psi85 = 0x%02x, Phi75 = 0x%03x\nPsi87 = 0x%02x, Phi77 = 0x%03x, Psi86 = 0x%02x, Phi76 = 0x%03x\n"
               ,local_72._1_1_ >> 1,local_72 & 0x1ff,local_74._1_1_ >> 1,local_74 & 0x1ff,
               local_6e._1_1_ >> 1,local_6e & 0x1ff,local_70._1_1_ >> 1,local_70 & 0x1ff,
               local_6a._1_1_ >> 1,local_6a & 0x1ff,local_6c._1_1_ >> 1,local_6c & 0x1ff,
               local_66._1_1_ >> 1,local_66 & 0x1ff,local_68._1_1_ >> 1,local_68 & 0x1ff,
               local_62._1_1_ >> 1,local_62 & 0x1ff,local_64._1_1_ >> 1,local_64 & 0x1ff,
               local_5e._1_1_ >> 1,local_5e & 0x1ff,local_60._1_1_ >> 1,local_60 & 0x1ff,
               local_5a._1_1_ >> 1,local_5a & 0x1ff,local_5c._1_1_ >> 1,local_5c & 0x1ff,
               local_56._1_1_ >> 1,local_56 & 0x1ff,local_58._1_1_ >> 1,local_58 & 0x1ff,
               local_52._1_1_ >> 1,local_52 & 0x1ff,local_54._1_1_ >> 1,local_54 & 0x1ff,
               local_4e._1_1_ >> 1,local_4e & 0x1ff,local_50._1_1_ >> 1,local_50 & 0x1ff,
               local_4a._1_1_ >> 1,local_4a & 0x1ff,local_4c._1_1_ >> 1,local_4c & 0x1ff,
               local_46._1_1_ >> 1,local_46 & 0x1ff,local_48._1_1_ >> 1,local_48 & 0x1ff,
               local_42._1_1_ >> 1,local_42 & 0x1ff,local_44._1_1_ >> 1,local_44 & 0x1ff,
               local_3e._1_1_ >> 1,local_3e & 0x1ff,local_40._1_1_ >> 1,local_40 & 0x1ff,uVar3,uVar9
              );
      }
    }
    if (DebugLevel < 3) {
      return;
    }
    printk("================================= Low Seg SNRs ===================================\nSNR00 = 0x%01x, SNR01 = 0x%01x, SNR02 = 0x%01x, SNR03 = 0x%01x\nSNR04 = 0x%01x, SNR05 = 0x%01x, SNR06 = 0x%01x, SNR07 = 0x%01x\n"
           ,local_3c & 0xf,local_3c >> 4,local_3b & 0xf,local_3b >> 4,local_3a & 0xf,local_3a >> 4,
           local_39 & 0xf,local_39 >> 4);
    if ((byte)(cVar1 - 3U) < 2) {
      if (DebugLevel < 3) {
        return;
      }
      printk("================================ High Seg SNRs ===================================\nSNR00 = 0x%01x, SNR01 = 0x%01x, SNR02 = 0x%01x, SNR03 = 0x%01x\nSNR04 = 0x%01x, SNR05 = 0x%01x, SNR06 = 0x%01x, SNR07 = 0x%01x\n"
             ,local_38 & 0xf,local_38 >> 4,local_37 & 0xf,local_37 >> 4,local_36 & 0xf,local_36 >> 4
             ,local_35 & 0xf,local_35 >> 4);
    }
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("==================================================================================\n");
  return;
}


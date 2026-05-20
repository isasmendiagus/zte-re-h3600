// module: mt7915.ko
// function: mt7915_iBFPhaseCalReport @ 0x89b00
// size: 2232 bytes
//

void mt7915_iBFPhaseCalReport
               (int param_1,int param_2,int param_3,int param_4,char param_5,undefined1 param_6,
               undefined1 *param_7)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  byte bVar13;
  byte bVar14;
  undefined1 uVar15;
  byte bVar16;
  undefined1 uVar17;
  undefined1 uVar18;
  undefined1 uVar19;
  undefined1 uVar20;
  undefined1 uVar21;
  undefined1 uVar22;
  undefined1 uVar23;
  undefined1 uVar24;
  undefined1 uVar25;
  undefined1 uVar26;
  undefined1 uVar27;
  byte bVar28;
  undefined1 uVar29;
  undefined1 uVar30;
  undefined1 uVar31;
  undefined1 *puVar32;
  int iVar33;
  int iVar34;
  uint uVar35;
  uint uVar36;
  int iVar37;
  uint uVar38;
  uint uVar39;
  int iVar40;
  
  if (0 < DebugLevel) {
    printk("%s :: Calibrated iBF phases\n","mt7915_iBFPhaseCalReport");
  }
  iVar34 = DebugLevel;
  uVar1 = *param_7;
  uVar2 = param_7[3];
  uVar3 = param_7[7];
  uVar4 = param_7[1];
  uVar5 = param_7[2];
  uVar6 = param_7[4];
  uVar7 = param_7[5];
  uVar8 = param_7[6];
  uVar9 = param_7[8];
  uVar10 = param_7[9];
  uVar11 = param_7[10];
  switch(param_6) {
  case 1:
  case 3:
    if (param_3 != 0 && param_4 == 1) {
      uVar12 = param_7[0x24];
      uVar15 = param_7[0x25];
      uVar17 = param_7[0x26];
      uVar18 = param_7[0x27];
      uVar19 = param_7[0x2b];
      uVar20 = param_7[0x2c];
      uVar21 = param_7[0x29];
      uVar22 = param_7[0x2a];
      uVar23 = param_7[0x31];
      if (param_2 != 1) {
        return;
      }
      iVar33 = *(int *)(param_1 + 0xa78688) + (param_3 - 1U & 0xff) * 0x28;
      *(undefined1 *)(iVar33 + 0x21) = uVar23;
      *(undefined1 *)(iVar33 + 0x17) = uVar18;
      *(undefined1 *)(iVar33 + 0x14) = uVar12;
      *(undefined1 *)(iVar33 + 0x15) = uVar15;
      *(undefined1 *)(iVar33 + 0x19) = uVar21;
      *(undefined1 *)(iVar33 + 0x16) = uVar17;
      *(undefined1 *)(iVar33 + 0x1b) = uVar19;
      *(undefined1 *)(iVar33 + 0x1a) = uVar22;
      *(undefined1 *)(iVar33 + 0x1c) = uVar20;
      if (iVar34 < 1) {
        return;
      }
      printk("Group_M\n G%d_M_T2_H_SX2 = %d\n G%d_R2_UH_SX2 = %d\n G%d_R2_H_SX2 = %d\n G%d_R2_M_SX2 = %d\n"
             ,param_3,uVar23,param_3,uVar12,param_3,uVar15,param_3,uVar17);
      if (0 < DebugLevel) {
        printk("G%d_R2_L_SX2 = %d\n G%d_R3_UH_SX2 = %d\n G%d_R3_H_SX2 = %d\n G%d_R3_M_SX2 = %d\n G%d_R3_L_SX2 = %d\n"
               ,param_3,uVar18,param_3,uVar21,param_3,uVar22,param_3,uVar19,param_3,uVar20);
        if (DebugLevel < 1) {
          return;
        }
        printk("Group : %d\n",param_3);
        if (DebugLevel < 1) {
          return;
        }
        printk("Calibration == 1? or Verification == 2? : %d\n",param_6);
        if (DebugLevel < 1) {
          return;
        }
        printk("Calibrated result = %d\n",param_5);
      }
      goto joined_r0x00089c44;
    }
    if (param_3 == 0) {
      uVar12 = param_7[0x11];
      bVar13 = param_7[0x16];
      uVar36 = (uint)bVar13;
      bVar14 = param_7[0x17];
      uVar35 = (uint)bVar14;
      uVar15 = param_7[0x12];
      bVar16 = param_7[0x18];
      uVar38 = (uint)bVar16;
      uVar17 = param_7[0x1a];
      uVar18 = param_7[0x1b];
      uVar19 = param_7[0x1c];
      uVar20 = param_7[0x1d];
      uVar21 = param_7[0x1f];
      uVar22 = param_7[0x20];
      uVar23 = param_7[0x22];
      uVar24 = param_7[0x23];
      uVar25 = param_7[0x21];
      puVar32 = *(undefined1 **)(param_1 + 0xa78684);
      uVar26 = param_7[0x10];
      uVar27 = param_7[0x13];
      bVar28 = param_7[0x15];
      uVar39 = (uint)bVar28;
      uVar29 = param_7[0x2e];
      uVar30 = param_7[0x2f];
      uVar31 = param_7[0x30];
      if (param_2 != 1) {
        return;
      }
      puVar32[1] = uVar12;
      *puVar32 = uVar26;
      puVar32[3] = uVar27;
      puVar32[2] = uVar15;
      iVar34 = DebugLevel;
      puVar32[0x1e] = uVar29;
      puVar32[0x1f] = uVar30;
      puVar32[0x20] = uVar31;
      puVar32[6] = bVar13;
      puVar32[5] = bVar28;
      puVar32[7] = bVar14;
      puVar32[8] = bVar16;
      puVar32[10] = uVar17;
      puVar32[0xb] = uVar18;
      puVar32[0xc] = uVar19;
      puVar32[0xd] = uVar20;
      puVar32[0xf] = uVar21;
      puVar32[0x10] = uVar22;
      puVar32[0x11] = uVar25;
      puVar32[0x12] = uVar23;
      if (iVar34 < 1) {
        return;
      }
      printk("G0 and Group_M\n G0_M_T0_H = %d\n G0_M_T1_H = %d\n");
      if (DebugLevel < 1) {
LAB_00089ee8:
        if (0 < DebugLevel) {
          param_3 = 0;
          goto LAB_0008a32c;
        }
      }
      else {
        printk("G0_M_T2_H = %d\n",uVar31);
        if (DebugLevel < 1) {
          return;
        }
        printk("G0_R0_UH = %d\n G0_R0_H = %d\n G0_R0_M = %d\n G0_R0_L = %d\n G0_R1_UH = %d\n G0_R1_H = %d\n G0_R1_M = %d\n G0_R1_L = %d\n"
               ,uVar26,uVar12,uVar15,uVar27,uVar39,uVar36,uVar35,uVar38);
        if (0 < DebugLevel) {
          printk("G0_R2_UH = %d\n G0_R2_H = %d\n G0_R2_M = %d\n G0_R2_L = %d\n",uVar17,uVar18,uVar19
                 ,uVar20,uVar39,uVar36,uVar35,uVar38);
          if (DebugLevel < 1) {
            return;
          }
          printk("G0_R3_UH = %d\n G0_R3_H = %d\n G0_R3_M = %d\n G0_R3_L = %d\n G0_R3_UL = %d\n",
                 uVar21,uVar22,uVar25,uVar23,uVar24,uVar36,uVar35,uVar38);
          goto LAB_00089ee8;
        }
LAB_0008a354:
        if (DebugLevel < 1) {
          return;
        }
        printk("Calibrated result = %d\n",param_5);
        if (DebugLevel < 1) {
          return;
        }
        printk("0 : Means failed\n 1: means pass\n 2: means on-going\n");
      }
    }
    else {
      bVar13 = param_7[0x15];
      uVar35 = (uint)bVar13;
      uVar12 = param_7[0x11];
      uVar15 = param_7[0x13];
      uVar17 = param_7[0x1a];
      bVar14 = param_7[0x16];
      uVar39 = (uint)bVar14;
      uVar18 = param_7[0x1f];
      bVar16 = param_7[0x17];
      uVar38 = (uint)bVar16;
      uVar19 = param_7[0x20];
      bVar28 = param_7[0x18];
      uVar36 = (uint)bVar28;
      uVar20 = param_7[0x21];
      uVar21 = param_7[0x1b];
      uVar22 = param_7[0x22];
      uVar23 = param_7[0x1c];
      uVar24 = param_7[0x1d];
      uVar25 = param_7[0x23];
      uVar26 = param_7[0x10];
      iVar34 = *(int *)(param_1 + 0xa78688);
      uVar27 = param_7[0x12];
      uVar29 = param_7[0x2e];
      uVar30 = param_7[0x2f];
      uVar31 = param_7[0x30];
      if (param_2 != 1) {
        return;
      }
      iVar33 = (param_3 - 1U & 0xff) * 0x28;
      iVar37 = iVar34 + iVar33;
      *(undefined1 *)(iVar37 + 0x20) = uVar31;
      *(undefined1 *)(iVar37 + 0x1e) = uVar29;
      *(undefined1 *)(iVar37 + 0x1f) = uVar30;
      *(undefined1 *)(iVar34 + iVar33) = uVar26;
      *(undefined1 *)(iVar37 + 2) = uVar27;
      *(undefined1 *)(iVar37 + 1) = uVar12;
      *(byte *)(iVar37 + 5) = bVar13;
      *(undefined1 *)(iVar37 + 3) = uVar15;
      iVar34 = DebugLevel;
      *(byte *)(iVar37 + 6) = bVar14;
      *(byte *)(iVar37 + 7) = bVar16;
      *(byte *)(iVar37 + 8) = bVar28;
      *(undefined1 *)(iVar37 + 10) = uVar17;
      *(undefined1 *)(iVar37 + 0xb) = uVar21;
      *(undefined1 *)(iVar37 + 0xc) = uVar23;
      *(undefined1 *)(iVar37 + 0xd) = uVar24;
      if (iVar34 < 1) {
        return;
      }
      printk("G%d and Group_M\n G%d_M_T0_H = %d\n G%d_M_T1_H = %d\n",param_3,param_3,uVar29,param_3,
             uVar30);
      if (0 < DebugLevel) {
        printk("G0_M_T2_H = %d\n",uVar31);
        if (DebugLevel < 1) {
          return;
        }
        iVar34 = param_3;
        iVar33 = param_3;
        iVar37 = param_3;
        iVar40 = param_3;
        printk("G%d_R0_UH = %d\n G%d_R0_H = %d\n G%d_R0_M = %d\n G%d_R0_L = %d\n G%d_R1_UH = %d\n G%d_R1_H = %d\n G%d_R1_M = %d\n G%d_R1_L = %d\n"
               ,param_3,uVar26,param_3,uVar12,param_3,uVar27,param_3,uVar15,param_3,uVar35,param_3,
               uVar39,param_3,uVar38,param_3,uVar36);
        if (DebugLevel < 1) goto LAB_0008a354;
        printk("G%d_R2_UH = %d\n G%d_R2_H = %d\n G%d_R2_M = %d\n G%d_R2_L = %d\n",param_3,uVar17,
               param_3,uVar21,param_3,uVar23,param_3,uVar24,iVar34,uVar35,iVar33,uVar39,iVar37,
               uVar38,iVar40,uVar36);
        if (DebugLevel < 1) {
          return;
        }
        printk("G%d_R3_UH = %d\n G%d_R3_H = %d\n G%d_R3_M = %d\n G%d_R3_L = %d\n G%d_R3_UL = %d\n",
               param_3,uVar18,param_3,uVar19,param_3,uVar20,param_3,uVar22,param_3,uVar25,iVar33,
               uVar39,iVar37,uVar38,iVar40,uVar36);
      }
      if (0 < DebugLevel) {
LAB_0008a32c:
        printk("Group : %d\n",param_3);
        if (DebugLevel < 1) {
          return;
        }
        printk("Calibration == 1? or Verification == 2? : %d\n",param_6);
        goto LAB_0008a354;
      }
    }
    break;
  case 2:
  case 4:
    *(byte *)(param_1 + 0xa7868c) = param_5 != '\x01' | *(byte *)(param_1 + 0xa7868c);
    *(bool *)(param_1 + param_3 + 0xa7868d) = param_5 != '\x01';
    if (iVar34 < 1) {
      return;
    }
    printk("Group : %d\n",param_3);
    if (DebugLevel < 1) {
      return;
    }
    printk("Calibration == 1? or Verification == 2? : %d\n",param_6);
    if (DebugLevel < 1) {
      return;
    }
    printk("Calibrated result = %d\n",param_5);
joined_r0x00089c44:
    if (DebugLevel < 1) {
      return;
    }
    printk("0 : Means failed\n 1: means pass\n 2: means on-going\n");
    break;
  default:
    goto switchD_00089b90_default;
  }
  if (0 < DebugLevel) {
    printk("C0_H : %d, C1_H : %d, C2_H : %d\n C0_M : %d, C1_M : %d, C2_M : %d\n C0_L : %d, C1_L : %d, C2_L : %d\n C3_M : %d, C3_L : %d\n"
           ,uVar9,uVar10,uVar11,uVar6,uVar7,uVar8,uVar1,uVar4,uVar5,uVar3,uVar2);
  }
switchD_00089b90_default:
  return;
}


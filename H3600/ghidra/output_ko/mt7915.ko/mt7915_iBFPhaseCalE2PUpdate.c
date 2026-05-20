// module: mt7915.ko
// function: mt7915_iBFPhaseCalE2PUpdate @ 0x89450
// size: 1696 bytes
//

void mt7915_iBFPhaseCalE2PUpdate(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  byte bVar6;
  undefined4 uVar7;
  char *pcVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  uint uVar15;
  undefined4 *puVar16;
  undefined4 uVar17;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined1 local_70 [2];
  undefined1 local_6e;
  undefined1 local_6d;
  undefined1 local_6c;
  undefined1 local_6b;
  undefined1 local_69;
  undefined1 local_68;
  undefined1 uStack_67;
  undefined1 uStack_66;
  byte bStack_65;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_61;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_5d;
  undefined1 local_5c;
  undefined1 local_5a;
  byte local_59;
  undefined1 local_58;
  undefined1 local_57;
  undefined4 local_50;
  undefined4 uStack_4c;
  byte local_48 [2];
  undefined1 local_46;
  undefined1 local_45;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 local_41;
  undefined1 local_40;
  undefined1 uStack_3f;
  undefined1 uStack_3e;
  undefined1 uStack_3d;
  undefined4 auStack_3c [2];
  undefined1 local_32;
  byte local_31;
  undefined1 local_30;
  
  __memzero(&local_50,0x28);
  __memzero(&local_78,0x28);
  switch(param_4) {
  case 0:
    if (param_2 == 0) {
      iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      if (*(code **)(iVar2 + 0x14) != (code *)0x0) {
        (**(code **)(iVar2 + 0x14))
                  (param_1,au2MT7915IBfCalEEPROMOffset._0_2_,0x28,
                   *(undefined4 *)(param_1 + 0xa78684));
      }
      puVar13 = *(undefined4 **)(param_1 + 0xa78684);
      puVar1 = &local_50;
      puVar14 = puVar13;
      do {
        puVar16 = puVar14;
        puVar12 = puVar1;
        puVar14 = puVar16 + 4;
        uVar3 = puVar16[1];
        uVar4 = puVar16[2];
        uVar7 = puVar16[3];
        *puVar12 = *puVar16;
        puVar12[1] = uVar3;
        puVar12[2] = uVar4;
        puVar12[3] = uVar7;
        puVar1 = puVar12 + 4;
      } while (puVar14 != puVar13 + 8);
      uVar3 = puVar16[5];
      puVar12[4] = *puVar14;
      puVar12[5] = uVar3;
      if (DebugLevel < 1) {
        return;
      }
      uVar11 = (uint)local_31;
      uVar3 = 0;
      printk("G%d and Group_M\n G%d_M_T0_H = %d\n G%d_M_T1_H = %d\n",0,0,local_32,0,uVar11);
      if (0 < DebugLevel) {
        printk("G%d_M_T2_H = %d\n",0,local_30,DebugLevel,uVar3,uVar11);
        if (DebugLevel < 1) {
          return;
        }
        uVar10 = (uint)uStack_4c._1_1_;
        uVar9 = (uint)uStack_4c._2_1_;
        uVar11 = (uint)uStack_4c._3_1_;
        uVar15 = (uint)local_48[0];
        uVar3 = 0;
        uVar4 = 0;
        uVar7 = 0;
        uVar17 = 0;
        printk("G%d_R0_UH = %d\n G%d_R0_H = %d\n G%d_R0_M = %d\n G%d_R0_L = %d\n G%d_R1_UH = %d\n G%d_R1_H = %d\n G%d_R1_M = %d\n G%d_R1_L = %d\n"
               ,0,(undefined1)local_50,0,local_50._1_1_,0,local_50._2_1_,0,local_50._3_1_,0,uVar10,0
               ,uVar9,0,uVar11,0,uVar15);
        if (0 < DebugLevel) {
          printk("G%d_R2_UH = %d\n G%d_R2_H = %d\n G%d_R2_M = %d\n G%d_R2_L = %d\n",0,local_46,0,
                 local_45,0,local_44,0,local_43,uVar3,uVar10,uVar4,uVar9,uVar7,uVar11,uVar17,uVar15)
          ;
          if (DebugLevel < 1) {
            return;
          }
          printk("G%d_R3_UH = %d\n G%d_R3_H = %d\n G%d_R3_M = %d\n G%d_R3_L = %d \n G%d_R3_UL = %d \n"
                 ,0,local_41,0,local_40,0,uStack_3f,0,uStack_3e,0,uStack_3d,uVar4,uVar9,uVar7,uVar11
                 ,uVar17,uVar15);
        }
      }
    }
    else {
      uVar11 = param_2 - 1U & 0xff;
      iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      if (*(code **)(iVar2 + 0x14) != (code *)0x0) {
        (**(code **)(iVar2 + 0x14))
                  (param_1,*(undefined2 *)(au2MT7915IBfCalEEPROMOffset + param_2 * 2),0x28,
                   *(int *)(param_1 + 0xa78688) + uVar11 * 0x28);
      }
      puVar13 = (undefined4 *)(*(int *)(param_1 + 0xa78688) + uVar11 * 0x28);
      puVar1 = &local_78;
      puVar14 = puVar13;
      do {
        puVar16 = puVar14;
        puVar12 = puVar1;
        puVar14 = puVar16 + 4;
        uVar3 = puVar16[1];
        uVar4 = puVar16[2];
        uVar7 = puVar16[3];
        *puVar12 = *puVar16;
        puVar12[1] = uVar3;
        puVar12[2] = uVar4;
        puVar12[3] = uVar7;
        puVar1 = puVar12 + 4;
      } while (puVar14 != puVar13 + 8);
      uVar3 = puVar16[5];
      puVar12[4] = *puVar14;
      puVar12[5] = uVar3;
      if (DebugLevel < 1) {
        return;
      }
      uVar11 = (uint)local_59;
      iVar2 = param_2;
      printk("G%d and Group_M\n G%d_M_T0_H = %d\n G%d_M_T1_H = %d\n",param_2,param_2,local_5a,
             param_2,uVar11);
      if (0 < DebugLevel) {
        printk("G%d_M_T2_H = %d\n",param_2,local_58,DebugLevel,iVar2,uVar11);
        if (DebugLevel < 1) {
          return;
        }
        printk("G%d_R0_UH = %d\n G%d_R0_H = %d\n G%d_R0_M = %d\n G%d_R0_L = %d\n G%d_R1_UH = %d\n G%d_R1_H = %d\n G%d_R1_M = %d\n G%d_R1_L = %d\n"
               ,param_2,(undefined1)local_78,param_2,local_78._1_1_,param_2,local_78._2_1_,param_2,
               local_78._3_1_,param_2,uStack_74._1_1_,param_2,uStack_74._2_1_,param_2,
               uStack_74._3_1_,param_2,local_70[0]);
      }
    }
    if (0 < DebugLevel) {
      printk("G%d_R2_UH = %d\n G%d_R2_H = %d\n G%d_R2_M = %d\n G%d_R2_L = %d\n",param_2,local_6e,
             param_2,local_6d,param_2,local_6c,param_2,local_6b);
      if (DebugLevel < 1) {
        return;
      }
      printk("G%d_R3_UH = %d\n G%d_R3_H = %d\n G%d_R3_M = %d\n G%d_R3_L = %d \n G%d_R3_UL = %d \n",
             param_2,local_69,param_2,local_68,param_2,uStack_67,param_2,uStack_66,param_2,bStack_65
            );
      if (DebugLevel < 1) {
        return;
      }
      uVar11 = (uint)bStack_65;
      iVar2 = param_2;
      printk("G%d_R3_UH = %d\n G%d_R3_H = %d\n G%d_R3_M = %d\n G%d_R3_L = %d \n G%d_R3_UL = %d \n",
             param_2,local_69,param_2,local_68,param_2,uStack_67,param_2,uStack_66,param_2,uVar11);
      if (DebugLevel < 1) {
        return;
      }
      printk("G%d_R2_UH_SX2 = %d\n G%d_R2_H_SX2 = %d\n G%d_R2_M_SX2 = %d\n G%d_R2_L_SX2 = %d\n",
             param_2,local_64,param_2,local_63,param_2,local_62,param_2,local_61,iVar2,uVar11);
    }
    if (DebugLevel < 1) {
      return;
    }
    printk("G%d_R3_UH_SX2 = %d\n G%d_R3_H_SX2 = %d\n G%d_R3_M_SX2 = %d\n G%d_R3_L_SX2 = %d\n G%d_M_T2_H_SX2 = %d\n"
           ,param_2,local_5f,param_2,local_5e,param_2,local_5d,param_2,local_5c,param_2,local_57);
    return;
  case 1:
    if (*(char *)(param_1 + 0xa7868c) != '\0') {
      if (0 < DebugLevel) {
        printk(
              "Calibrated phases can\'t be written into EEPROM because some groups can\'t pass criterion!!!\n"
              );
      }
      pcVar8 = (char *)(param_1 + 0xa7868d);
      iVar2 = 0;
      do {
        if (0 < DebugLevel) {
          puVar5 = &_LC0;
          if (*pcVar8 != '\x01') {
            puVar5 = &_LC1;
          }
          printk("Group%d = %s\n",iVar2,puVar5);
        }
        iVar2 = iVar2 + 1;
        pcVar8 = pcVar8 + 1;
      } while (iVar2 != 9);
      return;
    }
    if (0 < DebugLevel) {
      printk("All of groups can pass criterion and calibrated phases can be written into EEPROM\n");
    }
    break;
  case 2:
    __memzero(*(undefined4 *)(param_1 + 0xa78684),0x28);
    __memzero(*(undefined4 *)(param_1 + 0xa78688),0x140);
    break;
  case 3:
    mt7915_iBFPhaseCalE2PInit(param_1);
    return;
  default:
    goto switchD_00089480_default;
  }
  bVar6 = *(byte *)(param_1 + 0xa78730);
  if (bVar6 < 2) {
    iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(code **)(iVar2 + 0x14) != (code *)0x0) {
      (**(code **)(iVar2 + 0x14))
                (param_1,au2MT7915IBfCalEEPROMOffset._0_2_,0x28,*(undefined4 *)(param_1 + 0xa78684))
      ;
    }
    bVar6 = *(byte *)(param_1 + 0xa78730);
  }
  if ((bVar6 & 0xfd) == 0) {
    iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(code **)(iVar2 + 0x14) != (code *)0x0) {
      (**(code **)(iVar2 + 0x14))
                (param_1,au2MT7915IBfCalEEPROMOffset._2_2_,0x140,*(undefined4 *)(param_1 + 0xa78688)
                );
    }
  }
switchD_00089480_default:
  return;
}


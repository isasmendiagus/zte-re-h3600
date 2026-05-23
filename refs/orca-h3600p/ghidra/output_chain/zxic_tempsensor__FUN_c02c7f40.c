// compatible: zxic,tempsensor
// function: FUN_c02c7f40 @ 0xc02c7f40
// found via xref to compat string
// total struct-refs for compat: 4
//

void FUN_c02c7f40(char *param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char cVar8;
  undefined1 auStack_120 [128];
  undefined1 auStack_a0 [128];
  char *pcVar7;
  
  FUN_c0181b40(auStack_120,0x80);
  FUN_c0181b40(auStack_a0,0x80);
  if (param_1 == (char *)0x0) {
LAB_c02c80f0:
    FUN_c046918c(s_get_items_failed_c05bf11c);
  }
  else {
    cVar8 = *param_1;
    uVar4 = 0;
    iVar2 = FUN_c02c7efc(cVar8);
    do {
      do {
        while (pcVar6 = param_1, iVar2 == 0) {
          uVar4 = uVar4 + 1;
          if (param_2 <= uVar4) goto LAB_c02c80f0;
          cVar8 = param_1[1];
          iVar2 = FUN_c02c7efc(cVar8);
          param_1 = param_1 + 1;
        }
        do {
          pcVar5 = pcVar6;
          uVar4 = uVar4 + 1;
          if (param_2 <= uVar4) goto LAB_c02c80f0;
          iVar3 = FUN_c02c7efc(pcVar5[1]);
          pcVar6 = pcVar5 + 1;
        } while (iVar3 != 0);
        pcVar6 = param_1;
      } while (cVar8 == '\n' || (cVar8 == '\r' || cVar8 == '='));
      do {
        pcVar7 = pcVar6;
        pcVar6 = pcVar7 + 1;
        cVar1 = *pcVar6;
      } while (cVar1 != '\n' && (cVar1 != '\r' && cVar1 != '='));
    } while (pcVar6 <= param_1);
    FUN_c01813e0(auStack_120,param_1,(int)pcVar6 - (int)param_1);
    if (pcVar6 < pcVar5 && *pcVar6 == '=') {
      FUN_c01813e0(auStack_a0,pcVar7 + 2,(int)pcVar5 - (int)pcVar6);
    }
    iVar2 = FUN_c0188238(auStack_120,s_pin_low_power_c05a182c + 8);
    if (iVar2 == 0) {
      iVar2 = FUN_c0188238(auStack_a0,s_syscon_c05a8238 + 4);
      if (iVar2 == 0) {
        FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x123,auStack_a0,auStack_120);
        *DAT_c06a1654 = *DAT_c06a1654 & 0xffffefff;
        DAT_c06a1628 = 0;
      }
      else {
        iVar2 = FUN_c0188238(auStack_a0,s_pinctrl_single_function_off_c05a1a80 + 0x18);
        if (iVar2 == 0) {
          FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x129,auStack_a0,auStack_120);
          *DAT_c06a1654 = *DAT_c06a1654 | 0x1000;
          DAT_c06a1628 = 1;
        }
      }
    }
    else {
      iVar2 = FUN_c0188238(auStack_120,&DAT_c059e248);
      if (iVar2 == 0) {
        iVar2 = FUN_c0188238(auStack_a0,s_syscon_c05a8238 + 4);
        if (iVar2 == 0) {
          FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x133,auStack_a0,auStack_120);
          *DAT_c06a1654 = *DAT_c06a1654 | 0x2000;
          DAT_c06a162c = 1;
        }
        else {
          iVar2 = FUN_c0188238(auStack_a0,s_pinctrl_single_function_off_c05a1a80 + 0x18);
          if (iVar2 == 0) {
            FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x139,auStack_a0,auStack_120);
            *DAT_c06a1654 = *DAT_c06a1654 & 0xffffdfff;
            DAT_c06a162c = 0;
          }
        }
      }
      else {
        iVar2 = FUN_c0188238(auStack_120,s_select_c05c5004);
        if (iVar2 == 0) {
          iVar2 = FUN_c0188238(auStack_a0,s_unknown_0_c05832ec + 8);
          if (iVar2 == 0) {
            FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x143,auStack_a0,auStack_120);
            *DAT_c06a1654 = *DAT_c06a1654 & 0xfffcffff;
            DAT_c06a1630 = 0;
          }
          else {
            iVar2 = FUN_c0188238(auStack_a0,s_no_delete_0_1_c05dd234 + 0xc);
            if (iVar2 == 0) {
              FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x149,auStack_a0,auStack_120);
              *DAT_c06a1654 = *DAT_c06a1654 & 0xfffcffff | 0x10000;
              DAT_c06a1630 = 1;
            }
            else {
              iVar2 = FUN_c0188238(auStack_a0,&DAT_c05b4214);
              if (iVar2 == 0) {
                FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x14f,auStack_a0,auStack_120);
                *DAT_c06a1654 = *DAT_c06a1654 & 0xfffcffff | 0x20000;
                DAT_c06a1630 = 2;
              }
            }
          }
        }
        else {
          iVar2 = FUN_c0188238(auStack_120,&DAT_c05c500c);
          if (iVar2 == 0) {
            iVar2 = FUN_c0188238(auStack_a0,s_syscon_c05a8238 + 4);
            if (iVar2 == 0) {
              FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x159,auStack_a0,auStack_120);
              DAT_c06a1654[2] = DAT_c06a1654[2] & 0xfffffc00;
              DAT_c06a1634 = 1;
            }
            else {
              iVar2 = FUN_c0188238(auStack_a0,s_pinctrl_single_function_off_c05a1a80 + 0x18);
              if (iVar2 == 0) {
                FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x15f,auStack_a0,auStack_120);
                DAT_c06a1654[2] = ~(~(DAT_c06a1654[2] >> 10) << 10);
                DAT_c06a1634 = 0;
              }
            }
          }
          else {
            iVar2 = FUN_c0188238(auStack_120,&DAT_c05c5014);
            if (iVar2 == 0) {
              iVar2 = FUN_c0188238(auStack_a0,s_syscon_c05a8238 + 4);
              if (iVar2 == 0) {
                FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x168,auStack_a0,auStack_120);
                DAT_c06a1654[2] = DAT_c06a1654[2] & 0xfff003ff;
                DAT_c06a1638 = 1;
              }
              else {
                iVar2 = FUN_c0188238(auStack_a0,s_pinctrl_single_function_off_c05a1a80 + 0x18);
                if (iVar2 == 0) {
                  FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x16e,auStack_a0,auStack_120);
                  DAT_c06a1654[2] = DAT_c06a1654[2] | 0xffc00;
                  DAT_c06a1638 = 0;
                }
              }
            }
            else {
              iVar2 = FUN_c0188238(auStack_120,&DAT_c05c501c);
              if (iVar2 == 0) {
                iVar2 = FUN_c0188238(auStack_a0,s_syscon_c05a8238 + 4);
                if (iVar2 == 0) {
                  FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x177,auStack_a0,auStack_120);
                  DAT_c06a1654[2] = DAT_c06a1654[2] & 0xc00fffff;
                  DAT_c06a163c = 1;
                }
                else {
                  iVar2 = FUN_c0188238(auStack_a0,s_pinctrl_single_function_off_c05a1a80 + 0x18);
                  if (iVar2 == 0) {
                    FUN_c046918c(s_<_s>__d___s__s_c05bf0bc,DAT_c02c85e8,0x17d,auStack_a0,auStack_120
                                );
                    DAT_c06a1654[2] = DAT_c06a1654[2] | 0x3ff00000;
                    DAT_c06a163c = 0;
                  }
                }
              }
              else {
                FUN_c046918c(s_<_s>__d__invalid_command__c05c5024,DAT_c02c85e8,0x184);
              }
            }
          }
        }
      }
    }
  }
  return;
}


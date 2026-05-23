// module: mt7915.ko
// function: ReadApcliSecParameterFromFile @ 0x1157f4
// size: 1668 bytes
//

void ReadApcliSecParameterFromFile(int param_1,char *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  undefined1 *__dest;
  int iVar8;
  uint uVar9;
  byte bVar10;
  undefined *puVar11;
  bool bVar12;
  char acStack_48 [16];
  char acStack_38 [20];
  
  iVar1 = RTMPGetKeyParameter("ApCliAuthMode",param_2,0xff,param_3,1);
  if ((iVar1 != 0) && (pcVar5 = (char *)rstrtok(param_2,&_LC53), pcVar5 != (char *)0x0)) {
    uVar9 = 0;
    do {
      if (pcVar5 == param_2) {
        uVar6 = 0;
      }
      else {
        uVar6 = (uVar9 ^ 1) & 1;
      }
      uVar7 = uVar9 + 1;
      if (uVar6 == 0) {
        puVar11 = &DAT_0036db84 + param_1 + uVar9 * 0x2137b0;
        if (2 < DebugLevel) {
          uVar7 = uVar9 + 1;
          if ((int)uVar7 < 2) {
            bVar12 = true;
          }
          else {
            bVar12 = false;
          }
          goto LAB_00115e40;
        }
        if ((int)uVar7 < 2) {
          bVar12 = true;
        }
        else {
          bVar12 = false;
        }
      }
      else {
        if (DebugLevel < 3) {
          SetWdevAuthMode(&DAT_00581334 + param_1,pcVar5);
          rstrtok(0,&_LC53);
          break;
        }
        bVar12 = false;
        uVar7 = 2;
        uVar9 = 1;
        puVar11 = &DAT_00581334 + param_1;
LAB_00115e40:
        printk("I/F(apcli%d) ==> ",uVar9);
      }
      SetWdevAuthMode(puVar11,pcVar5);
      pcVar5 = (char *)rstrtok(0,&_LC53);
      if (pcVar5 == (char *)0x0) {
        bVar12 = false;
      }
      uVar9 = uVar7;
    } while (bVar12);
  }
  iVar1 = RTMPGetKeyParameter("ApCliEncrypType",param_2,0xff,param_3,1);
  if ((iVar1 != 0) && (pcVar5 = (char *)rstrtok(param_2,&_LC53), pcVar5 != (char *)0x0)) {
    uVar9 = 0;
    do {
      if (pcVar5 == param_2) {
        uVar6 = 0;
      }
      else {
        uVar6 = (uVar9 ^ 1) & 1;
      }
      uVar7 = uVar9 + 1;
      if (uVar6 == 0) {
        puVar11 = &DAT_0036db84 + param_1 + uVar9 * 0x2137b0;
        if (2 < DebugLevel) {
          uVar7 = uVar9 + 1;
          if ((int)uVar7 < 2) {
            bVar12 = true;
          }
          else {
            bVar12 = false;
          }
          goto LAB_00115e18;
        }
        if ((int)uVar7 < 2) {
          bVar12 = true;
        }
        else {
          bVar12 = false;
        }
      }
      else {
        if (DebugLevel < 3) {
          SetWdevEncrypMode(&DAT_00581334 + param_1,pcVar5);
          rstrtok(0,&_LC53);
          break;
        }
        bVar12 = false;
        uVar7 = 2;
        uVar9 = 1;
        puVar11 = &DAT_00581334 + param_1;
LAB_00115e18:
        printk("I/F(apcli%d) ==> ",uVar9);
      }
      SetWdevEncrypMode(puVar11,pcVar5);
      pcVar5 = (char *)rstrtok(0,&_LC53);
      if (pcVar5 == (char *)0x0) {
        bVar12 = false;
      }
      uVar9 = uVar7;
    } while (bVar12);
  }
  __dest = &DAT_0036dcd1 + param_1;
  iVar1 = 1;
  do {
    if (iVar1 + -1 == 0) {
      builtin_strncpy(acStack_48,"ApCliWPAPSK",0xc);
      iVar2 = RTMPGetKeyParameter(acStack_48,param_2,0x41,param_3,0);
      if (iVar2 != 0) goto LAB_001158b4;
    }
    else {
      snprintf(acStack_48,0x10,"ApCliWPAPSK%d",1);
      iVar2 = RTMPGetKeyParameter(acStack_48,param_2,0x41,param_3,0);
      if (iVar2 != 0) {
LAB_001158b4:
        sVar3 = strlen(param_2);
        if (sVar3 < 0x41) {
          os_move_mem(__dest,param_2,sVar3);
          sVar3 = strlen(param_2);
          (&DAT_0036dcd1)[param_1 + (iVar1 + -1) * 0x2137b0 + sVar3] = 0;
        }
        else {
          *__dest = 0;
        }
      }
      if (iVar1 == 2) {
        iVar1 = RTMPGetKeyParameter("ApCliDefaultKeyID",param_2,0xff,param_3,1);
        if ((iVar1 != 0) && (pcVar5 = (char *)rstrtok(param_2,&_LC53), pcVar5 != (char *)0x0)) {
          uVar9 = 0;
          do {
            uVar6 = uVar9 + 1;
            if (pcVar5 == param_2) {
              uVar7 = 0;
            }
            else {
              uVar7 = (uVar9 ^ 1) & 1;
            }
            bVar12 = false;
            if (uVar7 == 0) {
              bVar12 = false;
              if ((int)uVar6 < 2) {
                bVar12 = true;
              }
            }
            else {
              uVar6 = 2;
              uVar9 = 1;
            }
            iVar2 = os_str_tol(pcVar5,0,10);
            iVar1 = DebugLevel;
            if (iVar2 - 1U < 4) {
              (&DAT_0036dcd0)[param_1 + uVar9 * 0x2137b0] = (char)(iVar2 - 1U);
              iVar1 = DebugLevel;
            }
            else {
              (&DAT_0036dcd0)[param_1 + uVar9 * 0x2137b0] = 0;
            }
            if (2 < iVar1) {
              printk("I/F(apcli%d)) ==> DefaultKeyId=%d\n",uVar9,
                     (&DAT_0036dcd0)[param_1 + uVar9 * 0x2137b0]);
            }
            pcVar5 = (char *)rstrtok(0,&_LC53);
            if (pcVar5 == (char *)0x0) {
              bVar12 = false;
            }
            uVar9 = uVar6;
          } while (bVar12);
        }
        iVar1 = 0;
        do {
          iVar8 = iVar1 + 1;
          snprintf(acStack_38,0x10,"ApCliKey%dType",iVar8);
          iVar2 = RTMPGetKeyParameter(acStack_38,param_2,0x80,param_3,1);
          if (iVar2 != 0) {
            iVar2 = rstrtok(param_2,&_LC53);
            if (iVar2 != 0) {
              bVar10 = 0;
              do {
                os_str_tol(iVar2,0,10);
                iVar2 = rstrtok(0,&_LC53);
                bVar12 = (bool)(bVar10 ^ 1);
                bVar10 = 1;
                if (iVar2 == 0) {
                  bVar12 = false;
                }
              } while (bVar12);
            }
            if (*(char *)(param_1 + 0x286285) == '\x01') {
              iVar2 = 1;
              puVar11 = &DAT_0036db84 + param_1;
              do {
                if (iVar2 == 1) {
                  snprintf(acStack_38,0x10,"ApCliKey%dStr",iVar8);
                  iVar4 = RTMPGetKeyParameter(acStack_38,param_2,0x80,param_3,0);
                  if (iVar4 != 0) goto LAB_00115df0;
                }
                else {
                  snprintf(acStack_38,0x10,"ApCliKey%dStr%d",iVar8,1);
                  iVar4 = RTMPGetKeyParameter(acStack_38,param_2,0x80,param_3,0);
                  if (iVar4 != 0) {
LAB_00115df0:
                    ParseWebKey(puVar11,param_2,iVar1,0);
                  }
                  if (iVar2 == 2) break;
                }
                iVar2 = iVar2 + 1;
                puVar11 = puVar11 + 0x2137b0;
              } while( true );
            }
          }
          iVar1 = iVar8;
          if (iVar8 == 4) {
            return;
          }
        } while( true );
      }
    }
    iVar1 = iVar1 + 1;
    __dest = __dest + 0x2137b0;
  } while( true );
}


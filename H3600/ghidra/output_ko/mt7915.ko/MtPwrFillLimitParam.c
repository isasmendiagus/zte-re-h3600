// module: mt7915.ko
// function: MtPwrFillLimitParam @ 0x1524c0
// size: 804 bytes
//

undefined4
MtPwrFillLimitParam(int param_1,uint param_2,uint param_3,uint param_4,int param_5,byte param_6)

{
  byte bVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  uint uVar12;
  byte bVar13;
  uint uVar14;
  int iVar15;
  uint local_4c;
  byte local_36 [2];
  int local_34;
  int local_30;
  int *local_2c [2];
  
  local_34 = 0;
  local_30 = 0;
  uVar10 = (uint)param_6;
  iVar5 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  local_36[0] = *(byte *)(iVar5 + 0x1fc);
  local_36[1] = *(undefined1 *)(iVar5 + 0x200);
  local_2c[0] = (int *)0x0;
  if (param_5 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: null pointer for buffer to fill power limit table !!\n","MtPwrFillLimitParam");
    }
  }
  else {
    MtPwrGetPwrLimitInstance(param_1,uVar10,3,&local_34);
    if (local_34 != 0) {
      MtPwrGetPwrLimitInstance(param_1,uVar10,2,&local_30);
      MtPwrGetPwrLimitInstance(param_1,uVar10,0,local_2c);
      if (local_30 != 0) {
        local_4c = param_3;
        if (param_3 < 0x10) {
          if (param_3 < 8) {
            param_2 = 0;
            local_4c = param_4;
          }
          else if (param_2 == 0) {
            local_4c = param_4;
          }
        }
        else {
          param_2 = 1;
        }
        piVar4 = *(int **)*local_2c[0];
        piVar3 = (undefined4 *)*local_2c[0];
        do {
          piVar2 = piVar4;
          if (local_2c[0] == piVar3) {
            return 0;
          }
          if (*(byte *)((int)piVar3 + 9) != 0) {
            uVar8 = 0;
            do {
              if ((*(byte *)(piVar3 + 4) == param_2) && (*(byte *)(piVar3[3] + uVar8) == local_4c))
              {
                bVar1 = local_36[uVar10];
                if (bVar1 != 0) {
                  bVar13 = 0;
                  pbVar11 = (byte *)(local_34 + -1);
                  uVar14 = 0;
                  uVar8 = 0;
                  do {
                    pbVar11 = pbVar11 + 1;
                    uVar12 = (uint)*(byte *)(local_30 + uVar14);
                    uVar6 = 0;
                    if (*pbVar11 != 0) {
                      uVar9 = 0;
                      do {
                        iVar7 = uVar9 + uVar8;
                        *(undefined1 *)(param_5 + iVar7) = 0x3f;
                        if (uVar10 == 0) {
                          if ((*(byte *)(iVar5 + 0x211) != bVar13) ||
                             (uVar9 != *(byte *)(iVar5 + 0x205) - 1)) goto LAB_00152658;
                          uVar14 = uVar14 - 2 & 0xff;
                          iVar15 = (*(byte *)(iVar5 + 0x20a) - 1) + uVar12;
                          if (piVar3[5] + iVar15 != 0) {
                            *(undefined1 *)(param_5 + iVar7) = *(undefined1 *)(piVar3[5] + iVar15);
                          }
                        }
                        else if (((uVar10 == 1) && (*(byte *)(iVar5 + 0x212) == bVar13)) &&
                                (uVar9 == *(byte *)(iVar5 + 0x20b) - 1)) {
                          uVar14 = uVar14 - 4 & 0xff;
                          if (piVar3[5] + uVar9 + uVar12 != 0) {
                            *(undefined1 *)(param_5 + iVar7) =
                                 *(undefined1 *)(piVar3[5] + uVar9 + uVar12);
                          }
                        }
                        else {
LAB_00152658:
                          if (piVar3[5] + uVar9 + uVar12 != 0) {
                            *(undefined1 *)(param_5 + iVar7) =
                                 *(undefined1 *)(piVar3[5] + uVar9 + uVar12);
                          }
                        }
                        uVar6 = (uint)*pbVar11;
                        uVar9 = uVar9 + 1 & 0xff;
                      } while (uVar9 < uVar6);
                    }
                    bVar13 = bVar13 + 1;
                    uVar8 = uVar6 + uVar8 & 0xff;
                    uVar14 = uVar14 + 1 & 0xff;
                  } while (bVar13 < bVar1);
                }
                break;
              }
              uVar8 = uVar8 + 1;
            } while ((uVar8 & 0xff) < (uint)*(byte *)((int)piVar3 + 9));
          }
          piVar4 = (int *)*piVar2;
          piVar3 = piVar2;
        } while( true );
      }
    }
    if (-1 < DebugLevel) {
      printk("%s: null pointer for parameter related to fill power limit table proc !!\n",
             "MtPwrFillLimitParam");
    }
  }
  return 1;
}


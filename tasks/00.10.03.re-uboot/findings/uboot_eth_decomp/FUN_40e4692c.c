/* ===== FUN thunk_FUN_40e45fd8 @ 40e4692c =====
 * callers: 40e2a1b4:FUN_40e2a1b4, 40e2a200:FUN_40e2a200
 * callees: (none)
 */


int thunk_FUN_40e45fd8(byte *param_1,byte *param_2,uint *param_3)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  byte *pbVar4;
  undefined4 uVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined1 *puVar11;
  uint uVar12;
  byte *pbVar13;
  byte *pbVar14;
  uint uVar15;
  undefined1 *puVar16;
  uint *puVar17;
  undefined1 *puVar18;
  bool bVar19;
  undefined1 auStack_4c [4];
  undefined1 auStack_48 [40];
  
  pbVar13 = param_1;
  do {
    bVar1 = *param_2;
    if (bVar1 == 0) {
      *pbVar13 = 0;
      return (int)pbVar13 - (int)param_1;
    }
    if (bVar1 == 0x25) {
      uVar12 = 0;
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              pbVar14 = param_2 + 1;
              uVar9 = (uint)*pbVar14;
              if (uVar9 != 0x2b) break;
              uVar12 = uVar12 | 4;
              param_2 = pbVar14;
            }
            if (uVar9 < 0x2c) break;
            if (uVar9 == 0x2d) {
              uVar12 = uVar12 | 0x10;
              param_2 = pbVar14;
            }
            else {
              if (uVar9 != 0x30) goto LAB_40e46060;
              uVar12 = uVar12 | 1;
              param_2 = pbVar14;
            }
          }
          if (uVar9 != 0x20) break;
          uVar12 = uVar12 | 8;
          param_2 = pbVar14;
        }
        if (uVar9 != 0x23) break;
        uVar12 = uVar12 | 0x40;
        param_2 = pbVar14;
      }
LAB_40e46060:
      if (uVar9 - 0x30 < 10) {
        uVar9 = 0;
        while( true ) {
          if (9 < *pbVar14 - 0x30) break;
          uVar9 = (uVar9 * 10 + (uint)*pbVar14) - 0x30;
          pbVar14 = pbVar14 + 1;
        }
      }
      else if (uVar9 == 0x2a) {
        uVar9 = *param_3;
        param_3 = param_3 + 1;
        pbVar14 = param_2 + 2;
        if ((int)uVar9 < 0) {
          uVar9 = -uVar9;
          uVar12 = uVar12 | 0x10;
        }
      }
      else {
        uVar9 = 0xffffffff;
      }
      if (*pbVar14 == 0x2e) {
        pbVar4 = pbVar14 + 1;
        if (pbVar14[1] - 0x30 < 10) {
          uVar15 = 0;
          while( true ) {
            if (9 < *pbVar4 - 0x30) break;
            uVar15 = (uVar15 * 10 + (uint)*pbVar4) - 0x30;
            pbVar4 = pbVar4 + 1;
          }
        }
        else {
          if (pbVar14[1] == 0x2a) {
            uVar15 = *param_3;
            pbVar4 = pbVar14 + 2;
            param_3 = param_3 + 1;
            if (-1 < (int)uVar15) goto LAB_40e46148;
          }
          uVar15 = 0;
        }
      }
      else {
        uVar15 = 0xffffffff;
        pbVar4 = pbVar14;
      }
LAB_40e46148:
      uVar10 = (uint)*pbVar4;
      if ((uVar10 & 0xdf) == 0x5a || ((uVar10 & 0xdf) == 0x4c || (uVar10 == 0x68 || uVar10 == 0x74))
         ) {
        param_2 = pbVar4 + 1;
        if ((uVar10 == 0x6c) && (pbVar4[1] == 0x6c)) {
          param_2 = pbVar4 + 2;
          uVar10 = 0x4c;
        }
      }
      else {
        uVar10 = 0xffffffff;
        param_2 = pbVar4;
      }
      bVar1 = *param_2;
      if (bVar1 == 0x6e) {
        *(int *)*param_3 = (int)pbVar13 - (int)param_1;
LAB_40e464f0:
        param_3 = param_3 + 1;
      }
      else {
        if (bVar1 < 0x6f) {
          if (bVar1 == 99) {
            if ((uVar12 & 0x10) == 0) {
              while (uVar9 = uVar9 - 1, 0 < (int)uVar9) {
                *pbVar13 = 0x20;
                pbVar13 = pbVar13 + 1;
              }
            }
            *pbVar13 = (byte)*param_3;
            while( true ) {
              pbVar13 = pbVar13 + 1;
              uVar9 = uVar9 - 1;
              if ((int)uVar9 < 1) break;
              *pbVar13 = 0x20;
            }
            goto LAB_40e464f0;
          }
          if (bVar1 < 100) {
            if (bVar1 == 0x25) {
              *pbVar13 = 0x25;
              goto LAB_40e464fc;
            }
            if (bVar1 == 0x58) {
LAB_40e46504:
              uVar5 = 0x10;
              goto LAB_40e46544;
            }
          }
          else if ((bVar1 == 100) || (bVar1 == 0x69)) {
            uVar12 = uVar12 | 2;
LAB_40e46538:
            uVar5 = 10;
LAB_40e46544:
            if (uVar10 == 0x4c) {
              puVar7 = (uint *)((int)param_3 + 7U & 0xfffffff8);
              puVar17 = puVar7 + 2;
              uVar8 = *puVar7;
              uVar10 = puVar7[1];
            }
            else {
              puVar17 = param_3 + 1;
              if (uVar10 == 0x6c) {
                uVar8 = *param_3;
joined_r0x40e465bc:
                if ((uVar12 & 2) != 0) {
LAB_40e465c0:
                  uVar10 = (int)uVar8 >> 0x1f;
                  goto LAB_40e465c4;
                }
              }
              else {
                uVar8 = *param_3;
                if ((uVar10 & 0xffffffdf) != 0x5a) {
                  if (uVar10 != 0x74) {
                    if (uVar10 != 0x68) goto joined_r0x40e465bc;
                    if ((uVar12 & 2) == 0) {
                      uVar8 = uVar8 & 0xffff;
                      goto LAB_40e46588;
                    }
                    uVar8 = (uint)(short)uVar8;
                  }
                  goto LAB_40e465c0;
                }
              }
LAB_40e46588:
              uVar10 = 0;
            }
LAB_40e465c4:
            pbVar13 = (byte *)FUN_40e45d88(pbVar13,uVar5,uVar8,uVar10,uVar5,uVar9,uVar15,uVar12);
            param_3 = puVar17;
            goto LAB_40e465dc;
          }
        }
        else {
          if (bVar1 == 0x73) {
            pbVar13 = (byte *)FUN_40e45cf4(pbVar13,*param_3,uVar9,uVar15,uVar12);
            param_3 = param_3 + 1;
            goto LAB_40e465dc;
          }
          if (bVar1 < 0x74) {
            if (bVar1 == 0x6f) {
              uVar5 = 8;
              goto LAB_40e46544;
            }
            if (bVar1 == 0x70) {
              puVar7 = param_3 + 1;
              uVar10 = *param_3;
              bVar1 = param_2[1];
              if (bVar1 == 0x4d) {
LAB_40e462bc:
                puVar11 = auStack_48;
                iVar6 = 0;
                do {
                  uVar2 = *(undefined1 *)(DAT_40e465f8/*=0x47f34d0a*/ + (*(byte *)(uVar10 + iVar6) & 0xf) + 0x10);
                  *puVar11 = *(undefined1 *)
                              (DAT_40e465f8/*=0x47f34d0a*/ + (uint)(*(byte *)(uVar10 + iVar6) >> 4) + 0x10);
                  puVar11[1] = uVar2;
                  uVar8 = ((uVar12 ^ 0x40) << 0x19) >> 0x1f;
                  if (iVar6 == 5) {
                    uVar8 = 0;
                  }
                  iVar6 = iVar6 + 1;
                  if (uVar8 == 0) {
                    puVar11 = puVar11 + 2;
                  }
                  else {
                    puVar11[2] = 0x3a;
                    puVar11 = puVar11 + 3;
                  }
                } while (iVar6 != 6);
LAB_40e463c0:
                *puVar11 = 0;
LAB_40e46474:
                pbVar13 = (byte *)FUN_40e45cf4(pbVar13,auStack_48,uVar9,uVar15,uVar12 & 0xffffffbf);
                pbVar14 = param_2;
              }
              else {
                if (bVar1 < 0x4e) {
                  if (bVar1 == 0x49) {
LAB_40e46328:
                    if (param_2[2] == 0x36) {
                      puVar11 = auStack_48;
                      iVar6 = 0;
                      do {
                        bVar1 = *(byte *)(uVar10 + iVar6 * 2);
                        uVar2 = *(undefined1 *)(DAT_40e465f8/*=0x47f34d0a*/ + (bVar1 & 0xf) + 0x10);
                        *puVar11 = *(undefined1 *)(DAT_40e465f8/*=0x47f34d0a*/ + (uint)(bVar1 >> 4) + 0x10);
                        puVar11[1] = uVar2;
                        bVar1 = *(byte *)(uVar10 + iVar6 * 2 + 1);
                        uVar2 = *(undefined1 *)(DAT_40e465f8/*=0x47f34d0a*/ + (bVar1 & 0xf) + 0x10);
                        puVar11[2] = *(undefined1 *)(DAT_40e465f8/*=0x47f34d0a*/ + (uint)(bVar1 >> 4) + 0x10);
                        puVar11[3] = uVar2;
                        uVar8 = ((uVar12 ^ 0x40) << 0x19) >> 0x1f;
                        if (iVar6 == 7) {
                          uVar8 = 0;
                        }
                        iVar6 = iVar6 + 1;
                        if (uVar8 == 0) {
                          puVar11 = puVar11 + 4;
                        }
                        else {
                          puVar11[4] = 0x3a;
                          puVar11 = puVar11 + 5;
                        }
                      } while (iVar6 != 8);
                      goto LAB_40e463c0;
                    }
                    if (param_2[2] == 0x34) {
                      iVar6 = 0;
                      puVar11 = auStack_48;
                      do {
                        iVar3 = FUN_40e45ae4(auStack_4c,*(undefined1 *)(uVar10 + iVar6));
                        iVar3 = iVar3 - (int)auStack_4c;
                        puVar18 = auStack_4c + iVar3;
                        puVar16 = puVar11 + iVar3;
                        for (; puVar11 != puVar16; puVar11 = puVar11 + 1) {
                          puVar18 = puVar18 + -1;
                          *puVar11 = *puVar18;
                        }
                        bVar19 = iVar6 != 3;
                        iVar6 = iVar6 + 1;
                        if (bVar19) {
                          *puVar16 = 0x2e;
                          puVar16 = puVar16 + 1;
                        }
                        puVar11 = puVar16;
                      } while (iVar6 != 4);
                      *puVar16 = 0;
                      goto LAB_40e46474;
                    }
                    uVar12 = uVar12 & 0xffffffbf;
                  }
                }
                else {
                  if (bVar1 == 0x69) {
                    uVar12 = uVar12 | 0x40;
                    goto LAB_40e46328;
                  }
                  if (bVar1 == 0x6d) {
                    uVar12 = uVar12 | 0x40;
                    goto LAB_40e462bc;
                  }
                }
                if (uVar9 == 0xffffffff) {
                  uVar12 = uVar12 | 0x21;
                  uVar9 = 8;
                }
                else {
                  uVar12 = uVar12 | 0x20;
                }
                pbVar13 = (byte *)FUN_40e45d88(pbVar13,0x70,uVar10,0,0x10,uVar9,uVar15,uVar12);
                pbVar14 = param_2;
              }
              do {
                param_2 = pbVar14;
                param_3 = puVar7;
                pbVar14 = param_2 + 1;
              } while ((*(byte *)(DAT_40e465fc/*=0x47f34c04*/ + (uint)param_2[1]) & 7) != 0);
              goto LAB_40e465dc;
            }
          }
          else {
            if (bVar1 == 0x75) goto LAB_40e46538;
            if (bVar1 == 0x78) {
              uVar12 = uVar12 | 0x20;
              goto LAB_40e46504;
            }
          }
        }
        *pbVar13 = 0x25;
        if (*param_2 == 0) {
          pbVar13 = pbVar13 + 1;
          param_2 = param_2 + -1;
        }
        else {
          pbVar13[1] = *param_2;
          pbVar13 = pbVar13 + 2;
        }
      }
    }
    else {
      *pbVar13 = bVar1;
LAB_40e464fc:
      pbVar13 = pbVar13 + 1;
    }
LAB_40e465dc:
    param_2 = param_2 + 1;
  } while( true );
}

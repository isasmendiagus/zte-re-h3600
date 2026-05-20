// module: mt7915.ko
// function: hqa_muru_parse_cmd_param_dltx @ 0x23b550
// size: 2200 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 hqa_muru_parse_cmd_param_dltx(int param_1,char *param_2,char *param_3,uint *param_4)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  undefined4 uVar10;
  int local_30;
  char *local_2c [2];
  
  local_2c[0] = param_3;
  iVar5 = strcmp("comm_cfg",param_2);
  if (iVar5 == 0) {
    pcVar7 = strsep(local_2c,":");
    if (pcVar7 != (char *)0x0) {
      bVar1 = os_str_tol(pcVar7,0,10);
      *(byte *)((int)param_4 + 0xe) = bVar1;
      if (1 < bVar1) {
LAB_0023b6e4:
        uVar10 = 0;
        iVar5 = DebugLevel;
        goto LAB_0023b5dc;
      }
      iVar5 = net_ad_wrap_service(param_1);
      uVar2 = HcGetWmmIdx(param_1,*(undefined4 *)
                                   ((uint)*(byte *)((int)param_4 + 0xe) * 0xd18 + iVar5 + 0x508));
      *param_4 = *param_4 | 0xc;
      *(undefined1 *)((int)param_4 + 0xf) = uVar2;
      pcVar7 = strsep(local_2c,":");
      if (pcVar7 != (char *)0x0) {
        uVar2 = os_str_tol(pcVar7,0,10);
        *(undefined1 *)(param_4 + 5) = uVar2;
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 != (char *)0x0) {
          uVar2 = os_str_tol(pcVar7,0,10);
          *(undefined1 *)((int)param_4 + 0x15) = uVar2;
          pcVar7 = strsep(local_2c,":");
          if (pcVar7 != (char *)0x0) {
            uVar2 = os_str_tol(pcVar7,0,10);
            *(undefined1 *)((int)param_4 + 0x16) = uVar2;
            pcVar7 = strsep(local_2c,":");
            if (pcVar7 != (char *)0x0) {
              iVar5 = *(int *)(param_1 + 0x7959b8);
              if (iVar5 == 0) {
                iVar5 = os_str_tol(pcVar7,0,10);
              }
              *(char *)((int)param_4 + 0x12) = (char)iVar5;
              *(byte *)(param_4 + 3) = (byte)param_4[3] | 8;
              *(byte *)((int)param_4 + 0xd) = *(byte *)((int)param_4 + 0xd) | 1;
              *param_4 = *param_4 | 3;
              pcVar7 = strsep(local_2c,":");
              if (pcVar7 == (char *)0x0) goto LAB_0023b6e4;
              iVar5 = strcmp("VHT",pcVar7);
              if (iVar5 == 0) {
                *(undefined1 *)((int)param_4 + 0x13) = 0;
              }
              else {
                iVar5 = strcmp("HE",pcVar7);
                if (iVar5 == 0) {
                  *(undefined1 *)((int)param_4 + 0x13) = 1;
                }
              }
              pcVar7 = strsep(local_2c,":");
              if (pcVar7 != (char *)0x0) {
                uVar2 = os_str_tol(pcVar7,0,10);
                *param_4 = *param_4 | 0x10;
                iVar5 = DebugLevel;
                *(undefined1 *)(param_4 + 4) = uVar2;
                if (0 < iVar5) {
                  printk("%s:cmd=comm_cfg: band=%u, AC=%u, bw=%u, GI=%u, UserCnt=%u, TxMode=%u, SpeIdx=%u\n"
                         ,"hqa_muru_parse_cmd_param_dltx",*(undefined1 *)((int)param_4 + 0xe),
                         *(undefined1 *)((int)param_4 + 0xf),(char)param_4[5],
                         *(undefined1 *)((int)param_4 + 0x15),*(undefined1 *)((int)param_4 + 0x12),
                         *(undefined1 *)((int)param_4 + 0x13),uVar2);
                }
                uVar10 = 1;
                _LANCHOR1 = (1 << *(sbyte *)((int)param_4 + 0x12)) - 1;
                param_4[1] = param_4[1] | 0x37;
                goto LAB_0023b58c;
              }
            }
          }
        }
      }
    }
    uVar10 = 0;
    iVar5 = DebugLevel;
    goto LAB_0023b5dc;
  }
  uVar10 = 0;
LAB_0023b58c:
  iVar5 = strcmp("comm_sigb_cfg",param_2);
  if (iVar5 == 0) {
    pcVar7 = strsep(local_2c,":");
    if (pcVar7 != (char *)0x0) {
      cVar3 = os_str_tol(pcVar7,0,10);
      if (cVar3 != -1) {
        *(char *)((int)param_4 + 0x17) = cVar3;
        param_4[1] = param_4[1] | 0x40;
      }
      pcVar7 = strsep(local_2c,":");
      if (pcVar7 != (char *)0x0) {
        cVar3 = os_str_tol(pcVar7,0,10);
        if (cVar3 != -1) {
          *(char *)(param_4 + 6) = cVar3;
          param_4[1] = param_4[1] | 0x80;
        }
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 != (char *)0x0) {
          cVar3 = os_str_tol(pcVar7,0,10);
          if (cVar3 != -1) {
            *(char *)((int)param_4 + 0x19) = cVar3;
            param_4[1] = param_4[1] | 0x100;
          }
          if (DebugLevel < 1) {
            uVar10 = 1;
          }
          else {
            uVar10 = 1;
            printk("%s:cmd=comm_sigb_cfg: sigb mcs=%u, sigb dcm=%u, sigb compress=%u\n",
                   "hqa_muru_parse_cmd_param_dltx",*(undefined1 *)((int)param_4 + 0x17),
                   (char)param_4[6],(char)param_4[6]);
          }
          goto LAB_0023b5a4;
        }
      }
    }
  }
  else {
LAB_0023b5a4:
    iVar5 = strcmp("comm_toneplan",param_2);
    if (iVar5 == 0) {
      uVar9 = (byte)param_4[5] - 1 & 0xff;
      if (uVar9 < 3) {
        iVar5 = *(int *)(&DAT_002a3b18 + uVar9 * 4);
        if (0 < iVar5) goto LAB_0023b608;
      }
      else {
        iVar5 = 1;
LAB_0023b608:
        iVar6 = 0;
        local_30 = 0;
        uVar9 = 0;
        do {
          pcVar7 = strsep(local_2c,":");
          if (pcVar7 == (char *)0x0) goto LAB_0023b860;
          if (iVar6 % 5 == 4) {
            uVar2 = os_str_tol(pcVar7,0,10);
            *(undefined1 *)((int)param_4 + local_30 + 0x22) = uVar2;
            local_30 = local_30 + 1;
            uVar8 = uVar9;
          }
          else {
            if (7 < uVar9) break;
            uVar2 = os_str_tol(pcVar7,0,10);
            uVar8 = uVar9 + 1;
            *(undefined1 *)((int)param_4 + uVar9 + 0x1a) = uVar2;
          }
          iVar6 = iVar6 + 1;
          uVar9 = uVar8;
        } while (iVar6 < iVar5);
      }
      if (0 < DebugLevel) {
        printk("%s:cmd=comm_toneplan: RU1=%u,RU2=%u,RU3=%u,RU4=%u,D26=%u,RU5=%u,RU6=%u,RU7=%u,RU8=%u,U26=%u\n"
               ,"hqa_muru_parse_cmd_param_dltx",*(undefined1 *)((int)param_4 + 0x1a),
               *(undefined1 *)((int)param_4 + 0x1b),(char)param_4[7],
               *(undefined1 *)((int)param_4 + 0x1d),*(undefined1 *)((int)param_4 + 0x22),
               *(undefined1 *)((int)param_4 + 0x1e),*(undefined1 *)((int)param_4 + 0x1f),
               (char)param_4[8],*(undefined1 *)((int)param_4 + 0x21),
               *(undefined1 *)((int)param_4 + 0x23));
      }
      uVar10 = 1;
      param_4[1] = param_4[1] | 8;
    }
    iVar6 = strcmp("user",param_2);
    iVar5 = DebugLevel;
    if (iVar6 != 0) goto LAB_0023b5dc;
    pcVar7 = strsep(local_2c,":");
    if (pcVar7 != (char *)0x0) {
      iVar5 = os_str_tol(pcVar7,0,10);
      pcVar7 = strsep(local_2c,":");
      if (pcVar7 != (char *)0x0) {
        uVar4 = os_str_tol(pcVar7,0,10);
        uVar9 = iVar5 - 1U & 0xff;
        *(undefined2 *)(param_4 + uVar9 * 4 + 9) = uVar4;
        pcVar7 = strsep(local_2c,":");
        if (pcVar7 != (char *)0x0) {
          uVar2 = os_str_tol(pcVar7,0,10);
          *(undefined1 *)((int)param_4 + uVar9 * 0x10 + 0x26) = uVar2;
          pcVar7 = strsep(local_2c,":");
          if (pcVar7 != (char *)0x0) {
            uVar2 = os_str_tol(pcVar7,0,10);
            *(undefined1 *)((int)param_4 + uVar9 * 0x10 + 0x27) = uVar2;
            pcVar7 = strsep(local_2c,":");
            if (pcVar7 != (char *)0x0) {
              uVar2 = os_str_tol(pcVar7,0,10);
              *(undefined1 *)(param_4 + uVar9 * 4 + 10) = uVar2;
              pcVar7 = strsep(local_2c,":");
              if (pcVar7 != (char *)0x0) {
                uVar2 = os_str_tol(pcVar7,0,10);
                *(undefined1 *)((int)param_4 + uVar9 * 0x10 + 0x29) = uVar2;
                pcVar7 = strsep(local_2c,":");
                if (pcVar7 != (char *)0x0) {
                  uVar2 = os_str_tol(pcVar7,0,10);
                  *(undefined1 *)((int)param_4 + uVar9 * 0x10 + 0x2a) = uVar2;
                  pcVar7 = strsep(local_2c,":");
                  if (pcVar7 != (char *)0x0) {
                    cVar3 = os_str_tol(pcVar7,0,10);
                    *(char *)((int)param_4 + uVar9 * 0x10 + 0x2b) = cVar3;
                    if (cVar3 != '\0') {
                      param_4[1] = param_4[1] | 0x200000;
                    }
                    pcVar7 = strsep(local_2c,":");
                    if (pcVar7 != (char *)0x0) {
                      uVar2 = os_str_tol(pcVar7,0,10);
                      iVar5 = uVar9 * 0x10;
                      *(undefined1 *)(param_4 + uVar9 * 4 + 0xb) = uVar2;
                      pcVar7 = strsep(local_2c,":");
                      if (pcVar7 != (char *)0x0) {
                        uVar2 = os_str_tol(pcVar7,0,10);
                        *(undefined1 *)((int)param_4 + iVar5 + 0x2d) = uVar2;
                        pcVar7 = strsep(local_2c,":");
                        if (pcVar7 != (char *)0x0) {
                          uVar2 = os_str_tol(pcVar7,0,10);
                          *(undefined1 *)((int)param_4 + iVar5 + 0x2e) = uVar2;
                          pcVar7 = strsep(local_2c,":");
                          if (pcVar7 != (char *)0x0) {
                            uVar2 = os_str_tol(pcVar7,0,10);
                            *(undefined1 *)((int)param_4 + iVar5 + 0x2f) = uVar2;
                            pcVar7 = strsep(local_2c,":");
                            if (pcVar7 != (char *)0x0) {
                              uVar2 = os_str_tol(pcVar7,0,10);
                              *(undefined1 *)(param_4 + uVar9 * 4 + 0xc) = uVar2;
                              param_4[1] = param_4[1] | 0x800000;
                            }
                            if (0 < DebugLevel) {
                              printk("%s:cmd=user, user#%u, WlanIdx=%u, RBN=%u, RuAlloc=%u, Ldpc=%u, Nss=%u, Mcs=%u, MuGroup=%u, VhtGid=%u, VhtUp=%u, HeStartStream=%u, HeMuMimoSpatial=%u, AckPolicy=%u\n"
                                     ,"hqa_muru_parse_cmd_param_dltx",uVar9 + 1,
                                     (short)param_4[uVar9 * 4 + 9],
                                     *(undefined1 *)((int)param_4 + uVar9 * 0x10 + 0x26),
                                     *(undefined1 *)((int)param_4 + uVar9 * 0x10 + 0x27),
                                     (char)param_4[uVar9 * 4 + 10],
                                     *(undefined1 *)((int)param_4 + uVar9 * 0x10 + 0x29),
                                     *(undefined1 *)((int)param_4 + uVar9 * 0x10 + 0x2a),
                                     *(undefined1 *)((int)param_4 + uVar9 * 0x10 + 0x2b),
                                     (char)param_4[uVar9 * 4 + 0xb],
                                     *(undefined1 *)((int)param_4 + iVar5 + 0x2d),
                                     *(undefined1 *)((int)param_4 + iVar5 + 0x2e),
                                     *(undefined1 *)((int)param_4 + iVar5 + 0x2f),
                                     (char)param_4[uVar9 * 4 + 0xc]);
                            }
                            iVar5 = DebugLevel;
                            uVar10 = 1;
                            param_4[1] = param_4[1] | 0x1f0000;
                            _LANCHOR1 = _LANCHOR1 & ~(1 << uVar9);
                            goto LAB_0023b5dc;
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
LAB_0023b860:
  uVar10 = 0;
  iVar5 = DebugLevel;
LAB_0023b5dc:
  if (3 < iVar5) {
    printk("%s:(status = %d\n","hqa_muru_parse_cmd_param_dltx",uVar10);
  }
  return uVar10;
}


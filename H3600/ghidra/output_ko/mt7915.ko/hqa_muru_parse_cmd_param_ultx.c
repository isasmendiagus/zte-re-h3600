// module: mt7915.ko
// function: hqa_muru_parse_cmd_param_ultx @ 0x23bdec
// size: 1480 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 hqa_muru_parse_cmd_param_ultx(int param_1,char *param_2,char *param_3,uint *param_4)

{
  undefined1 uVar1;
  byte bVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  uint *puVar10;
  uint uVar11;
  char *local_2c [2];
  
  local_2c[0] = param_3;
  iVar5 = strcmp("comm_cfg",param_2);
  if (iVar5 != 0) {
    uVar9 = 0;
LAB_0023be24:
    iVar5 = strcmp("comm_ta",param_2);
    if (iVar5 == 0) {
      puVar10 = (uint *)((int)param_4 + 0x12e);
      do {
        pcVar6 = strsep(local_2c,":");
        uVar9 = 0;
        iVar5 = DebugLevel;
        if (pcVar6 == (char *)0x0) goto LAB_0023becc;
        uVar1 = os_str_tol(pcVar6,0,0x10);
        puVar10 = (uint *)((int)puVar10 + 1);
        *(undefined1 *)puVar10 = uVar1;
      } while (puVar10 != param_4 + 0x4d);
      if (0 < DebugLevel) {
        printk("%s:cmd=comm_ta:%02x:%02x:%02x:%02x:%02x:%02x\n","hqa_muru_parse_cmd_param_ultx",
               *(undefined1 *)((int)param_4 + 0x12f),(char)param_4[0x4c],
               *(undefined1 *)((int)param_4 + 0x131),*(undefined1 *)((int)param_4 + 0x132),
               *(undefined1 *)((int)param_4 + 0x133),(char)param_4[0x4d]);
      }
      uVar9 = 1;
      param_4[2] = param_4[2] | 0x2000;
    }
    iVar5 = strcmp("ul_trig_cfg",param_2);
    if (iVar5 == 0) {
      pcVar6 = strsep(local_2c,":");
      uVar9 = 0;
      iVar5 = DebugLevel;
      if (pcVar6 == (char *)0x0) goto LAB_0023becc;
      sVar3 = os_str_tol(pcVar6,0,10);
      *(short *)((int)param_4 + 0x126) = sVar3;
      if (sVar3 != 0) {
        param_4[2] = param_4[2] | 2;
      }
      pcVar6 = strsep(local_2c,":");
      uVar9 = 0;
      iVar5 = DebugLevel;
      if (pcVar6 == (char *)0x0) goto LAB_0023becc;
      sVar3 = os_str_tol(pcVar6,0,10);
      *(short *)(param_4 + 0x4a) = sVar3;
      if (sVar3 != 0) {
        param_4[2] = param_4[2] | 4;
      }
      if (DebugLevel < 1) {
        uVar9 = 1;
      }
      else {
        uVar9 = 1;
        printk("%s:cmd=ul_trig_cfg: TrigCnt=%u, TrigIntv=%u\n","hqa_muru_parse_cmd_param_ultx",
               *(undefined2 *)((int)param_4 + 0x126));
      }
    }
    iVar7 = strcmp("user",param_2);
    iVar5 = DebugLevel;
    if (iVar7 == 0) {
      pcVar6 = strsep(local_2c,":");
      uVar9 = 0;
      iVar5 = DebugLevel;
      if (pcVar6 != (char *)0x0) {
        iVar7 = os_str_tol(pcVar6,0,10);
        pcVar6 = strsep(local_2c,":");
        uVar9 = 0;
        iVar5 = DebugLevel;
        if (pcVar6 != (char *)0x0) {
          uVar4 = os_str_tol(pcVar6,0,10);
          uVar11 = iVar7 - 1U & 0xff;
          iVar7 = uVar11 * 0xc;
          *(undefined2 *)(param_4 + uVar11 * 3 + 0x50) = uVar4;
          pcVar6 = strsep(local_2c,":");
          uVar9 = 0;
          iVar5 = DebugLevel;
          if (pcVar6 != (char *)0x0) {
            uVar1 = os_str_tol(pcVar6,0,10);
            *(undefined1 *)((int)param_4 + iVar7 + 0x142) = uVar1;
            pcVar6 = strsep(local_2c,":");
            uVar9 = 0;
            iVar5 = DebugLevel;
            if (pcVar6 != (char *)0x0) {
              uVar1 = os_str_tol(pcVar6,0,10);
              *(undefined1 *)((int)param_4 + iVar7 + 0x143) = uVar1;
              pcVar6 = strsep(local_2c,":");
              uVar9 = 0;
              iVar5 = DebugLevel;
              if (pcVar6 != (char *)0x0) {
                uVar1 = os_str_tol(pcVar6,0,10);
                *(undefined1 *)(param_4 + uVar11 * 3 + 0x51) = uVar1;
                pcVar6 = strsep(local_2c,":");
                uVar9 = 0;
                iVar5 = DebugLevel;
                if (pcVar6 != (char *)0x0) {
                  uVar1 = os_str_tol(pcVar6,0,10);
                  *(undefined1 *)((int)param_4 + iVar7 + 0x145) = uVar1;
                  pcVar6 = strsep(local_2c,":");
                  uVar9 = 0;
                  iVar5 = DebugLevel;
                  if (pcVar6 != (char *)0x0) {
                    uVar1 = os_str_tol(pcVar6,0,10);
                    *(undefined1 *)((int)param_4 + iVar7 + 0x146) = uVar1;
                    uVar8 = param_4[2];
                    iVar5 = DebugLevel;
                    if ((uVar8 & 2) != 0) {
                      uVar8 = os_str_tol(pcVar6,0,10);
                      iVar5 = DebugLevel;
                      param_4[uVar11 * 3 + 0x52] = uVar8;
                      if (0 < iVar5) {
                        printk("%s:cmd=user, user#%u, PktSize=%u\n","hqa_muru_parse_cmd_param_ultx",
                               uVar11 + 1,uVar8);
                        iVar5 = DebugLevel;
                      }
                      uVar8 = param_4[2] | 8;
                      param_4[2] = uVar8;
                    }
                    if (0 < iVar5) {
                      iVar5 = uVar11 * 0xc;
                      printk("%s:cmd=user, user#%u, WlanIdx=%u, RBN=%u, RuAlloc=%u, Ldpc=%u, Nss=%u, Mcs=%u\n"
                             ,"hqa_muru_parse_cmd_param_ultx",uVar11 + 1,
                             (short)param_4[uVar11 * 3 + 0x50],
                             *(undefined1 *)((int)param_4 + iVar5 + 0x142),
                             *(undefined1 *)((int)param_4 + iVar5 + 0x143),
                             (char)param_4[uVar11 * 3 + 0x51],
                             *(undefined1 *)((int)param_4 + iVar5 + 0x145),
                             *(undefined1 *)((int)param_4 + iVar5 + 0x146));
                      uVar8 = param_4[2];
                      iVar5 = DebugLevel;
                    }
                    uVar9 = 1;
                    param_4[2] = uVar8 | 0x3d0000;
                    DAT_005f591c = DAT_005f591c & ~(1 << uVar11);
                  }
                }
              }
            }
          }
        }
      }
    }
    goto LAB_0023becc;
  }
  pcVar6 = strsep(local_2c,":");
  if (pcVar6 != (char *)0x0) {
    bVar2 = os_str_tol(pcVar6,0,10);
    *(byte *)((int)param_4 + 0xe) = bVar2;
    if (1 < bVar2) {
LAB_0023bf18:
      uVar9 = 0;
      iVar5 = DebugLevel;
      goto LAB_0023becc;
    }
    iVar5 = net_ad_wrap_service(param_1);
    uVar1 = HcGetWmmIdx(param_1,*(undefined4 *)
                                 ((uint)*(byte *)((int)param_4 + 0xe) * 0xd18 + iVar5 + 0x508));
    *param_4 = *param_4 | 0xc;
    *(undefined1 *)((int)param_4 + 0xf) = uVar1;
    pcVar6 = strsep(local_2c,":");
    if (pcVar6 != (char *)0x0) {
      uVar1 = os_str_tol(pcVar6,0,10);
      *(undefined1 *)((int)param_4 + 0x12a) = uVar1;
      pcVar6 = strsep(local_2c,":");
      if (pcVar6 != (char *)0x0) {
        uVar1 = os_str_tol(pcVar6,0,10);
        *(undefined1 *)((int)param_4 + 299) = uVar1;
        pcVar6 = strsep(local_2c,":");
        if (pcVar6 != (char *)0x0) {
          uVar11 = *(uint *)(param_1 + 0x7959b8);
          if (uVar11 == 0) {
            uVar11 = os_str_tol(pcVar6,0,10);
          }
          uVar8 = uVar11 & 0xff;
          *param_4 = *param_4 | 3;
          iVar5 = DebugLevel;
          *(char *)(param_4 + 0x49) = (char)uVar11;
          *(byte *)(param_4 + 3) = (byte)param_4[3] | 4;
          *(byte *)((int)param_4 + 0xd) = *(byte *)((int)param_4 + 0xd) | 2;
          if (0 < iVar5) {
            printk("%s:cmd=comm_cfg: Band=%u, AC=%u, UlBw=%u, UlGiLtf=%u, UserCnt=%u\n",
                   "hqa_muru_parse_cmd_param_ultx",*(undefined1 *)((int)param_4 + 0xe),
                   *(undefined1 *)((int)param_4 + 0xf),*(undefined1 *)((int)param_4 + 0x12a),
                   *(undefined1 *)((int)param_4 + 299),uVar8);
            uVar8 = (uint)(byte)param_4[0x49];
          }
          uVar9 = 1;
          DAT_005f591c = (1 << uVar8) - 1;
          param_4[2] = param_4[2] | 0x70;
          goto LAB_0023be24;
        }
        goto LAB_0023bf18;
      }
    }
  }
  uVar9 = 0;
  iVar5 = DebugLevel;
LAB_0023becc:
  if (3 < iVar5) {
    printk("%s:(status = %d\n","hqa_muru_parse_cmd_param_ultx",uVar9);
  }
  return uVar9;
}


// module: mt7915.ko
// function: WscEapEnrolleeAction @ 0x1eed0c
// size: 4720 bytes
//

void WscEapEnrolleeAction(int param_1,int param_2,int param_3,int *param_4,undefined4 *param_5)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  ushort uVar4;
  uint uVar5;
  char cVar6;
  undefined1 uVar7;
  undefined4 uVar8;
  int iVar9;
  undefined2 uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined1 *puVar14;
  void *__src;
  uint local_100;
  size_t local_f8;
  uint local_f0;
  void *local_ec;
  undefined1 auStack_e8 [192];
  undefined1 auStack_28 [4];
  
  local_f0 = 0;
  local_ec = (void *)0x0;
  if (2 < DebugLevel) {
    printk("WscEapEnrolleeAction Enter!\n");
  }
  uVar2 = (uint)(*(int *)(param_2 + 0x904) == 0x24);
  uVar1 = uVar2 << 4;
  uVar13 = uVar2;
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    if (param_5[0xa88] == 1) {
      if (*(char *)((int)param_5 + 0x1c51) == '\0') {
        if (param_4 != (int *)0x0) {
LAB_001ef76c:
          iVar12 = 0;
          local_f8 = iVar12;
          goto LAB_001eed9c;
        }
      }
      else if (param_4 == (int *)0x0) goto LAB_001ef76c;
    }
    if (2 < DebugLevel) {
      iVar12 = 0;
      printk("EarlyCheckFailed: pWscControl->WscActionMode=%d, Configured=%d, WscUseUPnP=%d, pEntry=%p!\n"
             ,param_5[0xa88],*(undefined1 *)(param_5 + 2),*(undefined1 *)((int)param_5 + 0x1c51),
             param_4);
      goto LAB_001ef404;
    }
    iVar12 = 0;
LAB_001ef11c:
    if (local_ec != (void *)0x0) {
LAB_001ef124:
      os_free_mem();
    }
    if (uVar13 != 0) goto LAB_001eee04;
    if (iVar12 == 0) goto LAB_001ef138;
LAB_001eee1c:
    if (iVar12 != 2) {
      return;
    }
LAB_001eee24:
    if (param_5[4] != 0x1a && param_5[4] != 4) {
      return;
    }
  }
  else {
    if (*(char *)(param_1 + 0x286285) == '\0') {
      local_f8 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
      if (local_f8 == 0) {
        printk(&_LC309,0x7f7);
        dump_stack();
        return;
      }
      iVar12 = 2;
    }
    else {
      iVar12 = 0xff;
      local_f8 = 0;
    }
LAB_001eed9c:
    if (2 < DebugLevel) {
      printk("MsgType=0x%x, WscState=%d, bUPnPMsg=%d!\n",param_3,param_5[4],uVar2);
    }
    local_100 = uVar1;
    if (((uVar2 == 0) || (param_3 == 0x21 && iVar12 == 0)) || (iVar12 == 2 && param_3 == 0x26)) {
LAB_001ef004:
      iVar11 = *(ushort *)((int)param_5 + 0x2b26) + 0x400;
      os_alloc_mem(0,&local_ec,iVar11);
      if (local_ec == (void *)0x0) {
LAB_001ef7d8:
        if (2 < DebugLevel) {
          printk("WscData Allocate failed!\n");
          goto LAB_001ef404;
        }
        goto LAB_001ef11c;
      }
      __memzero(local_ec,iVar11);
      zte_wps_overlap_detected(param_1,*(byte *)(param_5 + 0x715) & 0xf);
      switch(param_3) {
      case 5:
switchD_001ef064_caseD_5:
        if (2 < DebugLevel) {
          printk("WscEapEnrolleeAction : Rx M2\n");
        }
        if (param_5[4] == 0xd || param_5[4] == 0x10) {
          param_5[3] = 0xd;
          *(undefined4 *)((int)param_5 + 0x1f6) = *(undefined4 *)((int)param_5 + 0x1c55);
          *(undefined2 *)((int)param_5 + 0x1fa) = *(undefined2 *)((int)param_5 + 0x1c59);
          iVar9 = ProcessMessageM2(param_1,param_5,param_2,*(undefined4 *)(param_2 + 0x908),
                                   *(byte *)(param_5 + 0x715) & 0xf,param_5 + 0x1c);
          if (iVar9 == 0) {
            if ((iVar12 != 0) || (*(char *)((int)param_5 + 0x2bd9) == '\0')) {
              local_f8 = BuildMessageM3(param_1,param_5,local_ec);
              param_5[3] = 0xf;
              param_5[4] = 0x13;
              local_100 = uVar1 | 4;
              break;
            }
            iVar9 = 0xf;
          }
LAB_001ef65c:
          if (2 < DebugLevel) {
            printk("WscEapEnrolleeAction : rv = %d\n",iVar9);
          }
          if ((iVar12 == 0) && (*(char *)((int)param_5 + 0x2bd9) != '\0')) {
            iVar9 = 0xf;
            uVar10 = 0xf;
LAB_001ef684:
            *(undefined2 *)(param_5 + 0x5e) = uVar10;
          }
          else {
            if (iVar9 < 0x13) {
              uVar10 = (undefined2)iVar9;
              goto LAB_001ef684;
            }
            if (iVar9 - 0xfeU < 2) {
              *(undefined2 *)(param_5 + 0x5e) = 2;
            }
          }
          if (iVar9 == 0x12) {
            uVar8 = 0x21;
          }
          else {
            uVar8 = 2;
          }
          param_5[3] = uVar8;
          if (uVar2 == 0) {
            FUN_001e2b5c(param_1,param_4,param_5);
          }
          else {
            if (*(char *)((int)param_5 + 0x278d) == '\x01') {
              RTMPCancelTimer(param_5 + 0x9e5,auStack_e8);
              *(undefined1 *)((int)param_5 + 0x278d) = 0;
            }
            *(undefined1 *)(param_5 + 0x9e3) = 0;
          }
          if (iVar12 == 0) {
            param_5[4] = 0;
            if ((param_4 != (int *)0x0) && (*param_4 == 2)) {
              param_5[4] = 0x1b;
            }
          }
          else if (iVar12 == 2) {
            param_5[4] = 0x1b;
            if (param_5[10] == 0) {
              *(undefined1 *)(local_f8 + 0x4160) = 0;
            }
            else {
              *(char *)(local_f8 + 0x4160) = (char)param_5[10];
              __memzero((void *)(local_f8 + 0x4140),0x20);
              memmove((void *)(local_f8 + 0x4140),param_5 + 0xb,param_5[10]);
            }
          }
          goto LAB_001ef11c;
        }
        local_f8 = 0;
        break;
      case 6:
        if (2 < DebugLevel) {
          printk("WscEapEnrolleeAction : Rx M2D\n");
        }
        if (param_5[4] == 0xd || param_5[4] == 0x10) {
          iVar9 = ProcessMessageM2D(param_1,param_2,*(undefined4 *)(param_2 + 0x908),param_5 + 0x1c)
          ;
          if (iVar9 != 0) goto LAB_001ef65c;
          param_5[3] = 0xe;
          if ((param_4 == (int *)0x0 || iVar12 != 0) || (*param_4 == 2)) {
            local_100 = uVar1 | 2;
            local_f8 = BuildMessageACK(param_1,param_5,local_ec);
          }
          else {
            local_100 = uVar1 | 3;
            local_f8 = BuildMessageNACK(param_1,param_5,local_ec);
          }
          param_5[4] = 0x10;
        }
        else {
          local_f8 = 0;
        }
        break;
      default:
        if (DebugLevel < 3) {
          local_f8 = 0;
        }
        else {
          local_f8 = 0;
          printk("WscEapEnrolleeAction : Unsupported Msg Type\n");
        }
LAB_001ef6f8:
        if (uVar2 == 0) goto LAB_001ef2dc;
        if (param_3 == 0xc) {
          iVar11 = param_5[4];
          goto LAB_001ef710;
        }
        goto LAB_001ef2f4;
      case 8:
        if (2 < DebugLevel) {
          printk("WscEapEnrolleeAction : Rx M4\n");
        }
        if (param_5[4] == 0x13) {
          param_5[3] = 0x12;
          iVar9 = ProcessMessageM4(param_1,param_5,param_2,*(undefined4 *)(param_2 + 0x908),
                                   param_5 + 0x1c);
          if (iVar9 != 0) {
LAB_001efa20:
            if (iVar12 == 0) {
              WscCheckPinAttackCount(param_1,param_5);
            }
            goto LAB_001ef65c;
          }
          local_f8 = BuildMessageM5(param_1,param_5,local_ec);
          param_5[3] = 0x13;
          param_5[4] = 0x15;
          local_100 = uVar1 | 4;
        }
        else {
LAB_001ef2d0:
          local_f8 = 0;
        }
        break;
      case 10:
        if (2 < DebugLevel) {
          printk("WscEapEnrolleeAction : Rx M6\n");
        }
        if (param_5[4] != 0x15) goto LAB_001ef2d0;
        param_5[3] = 0x16;
        iVar9 = ProcessMessageM6(param_1,param_5,param_2,*(undefined4 *)(param_2 + 0x908),
                                 param_5 + 0x1c);
        if (iVar9 != 0) goto LAB_001efa20;
        local_f8 = BuildMessageM7(param_1,param_5,local_ec);
        param_5[3] = 0x17;
        param_5[4] = 0x17;
        local_100 = uVar1 | 4;
        if (param_4 != (int *)0x0) {
          _raw_spin_lock_bh(param_5 + 0xb00);
          WscDelListEntryByMAC(param_5 + 0xb01,param_4 + 0x3b);
          _raw_spin_unlock_bh(param_5 + 0xb00);
        }
        break;
      case 0xc:
        if (2 < DebugLevel) {
          printk("WscEapEnrolleeAction : Rx M8\n");
        }
        iVar11 = param_5[4];
        if (iVar11 == 0x17) {
          iVar11 = 0x1a;
          param_5[3] = 0x1a;
          iVar9 = ProcessMessageM8(param_1,param_2,*(undefined4 *)(param_2 + 0x908),param_5);
          if (iVar9 != 0) goto LAB_001ef65c;
          local_100 = uVar1 | 5;
          local_f8 = BuildMessageDONE(param_1,param_5,local_ec);
          if (iVar12 == 0) {
            if ((uVar2 < (param_4 != (int *)0x0)) && (*param_4 == 2)) {
              param_5[4] = 0x1a;
              param_5[0xb18] = 0;
              __init_waitqueue_head(param_5 + 0xb19,"&x->wait",TmpInfo_5G);
              iVar11 = param_5[4];
            }
            else {
              iVar11 = 0x19;
              param_5[4] = 0x19;
            }
          }
          else if (iVar12 == 2) {
            param_5[4] = 0x1a;
            param_5[3] = 0x25;
          }
          else {
            iVar11 = param_5[4];
          }
        }
        else {
          local_f8 = 0;
        }
        if (uVar2 != 0) {
LAB_001ef710:
          if (iVar11 == 0x19) {
            *(undefined1 *)((int)param_5 + 0x1c52) = 0;
            param_5[4] = 4;
            param_5[3] = 0x22;
            if (*(char *)((int)param_5 + 0x278d) == '\x01') {
              RTMPCancelTimer(param_5 + 0x9e5,auStack_e8);
              *(undefined1 *)((int)param_5 + 0x278d) = 0;
            }
            *(undefined1 *)(param_5 + 0x9e3) = 0;
            param_5[0x9e4] = 0;
          }
          goto LAB_001ef2f4;
        }
        goto LAB_001ef8cc;
      case 0xd:
        if (2 < DebugLevel) {
          printk("WscEapEnrolleeAction : Rx ACK\n");
        }
        if (param_5[4] == 0x19) {
          param_5[3] = 0x1b;
          WscSendEapFail(param_1,param_5,0);
          param_5[4] = 4;
          param_5[3] = 0x22;
        }
        if (uVar2 == 0) {
          local_f8 = 0;
          if (param_5[4] != 4) goto LAB_001ef300;
          goto LAB_001ef264;
        }
        local_f8 = 0;
        goto LAB_001ef300;
      case 0x21:
      case 0x26:
        if (param_3 == 0x21) {
          if (2 < DebugLevel) {
            printk("WscEapEnrolleeAction : Rx Identity(ReComputePke=%d)\n",
                   *(undefined1 *)(param_5 + 0x106));
          }
        }
        else if ((param_3 == 0x26) && (2 < DebugLevel)) {
          printk("WscEapEnrolleeAction : Rx Wsc_Start(ReComputePke=%d)\n",
                 *(undefined1 *)(param_5 + 0x106));
        }
        if (((*(char *)(param_1 + 0x286285) != '\x01') || (*(char *)(param_5 + 0xb13) != '\x01')) ||
           (*(char *)(param_5 + 0xa79) != '\0')) {
          if (*(char *)(param_5 + 0x106) == '\x01') goto LAB_001efbb0;
LAB_001ef1e0:
          local_100 = uVar1 | 4;
          local_f8 = BuildMessageM1(param_1,param_5,local_ec);
          if (uVar2 == 0) goto LAB_001ef208;
          param_5[3] = 1;
          if ((int)param_5[4] < 0xd) goto LAB_001ef228;
          goto LAB_001ef2f4;
        }
        if (uVar2 != 0) {
          if (2 < DebugLevel) {
            printk("%s(%d): WscAutoTrigger is disabled.\n","WscEapEnrolleeAction",0x869);
          }
          WscUPnPErrHandle(param_1,param_5,*(undefined4 *)(param_2 + 0x910));
          os_free_mem(local_ec);
          return;
        }
        if ((param_4 != (int *)0x0) && (*param_4 == 0x20001)) {
          if (2 < DebugLevel) {
            printk("%s(%d): WscAutoTrigger is disabled! Send EapFail to STA.\n",
                   "WscEapEnrolleeAction",0x86f);
          }
          WscSendEapFail(param_1,param_5,1);
          os_free_mem(local_ec);
          return;
        }
        if (*(char *)(param_5 + 0x106) == '\x01') {
LAB_001efbb0:
          puVar14 = (undefined1 *)((int)param_5 + 0x357);
          local_f0 = 0xc0;
          do {
            uVar7 = RandomByte(param_1);
            puVar14 = puVar14 + 1;
            *puVar14 = uVar7;
          } while (puVar14 != (undefined1 *)((int)param_5 + 0x417));
          __src = (void *)((int)param_5 + 0x419);
          __memzero(__src,0xc0);
          DH_PublicKey_Generate
                    (&WPS_DH_G_VALUE,1,WPS_DH_P_VALUE,0xc0,param_5 + 0xd6,0xc0,__src,&local_f0);
          if (local_f0 < 0xc0) {
            iVar11 = -local_f0;
            iVar9 = iVar11 + 0xc0;
            __memzero(auStack_e8,iVar9);
            uVar5 = local_f0;
            memcpy(auStack_28 + iVar11,__src,local_f0);
            memcpy(__src,auStack_e8,0xc0);
            local_f0 = iVar9 + uVar5;
            if (2 < DebugLevel) {
              printk("%s: Do zero padding!\n","WscEapEnrolleeAction");
            }
          }
          *(undefined1 *)(param_5 + 0x106) = 0;
          goto LAB_001ef1e0;
        }
        local_f8 = BuildMessageM1(param_1,param_5,local_ec);
LAB_001ef208:
        local_100 = uVar1 | 4;
        *(undefined1 *)((int)param_5 + 0x1c52) = 1;
        param_5[3] = 10;
        if ((int)param_5[4] < 0xd) {
LAB_001ef228:
          local_100 = uVar1 | 4;
          param_5[4] = 0xd;
          goto LAB_001ef6f8;
        }
        goto LAB_001ef2e8;
      }
      if (uVar2 == 0) {
LAB_001ef2dc:
        if (param_3 == 0xd) {
          if (param_5[4] == 4) {
LAB_001ef264:
            RTMPCancelTimer(param_5 + 0x9f3,auStack_e8);
            *(undefined1 *)(param_5 + 0x9f2) = 0;
            *(undefined1 *)((int)param_5 + 0x1c52) = 0;
          }
        }
        else {
LAB_001ef2e8:
          if (param_3 == 0xc) {
            iVar11 = param_5[4];
LAB_001ef8cc:
            if (iVar11 == 0x19) goto LAB_001ef264;
          }
        }
      }
LAB_001ef2f4:
      if (local_100 < 0x11) {
LAB_001ef300:
        if (local_100 - 1 < 0xf) {
          if (param_5[4] != 4) {
            param_5[0xafc] = 0;
            param_5[0xaff] = 0;
            *(undefined1 *)(param_5 + 0xafe) = 1;
            if ((*(char *)((int)param_5 + 0x2be1) != '\0') &&
               ((int)(uint)*(ushort *)(param_5 + 0xafb) < (int)local_f8)) {
              if (0x8ff < (int)local_f8) {
                printk(&_LC325,0x9d8);
                dump_stack();
              }
              memmove((void *)param_5[0xafd],local_ec,local_f8);
              param_5[0xafc] = local_f8;
              __memzero(local_ec,local_f8);
              *(undefined1 *)((int)param_5 + 0x2bf9) = 1;
              *(undefined1 *)(param_5 + 0xafe) = 0;
              memmove(local_ec,(void *)param_5[0xafd],(uint)*(ushort *)(param_5 + 0xafb));
              param_5[0xafc] = param_5[0xafc] - (uint)*(ushort *)(param_5 + 0xafb);
              param_5[0xaff] = param_5[0xafd] + (uint)*(ushort *)(param_5 + 0xafb);
            }
            if (iVar12 == 0) {
              if ((param_4 == (int *)0x0) || (*param_4 != 2)) {
                WscSendMessage(param_1,local_100,local_ec);
              }
              else {
                WscSendMessage(param_1,local_100,local_ec);
              }
            }
            else if (iVar12 == 2) {
              WscSendMessage(param_1,local_100,local_ec);
            }
          }
        }
        else {
          uVar13 = 0;
        }
      }
      else {
        cVar6 = WscSendUPnPMessage(param_1,*(byte *)(param_5 + 0x715) & 0xf,0x11,0,local_ec,local_f8
                                   ,*(undefined4 *)(param_2 + 0x910),
                                   *(undefined4 *)(param_2 + 0x914),param_1 + 0x794b5b,iVar12);
        if (cVar6 != '\0') {
          uVar13 = 0;
        }
      }
LAB_001ef404:
      if (2 < DebugLevel) {
        printk("WscEapEnrolleeAction : rv = %d\n",0);
      }
      goto LAB_001ef11c;
    }
    if (param_3 == 5) {
      if (*(char *)(param_5 + 0x9e3) == '\0') {
        if (((iVar12 == 0) && (iVar11 = MacTableLookup(param_1,(int)param_5 + 0x1c55), iVar11 != 0))
           && ((*(byte *)(iVar11 + 0xd25) & 2) != 0)) goto LAB_001eedf4;
        *(undefined1 *)(param_5 + 0x9e3) = 1;
        RTMPSetTimer(param_5 + 0x9e5,15000);
        uVar4 = *(ushort *)((int)param_5 + 0x2b26);
        *(undefined1 *)((int)param_5 + 0x278d) = 1;
      }
      else {
        uVar4 = *(ushort *)((int)param_5 + 0x2b26);
      }
      os_alloc_mem(0,&local_ec,uVar4 + 0x400);
      if (local_ec != (void *)0x0) {
        __memzero(local_ec,uVar4 + 0x400);
        zte_wps_overlap_detected(param_1,*(byte *)(param_5 + 0x715) & 0xf);
        goto switchD_001ef064_caseD_5;
      }
      goto LAB_001ef7d8;
    }
    if (*(char *)(param_5 + 0x9e3) != '\0') goto LAB_001ef004;
LAB_001eedf4:
    if (local_ec != (void *)0x0) goto LAB_001ef124;
LAB_001eee04:
    WscUPnPErrHandle(param_1,param_5,*(undefined4 *)(param_2 + 0x910));
    if (iVar12 != 0) goto LAB_001eee1c;
LAB_001ef138:
    if (uVar2 == 0) {
      if (param_4 == (int *)0x0) {
        return;
      }
      if ((*param_4 == 0x20001) && (param_5[4] == 4 || param_5[4] == 0x19)) goto LAB_001eee34;
      if (*param_4 != 2) {
        return;
      }
      goto LAB_001eee24;
    }
    if (param_5[4] != 4 && param_5[4] != 0x19) {
      return;
    }
  }
LAB_001eee34:
  *(undefined1 *)(param_5 + 0xa79) = 0;
  *(undefined1 *)(param_5 + 0x106) = 1;
  RTMPCancelTimer(param_5 + 0x9f3,auStack_e8);
  if (*(char *)((int)param_5 + 0x1c5b) != '\0') {
    *(undefined1 *)((int)param_5 + 0x1c5b) = 0;
    RTMPCancelTimer(param_5 + 0x717,auStack_e8);
  }
  cVar6 = *(char *)(param_5 + 2);
  if (((cVar6 != '\x01') && (*(char *)((int)param_5 + 0x2a19) != '\x01')) &&
     ((*(char *)((int)param_5 + 0x2b31) == '\0' || iVar12 != 0 ||
      (*(char *)((int)param_5 + 0x2bd9) != '\0')))) goto LAB_001eefe4;
  param_5[3] = 0x22;
  if (iVar12 == 0 && param_4 != (int *)0x0) {
    if (*param_4 == 2) {
      param_5[1] = 1;
    }
    else {
      cVar6 = '\x02';
      *(undefined1 *)(param_5 + 2) = 2;
      param_5[1] = 1;
    }
  }
  else {
    cVar6 = '\x02';
    *(undefined1 *)(param_5 + 2) = 2;
    param_5[1] = 1;
    if (iVar12 != 0) {
      if (iVar12 == 2) {
        *param_5 = 0;
        if (uVar2 != 0) {
          param_5[4] = 0;
          FUN_001e0304(param_1,param_5[0xa7b]);
        }
        if (*(char *)(param_5 + 0xa48) != '\0') {
          (&DAT_00580cca)[param_1] = 1;
          param_5[0x725] = 0;
          WscWriteConfToPortCfg(param_1,param_5,param_5 + 0x726,1);
          *(byte *)(param_1 + 0x794b18) = *(byte *)(param_5 + 0x715) & 0xf;
          RtmpOsTaskWakeUp(param_1 + 0x794ae8);
        }
      }
      goto LAB_001eefe4;
    }
  }
  *(char *)((int)param_5 + 0xca) = cVar6;
  if ((uVar2 < (param_4 != (int *)0x0)) && (*param_4 == 2)) {
    WscWriteConfToApCliCfg(param_1,param_5,param_5 + 0x726,1);
    RtmpOsTaskWakeUp(param_1 + 0x794ae8);
LAB_001eef34:
    if (((param_4 != (int *)0x0) == 0) || (*param_4 != 0x20001)) goto LAB_001eefe4;
  }
  else {
    RTMPSetTimer(param_5 + 0xacd,1000);
    *(undefined1 *)(param_5 + 0xada) = 1;
    if (uVar2 == 0) goto LAB_001eef34;
  }
  bVar3 = *(byte *)(param_5 + 0x715);
  WscBuildBeaconIE(param_1,2,0,0,0,bVar3 & 0xf,0,0,0);
  WscBuildProbeRespIE(param_1,3,2,0,0,0,*(byte *)(param_5 + 0x715) & 0xf,0,0,0);
  UpdateBeaconHandler(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              + (bVar3 & 0xf) * 0x5834 + param_1 + 0xe0,2);
LAB_001eefe4:
  uVar8 = HcGetBandByWdev(param_5[0xa7b]);
  RTMPSetLED(param_1,0xb,uVar8);
  return;
}


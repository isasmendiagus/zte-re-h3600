// module: mt7915.ko
// function: APOverlappingBSSScan @ 0x15e04
// size: 1740 bytes
//

/* WARNING: Type propagation algorithm not settling */

void APOverlappingBSSScan(int param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  byte bVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  char cVar13;
  undefined1 *puVar14;
  int iVar15;
  uint local_a0;
  uint local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  char *local_70;
  int local_6c;
  uint local_68;
  uint local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  undefined1 auStack_4c [4];
  undefined1 auStack_48 [12];
  undefined4 local_3c [3];
  undefined4 *******local_30;
  undefined4 *******local_2c;
  
  uVar2 = *(ushort *)(param_2 + 0x18);
  cVar13 = *(char *)(param_2 + 0x1a);
  local_7c = wlan_operate_get_ht_bw(param_2);
  local_74 = wlan_operate_get_ext_cha(param_2);
  local_80 = HcGetBandByWdev(param_2);
  pcVar4 = (char *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),local_80);
  if (2 < DebugLevel) {
    printk("APOverlappingBSSScan!!!\n");
  }
  if ((uVar2 & 0x4e) != 0) {
    local_5c = param_1 + 0x790000;
    local_78 = param_1 + 0x795000;
    if (*(char *)(param_1 + 0x79564f) != '\0') {
      if (local_7c == 0 || (uVar2 & 0x18) == 0) {
        if (2 < DebugLevel) {
          printk("PhyMode=%d, BW=%d, didn\'t need channel adjustment!\n",uVar2);
        }
      }
      else {
        iVar9 = param_1 + (short)local_80 * 8;
        local_60 = iVar9 + 0x790000;
        local_58 = jiffies;
        iVar10 = *(int *)(iVar9 + 0x795690) - jiffies;
        uVar6 = ~(iVar10 + 6000U) >> 0x1f;
        if (*(int *)(iVar9 + 0x795690) == 0) {
          uVar6 = 0;
        }
        if (uVar6 == 0) {
          uVar6 = (uint)(byte)pcVar4[0x49c];
          if (uVar6 == 0) {
LAB_00015ff8:
            if (DebugLevel < 0) {
              return;
            }
            printk("2.4GHz: Cannot found the Control Channel(%d) in ChannelList, something wrong?\n"
                   ,cVar13);
            return;
          }
          if (*pcVar4 == cVar13) {
            local_68 = 0;
          }
          else {
            local_68 = 0;
            pcVar7 = pcVar4;
            do {
              local_68 = local_68 + 1;
              if (local_68 == uVar6) goto LAB_00015ff8;
              pcVar7 = pcVar7 + 0x14;
            } while (*pcVar7 != cVar13);
          }
          if (local_74 == 1) {
            local_64 = uVar6 - 1;
            if ((int)(local_68 + 4) < (int)uVar6) {
              local_64 = local_68 + 4;
            }
          }
          else {
            local_64 = local_68 - 4 & ~((int)(local_68 - 4) >> 0x1f);
          }
          local_84 = uVar6 - 1;
          greenap_suspend(param_1,2);
          GetBssCoexEffectedChRange(param_1,param_2,auStack_4c,cVar13);
          *(undefined1 *)(param_1 + local_80 + 0x795688) = 0;
          uVar6 = *(uint *)(param_1 + 0xa39f84);
          if ((uVar6 & 0x10000000) == 0) {
            if (2 < DebugLevel) {
              printk("Card still not enable Tx/Rx, enable it now!\n");
              uVar6 = *(uint *)(param_1 + 0xa39f84);
            }
            *(uint *)(param_1 + 0xa39f84) = uVar6 | 0x10000000;
          }
          RTMPEnableRxTx(param_1);
          if (2 < DebugLevel) {
            printk("Ready to do passive scanning for Channel[%d] to Channel[%d]!\n",*pcVar4,
                   pcVar4[local_84 * 0x14]);
          }
          *(undefined1 *)(local_78 + 0x941) = 1;
          iVar9 = 0;
          iVar10 = 0;
          local_70 = pcVar4;
          local_6c = param_2;
          local_54 = param_1;
          do {
            wlan_operate_scan(local_6c,local_70[iVar9]);
            if (2 < DebugLevel) {
              printk("AP OBSS SYNC - BBP R4 to 20MHz.l\n");
            }
            if ((*(uint *)(((uint)&local_a0 & 0xffffe000) + 4) & 0x1fff00) == 0) {
              __init_waitqueue_head(auStack_48,"&_wait",&DetectOverlappingPeriodicRound);
              iVar11 = 0x1e;
              do {
                local_3c[0] = 0;
                local_30 = &local_30;
                local_2c = &local_30;
                for (iVar15 = 1; iVar5 = prepare_to_wait_event(auStack_48,local_3c,1),
                    iVar15 != 0 && iVar5 == 0; iVar15 = schedule_timeout(iVar15)) {
                }
                finish_wait(auStack_48,local_3c);
                iVar11 = iVar11 + -1;
              } while (iVar11 != 0);
            }
            else {
              RtmpusecDelay(300000);
            }
            iVar5 = local_54;
            iVar15 = local_6c;
            pcVar7 = local_70;
            iVar11 = DebugLevel;
            iVar10 = iVar10 + 1;
            iVar9 = iVar9 + 0x14;
          } while (iVar10 <= local_84);
          puVar14 = g_tBssCoexApEntryTable;
          iVar9 = 0;
          *(undefined1 *)(local_78 + 0x941) = 0;
          do {
            if ((g_tBssCoexApEntryTable[iVar9 * 0x10] != '\0') && (2 < iVar11)) {
              local_9c = (uint)(byte)puVar14[10];
              local_98 = (uint)(byte)puVar14[0xb];
              local_a0 = (uint)(byte)puVar14[9];
              local_94 = (uint)(byte)puVar14[0xc];
              local_90 = (uint)(byte)puVar14[0xd];
              printk("[%02d] Ch[%02d] Bssid[%02x:%02x:%02x:%02x:%02x:%02x].\n",iVar9,
                     *(undefined4 *)(puVar14 + 4),puVar14[8]);
              iVar11 = DebugLevel;
            }
            uVar3 = local_64;
            uVar6 = local_68;
            iVar10 = local_84;
            iVar9 = iVar9 + 1;
            puVar14 = puVar14 + 0x10;
          } while (iVar9 != 0x80);
          uVar12 = 0;
          local_84 = iVar5;
          cVar13 = '\0';
          local_70 = pcVar7;
          local_6c = iVar15;
          do {
            if (iVar11 < 3) {
              bVar8 = pcVar7[1];
              if (uVar12 == uVar6 || (bVar8 & 6) == 0) goto LAB_0001637c;
LAB_000162bc:
              cVar13 = '\x01';
            }
            else {
              printk("Channel[Idx=%d, Ch=%d].bEffectedChannel=0x%x!\n",uVar12,*pcVar7,pcVar7[1]);
              bVar8 = pcVar7[1];
              iVar11 = DebugLevel;
              if (uVar12 != uVar6 && (bVar8 & 6) != 0) {
                if (DebugLevel < 3) goto LAB_000162bc;
                cVar13 = '\x01';
                printk("needFallBack=TRUE due to OP/OT!\n");
                bVar8 = pcVar7[1];
                iVar11 = DebugLevel;
              }
LAB_0001637c:
              if (uVar12 == uVar3) {
                bVar8 = 0;
              }
              else {
                bVar8 = bVar8 & 1;
              }
              if (bVar8 != 0) {
                if (iVar11 < 3) goto LAB_000162bc;
                cVar13 = '\x01';
                printk("needFallBack=TRUE due to OS!\n");
                iVar11 = DebugLevel;
              }
            }
            param_2 = local_6c;
            pcVar4 = local_70;
            param_1 = local_84;
            uVar12 = uVar12 + 1;
            pcVar7 = pcVar7 + 0x14;
          } while ((int)uVar12 <= iVar10);
          if (-1 < iVar11) {
            printk("needFallBack=%d BssCoexApCnt:%d BssCoexApCntThr:%d \n",cVar13,
                   *(undefined1 *)(local_78 + 0x650),*(undefined1 *)(local_78 + 0x64f));
          }
          bVar8 = *(byte *)(local_78 + 0x650);
          bVar1 = *(byte *)(local_78 + 0x64f);
          *(undefined1 *)(local_60 + 0x568c) = *(undefined1 *)(param_2 + 0xc);
          if (bVar8 <= bVar1) {
            cVar13 = '\0';
          }
          *(char *)(local_60 + 0x568d) = cVar13;
          *(int *)(local_60 + 0x5690) = local_58;
        }
        else {
          if (1 < DebugLevel) {
            local_a0 = (uint)*(byte *)(iVar9 + 0x79568d);
            local_9c = (iVar10 * 1000 + 6000000U) / 100;
            printk("%s, leverage result of wdev(%d@BN%d), FallBack=%d (remaining %ld ms)\n",
                   "APOverlappingBSSScan",*(undefined1 *)(iVar9 + 0x79568c),local_80);
          }
          cVar13 = *(char *)(local_60 + 0x568d);
        }
        if (cVar13 == '\x01') {
          zte_wlan_operate_set_ht_bw(param_2,0,0);
          *(byte *)(local_78 + 0x6b4) = *(byte *)(local_78 + 0x6b4) | 4;
          *(byte *)(local_78 + 0x652) = *(byte *)(local_78 + 0x652) | 2;
          *(undefined1 *)(param_1 + local_80 + 0x795688) = 1;
        }
        else {
          wlan_operate_set_prim_ch(param_2,*(undefined1 *)(param_2 + 0x1a));
          zte_wlan_operate_set_ht_bw(param_2,local_7c,local_74);
        }
        greenap_resume(param_1,2);
        if ((byte)pcVar4[0x49c] != 0) {
          pcVar7 = pcVar4 + (uint)(byte)pcVar4[0x49c] * 0x14;
          do {
            pcVar4[1] = '\0';
            pcVar4 = pcVar4 + 0x14;
          } while (pcVar4 != pcVar7);
        }
        *(undefined1 *)(local_5c + 0x5650) = 0;
        __memzero(g_tBssCoexApEntryTable,0x800);
      }
    }
  }
  return;
}


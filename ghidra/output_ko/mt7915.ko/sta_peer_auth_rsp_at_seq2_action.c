// module: mt7915.ko
// function: sta_peer_auth_rsp_at_seq2_action @ 0x75c68
// size: 1496 bytes
//

void sta_peer_auth_rsp_at_seq2_action(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  void *__s1;
  undefined1 *puVar10;
  undefined4 uVar11;
  byte *pbVar12;
  undefined4 uVar13;
  undefined1 uStack_6b;
  undefined1 local_6a;
  byte local_69;
  short local_68;
  short local_66;
  short local_64;
  undefined2 local_62;
  int local_60;
  int local_5c;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined1 auStack_4a [4];
  undefined4 local_46;
  undefined2 local_42;
  undefined1 uStack_40;
  byte local_3f;
  undefined4 local_36;
  undefined2 local_32;
  
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_6a = 0x10;
  local_69 = 0x80;
  iVar3 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  iVar8 = *(int *)(param_2 + 0x92c);
  bVar1 = *(byte *)(iVar8 + 0xe);
  if (iVar3 == 0) {
    printk(&_LC3,0x1ef);
    dump_stack();
  }
  if (iVar8 == 0) {
    printk(&_LC1,0x1f0);
    dump_stack();
  }
  if (2 < DebugLevel) {
    printk(&_LC0,"sta_peer_auth_rsp_at_seq2_action");
  }
  if (iVar3 == 0) {
    return;
  }
  iVar6 = *(int *)(iVar8 + 0x14);
  if ((*(char *)(param_1 + 0x286285) == '\x01') && (iVar6 == 2)) {
    iVar6 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(byte *)(iVar6 + 0x14a) <= bVar1) {
      return;
    }
    iVar6 = *(int *)(iVar8 + 0x14);
  }
  if (iVar6 == 0x100) {
    iVar6 = *(int *)(iVar8 + 4) + 0x3c;
  }
  else {
    iVar6 = iVar3 + 0x211e80;
  }
  os_alloc_mem(0,&local_60,0x80);
  if (local_60 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: alloc mem fail\n","sta_peer_auth_rsp_at_seq2_action");
    return;
  }
  os_alloc_mem(0,&local_5c,0x90);
  if (local_5c == 0) {
    if (-1 < DebugLevel) {
      printk("%s: CyperChlgText Allocate memory fail!!!\n","sta_peer_auth_rsp_at_seq2_action");
    }
    os_free_mem(local_60);
    return;
  }
  iVar4 = PeerAuthSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908),&local_46,&local_62,
                         &local_68,&local_66,local_60);
  if (iVar4 == 0) {
    if (2 < DebugLevel) {
      printk("AUTH - PeerAuthSanity() sanity check fail\n");
    }
  }
  else {
    __s1 = (void *)(iVar3 + 0x413a);
    iVar4 = memcmp(__s1,&local_46,6);
    if ((iVar4 == 0) && (local_68 == 2)) {
      if (2 < DebugLevel) {
        printk("AUTH - Receive AUTH_RSP seq#2 to me (Alg=%d, Status=%d, wdev_type=%u)\n",local_62,
               local_66,*(undefined4 *)(iVar8 + 0x14));
      }
      if ((iVar8 != 0) && (*(int *)(iVar8 + 0x14) == 2)) {
        if (*(byte *)(iVar8 + 0x1a) < 0xf) {
          __ZTE_STA_Assoc_Process
                    (param_1,0x15,__s1,0xffffffff,local_66 + 200,0,0,
                     "sta_peer_auth_rsp_at_seq2_action",0x21b);
        }
        else {
          __ZTE_STA_Assoc_Process
                    (param_1,0x15,__s1,0xfffffffb,local_66 + 200,0,0,
                     "sta_peer_auth_rsp_at_seq2_action",0x21f);
        }
      }
      RTMPCancelTimer(iVar6,&uStack_6b);
      if (local_66 == 0) {
        if (*(short *)(iVar3 + 0x4162) != 0) {
          local_64 = local_66;
          local_68 = local_68 + 1;
          uVar9 = (uint)*(byte *)(iVar8 + 0x178);
          iVar3 = os_alloc_mem(param_1,&local_54,0x900);
          if (iVar3 == 0) {
            if (2 < DebugLevel) {
              printk("AUTH - Send AUTH request seq#3...\n");
            }
            MgtMacHeaderInitExt(param_1,&uStack_40,0xb,0,&local_46,iVar8 + 0x1b,__s1);
            local_3f = local_3f | 0x40;
            if (*(int *)(iVar8 + 0x14) == 0x100) {
              local_36 = *(undefined4 *)(*(int *)(iVar8 + 4) + 0x83);
              local_32 = *(undefined2 *)(*(int *)(iVar8 + 4) + 0x87);
            }
            iVar3 = 0;
            pcVar5 = (char *)(uVar9 * 0x51 + iVar8 + 0x5f);
            do {
              pcVar5 = pcVar5 + 1;
              cVar2 = *pcVar5;
              iVar3 = iVar3 + 1;
              *pcVar5 = cVar2 + '\x01';
              if ((char)(cVar2 + '\x01') != '\0') break;
            } while (iVar3 != 3);
            RTMPConstructWEPIVHdr(uVar9,iVar8 + uVar9 * 0x51 + 0x60,auStack_4a);
            uVar7 = (uint)local_69;
            puVar10 = &local_6a;
            pbVar12 = &local_69;
            uVar11 = 1;
            uVar13 = 0xffffffff;
            iVar3 = local_60;
            MakeOutgoingFrame(local_5c,&local_58,2,&local_62,2,&local_68,2,&local_64,1,puVar10,1,
                              pbVar12,uVar7,local_60,0xffffffff);
            iVar4 = RTMPSoftEncryptWEP(auStack_4a,iVar8 + uVar9 * 0x51 + 0x30,local_5c,local_58);
            if (iVar4 == 0) {
              os_free_mem();
              auth_fsm_state_transition(iVar8,0,"sta_peer_auth_rsp_at_seq2_action");
              cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),2,local_66);
            }
            else {
              local_58 = local_58 + 4;
              MakeOutgoingFrame(local_54,&local_50,0x18,&uStack_40,4,auStack_4a,local_58,local_5c,
                                0xffffffff,puVar10,uVar11,pbVar12,uVar7,iVar3,uVar13);
              MiniportMMRequest(param_1,0,local_54,local_50);
              os_free_mem(local_54);
              RTMPSetTimer(iVar6,300);
              auth_fsm_state_transition(iVar8,2,"sta_peer_auth_rsp_at_seq2_action");
            }
          }
          else {
            if (2 < DebugLevel) {
              printk("AUTH - PeerAuthRspAtSeq2Action() allocate memory fail\n");
            }
            auth_fsm_state_transition(iVar8,0,"sta_peer_auth_rsp_at_seq2_action");
            cntl_auth_assoc_conf(iVar8,2,0x52);
          }
          goto LAB_00075d9c;
        }
      }
      else {
        *(short *)(iVar3 + 0x213200) = local_66;
        *(undefined4 *)(iVar3 + 0x213202) = local_46;
        *(undefined2 *)(iVar3 + 0x213206) = local_42;
      }
      auth_fsm_state_transition(iVar8,0,"sta_peer_auth_rsp_at_seq2_action");
      cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),2,local_66);
    }
  }
LAB_00075d9c:
  if (local_60 != 0) {
    os_free_mem();
  }
  if (local_5c != 0) {
    os_free_mem();
  }
  return;
}


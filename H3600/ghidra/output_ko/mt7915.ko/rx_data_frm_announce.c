// module: mt7915.ko
// function: rx_data_frm_announce @ 0xcbe7c
// size: 1276 bytes
//

void rx_data_frm_announce(int param_1,int *param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  undefined1 *puVar7;
  
  bVar1 = *(byte *)(param_4 + 0xc);
  pbVar6 = *(byte **)(param_3 + 0x1c);
  if (param_2 == (int *)0x0) {
    return;
  }
  if (0x67 < bVar1) {
    if (-1 < DebugLevel) {
      printk("%s():Invalid wdev_idx(%d)\n","rx_data_frm_announce",bVar1);
    }
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
    uVar3 = 0x1870;
    goto LAB_000cbee0;
  }
  iVar2 = RTMPCheckWPAframe(param_1,param_2,*(undefined4 *)(param_3 + 0x3c),
                            *(undefined2 *)(param_3 + 0x40),bVar1,0);
  if (iVar2 != 0) {
    uVar4 = *(uint *)(param_3 + 0x44) | 0x40;
    *(uint *)(param_3 + 0x44) = uVar4;
    if ((*param_2 == 0x20001) && ((char)param_2[0x145] == '\x04')) {
      *(undefined1 *)(param_2 + 0x145) = 5;
      uVar4 = *(uint *)(param_3 + 0x44);
    }
    if ((uVar4 & 1) == 0) {
      rx_eapol_frm_handle(param_1,param_2,param_3,bVar1);
      return;
    }
    goto LAB_000cc0a8;
  }
  uVar4 = (uint)(pbVar6 != (byte *)0x0);
  if (((((uVar4 & *(uint *)(param_3 + 0x44) >> 0x14) != 0) && ((*pbVar6 & 0xc) == 8)) &&
      (*(short *)(param_3 + 0x40) != 0)) && ((pbVar6[1] & 0x40) != 0)) {
    if ((1 < DebugLevel) &&
       (printk("%s: CM, wcid=%d\n","rx_data_frm_announce",*(undefined2 *)(param_3 + 0x4e)),
       2 < DebugLevel)) {
      puVar7 = *(undefined1 **)(param_3 + 0x28);
      printk("Addr1=%02x:%02x:%02x:%02x:%02x:%02x\t",*puVar7,puVar7[1],puVar7[2],puVar7[3],puVar7[4]
             ,puVar7[5]);
      if (2 < DebugLevel) {
        puVar7 = *(undefined1 **)(param_3 + 0x2c);
        printk("Addr2=%02x:%02x:%02x:%02x:%02x:%02x\n",*puVar7,puVar7[1],puVar7[2],puVar7[3],
               puVar7[4],puVar7[5]);
      }
    }
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
    uVar3 = 0x1889;
LAB_000cbee0:
    wlan_dbg_set_last_error(0,1,uVar3,"rx_data_frm_announce");
    return;
  }
  uVar5 = uVar4;
  if ((char)param_2[0x3a] != '\x01') {
    uVar5 = 0;
  }
  if ((uVar5 != 0) && ((pbVar6[1] & 3) != 3)) {
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
    uVar3 = 0x1891;
    goto LAB_000cbee0;
  }
  iVar2 = *(int *)(param_2[2] + 0x14);
  if (iVar2 == 2 || iVar2 == 0x40) {
    iVar2 = GetStaCfgByWdev(param_1);
    if ((iVar2 != 0 && *param_2 != 2) && ((*(uint *)(iVar2 + 0x212464) & 0x80) == 0))
    goto LAB_000cc02c;
    iVar2 = *(int *)(param_2[2] + 0x14);
  }
  if (iVar2 == 1 || iVar2 == 0x20) {
    if (*param_2 == 0x20001) {
      if (param_2[0x2b7] == 1) {
        if ((((uVar4 != 0) && ((pbVar6[1] & 0x40) != 0)) && (5 < (uint)param_2[0x2c1])) &&
           (*(byte *)(param_2 + 0x145) < 5)) {
          if (1 < DebugLevel) {
            printk("==> De-Auth this STA(%02x:%02x:%02x:%02x:%02x:%02x)\n",(char)param_2[0x3b],
                   *(undefined1 *)((int)param_2 + 0xed),*(undefined1 *)((int)param_2 + 0xee),
                   *(undefined1 *)((int)param_2 + 0xef),(char)param_2[0x3c],
                   *(undefined1 *)((int)param_2 + 0xf1));
          }
          __MlmeDeAuthAction(param_1,param_2,2,0,"rx_data_frm_announce",0x18d8);
        }
        wlan_dbg_set_last_error(0,1,0x18da,"rx_data_frm_announce");
        goto LAB_000cc02c;
      }
      if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_000cbffc;
      goto LAB_000cc138;
    }
    if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_000cbffc;
  }
  else {
    if (*(char *)(param_1 + 0x286285) == '\0') {
LAB_000cbffc:
      if ((uVar4 == 0) || ((pbVar6[1] & 0x40) == 0)) {
        if (((*(int *)(param_4 + 0x2c) != 1) || (*(int *)(param_4 + 0x174) != 1)) &&
           (*(char *)(param_4 + 0x888) == '\x02')) goto LAB_000cc02c;
      }
      else if (((*(uint *)(param_4 + 0x2c) & 1) != 0) && ((*(uint *)(param_4 + 0x174) & 1) != 0)) {
LAB_000cc02c:
        RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
        return;
      }
    }
    if (*param_2 == 0x20001) {
LAB_000cc138:
      iVar2 = param_2[0x3d];
      if (iVar2 != 0) {
        if ((**(byte **)(param_3 + 0x30) & 1) == 0) {
          *(int *)(iVar2 + 0x4404) = *(int *)(iVar2 + 0x4404) + 1;
        }
        else if (**(byte **)(param_3 + 0x30) == 0xff) {
          *(int *)(iVar2 + 0x4414) = *(int *)(iVar2 + 0x4414) + 1;
        }
        else {
          *(int *)(iVar2 + 0x440c) = *(int *)(iVar2 + 0x440c) + 1;
        }
      }
    }
  }
  uVar4 = *(uint *)(param_3 + 0x44);
  if ((uVar4 & 1) == 0) {
    if ((uVar4 & 2) != 0) {
      indicate_amsdu_pkt(param_1,param_3,bVar1);
      return;
    }
    if ((uVar4 & 4) == 0) {
      indicate_802_11_pkt(param_1,param_3,bVar1);
      return;
    }
    indicate_agg_ralink_pkt(param_1,param_2,param_3,*(undefined1 *)(param_4 + 0xc));
    return;
  }
LAB_000cc0a8:
  indicate_ampdu_pkt(param_1,param_3,bVar1);
  return;
}


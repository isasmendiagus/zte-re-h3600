// module: mt7915.ko
// function: indicate_802_3_pkt @ 0xc9390
// size: 480 bytes
//

void indicate_802_3_pkt(int param_1,int param_2,undefined4 param_3)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  
  iVar6 = *(int *)(param_2 + 0x38);
  iVar2 = FUN_000c53fc();
  if (iVar2 == 0) {
    if (1 < DebugLevel) {
      printk("%s:drop packet by PN mismatch!\n","indicate_802_3_pkt");
    }
    *(int *)(param_1 + 0x9dce4) = *(int *)(param_1 + 0x9dce4) + 1;
    wlan_dbg_set_last_error(0,1,0xf33,"indicate_802_3_pkt");
  }
  else {
    if ((((*(char *)(param_1 + 0x286285) == '\x01') && ((**(byte **)(param_2 + 0x10) & 0x40) != 0))
        && ((&DAT_0036790d)[param_1] != '\0')) && ((&DAT_00367910)[param_1] != '\x01')) {
      iVar2 = *(int *)(iVar6 + 0xcc);
      if (CONCAT11(*(undefined1 *)(iVar2 + 0xc),*(undefined1 *)(iVar2 + 0xd)) == -0x7f00) {
        iVar2 = iVar2 + 0x12;
      }
      else {
        iVar2 = iVar2 + 0xe;
      }
      if ((*(char *)(iVar2 + 9) == '\x11') &&
         (*(short *)(iVar2 + 0x16) == 0x4400 && *(short *)(iVar2 + 0x14) == 0x4300)) {
        iVar4 = RTMPLookupRepeaterCliEntry(param_1,0,(void *)(iVar2 + 0x38),1);
        if (iVar4 != 0) {
          if (*(char *)(iVar4 + 1) != '\x01') {
            printk(&_LC71,0xf60);
            dump_stack();
          }
          memmove((void *)(iVar2 + 0x38),(void *)(iVar4 + 0x7d),6);
        }
        __memzero(iVar2 + 0x1a,2);
        uVar1 = RTMP_UDP_Checksum(iVar6);
        *(undefined2 *)(iVar2 + 0x1a) = uVar1;
      }
    }
    iVar2 = get_netdev_from_bssid(param_1,param_3);
    *(int *)(iVar6 + 0x18) = iVar2;
    if (iVar2 != 0) {
      *(int *)(iVar6 + 0xc0) = *(int *)(iVar6 + 0xcc) + *(int *)(iVar6 + 100);
      uVar5 = *(undefined4 *)(param_2 + 0x38);
      uVar3 = wdev_search_by_idx(param_1,param_3);
      announce_or_forward_802_3_pkt(param_1,uVar5,uVar3,*(undefined1 *)(param_1 + 0x286285));
      return;
    }
    *(int *)(param_1 + 0x9dce0) = *(int *)(param_1 + 0x9dce0) + 1;
  }
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
  return;
}


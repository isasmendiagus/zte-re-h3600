// module: mt7915.ko
// function: sync_fsm_peer_response_join_action @ 0x10838c
// size: 944 bytes
//

void sync_fsm_peer_response_join_action(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined2 local_56;
  int local_54;
  void *local_50;
  undefined1 auStack_4c [4];
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  
  puVar9 = *(undefined4 **)(param_2 + 0x92c);
  local_54 = 0;
  local_50 = (void *)0x0;
  iVar1 = get_scan_ctrl_by_wdev(param_1,puVar9);
  iVar2 = get_scan_tab_by_wdev(param_1,puVar9);
  iVar3 = GetStaCfgByWdev(param_1,puVar9);
  puVar8 = *(undefined4 **)(iVar1 + 0xaf5d0);
  if (puVar8 != puVar9) {
    if (DebugLevel < 4) {
      return;
    }
    printk("%s: %s is not in JOIN state (wdev %s issued scan)!\n",
           "sync_fsm_peer_response_join_action",*puVar9,*puVar8);
    return;
  }
  os_alloc_mem(0,&local_54,0x400);
  iVar1 = local_54;
  if (local_54 == 0) {
    if (DebugLevel < 0) goto LAB_00108498;
    printk("%s: Allocate memory fail!!!\n","sync_fsm_peer_response_join_action");
LAB_00108488:
    if (local_54 == 0) goto LAB_00108498;
  }
  else {
    *(undefined1 *)(local_54 + 1) = 0;
    os_alloc_mem(0,&local_50,0x180);
    if (local_50 != (void *)0x0) {
      __memzero(local_50,0x180);
      iVar4 = PeerBeaconAndProbeRspSanity
                        (param_1,puVar8,param_2,*(undefined4 *)(param_2 + 0x908),
                         *(undefined1 *)(param_2 + 0x91f),local_50,&local_56,iVar1,1,0);
      if (iVar4 != 0) {
        local_46 = *(undefined1 *)(param_2 + 0x91a);
        local_45 = *(undefined1 *)(param_2 + 0x91b);
        local_48 = *(undefined1 *)(param_2 + 0x918);
        local_47 = *(undefined1 *)(param_2 + 0x919);
        uVar5 = rtmp_avg_rssi(param_1,auStack_4c);
        *(undefined1 *)((int)puVar8 + 0x3fe2) = *(undefined1 *)((int)local_50 + 0xa5);
        if ((*(uint *)((int)local_50 + 0xa8) & 0x10) == 0) {
          uVar7 = *(uint *)(iVar3 + 0x2123ec) & 0xffffffef;
        }
        else {
          uVar7 = *(uint *)(iVar3 + 0x2123ec) | 0x10;
        }
        *(uint *)(iVar3 + 0x2123ec) = uVar7;
        if (2 < DebugLevel) {
          printk("%s:RootAP HE_CAP(%d)\n","sync_fsm_peer_response_join_action",
                 (uint)(*(int *)(iVar3 + 0x2123ec) << 0x1b) >> 0x1f);
        }
        ie_field_value_decision(puVar8,local_50);
        iVar4 = BssTableSetEntry(param_1,puVar8,iVar2,local_50,uVar5,local_56,iVar1);
        if (iVar4 == -1) {
          if (-1 < DebugLevel) {
            printk("ERROR: Driver ScanTable Full In Apcli ProbeRsp Join\n");
          }
        }
        else {
          iVar10 = iVar4 * 0xaf4;
          memmove((void *)(iVar2 + iVar10 + 0x4fe),(void *)(param_2 + 0x18),4);
          memmove((void *)(iVar2 + iVar10 + 0x502),(void *)(param_2 + 0x910),4);
          memmove((void *)(iVar2 + iVar10 + 0x506),(void *)(param_2 + 0x910),4);
          uVar7 = (uint)*(byte *)(param_2 + 0x91e) % 10;
          uVar6 = (undefined1)uVar7;
          if (uVar7 == 0) {
            uVar6 = 0xfb;
          }
          *(undefined1 *)(iVar2 + iVar10 + 0x8b) = uVar6;
          memmove((void *)(iVar4 * 0xaf4 + iVar2 + 8),local_50,6);
          iVar4 = puVar8[0x2f3];
          iVar2 = (**(code **)(iVar4 + 0x10))(param_1,puVar8,local_50,param_2);
          if ((iVar2 != 0) &&
             (iVar1 = (**(code **)(iVar4 + 0x14))(param_1,puVar8,local_50,param_2,iVar1,local_56),
             iVar1 != 0)) {
            if (iVar3 != 0) {
              *(undefined1 *)(iVar3 + 0x2123e9) = 1;
            }
            ApCliCheckPeerExistence
                      (param_1,(int)local_50 + 0xc,*(undefined1 *)((int)local_50 + 0x2c),
                       *(undefined1 *)((int)local_50 + 0x30));
          }
        }
      }
      goto LAB_00108488;
    }
    if (-1 < DebugLevel) {
      printk("%s: Allocate ie_list fail!!!\n","sync_fsm_peer_response_join_action");
      goto LAB_00108488;
    }
    if (local_54 == 0) {
      return;
    }
  }
  os_free_mem();
LAB_00108498:
  if (local_50 != (void *)0x0) {
    os_free_mem();
  }
  return;
}


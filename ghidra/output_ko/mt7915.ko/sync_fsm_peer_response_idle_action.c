// module: mt7915.ko
// function: sync_fsm_peer_response_idle_action @ 0x10a4f4
// size: 600 bytes
//

void sync_fsm_peer_response_idle_action(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 local_2a;
  int local_28;
  int local_24 [2];
  
  iVar3 = *(int *)(param_2 + 0x92c);
  local_28 = 0;
  local_24[0] = 0;
  if (param_1 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s():Unexpected pAd NULL!\n","sync_fsm_peer_response_idle_action");
    return;
  }
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return;
  }
  if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
     ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
    return;
  }
  if (*(int *)(iVar3 + 0x14) == 2) {
    iVar2 = GetStaCfgByWdev(param_1,iVar3);
    if (iVar2 == 0) {
      return;
    }
    if (((*(uint *)(iVar2 + 0x212464) & 1) == 0) && ((*(uint *)(param_1 + 0x795124) & 2) == 0)) {
      return;
    }
  }
  os_alloc_mem(0,local_24,0x180);
  if (local_24[0] == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate ie_list fail!!!\n","sync_fsm_peer_response_idle_action");
      goto LAB_0010a5dc;
    }
    if (local_28 == 0) {
      return;
    }
  }
  else {
    __memzero(local_24[0],0x180);
    os_alloc_mem(0,&local_28,0x400);
    iVar2 = local_28;
    if (local_28 == 0) {
      if (DebugLevel < 0) goto LAB_0010a5ec;
      printk("%s: Allocate VarIE fail!!!\n","sync_fsm_peer_response_idle_action");
    }
    else {
      *(undefined1 *)(local_28 + 1) = 0;
      *(undefined1 *)(local_24[0] + 0x30) = *(undefined1 *)(param_2 + 0x91f);
      iVar1 = PeerBeaconAndProbeRspSanity
                        (param_1,iVar3,param_2,*(undefined4 *)(param_2 + 0x908),
                         *(undefined1 *)(param_2 + 0x91f),local_24[0],&local_2a,local_28,0,0);
      if (iVar1 != 0) {
        if ((*(uint *)(local_24[0] + 0xa8) & 0x20) != 0) {
          parse_he_bss_color_info(iVar3,local_24[0]);
        }
        iVar4 = *(int *)(iVar3 + 0xbcc);
        iVar1 = (**(code **)(iVar4 + 8))(param_1,iVar3,local_24[0],param_2);
        if (iVar1 == 1) {
          (**(code **)(iVar4 + 0xc))(param_1,iVar3,local_24[0],param_2,iVar2,local_2a);
        }
      }
    }
LAB_0010a5dc:
    if (local_28 == 0) goto LAB_0010a5ec;
  }
  os_free_mem();
LAB_0010a5ec:
  if (local_24[0] != 0) {
    os_free_mem();
  }
  return;
}


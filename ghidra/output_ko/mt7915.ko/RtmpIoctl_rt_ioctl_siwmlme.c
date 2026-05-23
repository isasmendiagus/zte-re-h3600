// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwmlme @ 0x631b4
// size: 740 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4
RtmpIoctl_rt_ioctl_siwmlme(int *param_1,undefined4 param_2,undefined2 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  char *local_58;
  undefined4 local_54;
  int local_4c;
  undefined1 auStack_48 [12];
  undefined4 local_3c [3];
  undefined4 *******local_30;
  undefined4 *******local_2c;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  local_4c = 0;
  piVar4 = param_1 + iVar3 * 0x84dec + 0xdb6d6;
  os_alloc_mem(0,&local_4c,0x930);
  if (local_4c == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","RtmpIoctl_rt_ioctl_siwmlme");
      return 1;
    }
    return 1;
  }
  if (param_4 == 1) {
    if (2 < DebugLevel) {
      printk("====> %s - IW_MLME_DEAUTH\n","RtmpIoctl_rt_ioctl_siwmlme");
    }
    local_58 = "RtmpIoctl_rt_ioctl_siwmlme";
    local_54 = 0x1e80;
    __cntl_disconnect_request(piVar4,0,param_1 + iVar3 * 0x84dec + 0x15ffe0,param_3);
    if ((*(uint *)(((uint)&local_58 & 0xffffe000) + 4) & 0x1fff00) == 0) {
      __init_waitqueue_head(auStack_48,"&_wait",sta_cntl_api_ops);
      iVar2 = 100;
      do {
        local_3c[0] = 0;
        local_30 = &local_30;
        local_2c = &local_30;
        for (iVar5 = 1; iVar1 = prepare_to_wait_event(auStack_48,local_3c,1),
            iVar5 != 0 && iVar1 == 0; iVar5 = schedule_timeout(iVar5)) {
        }
        finish_wait(auStack_48,local_3c);
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    else {
      RtmpusecDelay(1000000);
    }
    if ((param_1[iVar3 * 0x84dec + 0x15ffef] & 1U) != 0) {
      LinkDown(param_1,0,piVar4,0);
      param_1[iVar3 * 0x84dec + 0xdb9cd] = 0;
    }
  }
  else {
    if (param_4 != 2) goto LAB_000632dc;
    if (2 < DebugLevel) {
      printk("====> %s - IW_MLME_DISASSOC\n","RtmpIoctl_rt_ioctl_siwmlme");
    }
    iVar2 = iVar3 * 0x2137b0;
    __memzero((int)param_1 + iVar2 + 0x580d69,0x20);
    __memzero((int)param_1 + iVar2 + 0x580d61,6);
    *(undefined1 *)(param_1 + iVar3 * 0x84dec + 0x16035a) = 0;
    *(undefined1 *)((int)param_1 + iVar2 + 0x580d89) = 1;
    *(undefined1 *)((int)param_1 + iVar2 + 0x580d67) = 0;
    local_58 = "RtmpIoctl_rt_ioctl_siwmlme";
    local_54 = 0x1e95;
    __cntl_disconnect_request
              (piVar4,1,(undefined *)((int)param_1 + (int)(&DAT_0057ff80 + iVar2)),param_3);
  }
  if (local_4c == 0) {
    return 0;
  }
LAB_000632dc:
  os_free_mem();
  return 0;
}


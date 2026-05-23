// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwap @ 0x622f0
// size: 208 bytes
//

undefined4
RtmpIoctl_rt_ioctl_siwap(int *param_1,void *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*param_1 + 0x3c);
  *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0x15fe68) = 0;
  *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0xdc72e) = 0x20;
  iVar1 = memcmp(param_2,&ZERO_MAC_ADDR,6);
  if (iVar1 != 0) {
    cntl_connect_request
              ((undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar2 * 0x2137b0)),1,6,param_2,
               param_4);
    return 0;
  }
  if ((param_1[iVar2 * 0x84dec + 0x15ffef] & 1U) == 0) {
    return 0;
  }
  LinkDown(param_1,0,(undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar2 * 0x2137b0)),0);
  return 0;
}


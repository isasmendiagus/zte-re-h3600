// module: mt7915.ko
// function: rt_ioctl_giwmode @ 0x6d688
// size: 328 bytes
//

undefined4 rt_ioctl_giwmode(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_1c [2];
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    iVar2 = RTMP_COM_IoctlHandle(iVar1,0,0x5011,0,0,0);
    if (iVar2 == 0) {
      iVar2 = DetermineCallerInterface(param_1,iVar1);
      if (iVar2 != 0) {
        return 0xfffffff2;
      }
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(iVar1,0,0xa00a,0,local_1c,0,uVar3);
      if ((local_1c[0] == 1) || (local_1c[0] == 2)) {
        *param_3 = local_1c[0];
      }
      else if (local_1c[0] == 3) {
        *param_3 = 6;
        iVar1 = get_sniffer_mode(param_1);
        if (iVar1 == 0) {
          *(undefined2 *)(param_1 + 0x150) = 0x323;
        }
        iVar1 = get_sniffer_mode(param_1);
        if (iVar1 == 1) {
          *(undefined2 *)(param_1 + 0x150) = 0x322;
        }
      }
      else {
        *param_3 = 0;
      }
      if (DebugLevel < 3) {
        return 0;
      }
      printk("==>rt_ioctl_giwmode(mode=%d)\n",*param_3);
      return 0;
    }
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return 0xffffff9c;
    }
  }
  return 0xffffff9c;
}


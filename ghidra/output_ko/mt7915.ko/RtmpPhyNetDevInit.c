// module: mt7915.ko
// function: RtmpPhyNetDevInit @ 0x2464e4
// size: 428 bytes
//

int RtmpPhyNetDevInit(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int local_24;
  undefined4 local_20;
  undefined1 auStack_1c [8];
  
  local_24 = 0;
  RTMP_COM_IoctlHandle(param_1,0,0x503f,0,&local_20,0);
  RTMP_COM_IoctlHandle(param_1,0,0x503e,0,&local_24,0);
  iVar1 = local_24;
  if (local_24 == 0) {
    local_24 = iVar1;
    if (-1 < DebugLevel) {
      printk("%s(): main physical net device creation failed!\n","RtmpPhyNetDevInit");
      local_24 = iVar1;
    }
  }
  else {
    os_zero_mem(param_2,0x40);
    *(undefined1 *)((int)param_2 + 0x3e) = 0;
    *param_2 = main_virtual_if_open;
    param_2[1] = main_virtual_if_close;
    param_2[2] = rt28xx_send_packets;
    param_2[3] = rt28xx_ioctl;
    param_2[4] = RT28xx_get_ether_stats;
    param_2[9] = local_20;
    RTMP_COM_IoctlHandle(param_1,0,0x5002,0,auStack_1c,0);
    RtmpOsSetNetDevPriv(local_24,param_1);
    iVar1 = RtmpOsGetNetDevPriv(local_24);
    if (iVar1 == 0) {
      RtmpOSNetDevFree(local_24);
      local_24 = 0;
    }
    else {
      RTMP_COM_IoctlHandle(param_1,0,0x5001,0,local_24,0);
      iVar1 = dev_get_by_name(&init_net,&_LC14);
      if (iVar1 != 0) {
        br0Addr._0_4_ = **(undefined4 **)(iVar1 + 0x1dc);
        br0Addr._4_2_ = *(undefined2 *)(*(undefined4 **)(iVar1 + 0x1dc) + 1);
        disableIRQinterrupts();
        iVar2 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
        *(int *)(iVar2 + *(int *)(iVar1 + 0x280)) = *(int *)(iVar2 + *(int *)(iVar1 + 0x280)) + -1;
      }
    }
  }
  return local_24;
}


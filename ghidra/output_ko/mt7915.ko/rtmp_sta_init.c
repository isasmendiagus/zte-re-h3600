// module: mt7915.ko
// function: rtmp_sta_init @ 0x68900
// size: 172 bytes
//

void rtmp_sta_init(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 != 0) {
    STAInitialize(param_1,param_2);
    memmove((void *)(iVar1 + 0x1b),(void *)(param_1 + 0x794b5b),6);
    RtmpOSNetDevAddrSet(*(undefined1 *)(param_1 + 0x286285),*(undefined4 *)(param_1 + 4),
                        (void *)(iVar1 + 0x1b),iVar1 + 0x2123f4);
    BuildChannelList(param_1,param_2);
    RTMPSetPhyMode(param_1,iVar1,*(undefined2 *)(iVar1 + 0x18));
    sta_os_completion_initialize(iVar1);
    MATEngineInit(param_1);
    return;
  }
  printk(&_LC9,0x83);
  dump_stack();
  return;
}


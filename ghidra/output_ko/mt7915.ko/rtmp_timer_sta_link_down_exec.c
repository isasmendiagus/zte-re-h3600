// module: mt7915.ko
// function: rtmp_timer_sta_link_down_exec @ 0x80084
// size: 228 bytes
//

void rtmp_timer_sta_link_down_exec(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x24);
  iVar2 = *(int *)(iVar3 + 8);
  iVar1 = GetStaCfgByWdev(iVar2,iVar3);
  if (((iVar2 != 0) && (*(char *)(iVar1 + 0x888) == '\x02')) &&
     ((*(uint *)(iVar1 + 0x212464) & 1) != 0)) {
    if (2 < DebugLevel) {
      printk("LinkDownExec(): disassociate with current AP...\n");
    }
    __cntl_disconnect_request(iVar3,1,iVar1 + 0x212428,8,"sta_link_down_exec",0xdd);
    RTMP_IndicateMediaState(iVar2,0);
    *(undefined4 *)(iVar2 + 0xa39fa4) = 1;
  }
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}


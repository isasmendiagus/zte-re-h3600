// module: mt7915.ko
// function: net_ad_init_thread @ 0x25ad14
// size: 280 bytes
//

int net_ad_init_thread(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  if (param_3 == 0) {
    DAT_005f6404 = 1;
    DAT_005f6418 = RTMPMsecsToJiffies(3000);
    DAT_005f6408 = param_3;
    __init_waitqueue_head(&DAT_005f640c,"&x->wait",&DAT_005f641c);
    if (_LANCHOR2 == '\0') {
      iVar1 = sys_ad_init_os_task(&DAT_005f63cc,"serv_thread_tx",param_1,param_2);
      if (iVar1 != 0) {
LAB_0025ae08:
        printk("%s: tx thread init fail err=0x%08x\n","net_ad_init_thread",iVar1);
        return iVar1;
      }
      DAT_005f63fc = param_3;
      iVar1 = sys_ad_attach_os_task(&DAT_005f63cc,net_ad_thread,&DAT_005f63cc);
      iVar2 = wait_for_completion_timeout(&DAT_005f6408,DAT_005f6418);
      if (iVar2 == 0 || iVar1 != 0) goto LAB_0025ae08;
      _LANCHOR2 = '\x01';
    }
    DAT_005f6400 = 0;
  }
  printk("%s: initialize thread_idx=%d\n","net_ad_init_thread",param_3);
  return 0;
}


// module: mt7915.ko
// function: PMF_SAQueryTimeOut @ 0x219b44
// size: 284 bytes
//

void PMF_SAQueryTimeOut(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_11 [5];
  
  if (param_2 == (int *)0x0) {
    return;
  }
  iVar2 = param_2[3];
  if (-1 < DebugLevel) {
    printk("[PMF]%s - STA(%02x:%02x:%02x:%02x:%02x:%02x)\n","PMF_SAQueryTimeOut",(char)param_2[0x3b]
           ,*(undefined1 *)((int)param_2 + 0xed),*(undefined1 *)((int)param_2 + 0xee),
           *(undefined1 *)((int)param_2 + 0xef),(char)param_2[0x3c],
           *(undefined1 *)((int)param_2 + 0xf1));
  }
  if (*param_2 == 2) {
    iVar2 = GetStaCfgByWdev(iVar2,param_2[2]);
    RTMPCancelTimer(param_2 + 0x170,auStack_11);
    RTMPCancelTimer(param_2 + 0x17d,auStack_11);
    __cntl_disconnect_request(param_2[2],1,iVar2 + 0x212428,8,"PMF_SAQueryTimeOut",0x13a);
  }
  else if (((*param_2 == 0x40001) && (iVar1 = param_2[0x2bf], iVar1 != 0)) &&
          (*(char *)(iVar1 + 5) == '\x02')) {
    RepeaterDisconnectRootAP(iVar2,iVar1,6);
  }
  else {
    mac_entry_delete(iVar2,param_2);
  }
  return;
}


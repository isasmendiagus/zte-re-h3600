// module: mt7915.ko
// function: MacTableResetWdev @ 0x14a018
// size: 704 bytes
//

void MacTableResetWdev(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined1 uStack_4b;
  undefined2 local_4a;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 auStack_40 [28];
  
  local_48 = 0;
  local_44 = 0;
  if (2 < DebugLevel) {
    printk("MacTableResetWdev\n");
  }
  iVar4 = param_1 + 0xa1d20;
  iVar2 = param_1 + 0xa1e0c;
  uVar3 = 0;
  do {
    iVar1 = HcGetMaxStaNum(param_1);
    if (iVar1 <= (int)uVar3) {
      if ((*(char *)(param_1 + 0x286285) == '\x01') && (*(int *)(param_2 + 0x14) == 1)) {
        param_1 = param_1 + (uint)*(byte *)(param_2 + 0xe) * 0x5834;
        RTMPCancelTimer("IF(ra0) Set_WscConfMode_Proc::(WscConfMode(0,1,2)=%d)\n" + param_1 + 0x10,
                        &uStack_4b);
        "IF(ra0) Set_WscConfMode_Proc::(WscConfMode(0,1,2)=%d)\n"[param_1 + 0xc] = '\0';
        __memzero("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n" +
                  param_1 + 0x31,6);
        "%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
        [param_1 + 0x2e] = '\0';
        "pStaCfg->WpaPassPhrase"[param_1 + 0xb] = '\0';
      }
      return;
    }
    if (*(int *)(iVar2 + -0xe4) == param_2) {
      if (((*(int *)(iVar2 + -0xec) == 0x20001) &&
          (*(undefined1 *)(iVar2 + 0x8f) = 0, *(char *)(param_1 + 0x286285) == '\x01')) &&
         (*(int *)(iVar2 + 0x10) == 2)) {
        iVar1 = os_alloc_mem(param_1,&local_48,0x900);
        if (iVar1 != 0) {
          if (DebugLevel < 3) {
            return;
          }
          printk(" MlmeAllocateMemory fail  ..\n");
          return;
        }
        local_4a = 2;
        if (1 < DebugLevel) {
          printk("Send DeAuth (Reason=%d) to %02x:%02x:%02x:%02x:%02x:%02x\n",2,
                 *(undefined1 *)(iVar4 + 0xec),*(undefined1 *)(iVar2 + 1),*(undefined1 *)(iVar2 + 2)
                 ,*(undefined1 *)(iVar2 + 3),*(undefined1 *)(iVar2 + 4),*(undefined1 *)(iVar2 + 5));
        }
        MgtMacHeaderInit(param_1,auStack_40,0xc,0,iVar2,param_2 + 0x1b,param_2 + 0x21);
        MakeOutgoingFrame(local_48,&local_44,0x18,auStack_40,2,&local_4a,0xffffffff);
        MiniportMMRequest(param_1,0,local_48,local_44);
        os_free_mem(local_48);
        RtmpusecDelay(5000);
        ZTE_Notify_Node_AD(0,iVar4);
        __ZTE_STA_Assoc_Process(param_1,0x11,0,0,local_4a,0,iVar4,"MacTableResetWdev",0x7e3);
        wlan_dbg_save_staoffline_record(iVar4,local_4a,0x7e5,"MacTableResetWdev");
      }
      MacTableDeleteEntry(param_1,uVar3 & 0xffff,iVar2);
    }
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + 0x14c0;
    iVar4 = iVar4 + 0x14c0;
  } while( true );
}


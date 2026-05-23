// module: mt7915.ko
// function: SendSMPSAction @ 0xa4124
// size: 428 bytes
//

void SendSMPSAction(int param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 auStack_33 [24];
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_3c = 0;
  iVar1 = os_alloc_mem(param_1,&local_3c,0x900);
  if (iVar1 == 0) {
    uVar2 = HcGetMaxStaNum(param_1);
    if (param_2 < uVar2) {
      iVar1 = *(int *)(param_1 + param_2 * 0x14c0 + 0xa1d28);
      if (iVar1 == 0) {
        os_free_mem(local_3c);
        if (-1 < DebugLevel) {
          printk("BA - wdev is null\n");
        }
      }
      else {
        ActHeaderInit(param_1,auStack_33,param_1 + param_2 * 0x14c0 + 0xa1e0c,iVar1 + 0x1b,
                      iVar1 + 0x21);
        local_1b = 7;
        local_1a = 1;
        if (param_3 == 1) {
          local_19 = 3;
        }
        else if (param_3 == 0) {
          local_19 = 1;
        }
        else if (param_3 == 3) {
          local_19 = 0;
        }
        MakeOutgoingFrame(local_3c,&local_38,0x1b,auStack_33,0xffffffff);
        MiniportMMRequest(param_1,1,local_3c,local_38);
        os_free_mem(local_3c);
        if (-1 < DebugLevel) {
          printk("HT - %s( %d )\n","SendSMPSAction",local_19);
        }
      }
    }
    else {
      os_free_mem(local_3c);
      if (-1 < DebugLevel) {
        printk("BA - Invalid WCID(%d)\n",param_2);
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("BA - MlmeADDBAAction() allocate memory failed\n");
  }
  return;
}


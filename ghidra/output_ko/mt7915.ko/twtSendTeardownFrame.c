// module: mt7915.ko
// function: twtSendTeardownFrame @ 0x168d64
// size: 492 bytes
//

undefined4 twtSendTeardownFrame(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 auStack_33 [24];
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_3c = 0;
  local_38 = 0;
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: wdev=NULL, please check\n","twtSendTeardownFrame");
    }
  }
  else {
    iVar2 = (uint)*(byte *)(param_2 + 0xe) * 0x2137b0;
    if (&DAT_0036db58 + param_1 + iVar2 == (undefined *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: apcli_entry=NULL, please check\n","twtSendTeardownFrame");
        return 1;
      }
    }
    else {
      iVar2 = *(int *)(&DAT_0057ffc4 + param_1 + iVar2);
      if (iVar2 == 0) {
        if (-1 < DebugLevel) {
          printk("%s: pEntry=NULL, please check\n","twtSendTeardownFrame");
          return 1;
        }
      }
      else {
        iVar1 = os_alloc_mem(param_1,&local_3c,0x900);
        if (iVar1 == 0) {
          os_zero_mem(auStack_33,0x1b);
          ActHeaderInit(param_1,auStack_33,iVar2 + 0xec,param_2 + 0x1b,param_2 + 0x21);
          local_1a = 7;
          local_19 = (undefined1)param_3;
          local_1b = 0x16;
          MakeOutgoingFrame(local_3c,&local_38,0x1b,auStack_33,0xffffffff);
          MiniportMMRequest(param_1,WMM_UP2AC_MAP._3_1_ | 0x80,local_3c,local_38);
          os_free_mem(local_3c);
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: wcid(%d), flow_id(%d)\n","twtSendTeardownFrame",*(undefined2 *)(iVar2 + 0xe0),
                 param_3);
          return 0;
        }
        if (-1 < DebugLevel) {
          printk("%s: allocate memory failed, please check\n","twtSendTeardownFrame");
          return 1;
        }
      }
    }
  }
  return 1;
}


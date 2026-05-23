// module: mt7915.ko
// function: twtSendSetupFrame @ 0x168b10
// size: 592 bytes
//

undefined4 twtSendSetupFrame(int param_1,int param_2,ushort param_3,byte *param_4)

{
  int iVar1;
  int iVar2;
  undefined4 local_54;
  undefined4 local_50;
  undefined1 auStack_4c [24];
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_31;
  undefined1 local_30;
  ushort local_2e;
  undefined4 local_2c;
  undefined4 local_28;
  byte local_24;
  undefined2 local_23;
  
  local_54 = 0;
  local_50 = 0;
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: wdev=NULL, please check\n","twtSendSetupFrame");
    }
  }
  else {
    iVar2 = (uint)*(byte *)(param_2 + 0xe) * 0x2137b0;
    if (&DAT_0036db58 + param_1 + iVar2 == (undefined *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: apcli_entry=NULL, please check\n","twtSendSetupFrame");
      }
    }
    else {
      iVar2 = *(int *)(&DAT_0057ffc4 + param_1 + iVar2);
      if (iVar2 == 0) {
        if (-1 < DebugLevel) {
          printk("%s: pEntry=NULL, please check\n","twtSendSetupFrame");
        }
      }
      else {
        iVar1 = os_alloc_mem(param_1,&local_54,0x900);
        if (iVar1 == 0) {
          os_zero_mem(auStack_4c,0x2c);
          ActHeaderInit(param_1,auStack_4c,iVar2 + 0xec,param_2 + 0x1b,param_2 + 0x21);
          local_2c = *(undefined4 *)(param_4 + 0x10);
          local_28 = *(undefined4 *)(param_4 + 0x14);
          local_23 = *(undefined2 *)(param_4 + 8);
          local_24 = param_4[5];
          local_2e = *param_4 & 1 | local_2e | 0x20 | (ushort)param_4[2] << 0xf |
                     (param_4[4] & 7) << 1 | (param_4[1] & 1) << 4 | (param_4[3] & 1) << 6 |
                     (param_4[6] & 0x1f) << 10 | (param_3 & 7) << 7;
          local_30 = 0xf;
          local_31 = 0xd8;
          local_34 = 0x16;
          local_33 = 6;
          MakeOutgoingFrame(local_54,&local_50,0x2c,auStack_4c,0xffffffff);
          MiniportMMRequest(param_1,1,local_54,local_50);
          os_free_mem(local_54);
          return 0;
        }
        if (-1 < DebugLevel) {
          printk("%s: allocate memory failed, please check\n","twtSendSetupFrame");
        }
      }
    }
  }
  return 1;
}


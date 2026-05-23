// module: mt7915.ko
// function: mlme_twt_teradown_action @ 0x167738
// size: 296 bytes
//

void mlme_twt_teradown_action(undefined4 param_1,int *param_2)

{
  int iVar1;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 auStack_2b [24];
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  local_34 = 0;
  local_30 = 0;
  iVar1 = os_alloc_mem(param_1,&local_34,0x900);
  if (iVar1 == 0) {
    iVar1 = *param_2;
    FUN_00167230(iVar1,(short)param_2[1],(char)param_2[3]);
    os_zero_mem(auStack_2b,0x1b);
    ActHeaderInit(param_1,auStack_2b,(int)param_2 + 6,iVar1 + 0x1b,iVar1 + 0x21);
    local_11 = (undefined1)param_2[3];
    local_13 = 0x16;
    local_12 = 7;
    MakeOutgoingFrame(local_34,&local_30,0x1b,auStack_2b,0xffffffff);
    MiniportMMRequest(param_1,WMM_UP2AC_MAP._3_1_ | 0x80,local_34,local_30);
    os_free_mem(local_34);
    if (2 < DebugLevel) {
      printk("%s: wcid(%d), flow_id(%d)\n","mlme_twt_teradown_action",(short)param_2[1],
             (char)param_2[3]);
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: allocate memory failed, please check\n","mlme_twt_teradown_action");
  }
  return;
}


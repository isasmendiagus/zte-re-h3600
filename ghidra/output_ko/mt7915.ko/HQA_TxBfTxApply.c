// module: mt7915.ko
// function: HQA_TxBfTxApply @ 0x278a38
// size: 392 bytes
//

undefined4 HQA_TxBfTxApply(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  undefined4 local_2c;
  char *local_28;
  int local_24;
  
  local_24 = param_3 + 0xc;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  os_alloc_mem(param_1,&local_28,0x200);
  if (local_28 == (char *)0x0) {
    uVar2 = 3;
  }
  else {
    FUN_00276034(1,4,&local_24,&local_38);
    FUN_00276034(1,4,&local_24,&local_34);
    FUN_00276034(1,4,&local_24,&local_30);
    FUN_00276034(1,4,&local_24,&local_2c);
    iVar1 = net_ad_wrap_service(param_1);
    *(char *)(local_30 * 0xd18 + iVar1 + 0x11cd) = (char)local_38;
    iVar1 = net_ad_wrap_service(param_1);
    *(char *)(local_30 * 0xd18 + iVar1 + 0x11cc) = (char)local_34;
    sprintf(local_28,"%02x:%02x:%02x:%02x:%02x",local_30,local_38,local_34,local_2c,1);
    if (0 < DebugLevel) {
      printk("%s: wlan_id:%x, eBF enable:%x, iBF enable:%x, MuTx:%x\n","HQA_TxBfTxApply",local_30,
             local_38,local_34,local_2c);
    }
    Set_TxBfTxApply(param_1,local_28);
    if (local_28 == (char *)0x0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0;
      os_free_mem();
    }
  }
  FUN_0026cdd0(param_3,param_2,2,uVar2);
  return uVar2;
}


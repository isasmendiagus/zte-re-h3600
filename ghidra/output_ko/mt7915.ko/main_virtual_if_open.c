// module: mt7915.ko
// function: main_virtual_if_open @ 0x245e60
// size: 352 bytes
//

undefined4 main_virtual_if_open(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  code *local_34;
  code *local_30;
  code *local_2c;
  code *local_28;
  int local_24;
  
  if (0 < DebugLevel) {
    printk("%s: ===> %s\n",param_1,"main_virtual_if_open");
  }
  iVar1 = RtmpOsGetNetDevPriv(param_1);
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    local_34 = virtual_if_init_handler;
    local_30 = virtual_if_deinit_handler;
    local_2c = virtual_if_up_handler;
    local_28 = virtual_if_down_handler;
    local_24 = param_1;
    iVar2 = RTMP_COM_IoctlHandle(iVar1,0,0x5038,0,&local_34,0);
    if (iVar2 == 0) {
      local_28 = virtual_if_down_handler;
      local_34 = virtual_if_init_handler;
      local_30 = virtual_if_deinit_handler;
      local_2c = virtual_if_up_handler;
      local_24 = param_1;
      iVar2 = RTMP_COM_IoctlHandle(iVar1,0,0x5036,0,&local_34,0);
      if (iVar2 == 0) {
        iVar2 = try_module_get(__this_module);
        if (iVar2 != 0) {
          _clear_bit(0,*(int *)(param_1 + 0x240) + 0x50);
          netif_carrier_on(param_1);
          netif_tx_wake_queue(*(undefined4 *)(param_1 + 0x240));
          ZTE_Bss_Report_Info_Active(iVar1,0,1);
          return 0;
        }
        if (-1 < DebugLevel) {
          printk("%s: cannot reserve module\n","main_virtual_if_open");
          return 0xffffffff;
        }
      }
    }
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


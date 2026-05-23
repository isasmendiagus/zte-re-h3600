// module: mt7915.ko
// function: main_virtual_if_close @ 0x245c3c
// size: 316 bytes
//

undefined4 main_virtual_if_close(int param_1)

{
  int iVar1;
  code *local_3c;
  code *local_38;
  code *local_34;
  code *local_30;
  int local_2c;
  
  if (0 < DebugLevel) {
    printk("%s: ===> %s\n",param_1,"main_virtual_if_close");
  }
  iVar1 = RtmpOsGetNetDevPriv(param_1);
  if (iVar1 != 0) {
    netif_carrier_off(param_1);
    if (*(int *)(param_1 + 0x240) == 0) {
      warn_slowpath_null("include/linux/netdevice.h",0xa06);
      printk(&_LC2);
    }
    else {
      _set_bit(0,*(int *)(param_1 + 0x240) + 0x50);
    }
    local_3c = virtual_if_init_handler;
    local_38 = virtual_if_deinit_handler;
    local_34 = virtual_if_up_handler;
    local_30 = virtual_if_down_handler;
    local_2c = param_1;
    RTMP_COM_IoctlHandle(iVar1,0,0x5037,0,&local_3c,0);
    local_3c = virtual_if_init_handler;
    local_38 = virtual_if_deinit_handler;
    local_34 = virtual_if_up_handler;
    local_30 = virtual_if_down_handler;
    local_2c = param_1;
    RTMP_COM_IoctlHandle(iVar1,0,0x5039,0,&local_3c,0);
    module_put(__this_module);
    ZTE_Bss_Report_Info_Active(iVar1,0,0);
  }
  return 0;
}


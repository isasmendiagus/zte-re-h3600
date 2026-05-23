// module: mt7915.ko
// function: msta_virtual_if_open @ 0x6716c
// size: 324 bytes
//

undefined4 msta_virtual_if_open(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  code *local_3c;
  code *local_38;
  code *local_34;
  code *local_30;
  int local_2c;
  
  if (0 < DebugLevel) {
    printk("%s: ===> %s\n",param_1,"msta_virtual_if_open");
  }
  uVar1 = RtmpOsGetNetDevPriv(param_1);
  local_3c = virtual_if_init_handler;
  local_38 = virtual_if_deinit_handler;
  local_34 = virtual_if_up_handler;
  local_30 = virtual_if_down_handler;
  local_2c = param_1;
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5038,0,&local_3c,0);
  if (iVar2 == 0) {
    local_30 = virtual_if_down_handler;
    local_3c = virtual_if_init_handler;
    local_38 = virtual_if_deinit_handler;
    local_34 = virtual_if_up_handler;
    local_2c = param_1;
    iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5036,0,&local_3c,0);
    if (iVar2 == 0) {
      iVar2 = try_module_get(__this_module);
      if (iVar2 != 0) {
        _clear_bit(0,*(int *)(param_1 + 0x240) + 0x50);
        netif_carrier_off(param_1);
        return 0;
      }
      if (-1 < DebugLevel) {
        printk("%s: cannot reserve module\n","msta_virtual_if_open");
      }
    }
  }
  return 0xffffffff;
}


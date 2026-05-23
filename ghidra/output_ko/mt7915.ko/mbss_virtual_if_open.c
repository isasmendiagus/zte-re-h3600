// module: mt7915.ko
// function: mbss_virtual_if_open @ 0x52628
// size: 352 bytes
//

undefined4 mbss_virtual_if_open(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  code *local_3c;
  code *local_38;
  code *local_34;
  code *local_30;
  int local_2c;
  
  if (0 < DebugLevel) {
    printk("%s: ===> %s\n",param_1,"mbss_virtual_if_open");
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
        uVar3 = RT28xx_MBSS_IdxGet(uVar1,param_1);
        if ((int)uVar3 < 0) {
          return 0;
        }
        ZTE_Bss_Report_Info_Active(uVar1,uVar3 & 0xff,1);
        return 0;
      }
      if (-1 < DebugLevel) {
        printk("%s: cannot reserve module\n","mbss_virtual_if_open");
        return 0xffffffff;
      }
    }
  }
  return 0xffffffff;
}


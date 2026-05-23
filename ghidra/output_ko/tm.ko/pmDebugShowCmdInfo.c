// module: tm.ko
// function: pmDebugShowCmdInfo @ 0x6bd84
// size: 224 bytes
//

int pmDebugShowCmdInfo(undefined4 param_1)

{
  int iVar1;
  undefined2 local_80;
  byte local_7e;
  byte local_7d;
  undefined4 auStack_7c [29];
  
  memcpy(auStack_7c,&_LANCHOR0,0x74);
  iVar1 = pp_pm_get_cmd_ram_info(param_1,&local_80);
  if (iVar1 == 0) {
    printk("\nget cmd ram info:\n");
    printk("modify_data             :0x%x\n",local_80);
    printk("cmd(%s)                 :0x%x\n",auStack_7c[local_7e & 0x1f]);
    printk("ip_checksum_up          :0x%x\n",((uint)local_7e << 0x1a) >> 0x1f);
    printk("tcp_checksum_up         :0x%x\n",((uint)local_7e << 0x19) >> 0x1f);
    printk("last_cmd                :0x%x\n",local_7e >> 7);
    printk("dat_type                :0x%x\n",local_7d & 3);
  }
  else {
    printk("pp_pm_get_cmd_ram_info fail, error code %d!\n",iVar1);
  }
  return iVar1;
}


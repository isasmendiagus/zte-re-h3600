// module: mt7915.ko
// function: mt_service_close @ 0x13d38c
// size: 176 bytes
//

undefined4 mt_service_close(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 0xa77bb8);
  iVar1 = mt_agent_exit_service(param_1 + 0xa77bb4);
  if (iVar1 == 0) {
    os_free_mem(puVar2[0x7c4]);
    os_free_mem(*puVar2);
    os_free_mem(puVar2);
    if (DebugLevel < 1) {
      return 0;
    }
    printk("%s: wlan service closes successfully!\n","mt_service_close");
    return 0;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s: wlan service exits failed!\n","mt_service_close");
  return 1;
}


// module: tm.ko
// function: greg_set_wifi_queue1_protocol @ 0x331b0
// size: 136 bytes
//

undefined4 greg_set_wifi_queue1_protocol(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 1) {
    return 0;
  }
  iVar1 = tmOnuRegWrite(0x46,0,0,&gregRegTable);
  iVar2 = tmOnuRegWrite(0x47,0,0,&gregRegTable);
  if (iVar2 != 0 || iVar1 != 0) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("greg_set_wifi_queue1_protocol] GREG_WRITE_REG( failed,ret= %d!\n");
    return 0xffffffff;
  }
  return 0;
}


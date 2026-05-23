// module: mt7915.ko
// function: set_fwlog_serverip @ 0x1d4dbc
// size: 168 bytes
//

undefined4 set_fwlog_serverip(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_94;
  char acStack_90 [128];
  
  memset(acStack_90,0,0x80);
  strncpy(acStack_90,param_2,0x7f);
  if (0 < DebugLevel) {
    printk("ip=[%s]\n",acStack_90);
  }
  iVar2 = rtinet_aton(acStack_90,&local_94);
  iVar1 = DebugLevel;
  if (iVar2 != 0) {
    *(undefined4 *)(param_1 + 0xa7cc28) = local_94;
    if (0 < iVar1) {
      printk("fw_log_server_ip=%s(%x)\n",param_2);
    }
  }
  return 1;
}


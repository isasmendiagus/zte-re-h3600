// module: idmfdb.ko
// function: idm_netdev_event @ 0x1080c
// size: 68 bytes
//

undefined4 idm_netdev_event(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = IfName2WlanIdmMap(*param_3);
  if (((iVar1 != 0) && (param_2 - 1U < 2)) && (*(char *)(iVar1 + 0x25) == '\0')) {
    idm_fdb_idm_isolate_handle();
    return 0;
  }
  return 0;
}


// module: mt7915.ko
// function: ap_conn_act @ 0x16cd4
// size: 336 bytes
//

undefined4 ap_conn_act(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  if (param_2 != 0 && param_1 != 0) {
    iVar3 = *(int *)(param_1 + 8);
    iVar1 = wifi_sys_conn_act();
    if ((iVar1 != 1) && (-1 < DebugLevel)) {
      printk("%s(): connect action fail!\n","ap_conn_act");
    }
    if (*(int *)(param_2 + 4) == 1) {
      if (2 < DebugLevel) {
        printk("**[%s] calling RTMP_OS_COMPLETE(WtblSetDone)\n","ap_conn_act");
      }
      *(undefined1 *)(param_2 + 0x1466) = 1;
      complete(param_2 + 0x1468);
    }
    uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + iVar3 + 0xc) & 0xffff;
    if (uVar2 == 0x7915 ||
        (uVar2 == 0x6867 ||
        (uVar2 == 0x7663 ||
        (uVar2 == 0x6632 ||
        ((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar3 + 0xc) & 0xfffb) == 0x7622 ||
        (uVar2 == 0x7615 || uVar2 == 0x7637)))))) {
      RAInit(iVar3,param_2);
    }
    ap_set_wireless_sta_configs(iVar3,param_2);
    ap_set_wireless_bss_configs(iVar3,*(undefined4 *)(param_2 + 8));
    return 1;
  }
  return 0;
}


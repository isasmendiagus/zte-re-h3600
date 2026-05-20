// module: mt7915.ko
// function: mt_ate_tx_unsubscribe @ 0x280148
// size: 240 bytes
//

undefined4
mt_ate_tx_unsubscribe(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = net_ad_wrap_service();
  iVar1 = (uint)*(byte *)(iVar1 + 0x4cc) * 0xd18 + 0x6f0;
  while( true ) {
    iVar2 = net_ad_wrap_service(param_1);
    if (*(char *)(iVar2 + iVar1 + 5) == '\0') break;
    iVar2 = net_ad_wrap_service(param_1);
    iVar2 = iVar2 + iVar1;
    iVar4 = iVar2 + 4;
    uVar3 = (uint)*(byte *)(iVar2 + 5);
    if (uVar3 == 0) {
      if (-1 < DebugLevel) {
        printk("(%s)Stack for MAC_TABL_ENRTY is empty!\n","mt_ate_pop_mac_tbl_entry");
      }
    }
    else {
      iVar6 = iVar4 + uVar3 * 4;
      iVar5 = *(int *)(iVar6 + 100);
      *(undefined4 *)(iVar6 + 100) = 0;
      *(undefined4 *)(iVar6 + 0xa4) = 0;
      *(char *)(iVar2 + 5) = (char)(uVar3 - 1);
      if (iVar5 != 0) {
        MacTableDeleteEntry(param_1,*(undefined2 *)(iVar5 + 0xe0),iVar4 + (uVar3 - 1) * 6 + 6,iVar4,
                            param_4);
      }
    }
  }
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) != 0x7915) {
    return 0;
  }
  wifi_test_muru_set_arb_op_mode(param_1,1);
  return 0;
}


// module: mt7915.ko
// function: ChannelSwitchAction @ 0xa249c
// size: 372 bytes
//

void ChannelSwitchAction(int param_1,int param_2,int param_3,uint param_4)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 uStack_21;
  char local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  
  if (2 < DebugLevel) {
    printk("%s(): NewChannel=%d, Secondary=%d\n","ChannelSwitchAction");
  }
  iVar2 = ChannelSwitchSanityCheck(param_1,param_2,param_3,param_4);
  if (iVar2 != 0) {
    param_1 = param_2 * 0x14c0 + param_1;
    iVar2 = *(int *)(param_1 + 0xa1d28);
    os_zero_mem(&uStack_21,9);
    if (iVar2 != 0) {
      local_1d = (undefined1)param_3;
      *(undefined1 *)(iVar2 + 0x1a) = local_1d;
      local_1e = (undefined1)param_4;
      local_20 = wlan_config_get_ht_bw(iVar2);
      local_1f = wlan_operate_get_vht_bw(iVar2);
      local_1c = wlan_operate_get_cen_ch_2(iVar2);
      if (param_4 == 0) {
        *(ushort *)(param_1 + 0xa1ddc) = *(ushort *)(param_1 + 0xa1ddc) & 0xfe7f;
        local_20 = '\0';
      }
      else if (((param_4 & 0xfd) == 1) && (local_20 == '\x01')) {
        *(ushort *)(param_1 + 0xa1ddc) = *(ushort *)(param_1 + 0xa1ddc) & 0xfe7f | 0x80;
      }
      if ((param_3 != 0) && (wlan_operate_set_phy(iVar2,&uStack_21), 2 < DebugLevel)) {
        iVar3 = wlan_operate_get_bw(iVar2);
        uVar1 = *(undefined1 *)(iVar2 + 0x1a);
        if (iVar3 == 1) {
          uVar5 = 0x28;
        }
        else {
          uVar5 = 0x14;
        }
        uVar4 = wlan_operate_get_cen_ch_1(iVar2);
        printk("%s(): %dMHz LINK UP, CtrlChannel=%d,  CentralChannel= %d\n","ChannelSwitchAction",
               uVar5,uVar1,uVar4);
      }
    }
  }
  return;
}


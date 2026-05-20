// module: switch.ko
// function: swport_dev_xmit_fin @ 0x107cc
// size: 356 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 swport_dev_xmit_fin(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_2 + 0x4c4);
  if (iVar3 == 0) {
    *(int *)(param_2 + 0x4e4) = *(int *)(param_2 + 0x4e4) + 1;
    __dev_kfree_skb_any();
    return 0xffffffff;
  }
  if ((g_pon_work_mode & 0x10) != 0) {
    if (wanLogicPort == 0xff) {
      if (wan_to_lan != 0) {
        uVar1 = (uint)*(byte *)(param_1 + 0xb4);
LAB_0001083c:
        if (_tm_vlan_check_ena_set == uVar1) {
          iVar3 = dev_get_by_name(&init_net,&_LC1,iVar3,_tm_vlan_check_ena_set,param_4);
          goto joined_r0x000108fc;
        }
      }
    }
    else if (wan_to_lan != 0) {
      uVar1 = (uint)*(byte *)(param_1 + 0xb4);
      if ((byte)zte_api_sw_mac_set_port_macfiltermode[wanLogicPort] != uVar1) goto LAB_0001083c;
      iVar3 = dev_get_by_name(&init_net,&_LC0,iVar3,
                              (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[wanLogicPort],
                              param_4);
joined_r0x000108fc:
      if (iVar3 == 0) {
        __dev_kfree_skb_any(param_1,1);
        return 0xffffffff;
      }
      *(int *)(param_1 + 0x18) = iVar3;
      disableIRQinterrupts();
      iVar2 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar2 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar2 + *(int *)(iVar3 + 0x280)) + -1;
      goto LAB_0001084c;
    }
  }
  *(int *)(param_1 + 0x18) = iVar3;
LAB_0001084c:
  *(int *)(param_2 + 0x4cc) = *(int *)(param_2 + 0x4cc) + 1;
  *(int *)(param_2 + 0x4d4) = *(int *)(param_2 + 0x4d4) + *(int *)(param_1 + 100);
  dev_queue_xmit_sk(*(undefined4 *)(param_1 + 0x14),param_1);
  return 0;
}


// module: switch.ko
// function: pdt_ethdriver_init @ 0x104b0
// size: 616 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
pdt_ethdriver_init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  code *pcVar8;
  undefined1 *puVar9;
  int iVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  
  set_mii_dev_name_type_part_0(0,&_LC26,param_3,param_4,param_4);
  set_mii_dev_name_type_part_0(1,&_LC27);
  if (_tm_port_unknwn_multicast_floodport_set != 0) {
    uVar6 = 0;
    puVar9 = g_sw_netInfo;
    pcVar8 = tm_set_p2pmode;
    iVar10 = 0;
    uVar7 = 1;
    do {
      uVar2 = (undefined1)uVar6;
      if (uVar6 < 8) {
        if ((byte)*pcVar8 == _zte_api_sw_mac_set_port_learnlimit) {
          iVar10 = dev_get_by_name(&init_net,0x2b90c);
          printk("port id %d, name %s\n",_zte_api_sw_mac_set_port_learnlimit,0x2b90c);
        }
        else {
          iVar10 = dev_get_by_name(&init_net,g_mii_dev_name);
        }
      }
      if (iVar10 == 0) {
        printk("mii_dev = NULL!@func %s %d\n","ethdrv_add_br_device",0xff);
        break;
      }
      if ((*(uint *)(iVar10 + 0x138) & 1) == 0) {
        rtnl_lock();
        dev_change_flags(iVar10,*(uint *)(iVar10 + 0x138) | 1);
        rtnl_unlock();
        msleep(1000);
      }
      disableIRQinterrupts();
      iVar3 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar3 + *(int *)(iVar10 + 0x280)) = *(int *)(iVar3 + *(int *)(iVar10 + 0x280)) + -1;
      uVar6 = uVar6 + 1;
      iVar3 = alloc_etherdev_mqs(100,1,1);
      pcVar8 = pcVar8 + 1;
      if (iVar3 == 0) {
        printk("kmalloc error!\n");
        break;
      }
      *(uint *)(iVar3 + 0x138) = *(uint *)(iVar10 + 0x138) & 0xfffffffe;
      *(undefined4 *)(iVar3 + 0x14c) = *(undefined4 *)(iVar10 + 0x14c);
      memcpy((void *)(iVar3 + 0x200),(void *)(iVar10 + 0x200),(uint)*(byte *)(iVar10 + 0x179));
      memcpy(*(void **)(iVar3 + 0x1dc),*(void **)(iVar10 + 0x1dc),(uint)*(byte *)(iVar10 + 0x179));
      uVar1 = *(undefined1 *)(iVar10 + 0x179);
      *(code **)(iVar3 + 0x298) = ethdrv_port_dev_destruct;
      *(undefined1 *)(iVar3 + 0x179) = uVar1;
      *(undefined1 **)(iVar3 + 300) = reg_eth_netdev_ops;
      __memzero(iVar3 + 0x4c0,100);
      *(undefined1 *)(iVar3 + 0x4c0) = uVar2;
      *(int *)(iVar3 + 0x4c4) = iVar10;
      iVar4 = register_netdev(iVar3);
      if (iVar4 != 0) {
        printk("Register_netdev %s failed..\n",iVar3);
        free_netdev(iVar3);
        break;
      }
      netif_carrier_off(iVar3);
      uVar5 = _tm_port_unknwn_multicast_floodport_set;
      bVar13 = 9 < (uVar7 & 0xff);
      bVar11 = (uVar7 & 0xff) == 10;
      if (!bVar11) {
        bVar13 = uVar7 <= _tm_port_unknwn_multicast_floodport_set;
      }
      bVar12 = _tm_port_unknwn_multicast_floodport_set == uVar7;
      puVar9 = (undefined1 *)((int)puVar9 + 4);
      *(int *)puVar9 = iVar3;
      uVar7 = uVar7 + 1;
      if (!bVar13 || (bVar11 || bVar12)) {
        uVar5 = 1;
      }
      if (bVar13 && (!bVar11 && !bVar12)) {
        uVar5 = 0;
      }
      g_sw_netInfo[0] = g_sw_netInfo[0] + '\x01';
    } while (uVar5 == 0);
  }
  switch_skb_recv = pdt_ethdrv_recv;
  iVar10 = sysfs_create_group(wake_up_process,&ethdrv_test_group);
  if (iVar10 != 0) {
    printk("sysfs group failed %d\n");
  }
  return 0;
}


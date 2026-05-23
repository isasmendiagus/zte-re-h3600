// module: plat-zxylzb_9128S.ko
// function: _dump_vlan_info @ 0x16658
// size: 100 bytes
//

void _dump_vlan_info(undefined4 param_1,uint param_2)

{
  undefined4 *puVar1;
  
  printk("vlan %u:",param_1);
  puVar1 = (undefined4 *)&port_name;
  do {
    if ((param_2 & 3) != 0) {
      printk(" %s(%u)",*puVar1);
    }
    puVar1 = puVar1 + 1;
    param_2 = param_2 >> 2;
  } while (puVar1 != (undefined4 *)&pon_tm_net_netdev_ops);
  printk(&_LC2);
  return;
}


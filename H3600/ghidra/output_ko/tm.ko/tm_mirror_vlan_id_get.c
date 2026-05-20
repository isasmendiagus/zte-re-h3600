// module: tm.ko
// function: tm_mirror_vlan_id_get @ 0x4ce00
// size: 88 bytes
//

undefined4
tm_mirror_vlan_id_get(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x3310,param_4,param_4);
    printk("param pp_vlanId is NULL\n");
    return 0xffffffff;
  }
  iVar1 = sbrg_get_mirror_vlid();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_mirror_vlan_id_get fail\n");
  return 0xffffffff;
}


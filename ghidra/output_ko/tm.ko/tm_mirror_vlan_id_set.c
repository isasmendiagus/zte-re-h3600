// module: tm.ko
// function: tm_mirror_vlan_id_set @ 0x4a9e4
// size: 36 bytes
//

undefined4 tm_mirror_vlan_id_set(void)

{
  int iVar1;
  
  iVar1 = sbrg_set_mirror_vlid();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_mirror_vlan_id_set fail\n");
  return 0xffffffff;
}


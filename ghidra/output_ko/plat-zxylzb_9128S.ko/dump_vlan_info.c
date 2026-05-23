// module: plat-zxylzb_9128S.ko
// function: dump_vlan_info @ 0x17590
// size: 116 bytes
//

undefined4 dump_vlan_info(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_1c [4];
  
  param_1 = param_1 & 0xfff;
  iVar1 = brg_ram_get(param_1,local_1c,4);
  if (iVar1 < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    if ((local_1c[0] & 1) == 0) {
      printk("vlan table %d invlaid\n",param_1);
      return 0;
    }
    _dump_vlan_info(param_1);
    printk("1:tag delete;2:tag include;3 tag no change\n");
    uVar2 = 0;
  }
  return uVar2;
}


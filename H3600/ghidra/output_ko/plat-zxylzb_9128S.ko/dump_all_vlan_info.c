// module: plat-zxylzb_9128S.ko
// function: dump_all_vlan_info @ 0x17834
// size: 120 bytes
//

undefined4 dump_all_vlan_info(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint local_14 [3];
  
  uVar3 = 0;
  do {
    while( true ) {
      iVar1 = brg_ram_get(uVar3,local_14,4);
      if (iVar1 < 0) {
        return 0xffffffff;
      }
      if ((local_14[0] & 1) == 0) break;
      uVar2 = uVar3 & 0xffff;
      uVar3 = uVar3 + 1;
      _dump_vlan_info(uVar2);
      if (uVar3 == 0x1000) goto LAB_00017888;
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 != 0x1000);
LAB_00017888:
  printk("1:tag delete;2:tag include;3 tag no change\n");
  return 0;
}


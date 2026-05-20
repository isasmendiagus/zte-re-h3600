// module: plat-zxylzb_9128S.ko
// function: pon_pp_dump_hash_mac @ 0x16b50
// size: 248 bytes
//

void pon_pp_dump_hash_mac(uint param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  byte local_25;
  byte local_24;
  
  if (*(ushort *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2) <= param_1) {
    return;
  }
  iVar4 = 0;
  do {
    iVar2 = brg_ram_get(param_1,&local_2c,iVar4);
    if (iVar2 < 0) {
      return;
    }
    if ((local_24 & 0xf0) != 0) {
      printk("depth %u id %u\n",param_1,iVar4);
      uVar1 = local_2c;
      uVar3 = get_mac_status(local_24 >> 4);
      printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar1,uVar3,
             (uint)local_25 | (local_24 & 0xf) << 8,local_26,local_27,local_28,local_29,local_2a,
             local_2b);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 4);
  return;
}


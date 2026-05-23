// module: plat-zxylzb_9128S.ko
// function: pon_pp_dump_mac @ 0x16e28
// size: 276 bytes
//

void pon_pp_dump_mac(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  byte local_2d;
  byte local_2c;
  
  uVar6 = (uint)*(ushort *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2);
  printk("mac table depth %u\n",uVar6);
  if (uVar6 != 0) {
    uVar5 = 0;
    do {
      iVar4 = 0;
      do {
        iVar2 = brg_ram_get(uVar5,&local_34,iVar4);
        if (iVar2 < 0) break;
        if ((local_2c & 0xf0) != 0) {
          printk("depth %u id %u\n",uVar5,iVar4);
          uVar1 = local_34;
          uVar3 = get_mac_status(local_2c >> 4);
          printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar1,uVar3,
                 (uint)local_2d | (local_2c & 0xf) << 8,local_2e,local_2f,local_30,local_31,local_32
                 ,local_33);
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 != 4);
      uVar5 = uVar5 + 1;
    } while (uVar6 != uVar5);
  }
  return;
}


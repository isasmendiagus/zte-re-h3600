// module: plat-zxylzb_9128S.ko
// function: pon_pp_del_mac @ 0x165c0
// size: 472 bytes
//

undefined4 pon_pp_del_mac(char *param_1,uint param_2)

{
  short sVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 local_34;
  char local_33;
  char local_32;
  char local_31;
  char local_30;
  char local_2f;
  char local_2e;
  byte local_2d;
  byte local_2c;
  
  if (param_1 == (char *)0x0) {
    uVar5 = 0xffffffff;
  }
  else {
    iVar6 = 0;
    sVar1 = *(short *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2);
    uVar3 = crc_16(param_1,6,0);
    uVar3 = sVar1 - 1U & uVar3 & 0x3ff;
    do {
      iVar4 = brg_ram_get(uVar3,&local_34,iVar6);
      if (iVar4 < 0) {
        return 0xfffffffe;
      }
      if ((local_2c & 0xf0) != 0) {
        if ((((local_2e == *param_1) && (local_2f == param_1[1])) && (local_30 == param_1[2])) &&
           (((local_31 == param_1[3] && (local_32 == param_1[4])) &&
            ((param_2 & 0xfff) == ((uint)local_2d | (local_2c & 0xf) << 8) && local_33 == param_1[5]
            )))) {
          local_2c = local_2c & 0xf;
          iVar4 = brg_ram_set(uVar3,&local_34,iVar6);
          if (iVar4 < 0) {
            return 0xfffffffd;
          }
          printk("del mac : ");
          printk("depth %u id %u\n",uVar3,iVar6);
          uVar2 = local_34;
          uVar5 = get_mac_status(local_2c >> 4);
          printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar2,uVar5,
                 (uint)local_2d | (local_2c & 0xf) << 8,local_2e,local_2f,local_30,local_31,local_32
                 ,local_33);
        }
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 != 4);
    uVar5 = 0;
  }
  return uVar5;
}


// module: plat-zxylzb_9128S.ko
// function: pon_pp_add_mac @ 0x16bcc
// size: 604 bytes
//

uint pon_pp_add_mac(char *param_1,uint param_2,uint param_3)

{
  short sVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  undefined1 local_34;
  char local_33;
  char local_32;
  char local_31;
  char local_30;
  char local_2f;
  char local_2e;
  byte local_2d;
  byte local_2c;
  byte local_2b;
  
  if (param_1 == (char *)0x0 || 7 < param_3) {
    uVar6 = 0xffffffff;
  }
  else {
    sVar1 = *(short *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2);
    uVar3 = crc_16(param_1,6,0);
    uVar3 = sVar1 - 1U & uVar3 & 0x3ff;
    iVar7 = 0;
    do {
      iVar4 = brg_ram_get(uVar3,&local_34,iVar7);
      if (iVar4 < 0) {
        return 0xfffffffe;
      }
      uVar6 = (uint)local_2c;
      if ((local_2c & 0xf0) == 0) {
        local_31 = param_1[3];
        local_2c = (byte)((param_2 << 0x14) >> 0x1c) | 0xf0;
        local_2e = *param_1;
        local_2f = param_1[1];
        local_2b = local_2b & 0xfe;
        local_30 = param_1[2];
        local_32 = param_1[4];
        local_33 = param_1[5];
        local_2d = (byte)(param_2 & 0xfff);
        local_34 = (undefined1)(1 << (param_3 & 0xff));
        iVar4 = brg_ram_set(uVar3,&local_34,iVar7);
        if (-1 < iVar4) {
          printk("add mac : ");
          printk("depth %u id %u\n",uVar3,iVar7);
          uVar2 = local_34;
          uVar5 = get_mac_status(local_2c >> 4);
          printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar2,uVar5,
                 (uint)local_2d | (local_2c & 0xf) << 8,local_2e,local_2f,local_30,local_31,local_32
                 ,local_33);
          return uVar6 & 0xf0;
        }
        return 0xfffffffd;
      }
      iVar7 = iVar7 + 1;
      if ((((local_2e == *param_1) && (local_2f == param_1[1])) && (local_30 == param_1[2])) &&
         (((local_31 == param_1[3] && (local_32 == param_1[4])) &&
          ((param_2 & 0xfff) == ((uint)local_2d | (uVar6 & 0xf) << 8) && local_33 == param_1[5]))))
      {
        printk("mac exist");
        return 0;
      }
    } while (iVar7 != 4);
    uVar6 = 0;
  }
  return uVar6;
}


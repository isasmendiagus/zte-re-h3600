// module: plat-zxylzb_9128S.ko
// function: pon_pp_add_port_to_vlan @ 0x17504
// size: 132 bytes
//

int pon_pp_add_port_to_vlan(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint local_1c [3];
  
  if (param_2 < 8) {
    iVar1 = brg_ram_get(param_1 & 0xfff,local_1c);
    if (iVar1 < 0) {
      iVar1 = -1;
    }
    else {
      uVar2 = param_2 * 2 + 1;
      local_1c[0] = (local_1c[0] | 1) & ~(3 << (uVar2 & 0xff)) | (param_3 & 3) << (uVar2 & 0xff);
      iVar1 = brg_ram_set(param_1 & 0xfff,local_1c,4);
      iVar1 = iVar1 >> 0x1f;
    }
    return iVar1;
  }
  return -1;
}


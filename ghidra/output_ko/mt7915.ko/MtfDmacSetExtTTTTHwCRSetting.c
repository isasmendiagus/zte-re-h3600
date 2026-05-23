// module: mt7915.ko
// function: MtfDmacSetExtTTTTHwCRSetting @ 0x196a34
// size: 380 bytes
//

void MtfDmacSetExtTTTTHwCRSetting(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  uint local_1c;
  
  uVar2 = *(undefined4 *)(&DAT_0029d6c8 + param_2 * 4);
  local_1c = 0;
  if (param_2 != 0) {
    if (param_3 == 1) {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb000,&local_1c);
      local_1c = local_1c | 0x20000000;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb000);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,&local_1c);
      local_1c = local_1c & 0xfffc0000 | 0xc0002800;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
      *(uint *)(&DAT_0036b91c + param_1) =
           *(uint *)(&DAT_0036b91c + param_1) | 1 << (param_2 & 0xff);
    }
    else {
      uVar1 = *(uint *)(&DAT_0036b91c + param_1) & ~(param_3 << (param_2 & 0xff));
      *(uint *)(&DAT_0036b91c + param_1) = uVar1;
      if (uVar1 == 0) {
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb000,&local_1c);
        local_1c = local_1c & 0xdfffffff;
      }
      else {
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb000,&local_1c);
        local_1c = local_1c | 0x20000000;
      }
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb000);
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,&local_1c);
      local_1c = local_1c & 0x3fffffff;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
    }
  }
  return;
}


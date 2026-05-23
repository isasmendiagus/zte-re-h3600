// module: mt7915.ko
// function: MtfDmacSetMbssHwCRSetting @ 0x196874
// size: 448 bytes
//

void MtfDmacSetMbssHwCRSetting(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint local_1c;
  
  local_1c = 0;
  if (param_2 == 0) {
    printk(&_LC19,0x5ac);
    dump_stack();
  }
  if (param_3 == 1) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb0a0,&local_1c);
    local_1c = local_1c | 0x20000000;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb0a0);
    iVar2 = param_2 * 4 + -0x7df04f64;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar2,&local_1c);
    local_1c = local_1c & 0xfff00000 | 0xc0000000 | param_2 * 0x1014 & 0xffffc;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar2);
    *(uint *)(&DAT_0036b918 + param_1) = *(uint *)(&DAT_0036b918 + param_1) | 1 << (param_2 & 0xff);
  }
  else {
    uVar1 = *(uint *)(&DAT_0036b918 + param_1) & ~(param_3 << (param_2 & 0xff));
    *(uint *)(&DAT_0036b918 + param_1) = uVar1;
    if (uVar1 == 0) {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb0a0,&local_1c);
      local_1c = local_1c & 0xdfffffff;
    }
    else {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb0a0,&local_1c);
      local_1c = local_1c | 0x20000000;
    }
    iVar2 = param_2 * 4 + -0x7df04f64;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820fb0a0);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar2,&local_1c);
    local_1c = local_1c & 0x3ff00000;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar2,local_1c);
  }
  return;
}


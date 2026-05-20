// module: mt7915.ko
// function: MCUSysInit @ 0x1a3d38
// size: 572 bytes
//

undefined4 MCUSysInit(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint local_1c [2];
  
  if (2 < DebugLevel) {
    printk(&_LC0,"MCUSysInit");
  }
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xa8) != (code *)0x0) {
    (**(code **)(iVar1 + 0xa8))(param_1);
  }
  chip_fw_init(param_1);
  if (0 < DebugLevel) {
    printk(&_LC1,"MCUSysInit",*(undefined1 *)(param_1 + 0xa78a54));
  }
  if (*(char *)(param_1 + 0xa78a54) == '\x01') {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f23c,local_1c);
    local_1c[0] = local_1c[0] & 0xfffffffc | 2;
    hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f23c);
  }
  else {
    uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
    if (*(char *)(param_1 + 0xa78a54) == '\x02') {
      if (uVar3 == 0x7615) {
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x220c,local_1c);
        local_1c[0] = local_1c[0] | 0x10;
        hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x220c);
      }
      else if (uVar3 == 0x7622) {
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x260c,local_1c);
        local_1c[0] = local_1c[0] | 0x10;
        hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x260c);
      }
    }
    else if (uVar3 == 0x7615) {
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x220c,local_1c);
      local_1c[0] = local_1c[0] & 0xffffffef;
      hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x220c);
    }
    else if (uVar3 == 0x7622) {
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x260c,local_1c);
      local_1c[0] = local_1c[0] & 0xffffffef;
      hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x260c);
    }
    else {
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f23c,local_1c);
      local_1c[0] = local_1c[0] & 0xfffffffc;
      hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f23c);
    }
  }
  iVar1 = NICLoadFirmware(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else if (DebugLevel < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("%s: NICLoadFirmware failed, Status[=0x%08x]\n","MCUSysInit");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


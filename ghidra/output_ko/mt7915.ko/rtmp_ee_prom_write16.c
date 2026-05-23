// module: mt7915.ko
// function: rtmp_ee_prom_write16 @ 0x1d1618
// size: 1844 bytes
//

undefined4 rtmp_ee_prom_write16(int param_1,uint param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint local_2c;
  uint local_28;
  uint local_24 [2];
  
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_28);
  iVar2 = 5;
  uVar3 = 0x10;
  local_28 = local_28 & 0xfffffff2 | 2;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  local_28 = local_28 | 1;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  local_28 = local_28 & 0xfffffffe;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff3;
  do {
    local_24[0] = local_24[0] & 0xfffffffb;
    if ((uVar3 & 0x13) != 0) {
      local_24[0] = local_24[0] | 4;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    uVar3 = uVar3 >> 1;
    local_24[0] = local_24[0] | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    local_24[0] = local_24[0] & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  local_24[0] = local_24[0] & 0xfffffffb;
  iVar2 = 6;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff3;
  do {
    local_24[0] = local_24[0] & 0xfffffffb;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    local_24[0] = local_24[0] | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    local_24[0] = local_24[0] & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  local_24[0] = local_24[0] & 0xfffffffb;
  uVar3 = 4;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = 3;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff9;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  local_24[0] = local_24[0] | 1;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  local_24[0] = local_24[0] & 0xfffffffe;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_2c);
  local_2c = local_2c & 0xfffffff2 | 2;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff3;
  do {
    local_24[0] = local_24[0] & 0xfffffffb;
    if ((uVar3 & 5) != 0) {
      local_24[0] = local_24[0] | 4;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    uVar3 = uVar3 >> 1;
    local_24[0] = local_24[0] | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    local_24[0] = local_24[0] & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  local_24[0] = local_24[0] & 0xfffffffb;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  uVar3 = 1 << ((byte)"Set_IRR_TTG"[param_1 + 10] - 1 & 0xff);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff3;
  do {
    local_24[0] = local_24[0] & 0xfffffffb;
    if ((uVar3 & param_2 >> 1 & 0xffff) != 0) {
      local_24[0] = local_24[0] | 4;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    local_24[0] = local_24[0] | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    local_24[0] = local_24[0] & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    uVar3 = uVar3 >> 1;
  } while (uVar3 != 0);
  local_24[0] = local_24[0] & 0xfffffffb;
  iVar2 = 0x10;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  uVar3 = 0x8000;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff3;
  do {
    local_24[0] = local_24[0] & 0xfffffffb;
    if ((uVar3 & param_3) != 0) {
      local_24[0] = local_24[0] | 4;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    uVar3 = uVar3 >> 1;
    local_24[0] = local_24[0] | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    local_24[0] = local_24[0] & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  local_24[0] = local_24[0] & 0xfffffffb;
  iVar2 = 5;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  bVar1 = true;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_2c);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff9;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  local_24[0] = local_24[0] | 1;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  local_24[0] = local_24[0] & 0xfffffffe;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  RtmpusecDelay(10000);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_28);
  local_28 = local_28 & 0xfffffff2 | 2;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  local_28 = local_28 | 1;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  local_28 = local_28 & 0xfffffffe;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff3;
  do {
    local_24[0] = local_24[0] & 0xfffffffb;
    if (bVar1) {
      local_24[0] = local_24[0] | 4;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    bVar1 = false;
    local_24[0] = local_24[0] | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    local_24[0] = local_24[0] & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  local_24[0] = local_24[0] & 0xfffffffb;
  iVar2 = 6;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff3;
  do {
    local_24[0] = local_24[0] & 0xfffffffb;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    local_24[0] = local_24[0] | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    local_24[0] = local_24[0] & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  local_24[0] = local_24[0] & 0xfffffffb;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff9;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  local_24[0] = local_24[0] | 1;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  local_24[0] = local_24[0] & 0xfffffffe;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
  local_24[0] = local_24[0] & 0xfffffff9;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  local_24[0] = local_24[0] | 1;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  local_24[0] = local_24[0] & 0xfffffffe;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  return 0;
}


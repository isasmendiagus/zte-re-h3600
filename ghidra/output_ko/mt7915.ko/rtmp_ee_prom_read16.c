// module: mt7915.ko
// function: rtmp_ee_prom_read16 @ 0x1d1360
// size: 696 bytes
//

bool rtmp_ee_prom_read16(int param_1,uint param_2,ushort *param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint local_28;
  uint local_24;
  
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_28);
  uVar3 = 4;
  iVar2 = 3;
  local_28 = local_28 & 0xfffffff2 | 2;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0));
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_24);
  local_24 = local_24 & 0xfffffff3;
  do {
    local_24 = local_24 & 0xfffffffb;
    if ((uVar3 & 6) != 0) {
      local_24 = local_24 | 4;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    uVar3 = uVar3 >> 1;
    local_24 = local_24 | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    local_24 = local_24 & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  local_24 = local_24 & 0xfffffffb;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  uVar3 = 1 << ((byte)"Set_IRR_TTG"[param_1 + 10] - 1 & 0xff);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_24);
  local_24 = local_24 & 0xfffffff3;
  do {
    local_24 = local_24 & 0xfffffffb;
    if ((uVar3 & param_2 >> 1 & 0xffff) != 0) {
      local_24 = local_24 | 4;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    local_24 = local_24 | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    local_24 = local_24 & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    uVar3 = uVar3 >> 1;
  } while (uVar3 != 0);
  local_24 = local_24 & 0xfffffffb;
  iVar2 = 0x10;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_24);
  local_24 = local_24 & 0xfffffff3;
  uVar1 = 0;
  do {
    local_24 = local_24 | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4,local_24);
    RtmpusecDelay(1);
    uVar1 = uVar1 << 1;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_24);
    local_24 = local_24 & 0xfffffffe;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
    RtmpusecDelay(1);
    uVar3 = local_24 & 8;
    local_24 = local_24 & 0xfffffffb;
    if (uVar3 != 0) {
      uVar1 = uVar1 | 1;
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,&local_24);
  local_24 = local_24 & 0xfffffff9;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  local_24 = local_24 | 1;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  local_24 = local_24 & 0xfffffffe;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),4);
  RtmpusecDelay(1);
  *param_3 = uVar1;
  return 0xfffd < (ushort)(uVar1 - 1);
}


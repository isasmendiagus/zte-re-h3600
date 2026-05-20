// module: mt7915.ko
// function: hif_wait_WPDMA_idle @ 0x178238
// size: 820 bytes
//

undefined4 hif_wait_WPDMA_idle(int param_1,uint param_2,int param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  uint local_2c [2];
  
  local_2c[0] = 0;
  iVar2 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = *(int *)(iVar2 + 0xa0);
  if ((*(uint *)(param_1 + 0xa39f84) & 0x100) != 0) {
    return 0;
  }
  if (param_2 == 0xff) {
    uVar6 = 0;
    uVar7 = 0;
    while( true ) {
      uVar3 = HcGetAmountOfBand(param_1);
      uVar4 = uVar6 & 0xff;
      uVar6 = uVar6 + 1;
      if (uVar3 <= uVar4) break;
      uVar7 = uVar7 | 1 << uVar4;
    }
  }
  else {
    uVar7 = 1 << (param_2 & 0xff);
  }
  if ((uVar7 & 1) == 0) {
LAB_001783b0:
    uVar8 = 1;
  }
  else {
    if (2 < DebugLevel) {
      printk("%s(): check band(0)\n","hif_wait_WPDMA_idle");
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02413c,local_2c);
    local_2c[0] = local_2c[0] | 7;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02413c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02513c,local_2c);
    local_2c[0] = local_2c[0] | 7;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02513c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02813c,local_2c);
    local_2c[0] = local_2c[0] & 0xfffffff8;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02813c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02913c,local_2c);
    local_2c[0] = local_2c[0] & 0xfffffff8;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02913c);
    iVar5 = 0;
    do {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c027044,local_2c);
      if ((local_2c[0] & 1) == 0) goto LAB_001783b0;
      RtmpusecDelay(param_4);
      bVar1 = iVar5 < param_3;
      iVar5 = iVar5 + 1;
    } while (bVar1);
    uVar8 = 0;
  }
  DataSynchronizationBarrier(0xf);
  if (((*(uint *)(*(int *)(iVar2 + 0xbc) + 0xd7090) & 0x7fffffff) != 0) && ((uVar7 & 2) != 0)) {
    if (2 < DebugLevel) {
      printk("%s(): check band(1)\n","hif_wait_WPDMA_idle");
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02413c,local_2c);
    local_2c[0] = local_2c[0] | 7;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02413c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02513c,local_2c);
    local_2c[0] = local_2c[0] | 7;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02513c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02813c,local_2c);
    local_2c[0] = local_2c[0] & 0xfffffffc | 4;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02813c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02913c,local_2c);
    local_2c[0] = local_2c[0] | 7;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02913c);
    iVar2 = 0;
    do {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c027044,local_2c);
      if ((local_2c[0] & 1) == 0) {
        return uVar8;
      }
      RtmpusecDelay(param_4);
      bVar1 = iVar2 < param_3;
      iVar2 = iVar2 + 1;
    } while (bVar1);
    uVar8 = 0;
  }
  return uVar8;
}


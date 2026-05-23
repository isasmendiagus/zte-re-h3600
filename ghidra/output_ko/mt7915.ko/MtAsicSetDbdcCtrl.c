// module: mt7915.ko
// function: MtAsicSetDbdcCtrl @ 0x196d70
// size: 424 bytes
//

undefined4 MtAsicSetDbdcCtrl(int param_1,byte *param_2)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  uint uVar7;
  uint local_28;
  uint local_24 [2];
  
  local_28 = 0;
  local_24[0] = 0;
  if (*param_2 != 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f0000,&local_28);
    local_28 = local_28 | 0x41000000;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f0000);
    if (2 < DebugLevel) {
      printk("%s: MAC D1 2x 1x initial(val=%x)\n","MtAsicSetDbdcCtrl",local_28);
    }
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f0050,&local_28);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f0054,local_24);
  local_28 = local_28 | (uint)*param_2 << 0x1f;
  if (*(int *)(param_2 + 4) != 0) {
    bVar6 = false;
    pbVar1 = param_2 + *(int *)(param_2 + 4) * 3;
    bVar5 = false;
    uVar2 = local_28;
    uVar4 = local_24[0];
    do {
      uVar7 = (uint)param_2[8];
      if ((uVar7 < 8) && (-1 < *(int *)(&DAT_0029d71c + uVar7 * 4))) {
        uVar3 = *(int *)(&DAT_0029d71c + uVar7 * 4) + (uint)param_2[9];
        if (-1 < (int)uVar3) {
          if (uVar7 == 4) {
            bVar6 = true;
            uVar4 = uVar4 & ~(1 << (uVar3 & 0xff)) | (param_2[10] & 1) << (uVar3 & 0xff);
          }
          else {
            bVar5 = true;
            uVar2 = uVar2 & ~(1 << (uVar3 & 0xff)) | (param_2[10] & 1) << (uVar3 & 0xff);
          }
        }
      }
      param_2 = param_2 + 3;
    } while (param_2 != pbVar1);
    if (bVar5) {
      local_28 = uVar2;
    }
    if (bVar6) {
      local_24[0] = uVar4;
    }
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f0050);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f0054,local_24[0]);
  return 0;
}


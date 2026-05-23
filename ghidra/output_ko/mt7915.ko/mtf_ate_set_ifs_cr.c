// module: mt7915.ko
// function: mtf_ate_set_ifs_cr @ 0x172a1c
// size: 464 bytes
//

undefined4 mtf_ate_set_ifs_cr(int param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint local_20;
  uint local_1c;
  
  local_20 = 0;
  local_1c = 0;
  iVar3 = net_ad_wrap_service();
  iVar4 = net_ad_wrap_service(param_1);
  iVar3 = (uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3;
  uVar1 = *(ushort *)(iVar3 + 0x10fa);
  uVar2 = *(ushort *)(iVar3 + 0x10fc);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e4098,&local_20);
  uVar5 = local_20 & 0xff;
  local_20 = uVar5 * 0x32;
  uVar6 = ((uint)uVar1 * 1000 + uVar5 * -0x32) - 0x5dc;
  uVar5 = ((uint)uVar2 * 1000 + uVar5 * -0x32) - 0x5dc;
  if (2 < DebugLevel) {
    printk("%s: txv_time=%dns, i2t_chk_time=%dns, tr2t_chk_time=%dns\n","mtf_ate_set_ifs_cr",
           local_20,uVar6,uVar5);
  }
  uVar6 = uVar6 / 0x32;
  if (param_2 != 0) {
    if (param_2 == 1) {
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f409c,&local_1c);
      local_1c = uVar5 / 0x32 & 0x1ff | local_1c | (uVar6 & 0x1ff) << 0x10;
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f409c,local_1c);
    }
    else if (-1 < DebugLevel) {
      printk("%s: Invalid band_idx!!\n","mtf_ate_set_ifs_cr",uVar5 * 0x51eb851f);
    }
    return 0;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820e409c,&local_1c);
  local_1c = uVar5 / 0x32 & 0x1ff | local_1c | (uVar6 & 0x1ff) << 0x10;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820e409c,local_1c);
  return 0;
}


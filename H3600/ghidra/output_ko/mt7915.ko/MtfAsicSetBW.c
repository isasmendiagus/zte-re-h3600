// module: mt7915.ko
// function: MtfAsicSetBW @ 0x195ed8
// size: 224 bytes
//

undefined4 MtfAsicSetBW(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint local_1c;
  
  bbp_set_bw(param_1,param_2 & 0xff);
  if (param_3 == 0) {
    uVar1 = 0xfffffff3;
    uVar3 = 0xc;
    iVar2 = 2;
  }
  else {
    uVar1 = 0xfff3ffff;
    uVar3 = 0xc0000;
    iVar2 = 0x12;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2078,&local_1c);
  local_1c = uVar1 & local_1c;
  switch(param_2) {
  case 0:
    break;
  case 1:
    local_1c = local_1c | 1 << iVar2;
    break;
  case 2:
    local_1c = local_1c | 2 << iVar2;
    break;
  case 3:
  case 6:
    local_1c = local_1c | uVar3;
    break;
  default:
    if (0 < DebugLevel) {
      printk("%s():Invalid BW(%d)!\n","MtfAsicSetBW",param_2);
    }
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f2078,local_1c);
  return 1;
}


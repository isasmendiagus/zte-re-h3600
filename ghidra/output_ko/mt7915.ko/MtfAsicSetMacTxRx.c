// module: mt7915.ko
// function: MtfAsicSetMacTxRx @ 0x19593c
// size: 1292 bytes
//

undefined4 MtfAsicSetMacTxRx(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c [2];
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f3080,&local_38);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f3070,&local_34);
  switch(param_2) {
  case 1:
    if (param_3 == 0) {
      if (param_4 == 0) {
        uVar2 = 0x100;
      }
      else {
        uVar2 = 0x400;
      }
      local_38 = uVar2 | local_38;
    }
    else {
      if (param_4 == 0) {
        uVar2 = 0xfffffeff;
      }
      else {
        uVar2 = 0xfffffbff;
      }
      local_38 = uVar2 & local_38;
    }
    goto LAB_00195a0c;
  case 2:
    if (param_3 == 0) {
      if (param_4 == 0) {
        uVar2 = 0xfffffffe;
        local_38 = local_38 | 0x200;
      }
      else {
        uVar2 = 0xfffeffff;
        local_38 = local_38 | 0x800;
      }
LAB_00195cf0:
      local_34 = uVar2 & local_34;
      goto LAB_00195a0c;
    }
    if (param_4 == 0) {
      uVar2 = 1;
      local_38 = local_38 & 0xfffffdff;
    }
    else {
      uVar2 = 0x10000;
      local_38 = local_38 & 0xfffff7ff;
    }
    break;
  case 3:
    if (param_3 == 0) {
      if (param_4 == 0) {
        uVar2 = 0xfffffffe;
        local_38 = local_38 | 0x300;
      }
      else {
        uVar2 = 0xfffeffff;
        local_38 = local_38 | 0xc00;
      }
      goto LAB_00195cf0;
    }
    if (param_4 == 0) {
      uVar2 = 1;
      local_38 = local_38 & 0xfffffcff;
    }
    else {
      uVar2 = 0x10000;
      local_38 = local_38 & 0xfffff3ff;
    }
    break;
  case 4:
    if (param_3 == 0) {
      if (param_4 == 0) {
        uVar2 = 0xfffffe6e;
        local_38 = local_38 | 0x300;
      }
      else {
        uVar2 = 0xfe6effff;
        local_38 = local_38 | 0xc00;
      }
      goto LAB_00195cf0;
    }
    if (param_4 == 0) {
      uVar2 = 0x191;
      local_38 = local_38 & 0xfffffcff;
    }
    else {
      uVar2 = 0x1910000;
      local_38 = local_38 & 0xfffff3ff;
    }
    break;
  case 5:
    if (param_3 == 0) {
      uVar2 = 0xfeffff6f;
      if (param_4 != 0) {
        uVar2 = 0xfe6fffff;
      }
      local_34 = uVar2 & local_34;
      goto LAB_00195a0c;
    }
    if (param_4 == 0) {
      uVar2 = 400;
      local_38 = local_38 & 0xfffffdff;
    }
    else {
      uVar2 = 0x1900000;
      local_38 = local_38 & 0xfffff7ff;
    }
    break;
  case 6:
    if (param_3 == 0) {
      if (param_4 == 0) {
        uVar2 = 0xfffffe6e;
        local_38 = local_38 | 0x200;
      }
      else {
        uVar2 = 0xfe6effff;
        local_38 = local_38 | 0x800;
      }
      goto LAB_00195cf0;
    }
    if (param_4 == 0) {
      uVar2 = 0x191;
      local_38 = local_38 & 0xfffffdff;
    }
    else {
      uVar2 = 0x1910000;
      local_38 = local_38 & 0xfffff7ff;
    }
    break;
  default:
    if (-1 < DebugLevel) {
      printk("%s: Unknown path (%d)\n","MtfAsicSetMacTxRx",param_2);
    }
    goto LAB_00195a0c;
  }
  local_34 = local_34 | uVar2;
LAB_00195a0c:
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f3080,local_38);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f3070,local_34);
  uVar2 = (uint)*(byte *)(iVar1 + 0x74);
  if (uVar2 != 0) {
    uVar3 = 0;
    do {
      while (3 < (int)uVar3 || 1 < param_4) {
        if (DebugLevel < 0) goto LAB_00195a80;
        printk("%s(): Invalid Input paramter!WmmSet=%d, BssIdx=%d, band=%d, Enable=%d\n",
               "MtAsicSetTxQ",uVar3,param_4,param_4,param_3);
LAB_00195b30:
        uVar2 = (uint)*(byte *)(iVar1 + 0x74);
        uVar3 = uVar3 + 1;
        if (uVar2 <= uVar3) {
          return 1;
        }
      }
      uVar5 = *(undefined4 *)(&DAT_0029d644 + param_4 * 4);
      uVar4 = (&DAT_0029d64c)[uVar3];
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar4,&local_30);
      if (param_3 == 0) {
        local_30 = local_30 & 0xf0f0f0f0;
        mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar4);
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,local_2c);
        local_2c[0] = local_2c[0] & 0xf0fff0f0;
      }
      else {
        local_30 = local_30 | 0xf0f0f0f;
        mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar4);
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,local_2c);
        local_2c[0] = local_2c[0] | 0xf000f0f;
      }
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,local_2c[0]);
      if (DebugLevel < 0) goto LAB_00195b30;
      printk("%s(): Set WmmSet=%d, band=%d, Enable=%d with CR[0x%x = 0x%08x, 0x%x=0x%08x]\n",
             "MtAsicSetTxQ",uVar3,param_4,param_3,uVar4,local_30,uVar5,local_2c[0]);
      uVar2 = (uint)*(byte *)(iVar1 + 0x74);
LAB_00195a80:
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar2);
  }
  return 1;
}


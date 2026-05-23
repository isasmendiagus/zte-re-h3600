// module: mt7915.ko
// function: mt7915_ctrl_rxv_group @ 0x1769c8
// size: 200 bytes
//

void mt7915_ctrl_rxv_group(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  uint local_1c [2];
  
  iVar1 = param_2 * 0x10000 + -0x7df19000;
  local_1c[0] = 0;
  switch(param_3) {
  case 0:
    uVar2 = 0x100000;
    break;
  case 1:
    uVar2 = 0x200000;
    break;
  case 2:
    uVar2 = 0x400000;
    break;
  case 3:
    uVar2 = 0x800000;
    break;
  default:
    if (DebugLevel < 0) {
      return;
    }
    printk("%s(): Unknown group(%d), ignored!\n","mt7915_ctrl_rxv_group");
    return;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar1,local_1c);
  if (param_4 == 0) {
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar1,local_1c[0] & ~uVar2);
    return;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar1,uVar2 | local_1c[0]);
  return;
}


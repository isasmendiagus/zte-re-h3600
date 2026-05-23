// module: mt7915.ko
// function: mtf_txpower_boost_ctrl @ 0x1a12f0
// size: 384 bytes
//

void mtf_txpower_boost_ctrl(int param_1,int param_2,undefined4 param_3,void *param_4)

{
  uint uVar1;
  
  switch(param_3) {
  case 0:
    os_move_mem((void *)(param_1 + param_2 * 0xa1 + 0x794d68),param_4,4);
    return;
  case 1:
    uVar1 = 0x4d6c;
    goto LAB_001a139c;
  case 2:
    uVar1 = 0x4d74;
LAB_001a139c:
    os_move_mem((void *)(param_1 + param_2 * 0xa1 + (uVar1 | 0x790000)),param_4,8);
    return;
  case 3:
    os_move_mem((void *)(param_1 + param_2 * 0xa1 + 0x794d7c),param_4,9);
    return;
  case 4:
    uVar1 = 0x4d85;
    break;
  case 5:
    uVar1 = 0x4d91;
    break;
  case 6:
    uVar1 = 0x4d9d;
    break;
  case 7:
    uVar1 = 0x4da9;
    break;
  case 8:
    uVar1 = 0x4db5;
    break;
  case 9:
    uVar1 = 0x4dc1;
    break;
  case 10:
    uVar1 = 0x4dcd;
    break;
  case 0xb:
    uVar1 = 0x4dd9;
    break;
  case 0xc:
    uVar1 = 0x4de5;
    break;
  case 0xd:
    uVar1 = 0x4df1;
    break;
  case 0xe:
    os_move_mem((void *)(param_1 + param_2 * 0xa1 + 0x794dfd),param_4,0xc);
    return;
  default:
    if (-1 < DebugLevel) {
      printk("%s: set wrong parameters\n","mtf_txpower_boost_ctrl");
      return;
    }
    return;
  }
  os_move_mem((void *)(param_1 + param_2 * 0xa1 + (uVar1 | 0x790000)),param_4,0xc);
  return;
}


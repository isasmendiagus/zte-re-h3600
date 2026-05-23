// module: mt7915.ko
// function: MtfAsicGetRxStat @ 0x195fd8
// size: 1028 bytes
//

uint MtfAsicGetRxStat(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint *puVar3;
  uint local_18;
  undefined4 local_14;
  
  puVar3 = &local_18;
  local_18 = 0;
  local_14 = 0;
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7663) {
    switch(param_2 + -1) {
    case 0:
      goto switchD_00196014_caseD_0;
    case 1:
      goto switchD_00196014_caseD_1;
    case 2:
      goto switchD_00196014_caseD_6;
    case 3:
      uVar2 = 0x224;
      goto LAB_001960f8;
    case 4:
      goto switchD_00196014_caseD_5;
    case 5:
      goto switchD_00196014_caseD_3;
    case 6:
      goto switchD_00196014_caseD_2;
    case 7:
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x13218,&local_14);
      uVar2 = 0x3618;
      uVar1 = *(undefined4 *)(param_1 + 0xa797a0);
      puVar3 = &local_14;
      break;
    case 8:
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x10414,&local_18);
      uVar2 = 0x1414;
      goto LAB_001962f8;
    case 9:
      goto switchD_00196014_caseD_9;
    case 10:
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x13a18,&local_18);
      uVar1 = *(undefined4 *)(param_1 + 0xa797a0);
      uVar2 = 0x3e18;
      break;
    case 0xb:
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x13220,&local_18);
      uVar2 = 0x3620;
      goto LAB_001963b4;
    case 0xc:
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x13a20,&local_18);
      uVar2 = 0x3e20;
LAB_001963b4:
      local_18 = local_18 | (local_14 & 0x20000) << 1;
      phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2 | 0x10000,&local_18);
      local_18 = local_14 & 0x20000 | local_18;
      goto LAB_00196110;
    case 0xd:
      goto switchD_00196014_caseD_d;
    case 0xe:
      goto switchD_00196014_caseD_e;
    case 0xf:
      goto switchD_00196014_caseD_f;
    case 0x10:
      goto switchD_00196014_caseD_10;
    case 0x11:
      goto switchD_00196014_caseD_11;
    case 0x12:
      goto switchD_00196014_caseD_12;
    case 0x13:
      goto switchD_00196014_caseD_13;
    case 0x14:
      goto switchD_00196014_caseD_14;
    case 0x15:
      goto switchD_00196014_caseD_15;
    case 0x16:
      goto switchD_00196014_caseD_16;
    case 0x17:
      goto switchD_00196014_caseD_17;
    default:
      goto switchD_00196014_default;
    case 0x19:
      uVar2 = 0xd1e0;
      goto LAB_001961c0;
    }
    local_18 = local_18 | local_14._2_2_;
    phy_io_read32(uVar1,uVar2 | 0x10000,puVar3);
    local_18 = local_14 & 0xffff0000 | local_18;
    goto LAB_00196110;
  }
  switch(param_2 + -1) {
  case 0:
switchD_00196014_caseD_0:
    uVar2 = 0xd014;
    goto LAB_001961c0;
  case 1:
switchD_00196014_caseD_1:
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd030,&local_18);
    local_18 = local_18 & 0x3ffffff;
    goto LAB_00196110;
  case 2:
switchD_00196014_caseD_2:
    uVar2 = 0x220;
    break;
  case 3:
switchD_00196014_caseD_3:
    uVar2 = 0x21c;
    break;
  case 4:
    uVar2 = 0x20c;
    break;
  case 5:
switchD_00196014_caseD_5:
    uVar2 = 0x210;
    break;
  case 6:
switchD_00196014_caseD_6:
    uVar2 = 0x214;
    break;
  case 7:
    uVar2 = 0x21a8;
    break;
  case 8:
    phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x10220,&local_18);
    uVar2 = 0x21c;
LAB_001962f8:
    phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2 | 0x10000,&local_18);
    goto LAB_00196110;
  case 9:
switchD_00196014_caseD_9:
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd014,&local_18);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd030,&local_18);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd214,&local_18);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd230,&local_18);
    goto LAB_00196110;
  case 10:
    uVar2 = 0x29a8;
    break;
  case 0xb:
    uVar2 = 0x21b0;
    break;
  case 0xc:
    uVar2 = 0x29b0;
    break;
  case 0xd:
switchD_00196014_caseD_d:
    uVar2 = 0xd214;
    goto LAB_0019619c;
  case 0xe:
switchD_00196014_caseD_e:
    uVar2 = 0xd230;
    goto LAB_0019619c;
  case 0xf:
switchD_00196014_caseD_f:
    uVar2 = 0xd034;
LAB_001961c0:
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2 | 0x820f0000,&local_18);
    local_18 = local_18 & 0xffff;
    goto LAB_00196110;
  case 0x10:
switchD_00196014_caseD_10:
    uVar2 = 0xd234;
LAB_0019619c:
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2 | 0x820f0000,&local_18);
    goto LAB_00196110;
  case 0x11:
switchD_00196014_caseD_11:
    uVar2 = 0xd018;
    goto LAB_00196168;
  case 0x12:
switchD_00196014_caseD_12:
    uVar2 = 0xd218;
LAB_00196168:
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2 | 0x820f0000,&local_18);
    local_18 = local_18 >> 0x10;
    goto LAB_00196110;
  case 0x13:
switchD_00196014_caseD_13:
    uVar2 = 0x420;
    break;
  case 0x14:
switchD_00196014_caseD_14:
    uVar2 = 0x41c;
    break;
  case 0x15:
switchD_00196014_caseD_15:
    uVar2 = 0x40c;
    break;
  case 0x16:
switchD_00196014_caseD_16:
    uVar2 = 0x410;
    break;
  case 0x17:
switchD_00196014_caseD_17:
    uVar2 = 0x414;
    break;
  default:
switchD_00196014_default:
    goto LAB_00196110;
  }
LAB_001960f8:
  phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2 | 0x10000,&local_18);
LAB_00196110:
  if (2 < DebugLevel) {
    printk("%s, Type(%d):%x\n","MtfAsicGetRxStat",param_2);
  }
  return local_18;
}


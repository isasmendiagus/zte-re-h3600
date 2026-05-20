// module: mt7915.ko
// function: chip_set_sta_psm @ 0x189568
// size: 216 bytes
//

undefined4 chip_set_sta_psm(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_1c;
  
  if (param_3 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0x40000000;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820d4038,0x40000000);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820d4034,uVar3);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820d4030,param_2 & 0x3ff | 0x5100000);
  iVar2 = 64000;
  local_1c = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820d4030,&local_1c);
  do {
    iVar1 = local_1c;
    RtmpusecDelay(1);
    if (-1 < iVar1) {
      return 1;
    }
    local_1c = 0;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820d4030,&local_1c);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return 0;
}


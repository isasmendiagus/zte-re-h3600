// module: mt7915.ko
// function: RTMP_IO_READ_BULK @ 0x27b30c
// size: 328 bytes
//

void RTMP_IO_READ_BULK(int param_1,int param_2,int param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int local_2c [2];
  uint local_24 [2];
  
  uVar1 = param_4 >> 2;
  local_24[0] = 0;
  local_2c[0] = param_3;
  if (1 < DebugLevel) {
    printk(&_LC223);
  }
  iVar2 = mt_mac_cr_range_mapping(param_1,local_2c);
  if (uVar1 < 2 || iVar2 != 0) {
    local_2c[0] = param_3;
    if (uVar1 == 0) goto LAB_0027b3e0;
  }
  else if ((local_2c[0] != 0) && ((*(uint *)(param_1 + 0xa3ac14) & 0x800) == 0)) {
    RTMP_IO_MCU_READ_BULK(param_1,param_2,local_2c[0],param_4);
    return;
  }
  uVar3 = 0;
  do {
    local_2c[0] = param_3;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_3,local_24);
    if (2 < DebugLevel) {
      printk("%s: Offset = %x, Value = %x\n","RTMP_IO_READ_BULK",local_2c[0],local_24[0]);
    }
    param_3 = param_3 + 4;
    local_24[0] = local_24[0] << 0x18 | (local_24[0] >> 8 & 0xff) << 0x10 |
                  (local_24[0] >> 0x10 & 0xff) << 8 | local_24[0] >> 0x18;
    *(uint *)(param_2 + uVar3 * 4) = local_24[0];
    uVar3 = uVar3 + 1;
    local_2c[0] = param_3;
  } while (uVar3 != uVar1);
LAB_0027b3e0:
  if (1 < DebugLevel) {
    printk(&_LC223);
  }
  return;
}


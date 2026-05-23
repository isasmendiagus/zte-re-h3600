// module: mt7915.ko
// function: EfusePhysicalReadRegisters @ 0x1d21d4
// size: 496 bytes
//

void EfusePhysicalReadRegisters(int param_1,uint param_2,uint param_3,void *param_4)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 local_30;
  uint local_2c [2];
  
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  uVar5 = 0x70011008;
  iVar4 = 500;
  if (iVar2 != 2) {
    uVar5 = 0x580;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_30);
  uVar1 = (undefined1)local_30;
  uVar3 = local_30 >> 0x10 & 0xfc00 | param_2 & 0x3f0;
  local_30 = CONCAT22((short)uVar3,(undefined2)local_30);
  local_30 = CONCAT13((char)(uVar3 >> 8),(int3)CONCAT31(local_30._1_3_,uVar1)) & 0xffffff3f |
             0x40000040;
  local_2c[0] = local_30;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,local_30);
  while( true ) {
    if ((*(uint *)(param_1 + 0xa39f84) & 0x100) != 0) {
      return;
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_30);
    if ((local_30 & 0x40000000) == 0) break;
    RtmpusecDelay(2);
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
LAB_001d22b4:
      if ((3 < DebugLevel) &&
         (printk("EfuseCtrlStruc.field.EFSROM_AOUT = %x\n",local_30 & 0x3f), 3 < DebugLevel)) {
        printk("EfuseCtrlStruc.field.EFSROM_DOUT_VLD = %x\n",((local_30 >> 0x18) << 0x1a) >> 0x1f);
      }
      iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar2 == 2) {
        uVar3 = local_30 >> 0x18 & 0x20;
        if ((local_30 & 0x20000000) == 0) {
          if (param_3 >> 1 != 0) {
            do {
              *(undefined2 *)((int)param_4 + uVar3) = 0xffff;
              uVar3 = uVar3 + 4;
            } while (uVar3 != (param_3 >> 1) << 2);
          }
          if (2 < DebugLevel) {
            printk("EfuseCtrlStruc.field.EFSROM_DOUT_VLD = %x\n",
                   ((local_30 >> 0x18) << 0x1a) >> 0x1f);
          }
          return;
        }
      }
      iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar2 == 2) {
        iVar2 = (param_2 & 0xc) + 0x70011030;
      }
      else {
        iVar2 = 0x59c - (param_2 & 0xc);
      }
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar2,local_2c);
      local_2c[0] = local_2c[0] >> ((param_2 & 3) << 3);
      memcpy(param_4,local_2c,param_3);
      return;
    }
  }
  RtmpusecDelay(2);
  goto LAB_001d22b4;
}


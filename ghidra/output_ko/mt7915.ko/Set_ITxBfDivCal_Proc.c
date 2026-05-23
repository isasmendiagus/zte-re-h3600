// module: mt7915.ko
// function: Set_ITxBfDivCal_Proc @ 0xe5594
// size: 368 bytes
//

undefined4 Set_ITxBfDivCal_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_34;
  int local_30;
  uint local_2c [2];
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = 0;
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x1004,local_2c);
  local_34 = local_2c[0] & 0xfffffff3;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x1004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x1344,0x92b00);
  while( true ) {
    iVar3 = iVar3 + 1;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x1200,&local_34);
    local_34 = local_34 & 1;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x2130,&local_30);
    if (3 < DebugLevel) {
      printk("%s:: Wait until MAC 0x1200 bit0 and BBP 0x2130 become 0\n","Set_ITxBfDivCal_Proc");
    }
    RtmpusecDelay(1);
    if ((local_34 == 0) && (local_30 == 0)) break;
    if (iVar3 == 300) {
LAB_000e5674:
      if (0 < DebugLevel) {
        printk("%s:: Wait until MAC 0x1200 bit0 and BBP 0x2130 become 0 > 300 times\n",
               "Set_ITxBfDivCal_Proc");
      }
      return 0;
    }
  }
  if (iVar3 != 300) {
    uVar2 = os_str_tol(param_2,0,10);
    (**(code **)(iVar1 + 0x18))(param_1,uVar2,0);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x1004,local_2c[0]);
    return 1;
  }
  goto LAB_000e5674;
}


// module: mt7915.ko
// function: net_ad_read_write_eeprom @ 0x25d914
// size: 148 bytes
//

undefined4 net_ad_read_write_eeprom(int param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_12 [2];
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x606;
  }
  else {
    if (param_3 != 0) {
      chip_eeprom_read16(iVar1,*param_2,auStack_12);
      sys_ad_move_mem((void *)param_2[2],auStack_12,2);
      return 0;
    }
    iVar3 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
    if (*(code **)(iVar3 + 0xc) == (code *)0x0) {
      uVar2 = 0;
    }
    else {
      (**(code **)(iVar3 + 0xc))(iVar1,*param_2,*(undefined2 *)param_2[2]);
      uVar2 = 0;
    }
  }
  return uVar2;
}


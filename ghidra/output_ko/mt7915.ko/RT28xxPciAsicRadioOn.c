// module: mt7915.ko
// function: RT28xxPciAsicRadioOn @ 0x1c9018
// size: 224 bytes
//

undefined4 RT28xxPciAsicRadioOn(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 == 0 && *(char *)(param_1 + 0x286285) == '\x01') {
    uVar2 = 0;
  }
  else {
    AsicSendCommandToMcu(param_1,0x31,3,0,2,0);
    *(undefined1 *)(iVar1 + 0x90) = 0;
    uVar2 = chip_interrupt_enable(param_1);
    if (param_2 != 3) {
      uVar2 = 1;
    }
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xbfffffff;
    if (param_2 == 3) {
      iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      if ((*(int *)(param_1 + 0x286280) == 4) || (*(code **)(iVar1 + 0x34) == (code *)0x0)) {
        hc_reset_radio(param_1);
        uVar2 = 1;
      }
      else {
        (**(code **)(iVar1 + 0x34))(param_1,0);
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}


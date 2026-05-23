// module: mt7915.ko
// function: efuse_probe @ 0x1d35d0
// size: 176 bytes
//

undefined4 efuse_probe(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14;
  
  iVar1 = WaitForAsicReady();
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    "Set_IRR_TTGOnOff"[param_1 + 1] = '\0';
    iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    uVar2 = 0x70011000;
    if (iVar1 != 2) {
      uVar2 = 0x580;
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,&local_14);
    printk("%s: efuse = %x\n","efuse_probe",local_14);
    iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar1 == 2) {
      if ((local_14 & 0x40000000) == 0) {
        "Set_IRR_TTGOnOff"[param_1 + 1] = '\x01';
      }
      else {
        "Set_IRR_TTGOnOff"[param_1 + 1] = '\0';
      }
      uVar2 = 0;
    }
    else {
      uVar2 = 0;
      "Set_IRR_TTGOnOff"[param_1 + 1] = (byte)(local_14 >> 0x1f);
    }
  }
  return uVar2;
}


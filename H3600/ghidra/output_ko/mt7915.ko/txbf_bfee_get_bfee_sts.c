// module: mt7915.ko
// function: txbf_bfee_get_bfee_sts @ 0x84fd8
// size: 164 bytes
//

uint txbf_bfee_get_bfee_sts(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_1;
  if ((((DAT_005f352c != '\0') && (DAT_005f352d != '\0')) &&
      (uVar1 = (uint)DAT_005f352e, uVar1 != 0)) && (uVar1 <= param_1)) {
    uVar2 = uVar1;
  }
  if (4 < DebugLevel) {
    printk("[%s] bfee_sts=%u, valid=%u, bfer_cap_su=%u, num_snd_dimension=%u, new_bfee_sts=%u\n",
           "txbf_bfee_get_bfee_sts",param_1,DAT_005f352c,DAT_005f352d,DAT_005f352e,uVar2);
  }
  DAT_005f352c = 0;
  DAT_005f352d = 0;
  DAT_005f352e = 0;
  return uVar2;
}


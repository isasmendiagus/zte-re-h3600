// module: mt7915.ko
// function: set_vow_counter_test_band @ 0x47dfc
// size: 136 bytes
//

undefined4 set_vow_counter_test_band(undefined4 param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_c;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",&local_c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    MtCmdSetVoWCounterCtrl(param_1,3,local_c & 0xff);
    if (DebugLevel < 0) {
      uVar2 = 1;
    }
    else {
      printk("%s: band = %d\n","set_vow_counter_test_band",local_c);
      uVar2 = 1;
    }
  }
  return uVar2;
}


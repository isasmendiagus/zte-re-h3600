// module: mt7915.ko
// function: set_eFuseGetFreeBlockCount_Proc @ 0x1d3568
// size: 104 bytes
//

undefined4 set_eFuseGetFreeBlockCount_Proc(int param_1)

{
  undefined4 uVar1;
  undefined4 local_c [2];
  
  local_c[0] = 0;
  if ("Set_IRR_TTGOnOff"[param_1 + 1] == '\0') {
    uVar1 = 0;
  }
  else {
    eFuseGetFreeBlockCount(param_1,local_c);
    if (DebugLevel < 1) {
      uVar1 = 1;
    }
    else {
      printk("efuseFreeNumber = %d\n",local_c[0]);
      uVar1 = 1;
    }
  }
  return uVar1;
}


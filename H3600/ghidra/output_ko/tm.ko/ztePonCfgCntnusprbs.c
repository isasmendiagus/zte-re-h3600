// module: tm.ko
// function: ztePonCfgCntnusprbs @ 0x63dc8
// size: 96 bytes
//

undefined4
ztePonCfgCntnusprbs(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 extraout_r2;
  undefined8 uVar2;
  
  uVar2 = fpga_read_reg(0x10006);
  if ((int)uVar2 == 0) {
    gpondrvCfgCntnusprbs(param_1);
    printk("gpondrvCfgCntnusprbs\n");
    return 0;
  }
  if ((int)uVar2 == 1) {
    uVar1 = epondrvCfgContinuesTransPrbs
                      (param_1,(int)((ulonglong)uVar2 >> 0x20),extraout_r2,param_4);
    return uVar1;
  }
  printk("error:not pon mode\n");
  return 0xffffffff;
}


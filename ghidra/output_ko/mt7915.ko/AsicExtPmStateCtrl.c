// module: mt7915.ko
// function: AsicExtPmStateCtrl @ 0x13504c
// size: 380 bytes
//

undefined4 AsicExtPmStateCtrl(int param_1,int param_2,int param_3,undefined1 param_4)

{
  undefined2 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined2 uStack_32;
  undefined2 local_30;
  undefined2 uStack_2e;
  undefined4 local_2c;
  undefined4 local_24;
  
  if (param_2 == 0) {
    uVar4 = 0;
    if (-1 < DebugLevel) {
      printk("%s:wdev(NULL) for PM=%d, State=%d\n","AsicExtPmStateCtrl");
    }
  }
  else if (*(int *)(param_2 + 0x14) == 2) {
    iVar5 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar5 == 2) {
      uStack_32 = 0;
      local_30 = 0;
      uStack_2e = 0;
      local_2c = 0;
      uVar1 = 0;
      local_24 = 0;
      if (param_3 == 4) {
        uVar2 = HcGetBandByWdev(param_2);
        uStack_2e = *(undefined2 *)(param_2 + 0x21242c);
        uVar1 = *(undefined2 *)(param_2 + 0x40b0);
        uStack_32 = (undefined2)*(undefined4 *)(param_2 + 0x212428);
        local_30 = (undefined2)((uint)*(undefined4 *)(param_2 + 0x212428) >> 0x10);
        local_2c = CONCAT22(*(undefined2 *)(param_2 + 0x212456),*(short *)(param_2 + 0x2132e0) << 8)
        ;
        local_2c = CONCAT31(local_2c._1_3_,*(undefined1 *)(param_2 + 0x212455));
        local_24._0_2_ = CONCAT11(0x1e,*(undefined1 *)(param_2 + 0x29));
        uVar3 = HcGetWmmIdx(param_1,param_2);
        local_24 = CONCAT13(uVar3,CONCAT12(uVar2,(undefined2)local_24));
      }
      uVar4 = MtCmdExtPmStateCtrl(param_1,CONCAT22(uStack_32,CONCAT11(param_4,(char)param_3)),
                                  CONCAT22(uStack_2e,local_30),local_2c,uVar1,local_24);
    }
    else {
      AsicNotSupportFunc(param_1,"AsicExtPmStateCtrl");
      uVar4 = 0;
    }
  }
  else if (DebugLevel < 0) {
    uVar4 = 0;
  }
  else {
    printk("%s:wdev_type(0x%x)!=STA,return!\n","AsicExtPmStateCtrl");
    uVar4 = 0;
  }
  return uVar4;
}


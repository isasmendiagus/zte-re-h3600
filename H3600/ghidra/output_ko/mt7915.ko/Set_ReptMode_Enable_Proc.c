// module: mt7915.ko
// function: Set_ReptMode_Enable_Proc @ 0x3451c
// size: 224 bytes
//

undefined4
Set_ReptMode_Enable_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  iVar3 = *param_1;
  iVar4 = *(int *)(iVar3 + 0x38);
  if (iVar4 != 0x200) {
    if (iVar4 == 0x400) {
      uVar2 = HcGetBandInfoByChannel
                        (param_1,*(undefined1 *)
                                  ((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x2137b0 + 0x36db72));
      goto LAB_0003459c;
    }
    if (iVar4 != 0x100) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("(%s)No Support This Type\n","Set_ReptMode_Enable_Proc");
      return 0;
    }
  }
  uVar2 = HcGetBandInfoByChannel
                    (param_1,*(undefined1 *)
                              ((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2b7262));
LAB_0003459c:
  AsicSetReptFuncEnable(param_1,uVar1,uVar2);
  return 1;
}


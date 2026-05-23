// module: mt7915.ko
// function: Set_ApCli_Enable_Proc @ 0x30400
// size: 324 bytes
//

undefined4
Set_ApCli_Enable_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  if (*(int *)(*param_1 + 0x38) != 0x400) {
    return 0;
  }
  uVar4 = *(uint *)(*param_1 + 0x3c) & 0xff;
  piVar3 = param_1 + uVar4 * 0x84dec;
  iVar1 = RtmpOSNetDevIsUp(piVar3[0xdb6d6]);
  if (iVar1 != 1) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s : interface is not up, please do ifconfig %s up first\n","Set_ApCli_Enable_Proc",
           (param_1 + uVar4 * 0x84dec)[0xdb6d6],param_1 + uVar4 * 0x84dec,param_4);
    return 1;
  }
  sta_reset_owe_parameters(param_1,uVar4);
  iVar2 = os_str_tol(param_2,0,0x10);
  iVar1 = DebugLevel;
  (&DAT_00580e8d)[(int)piVar3] = iVar2 != 0;
  if (0 < iVar1) {
    printk("I/F(apcli%d) Set_ApCli_Enable_Proc::(enable = %d)\n",uVar4,iVar2 != 0,piVar3 + 0x1603a2,
           param_4);
  }
  ApCliIfDown(param_1);
  wlan_operate_set_prim_ch
            ((undefined *)((int)param_1 + (int)(&DAT_0036db58 + uVar4 * 0x2137b0)),
             *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x36db72));
  return 1;
}


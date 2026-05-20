// module: mt7915.ko
// function: Set_ApCli_PwrSet_Proc @ 0x2ff44
// size: 308 bytes
//

undefined4 Set_ApCli_PwrSet_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  
  if (*(int *)(*param_1 + 0x38) == 0x400) {
    uVar6 = *(uint *)(*param_1 + 0x3c);
    iVar3 = os_str_tol(param_2,0,0x10);
    iVar2 = DebugLevel;
    uVar6 = uVar6 & 0xff;
    *(bool *)((int)param_1 + (int)(s__RB_FULL__Free_Queue_List___00371ba4 + uVar6 * 0x2137b0 + 0x15)
             ) = iVar3 != 0;
    if (0 < iVar2) {
      printk("I/F(apcli%d) Set_ApCli_PwrSet_Proc::(PwrSaveSet = %d)\n",uVar6);
    }
    uVar7 = 0;
    while( true ) {
      uVar4 = HcGetMaxStaNum(param_1);
      uVar5 = uVar7 & 0xffff;
      if (uVar4 <= uVar5) break;
      if ((param_1 + uVar5 * 0x530 + 0x28748 != (int *)0x0) &&
         (param_1[uVar5 * 0x530 + 0x28748] == 2)) {
        bVar8 = *(char *)((int)param_1 + uVar6 * 0x2137b0 + 0x371bb9) != '\0';
        if (bVar8) {
          uVar1 = *(undefined1 *)((int)param_1 + uVar5 * 0x14c0 + 0xa289f);
        }
        else {
          uVar1 = *(undefined1 *)((int)param_1 + uVar5 * 0x14c0 + 0xa289f);
        }
        AppsApCliRTMPSendNullFrame(param_1,uVar1,1,param_1 + uVar5 * 0x530 + 0x28748,bVar8);
      }
      uVar7 = uVar7 + 1;
    }
    return 1;
  }
  return 0;
}


// module: mt7915.ko
// function: Set_AP_WscMode_Proc @ 0x314dc
// size: 488 bytes
//

undefined4 Set_AP_WscMode_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  int *piVar10;
  int unaff_r9;
  
  uVar9 = *(uint *)(*param_1 + 0x3c) & 0xff;
  if (*(int *)(*param_1 + 0x38) == 0x400) {
    if (DebugLevel < 3) {
      unaff_r9 = 1;
    }
    piVar10 = param_1 + uVar9 * 0x84dec + 0xdbb8f;
    if (2 < DebugLevel) {
      unaff_r9 = 1;
      printk("IF(apcli%d) Set_WscMode_Proc:: This command is from apcli interface now.\n",uVar9);
    }
  }
  else {
    piVar10 = param_1 + uVar9 * 0x160d + 0xae14b;
    if (DebugLevel < 3) {
      unaff_r9 = 0;
      piVar10 = param_1 + uVar9 * 0x160d + 0xae14b;
    }
    else {
      unaff_r9 = 0;
      printk("IF(ra%d) Set_WscMode_Proc:: This command is from ra interface now.\n",uVar9);
    }
  }
  iVar7 = os_str_tol(param_2,0,10);
  if (iVar7 - 1U < 2) {
    piVar10[1] = iVar7;
    if (iVar7 == 2) {
      WscGetRegDataPIN(param_1,piVar10[5],piVar10);
    }
    if (unaff_r9 == 0) {
      uVar1 = *(undefined1 *)((int)param_1 + uVar9 * 0x5834 + 0x2b7269);
      uVar2 = *(undefined1 *)((int)param_1 + uVar9 * 0x5834 + 0x2b726a);
      uVar6 = (undefined1)param_1[uVar9 * 0x160d + 0xadc9b];
      uVar3 = *(undefined1 *)((int)param_1 + uVar9 * 0x5834 + 0x2b726b);
      uVar4 = *(undefined1 *)((int)param_1 + uVar9 * 0x5834 + 0x2b726d);
      uVar5 = *(undefined1 *)((int)param_1 + uVar9 * 0x5834 + 0x2b726e);
    }
    else {
      uVar1 = *(undefined1 *)((int)param_1 + uVar9 * 0x2137b0 + 0x36db73);
      uVar3 = *(undefined1 *)((int)param_1 + uVar9 * 0x2137b0 + 0x36db75);
      uVar2 = (undefined1)param_1[uVar9 * 0x84dec + 0xdb6dd];
      uVar6 = *(undefined1 *)((int)param_1 + uVar9 * 0x2137b0 + 0x36db76);
      uVar4 = *(undefined1 *)((int)param_1 + uVar9 * 0x2137b0 + 0x36db77);
      uVar5 = (undefined1)param_1[uVar9 * 0x84dec + 0xdb6de];
    }
    if (DebugLevel < 3) {
      uVar8 = 1;
    }
    else {
      printk("IF(%02x:%02x:%02x:%02x:%02x:%02x) Set_WscMode_Proc::(WscMode=%d)\n",uVar1,uVar2,uVar3,
             uVar6,uVar4,uVar5,piVar10[1]);
      uVar8 = 1;
    }
  }
  else {
    if ((2 < DebugLevel) &&
       (printk("Set_WscMode_Proc:: Set failed!!(Set_WscMode_Proc=%s), WscConfStatus is 1 or 2\n",
               param_2), 2 < DebugLevel)) {
      printk("Set_WscMode_Proc:: WscMode is not changed (%d)\n",piVar10[1]);
    }
    uVar8 = 0;
  }
  return uVar8;
}


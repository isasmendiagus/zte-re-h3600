// module: mt7915.ko
// function: DfsCacNormalStart @ 0x23536c
// size: 364 bytes
//

void DfsCacNormalStart(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == 0) {
    return;
  }
  iVar3 = *(int *)(param_2 + 0x3fe4);
  if (iVar3 == 0) {
    return;
  }
  uVar1 = HcGetBandByWdev(param_2);
  if (1 < uVar1) {
    return;
  }
  if ((*(char *)(param_1 + 0x795075) == '\0') &&
     (iVar2 = param_1 + 0x795000 + uVar1,
     iVar2 = DfsCacRestrictBand(param_1,*(undefined1 *)(iVar2 + 0x134),
                                *(undefined1 *)(iVar2 + 0x130),
                                *(undefined1 *)(((param_1 + 0x795000) - uVar1) + 0x131)), iVar2 != 0
     )) {
    if (*(char *)(param_1 + 0x7953f1) == '\0') {
      *(undefined2 *)(iVar3 + 8) = 0x25d;
      goto LAB_002353e8;
    }
  }
  else if (*(char *)(param_1 + 0x7953f1) == '\0') {
    *(undefined2 *)(iVar3 + 8) = 0x41;
    goto LAB_002353e8;
  }
  *(undefined2 *)(iVar3 + 8) = *(undefined2 *)(param_1 + 0x7953f4);
LAB_002353e8:
  if (param_3 == 2 && *(char *)(iVar3 + 4) == '\x02') {
    if (0 < DebugLevel) {
      printk("[%s] CAC %d seconds start . Disable MAC TX\n","DfsCacNormalStart",
             *(undefined2 *)(iVar3 + 8));
    }
    mtRddControl(param_1,0x32,uVar1,0,0);
  }
  else if (param_3 == 0 && *(char *)(iVar3 + 4) == '\0') {
    iVar3 = RadarChannelCheck(param_1,*(undefined1 *)(param_2 + 0x1a));
    if ((iVar3 != 0) && (0 < DebugLevel)) {
      printk("[%s] Normal start. Enable MAC TX\n","DfsCacNormalStart");
    }
    mtRddControl(param_1,0x34,uVar1,0,0);
  }
  return;
}


// module: mt7915.ko
// function: hqa_calibration_test_mode @ 0x24aaec
// size: 284 bytes
//

undefined4 hqa_calibration_test_mode(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int local_1c;
  uint local_18;
  undefined1 auStack_14 [8];
  
  local_1c = param_2 + 0xc;
  local_18 = 0;
  FUN_002474f4(1,4,&local_1c,&local_18);
  FUN_002474f4(1,4,&local_1c,auStack_14);
  iVar3 = (uint)*(byte *)(param_1 + 0x4cc) * 0xd18;
  if (param_1 + iVar3 + 0x4e0 == 0) {
    printk("%s: Mode = test_config is null!!!\n","hqa_calibration_test_mode");
  }
  else if (local_18 == 0) {
    uVar2 = *(uint *)(param_1 + iVar3 + 0x4e0);
    *(uint *)(param_1 + iVar3 + 0x4e0) = uVar2 & 0xfffffd7f;
    if (uVar2 == 1) {
      printk("%s: Mode = %d bypass=%d !!!\n","hqa_calibration_test_mode",0,1);
      uVar1 = 0;
      goto LAB_0024ab88;
    }
  }
  else if ((local_18 == 1) || (local_18 == 2)) {
    *(uint *)(param_1 + iVar3 + 0x4e0) = *(uint *)(param_1 + iVar3 + 0x4e0) | 0x200;
  }
  else {
    printk("%s: Mode = %d error!!!\n","hqa_calibration_test_mode");
  }
  uVar1 = mt_serv_calibration_test_mode(param_1,local_18 & 0xff);
LAB_0024ab88:
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}


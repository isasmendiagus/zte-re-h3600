// module: mt7915.ko
// function: muru_update_he_cfg @ 0x23f728
// size: 336 bytes
//

void muru_update_he_cfg(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar4 = *(int *)(param_1 + 0x7959b8);
  if (iVar4 != 0) {
    DAT_005f5932 = (undefined1)iVar4;
    DAT_005f5924 = DAT_005f5924 | 0x10;
    DAT_005f5928 = DAT_005f5928 | 0x10;
    DAT_005f5a44 = DAT_005f5932;
  }
  iVar2 = *(int *)(param_1 + 0x7959b0);
  if (iVar2 != 0) {
    DAT_005f592c = (undefined1)iVar2;
    DAT_005f5920 = DAT_005f5920 | 1;
  }
  iVar3 = *(int *)(param_1 + 0x7959b4);
  if (iVar3 != 0) {
    DAT_005f592d = (undefined1)iVar3;
    DAT_005f5920 = DAT_005f5920 | 2;
  }
  bVar1 = iVar3 != 0 || (iVar2 != 0 || iVar4 != 0);
  if (*(int *)(param_1 + 0x7959bc) == 0) {
    if (0 < DebugLevel) goto LAB_0023f868;
LAB_0023f854:
    if (!bVar1) {
      uVar5 = 1;
      goto LAB_0023f820;
    }
  }
  else {
    if (*(int *)(param_1 + 0x7959bc) == 8) {
      DAT_005f5a4e = 1;
    }
    else {
      DAT_005f5a4e = 2;
    }
    DAT_005f5928 = DAT_005f5928 | 0x100;
    if (0 < DebugLevel) {
      bVar1 = true;
LAB_0023f868:
      printk("set muru_update_he_cfg()!!!!\n");
      goto LAB_0023f854;
    }
  }
  iVar4 = wifi_test_muru_set_manual_config(param_1,&DAT_005f5920);
  uVar5 = 0;
  if (iVar4 != 0) {
    uVar5 = 1;
  }
LAB_0023f820:
  if (DebugLevel < 4) {
    return;
  }
  printk("%s:(Ret = %d_\n","muru_update_he_cfg",uVar5);
  return;
}


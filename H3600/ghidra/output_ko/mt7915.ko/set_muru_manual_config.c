// module: mt7915.ko
// function: set_muru_manual_config @ 0x23f0c0
// size: 612 bytes
//

undefined4 set_muru_manual_config(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  
  if (*param_2 != '\0') {
    uVar1 = strcmp("dl_init",param_2);
    if (uVar1 == 0) {
      DAT_005f592c = DAT_005f592c & 0xf7;
      DAT_005f592d = DAT_005f592d & 0xfe;
      DAT_005f5920 = DAT_005f5920 & 0xfffffffc;
      _LANCHOR1 = uVar1;
      DAT_005f5924 = uVar1;
      os_zero_mem(&DAT_005f5932,0x112);
      if (*(int *)(param_1 + 0x7959b8) != 0) {
        DAT_005f5932 = (undefined1)*(int *)(param_1 + 0x7959b8);
        DAT_005f5924 = DAT_005f5924 | 0x10;
      }
      if (*(int *)(param_1 + 0x7959b0) != 0) {
        DAT_005f592c = (byte)*(int *)(param_1 + 0x7959b0);
        DAT_005f5920 = DAT_005f5920 | 1;
      }
      if (*(int *)(param_1 + 0x7959b4) != 0) {
        uVar4 = 1;
        DAT_005f592d = (byte)*(int *)(param_1 + 0x7959b4);
        DAT_005f5920 = DAT_005f5920 | 2;
        goto LAB_0023f15c;
      }
    }
    else {
      uVar1 = strcmp("ul_init",param_2);
      if (uVar1 == 0) {
        DAT_005f592c = DAT_005f592c & 0xfb;
        DAT_005f592d = DAT_005f592d & 0xfd;
        DAT_005f5920 = DAT_005f5920 & 0xfffffffc;
        DAT_005f591c = uVar1;
        DAT_005f5928 = uVar1;
        os_zero_mem(&DAT_005f5a44,0xec);
        if (*(int *)(param_1 + 0x7959b8) != 0) {
          DAT_005f5a44 = (undefined1)*(int *)(param_1 + 0x7959b8);
          DAT_005f5928 = DAT_005f5928 | 0x10;
        }
        if (*(int *)(param_1 + 0x7959b0) != 0) {
          DAT_005f592c = (byte)*(int *)(param_1 + 0x7959b0);
          DAT_005f5920 = DAT_005f5920 | 1;
        }
        if (*(int *)(param_1 + 0x7959b4) != 0) {
          DAT_005f592d = (byte)*(int *)(param_1 + 0x7959b4);
          DAT_005f5920 = DAT_005f5920 | 2;
        }
        if (*(int *)(param_1 + 0x7959bc) != 0) {
          uVar4 = 1;
          if (*(int *)(param_1 + 0x7959bc) == 8) {
            DAT_005f5a4e = 1;
          }
          else {
            DAT_005f5a4e = 2;
          }
          DAT_005f5928 = DAT_005f5928 | 0x100;
          goto LAB_0023f15c;
        }
      }
      else {
        iVar2 = strcmp("update",param_2);
        if (iVar2 == 0) {
          uVar4 = wifi_test_muru_set_manual_config(param_1,&DAT_005f5920);
          goto LAB_0023f15c;
        }
        puVar3 = (undefined1 *)rtstrchr(param_2,0x3a);
        if (puVar3 != (undefined1 *)0x0) {
          *puVar3 = 0;
          if ((puVar3 + 1 != (undefined1 *)0x0 && *param_2 != '\0') && (puVar3[1] != '\0')) {
            uVar4 = muru_parse_cmd_param_muru_manual_config
                              (param_1,param_2,puVar3 + 1,&DAT_005f5920);
            goto LAB_0023f15c;
          }
        }
      }
    }
  }
  uVar4 = 1;
LAB_0023f15c:
  if (0 < DebugLevel) {
    printk("%s: cmd sub-group = %s, Ret = %d\n","set_muru_manual_config",param_2,uVar4);
  }
  return uVar4;
}


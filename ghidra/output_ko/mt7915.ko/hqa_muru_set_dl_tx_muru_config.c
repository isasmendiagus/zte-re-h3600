// module: mt7915.ko
// function: hqa_muru_set_dl_tx_muru_config @ 0x23ecac
// size: 496 bytes
//

undefined4
hqa_muru_set_dl_tx_muru_config(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  
  if (*param_2 != '\0') {
    uVar1 = strcmp("init",param_2);
    if (uVar1 == 0) {
      DAT_005f5920 = DAT_005f5920 & 0xfffffffc;
      DAT_005f592c = DAT_005f592c & 0xf7;
      DAT_005f592d = DAT_005f592d & 0xfe;
      _LANCHOR1 = uVar1;
      DAT_005f5924 = uVar1;
      os_zero_mem(&DAT_005f5932,0x112);
      if (*(int *)(param_1 + 0x7959b8) != 0) {
        DAT_005f5932 = (sbyte)*(int *)(param_1 + 0x7959b8);
        DAT_005f5924 = DAT_005f5924 | 0x10;
      }
      if (*(int *)(param_1 + 0x7959b0) != 0) {
        DAT_005f592c = (byte)*(int *)(param_1 + 0x7959b0);
        DAT_005f5920 = DAT_005f5920 | 1;
      }
      if (*(int *)(param_1 + 0x7959b4) != 0) {
        DAT_005f592d = (byte)*(int *)(param_1 + 0x7959b4);
        DAT_005f5920 = DAT_005f5920 | 2;
        uVar4 = 1;
        goto LAB_0023ed88;
      }
    }
    else {
      iVar2 = strcmp("update",param_2);
      if (iVar2 == 0) {
        if (_LANCHOR1 == 0) {
          uVar4 = wifi_test_muru_set_manual_config(param_1,&DAT_005f5920);
        }
        else {
          if (DebugLevel < 1) {
            return 1;
          }
          uVar4 = 1;
          printk("%s:cmd=update, target_updated_user_bmp=0x%x, not_yet_updated_user_bmp:0x%x\n",
                 "hqa_muru_set_dl_tx_muru_config",(1 << DAT_005f5932) + -1,_LANCHOR1,param_4);
        }
        goto LAB_0023ed88;
      }
      puVar3 = (undefined1 *)rtstrchr(param_2,0x3a);
      if (puVar3 != (undefined1 *)0x0) {
        *puVar3 = 0;
        if ((puVar3 + 1 != (undefined1 *)0x0 && *param_2 != '\0') && (puVar3[1] != '\0')) {
          uVar4 = hqa_muru_parse_cmd_param_dltx(param_1,param_2,puVar3 + 1,&DAT_005f5920);
          goto LAB_0023ed88;
        }
      }
    }
  }
  uVar4 = 1;
LAB_0023ed88:
  if (0 < DebugLevel) {
    printk("%s: cmd sub-group = %s, Ret = %d\n","hqa_muru_set_dl_tx_muru_config",param_2,uVar4,
           param_4);
  }
  return uVar4;
}


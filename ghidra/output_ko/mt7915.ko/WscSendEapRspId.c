// module: mt7915.ko
// function: WscSendEapRspId @ 0x1e1da4
// size: 692 bytes
//

void WscSendEapRspId(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined2 unaff_r9;
  int local_84;
  undefined4 local_80;
  undefined1 local_7c;
  undefined1 local_7b;
  undefined2 local_7a;
  undefined1 local_78;
  undefined1 local_77;
  undefined2 local_76;
  undefined1 local_74;
  undefined4 local_73;
  undefined2 local_6f;
  undefined4 local_6d;
  undefined2 local_69;
  undefined2 local_67;
  char local_65 [30];
  undefined4 local_47;
  char local_43 [31];
  
  local_84 = 0;
  local_80 = 0;
  local_47._0_1_ = 'W';
  local_47._1_1_ = 'F';
  local_47._2_1_ = 'A';
  local_47._3_1_ = '-';
  builtin_strncpy(local_43,"SimpleConfig-Registrar-1-0",0x1b);
  builtin_strncpy(local_65,"WFA-SimpleConfig-Enrollee-1-",0x1c);
  iVar2 = param_3[0xa7b];
  local_65[0x1c] = '0';
  local_65[0x1d] = '\0';
  __memzero(&local_73,0xe);
  if (2 < DebugLevel) {
    printk("-----> WscSendEapRspId\n");
  }
  local_6d = *(undefined4 *)(iVar2 + 0x1b);
  local_73 = *(undefined4 *)(param_2 + 0xec);
  iVar1 = *param_3;
  local_69 = *(undefined2 *)(iVar2 + 0x1f);
  local_6f = *(undefined2 *)(param_2 + 0xf0);
  if (iVar1 == 1) {
    unaff_r9 = 0x2200;
  }
  local_67 = EAPOL;
  if (iVar1 != 1) {
    if (iVar1 == 4) {
      unaff_r9 = 0x2300;
    }
    else {
      unaff_r9 = 0;
    }
  }
  __memzero(&local_7c,4);
  local_7c = 1;
  local_7b = 0;
  local_7a = unaff_r9;
  __memzero(&local_78,5);
  local_77 = (undefined1)param_3[0x714];
  local_74 = 1;
  local_78 = 2;
  local_76 = unaff_r9;
  os_alloc_mem(0,&local_84,0x800);
  if (local_84 == 0) {
    return;
  }
  iVar2 = *param_3;
  local_80 = 0;
  if (iVar2 == 4) {
    MakeOutgoingFrame(local_84,&local_80,4,&local_7c,5,&local_78,0x1e,&local_47,0xffffffff);
LAB_001e1f80:
    RTMPToWirelessSta(param_3[0xa7a],param_2,&local_73,0xe,local_84,local_80,1);
    *(undefined1 *)((int)param_3 + 0x1c53) = 0;
    if ((char)param_3[0x9f2] == '\0') {
      *(undefined1 *)(param_3 + 0x9f2) = 1;
      RTMPSetTimer(param_3 + 0x9f3,5000);
    }
LAB_001e1fc0:
    if (local_84 == 0) goto LAB_001e1f38;
  }
  else {
    if (iVar2 == 1) {
      MakeOutgoingFrame(local_84,&local_80,4,&local_7c,5,&local_78,0x1d,local_65,0xffffffff);
      goto LAB_001e1f80;
    }
    if (2 < DebugLevel) {
      printk("WscConfMode(%d) is not WSC_REGISTRAR nor WSC_ENROLLEE.\n",iVar2);
      goto LAB_001e1fc0;
    }
  }
  os_free_mem();
LAB_001e1f38:
  if (2 < DebugLevel) {
    printk("<----- WscSendEapRspId\n");
  }
  return;
}


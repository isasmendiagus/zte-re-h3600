// module: mt7915.ko
// function: HQA_MUSetGroup @ 0x2798a8
// size: 1136 bytes
//

undefined4 HQA_MUSetGroup(undefined4 param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined1 local_5c [4];
  void *local_58;
  undefined2 local_52;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 local_42;
  undefined1 local_41;
  undefined1 local_40;
  undefined1 local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  
  uVar1 = *(ushort *)(param_3 + 8);
  local_58 = (void *)(param_3 + 0xc);
  FUN_00276034(1,4,&local_58,local_5c);
  local_52 = local_5c._0_2_;
  FUN_00276034(1,4,&local_58,local_5c);
  local_50 = local_5c[0];
  local_5c[0] = local_50;
  FUN_00276034(1,4,&local_58,local_5c);
  local_4f = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_4e = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_4d = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_4c = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_4b = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_4a = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_49 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_48 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_47 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_46 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_45 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_44 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_43 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_42 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_41 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_40 = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_3f = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_3e = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_3d = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_3c = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_3b = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  local_3a = local_5c[0];
  FUN_00276034(1,4,&local_58,local_5c);
  pvVar2 = local_58;
  local_39 = local_5c[0];
  memmove(&local_38,local_58,6);
  memmove(&local_32,(void *)((int)pvVar2 + 6),6);
  memmove(&local_2c,(void *)((int)pvVar2 + 0xc),6);
  local_58 = (void *)((int)pvVar2 + 0x12);
  memmove(&local_26,(void *)((int)pvVar2 + 0x12),6);
  uVar3 = hqa_wifi_test_mu_group_set(param_1,&local_52);
  if ((0 < DebugLevel) &&
     (printk("%s: len:%x\n","HQA_MUSetGroup",uVar1 << 8 | uVar1 >> 8), 0 < DebugLevel)) {
    printk("0:%02x:%02x:%02x:%02x:%02x:%02x\n",local_38,local_37,local_36,local_35,local_34,local_33
          );
    if (0 < DebugLevel) {
      printk("1:%02x:%02x:%02x:%02x:%02x:%02x\n",local_32,local_31,local_30,local_2f,local_2e,
             local_2d);
      if (0 < DebugLevel) {
        printk("2:%02x:%02x:%02x:%02x:%02x:%02x\n",local_2c,local_2b,local_2a,local_29,local_28,
               local_27);
        if (0 < DebugLevel) {
          printk("3:%02x:%02x:%02x:%02x:%02x:%02x\n",local_26,local_25,local_24,local_23,local_22,
                 local_21);
        }
      }
    }
  }
  FUN_0026cdd0(param_3,param_2,2,uVar3);
  return uVar3;
}


// module: mt7915.ko
// function: HQA_MUTriggerTx @ 0x279734
// size: 368 bytes
//

undefined4 HQA_MUTriggerTx(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  undefined4 uVar2;
  undefined4 local_44;
  int local_40;
  undefined1 local_3c [4];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  uVar1 = *(ushort *)(param_3 + 8);
  local_40 = param_3 + 0xc;
  FUN_00276034(1,4,&local_40,&local_44);
  uVar2 = local_44;
  FUN_00276034(1,4,&local_40,&local_44);
  local_3c[0] = (undefined1)local_44;
  FUN_00276034(1,4,&local_40,&local_44);
  local_38 = local_44;
  FUN_00276034(1,4,&local_40,&local_44);
  local_34 = local_44;
  FUN_00276034(1,4,&local_40,&local_44);
  local_30 = local_44;
  FUN_00276034(1,4,&local_40,&local_44);
  local_2c = local_44;
  FUN_00276034(1,4,&local_40,&local_44);
  local_28 = local_44;
  FUN_00276034(1,4,&local_40,&local_44);
  *(char *)(param_1 + 0xa3ae36) = (char)uVar2;
  local_24 = local_44;
  uVar2 = hqa_wifi_test_mu_trigger_mu_tx(param_1,local_3c);
  if (0 < DebugLevel) {
    printk("%s: len:%x\n","HQA_MUTriggerTx",uVar1 << 8 | uVar1 >> 8);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar2);
  return uVar2;
}


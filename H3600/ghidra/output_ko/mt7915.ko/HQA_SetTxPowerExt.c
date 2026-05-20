// module: mt7915.ko
// function: HQA_SetTxPowerExt @ 0x276914
// size: 344 bytes
//

int HQA_SetTxPowerExt(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  int local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  local_4c = param_3 + 0xc;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_SetTxPowerExt");
  }
  FUN_00276034(1,4,&local_4c,&local_48);
  iVar1 = param_1 + 0xa3a000;
  FUN_00276034(1,4,&local_4c,&local_40);
  FUN_00276034(1,4,&local_4c,&local_44);
  FUN_00276034(1,4,&local_4c,&local_3c);
  FUN_00276034(1,4,&local_4c,&local_38);
  *(char *)(param_1 + 0xa3ae36) = (char)local_3c;
  os_zero_mem(&local_34,0x14);
  pcVar3 = *(code **)(iVar2 + 0x40);
  if (pcVar3 == (code *)0x0) {
    iVar1 = 1;
  }
  local_34 = local_38;
  local_30 = local_48;
  local_2c = local_44;
  local_28 = local_40;
  local_24 = local_3c;
  if (pcVar3 != (code *)0x0) {
    iVar1 = (*pcVar3)(param_1,local_38,local_48,local_44,local_40,local_3c);
  }
  FUN_0026cdd0(param_3,param_2,2,iVar1);
  return iVar1;
}


// module: mt7915.ko
// function: HQA_DevInfoUpdate @ 0x2764a0
// size: 272 bytes
//

undefined4 HQA_DevInfoUpdate(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  
  local_2c = param_3 + 0xc;
  iVar3 = *(int *)(param_1 + 0xa39fd4);
  local_34 = 0;
  local_30 = 0;
  FUN_00276034(1,4,&local_2c,&local_34);
  FUN_00276034(1,4,&local_2c,&local_30);
  FUN_00276034(0,6,&local_2c,&local_26);
  iVar1 = DebugLevel;
  *(char *)(param_1 + 0xa3ae36) = (char)local_34;
  if (2 < iVar1) {
    printk("%s: Band:%d OwnMacIdx:%d Bssid:%02x:%02x:%02x:%02x:%02x:%02x\n","HQA_DevInfoUpdate",
           local_34,local_30,local_26,local_25,local_24,local_23,local_22,local_21);
  }
  uVar2 = (**(code **)(iVar3 + 0xfc))(param_1,local_30,&local_26);
  FUN_0026cdd0(param_3,param_2,2,uVar2);
  return uVar2;
}


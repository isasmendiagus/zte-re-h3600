// module: mt7915.ko
// function: HQA_BssInfoUpdate @ 0x2765b4
// size: 260 bytes
//

undefined4 HQA_BssInfoUpdate(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
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
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  local_34 = 0;
  local_30 = 0;
  FUN_00276034(1,4,&local_2c,&local_34);
  FUN_00276034(1,4,&local_2c,&local_30);
  FUN_00276034(0,6,&local_2c,&local_26);
  if (2 < DebugLevel) {
    printk("%s: BssIdx:%d Bssid:%02x:%02x:%02x:%02x:%02x:%02x\n","HQA_BssInfoUpdate",local_30,
           local_26,local_25,local_24,local_23,local_22,local_21);
  }
  uVar1 = (**(code **)(iVar2 + 0xf8))(param_1,local_34,local_30,&local_26);
  FUN_0026cdd0(param_3,param_2,2,uVar1);
  return uVar1;
}


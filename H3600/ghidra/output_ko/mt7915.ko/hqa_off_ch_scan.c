// module: mt7915.ko
// function: hqa_off_ch_scan @ 0x2761c8
// size: 252 bytes
//

undefined4 hqa_off_ch_scan(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int local_38;
  undefined4 local_34;
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [4];
  undefined1 auStack_28 [4];
  undefined1 auStack_24 [4];
  undefined1 auStack_20 [4];
  undefined1 auStack_1c [8];
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  local_38 = param_3 + 0xc;
  os_zero_mem(&local_34,0x1c);
  FUN_00276034(1,4,&local_38,&local_34);
  FUN_00276034(1,4,&local_38,auStack_30);
  FUN_00276034(1,4,&local_38,auStack_2c);
  FUN_00276034(1,4,&local_38,auStack_28);
  FUN_00276034(1,4,&local_38,auStack_24);
  FUN_00276034(1,4,&local_38,auStack_20);
  FUN_00276034(1,4,&local_38,auStack_1c);
  uVar1 = (**(code **)(iVar2 + 0x11c))(param_1,&local_34);
  *(undefined4 *)(param_3 + 0xe) = local_34;
  FUN_0026cdd0(param_3,param_2,6,uVar1);
  return uVar1;
}


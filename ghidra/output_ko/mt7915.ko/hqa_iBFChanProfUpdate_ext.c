// module: mt7915.ko
// function: hqa_iBFChanProfUpdate_ext @ 0x278828
// size: 528 bytes
//

undefined4 hqa_iBFChanProfUpdate_ext(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  char *local_2c [2];
  
  local_60 = param_3 + 0xc;
  uVar2 = 0;
  local_5c = 0;
  os_alloc_mem(param_1,local_2c,0x200);
  if (local_2c[0] == (char *)0x0) {
    uVar2 = 3;
  }
  else {
    FUN_00276034(1,4,&local_60,&local_5c);
    FUN_00276034(1,4,&local_60,&local_58);
    FUN_00276034(1,4,&local_60,&local_54);
    FUN_00276034(1,4,&local_60,&local_50);
    FUN_00276034(1,4,&local_60,&local_4c);
    FUN_00276034(1,4,&local_60,&local_48);
    FUN_00276034(1,4,&local_60,&local_44);
    FUN_00276034(1,4,&local_60,&local_40);
    FUN_00276034(1,4,&local_60,&local_3c);
    FUN_00276034(1,4,&local_60,&local_38);
    FUN_00276034(1,4,&local_60,&local_34);
    FUN_00276034(1,4,&local_60,&local_30);
    __memzero(local_2c[0],0x200);
    sprintf(local_2c[0],"%03x:%03x:%03x:%03x:%03x:%03x:%03x:%03x:%03x:%03x:%03x",local_58,local_54,
            local_50,local_4c,local_48,local_44,local_40,local_3c,local_38,local_34,local_30);
    iVar1 = SetATETxBfChanProfileUpdate(param_1,local_2c[0]);
    if (iVar1 == 0) {
      if (DebugLevel < 0) {
        uVar2 = 1;
      }
      else {
        uVar2 = 1;
        printk(" SetATETxBfChanProfileUpdate is failed!!\n");
      }
    }
    else {
      os_free_mem(local_2c[0]);
      *(undefined4 *)(param_3 + 0xe) = local_5c;
    }
  }
  FUN_0026cdd0(param_3,param_2,6,uVar2);
  return uVar2;
}


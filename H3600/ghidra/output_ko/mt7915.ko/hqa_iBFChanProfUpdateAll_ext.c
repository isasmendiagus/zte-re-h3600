// module: mt7915.ko
// function: hqa_iBFChanProfUpdateAll_ext @ 0x2779dc
// size: 304 bytes
//

undefined4 hqa_iBFChanProfUpdateAll_ext(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_20;
  undefined4 local_1c;
  uint local_18;
  undefined1 auStack_14 [4];
  
  local_20 = param_3 + 0xc;
  local_1c = 0;
  FUN_00276034(1,4,&local_20,&local_1c);
  FUN_00276034(1,4,&local_20,&local_18);
  FUN_00276034(1,4,&local_20,auStack_14);
  FUN_00276034(1,4,&local_20,auStack_14);
  FUN_00276034(1,4,&local_20,auStack_14);
  FUN_00276034(1,4,&local_20,auStack_14);
  iVar1 = TxBfProfileDataWrite20MAll(param_1,local_18 & 0xff,local_20);
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
    if (0 < DebugLevel) {
      printk("%s: str:%d\n","hqa_iBFChanProfUpdateAll_ext",local_18);
    }
    uVar2 = 0;
    *(undefined4 *)(param_3 + 0xe) = local_1c;
  }
  FUN_0026cdd0(param_3,param_2,6,uVar2);
  return uVar2;
}


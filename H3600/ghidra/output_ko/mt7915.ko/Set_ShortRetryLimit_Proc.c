// module: mt7915.ko
// function: Set_ShortRetryLimit_Proc @ 0xe0600
// size: 92 bytes
//

undefined4
Set_ShortRetryLimit_Proc
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  
  uVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  AsicSetRetryLimit(param_1,1,uVar1);
  if (2 < DebugLevel) {
    printk("IF Set_ShortRetryLimit_Proc::(ShortRetryLimit=0x%x)\n",uVar1);
  }
  return 1;
}


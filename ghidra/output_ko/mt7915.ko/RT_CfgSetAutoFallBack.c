// module: mt7915.ko
// function: RT_CfgSetAutoFallBack @ 0xb8cc8
// size: 96 bytes
//

undefined4
RT_CfgSetAutoFallBack(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  cVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  AsicSetAutoFallBack(param_1,cVar1 != '\0');
  if (2 < DebugLevel) {
    printk("RT_CfgSetAutoFallBack::(AutoFallBack=%d)\n",cVar1 != '\0');
  }
  return 1;
}


// module: mt7915.ko
// function: set_apcli_sae_group_proc @ 0x6b260
// size: 192 bytes
//

undefined4
set_apcli_sae_group_proc(int *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  bool bVar3;
  
  if (*param_2 != '\0') {
    iVar2 = *(int *)(*param_1 + 0x3c);
    bVar1 = os_str_tol(param_2,0,10,*param_1,param_4);
    if (bVar1 - 0x13 < 2) {
      bVar3 = DebugLevel < 0;
      *(byte *)((int)param_1 + iVar2 * 0x2137b0 + 0x580eeb) = bVar1;
      if (bVar3) {
        return 1;
      }
      printk("[SAE]%s:: Set group=%d \n","set_apcli_sae_group_proc");
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("[SAE]%s:: group=%d not supported\n","set_apcli_sae_group_proc");
    }
  }
  return 0;
}


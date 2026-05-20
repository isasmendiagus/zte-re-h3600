// module: mt7915.ko
// function: Set_AP_WscSecurityMode_Proc @ 0x27e58
// size: 336 bytes
//

undefined4 Set_AP_WscSecurityMode_Proc(int *param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*param_1 + 0x3c);
  iVar1 = strcmp(param_2,"0");
  if (iVar1 == 0) {
    param_1[(uVar2 & 0xff) * 0x160d + 0xaec67] = 0;
  }
  else {
    iVar1 = strcmp(param_2,"1");
    if (iVar1 == 0) {
      param_1[(uVar2 & 0xff) * 0x160d + 0xaec67] = 1;
    }
    else {
      iVar1 = strcmp(param_2,"2");
      if (iVar1 == 0) {
        param_1[(uVar2 & 0xff) * 0x160d + 0xaec67] = 2;
      }
      else {
        iVar1 = strcmp(param_2,"3");
        if (iVar1 != 0) {
          return 0;
        }
        param_1[(uVar2 & 0xff) * 0x160d + 0xaec67] = 3;
      }
    }
  }
  if (DebugLevel < 3) {
    return 1;
  }
  printk("IF(ra%d) Set_WscSecurityMode_Proc::(WscSecurityMode=%d)\n",uVar2 & 0xff,
         param_1[(uVar2 & 0xff) * 0x160d + 0xaec67]);
  return 1;
}


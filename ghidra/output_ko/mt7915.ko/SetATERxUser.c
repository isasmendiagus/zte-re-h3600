// module: mt7915.ko
// function: SetATERxUser @ 0x261464
// size: 356 bytes
//

bool SetATERxUser(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0xa39fd4);
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetATERxUser");
      return false;
    }
    return false;
  }
  iVar2 = rstrtok(param_2,&_LC2);
  if (iVar2 == 0) {
    uVar1 = 0;
    uVar3 = 0;
  }
  else {
    uVar3 = simple_strtol(iVar2,0,10);
    uVar3 = uVar3 & 0xff;
    iVar2 = rstrtok(0,&_LC2);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = simple_strtol(iVar2,0,0x10);
      iVar2 = rstrtok(0,&_LC2);
      if (iVar2 != 0) {
        if (-1 < DebugLevel) {
          printk("%s(): Number of parameters exceed expectation !!\n","SetATERxUser");
          return false;
        }
        return false;
      }
    }
  }
  if (0 < DebugLevel) {
    printk("%s(): band_idx: %d, user_idx: %d\n","SetATERxUser",uVar3,uVar1);
  }
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined2 *)(uVar3 * 0xd18 + iVar2 + 0x1160) = uVar1;
  iVar4 = (**(code **)(iVar4 + 0x28))(param_1,uVar3,uVar1);
  return iVar4 == 0;
}


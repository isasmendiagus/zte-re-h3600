// module: mt7915.ko
// function: BeaconTransmitRequired @ 0xb313c
// size: 524 bytes
//

bool BeaconTransmitRequired(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = *(int *)(param_2 + 0x14);
  if ((iVar2 - 0x10U & 0xffffffef) == 0 || (iVar2 == 4 || iVar2 == 1)) {
    if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
      if (DebugLevel < 1) {
        return false;
      }
      goto LAB_000b3228;
    }
    if ((*(int *)(param_1 + 0xa77bb4) != 1) ||
       ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)) {
      if (param_2 == -0x948) {
        return false;
      }
      if (*(int *)(param_2 + 0x954) == 0) {
        if (DebugLevel < 4) {
          return false;
        }
        printk("%s(): no BeaconPkt\n","BeaconTransmitRequired",iVar2,DebugLevel,param_4);
        return false;
      }
      if (*(char *)(param_2 + 0x988) == '\x02') {
        if ((param_3 == 1) && (*(char *)(iVar1 + 0x14e) == '\0')) {
          if (DebugLevel < 0) {
            return false;
          }
          printk("%s(): Wrong BCN update method (%d)\n","BeaconTransmitRequired",2,DebugLevel,
                 param_4);
          return false;
        }
      }
      else if (param_3 == 0) {
        if (DebugLevel < 0) {
          return false;
        }
        printk("%s(): Wrong BCN update method (%d)\n","BeaconTransmitRequired",
               *(char *)(param_2 + 0x988),DebugLevel,param_4);
        return false;
      }
      return *(char *)(param_2 + 0x950) == '\x01';
    }
    if (DebugLevel < 1) {
      return false;
    }
  }
  else {
    if (DebugLevel < 1) {
      return false;
    }
    if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
LAB_000b3228:
      uVar3 = 1;
      goto LAB_000b322c;
    }
    uVar3 = 0;
    if (*(int *)(param_1 + 0xa77bb4) != 1) goto LAB_000b322c;
  }
  uVar3 = *(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1;
LAB_000b322c:
  printk("%s():Bcn Tx is blocked, wdev_type=%d, ATE_ON=%d\n","BeaconTransmitRequired",iVar2,uVar3,
         param_4);
  return false;
}


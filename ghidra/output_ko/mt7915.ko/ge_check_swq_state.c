// module: mt7915.ko
// function: ge_check_swq_state @ 0xd21f0
// size: 232 bytes
//

undefined1 ge_check_swq_state(int param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar3 = param_1 + param_2 * 0x4018;
  iVar4 = *(int *)(iVar3 + 0x28a34c);
  cVar1 = *(char *)(iVar3 + 0x28a35c);
  if (iVar4 < *(int *)(iVar3 + 0x28a350)) {
    iVar4 = -iVar4;
  }
  else {
    iVar4 = 0x2000 - iVar4;
  }
  uVar5 = *(int *)(iVar3 + 0x28a350) + iVar4;
  if (cVar1 == '\x01') {
    return uVar5 < *(uint *)(param_1 + param_2 * 0x4018 + 0x28a354);
  }
  if (cVar1 == '\0') {
    if (*(uint *)(param_1 + param_2 * 0x4018 + 0x28a358) < uVar5) {
      uVar2 = 3;
    }
    else {
      uVar2 = 2;
    }
    return uVar2;
  }
  if (0 < DebugLevel) {
    printk("%s: unknow state %d, q number = %d","ge_check_swq_state",cVar1,uVar5);
    return 4;
  }
  return 4;
}


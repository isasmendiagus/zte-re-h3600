// module: mt7915.ko
// function: WrapDfsSetNonOccupancy @ 0x232df4
// size: 204 bytes
//

void WrapDfsSetNonOccupancy(int param_1,uint param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  
  if (0 < DebugLevel) {
    printk("[%s]: band index: %d\n","WrapDfsSetNonOccupancy",param_2);
  }
  if ((1 < param_2) || (*(char *)(param_1 + 0x795000 + param_2 * 0x20 + 0x2f0) != '\x01')) {
    if ((*(char *)(param_1 + 0x7953fa) == '\x01') && (*(char *)(param_1 + 0x7953e6) == '\x01')) {
      uVar1 = *(undefined1 *)(param_1 + 0x7953fb);
      uVar2 = *(undefined1 *)(param_1 + 0x7953fc);
      uVar3 = *(undefined1 *)(param_1 + 0x7953e3);
    }
    else {
      iVar4 = param_1 + 0x795000 + param_2;
      uVar1 = *(undefined1 *)(iVar4 + 0x130);
      uVar2 = *(undefined1 *)(iVar4 + 0x134);
      uVar3 = *(undefined1 *)(iVar4 + 0x3e1);
    }
    DfsSetNonOccupancy(param_1,0,uVar1,uVar2,uVar3);
    DfsSetNonOccupancy(param_1,1,uVar1,uVar2,uVar3);
  }
  return;
}


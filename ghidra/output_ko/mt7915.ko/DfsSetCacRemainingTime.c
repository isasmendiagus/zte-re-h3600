// module: mt7915.ko
// function: DfsSetCacRemainingTime @ 0x23480c
// size: 160 bytes
//

void DfsSetCacRemainingTime(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  
  if (param_2 == 0) {
    return;
  }
  iVar2 = *(int *)(param_2 + 0x3fe4);
  if (iVar2 == 0) {
    return;
  }
  if (((*(char *)(param_1 + 0x7953fa) == '\x01') && (*(char *)(iVar2 + 4) == '\x02')) &&
     (*(char *)(param_1 + 0x795403) == '\0')) {
    uVar1 = *(ushort *)(param_1 + 0x795400);
    *(ushort *)(iVar2 + 2) = uVar1;
    if (0 < DebugLevel) {
      printk(&_LC99,"DfsSetCacRemainingTime",(uint)*(ushort *)(iVar2 + 8) - (uint)uVar1);
    }
  }
  *(undefined1 *)(param_1 + 0x795403) = 0;
  *(undefined2 *)(param_1 + 0x795400) = 0;
  *(undefined1 *)(param_1 + 0x795402) = 0;
  return;
}


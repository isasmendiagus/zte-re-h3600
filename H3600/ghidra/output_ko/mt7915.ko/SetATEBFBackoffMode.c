// module: mt7915.ko
// function: SetATEBFBackoffMode @ 0x26c82c
// size: 92 bytes
//

undefined4 SetATEBFBackoffMode(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = simple_strtol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0x28595c) = uVar2;
  if (0 < iVar1) {
    printk("%s: ucBFBackOffMode: %d\n","SetATEBFBackoffMode",uVar2);
  }
  return 1;
}


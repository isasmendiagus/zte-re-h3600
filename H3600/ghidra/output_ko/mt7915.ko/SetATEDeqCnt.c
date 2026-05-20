// module: mt7915.ko
// function: SetATEDeqCnt @ 0x260f00
// size: 88 bytes
//

undefined4 SetATEDeqCnt(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = simple_strtol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined4 *)(param_1 + 0xa3a058) = uVar2;
  if (0 < iVar1) {
    printk("%s: deq_cnt:%d\n","SetATEDeqCnt",uVar2);
  }
  return 1;
}


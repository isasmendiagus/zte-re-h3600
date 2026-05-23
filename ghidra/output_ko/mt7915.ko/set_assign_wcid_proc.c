// module: mt7915.ko
// function: set_assign_wcid_proc @ 0xdc768
// size: 96 bytes
//

undefined4 set_assign_wcid_proc(int param_1,undefined4 param_2)

{
  undefined2 uVar1;
  bool bVar2;
  
  uVar1 = os_str_tol(param_2,0,10);
  bVar2 = -1 < DebugLevel;
  *(undefined2 *)(param_1 + 0xa7c23c) = uVar1;
  if (bVar2) {
    printk("%s: assignWcid = %d\n","set_assign_wcid_proc",uVar1);
  }
  return 1;
}


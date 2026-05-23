// module: mt7915.ko
// function: Set_ByPassCac_Proc @ 0x230770
// size: 152 bytes
//

undefined4 Set_ByPassCac_Proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  
  uVar1 = os_str_tol(param_2,0,10);
  if (0 < DebugLevel) {
    printk("set CAC value to %d\n",uVar1);
  }
  if (*(char *)(param_1 + 0xa37728) == '\x02') {
    *(undefined2 *)(param_1 + 0xa37726) = *(undefined2 *)(param_1 + 0xa3772c);
  }
  if (*(char *)(param_1 + 0xa37748) == '\x02') {
    *(undefined2 *)(param_1 + 0xa37746) = *(undefined2 *)(param_1 + 0xa3774c);
  }
  *(undefined2 *)(param_1 + 0x795400) = *(undefined2 *)(param_1 + 0x795406);
  return 1;
}


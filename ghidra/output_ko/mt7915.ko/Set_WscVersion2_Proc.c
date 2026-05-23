// module: mt7915.ko
// function: Set_WscVersion2_Proc @ 0x2ace0
// size: 116 bytes
//

bool Set_WscVersion2_Proc(int *param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *param_1;
  bVar1 = os_str_tol(param_2,0,0x10);
  if (2 < DebugLevel) {
    printk("Set_WscVersion2_Proc::(version=%x)\n",bVar1);
  }
  if (0x1f < bVar1) {
    *(byte *)((int)param_1 + *(int *)(iVar2 + 0x3c) * 0x5834 + 0x2b859d) = bVar1;
  }
  return 0x1f < bVar1;
}


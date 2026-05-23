// module: mt7915.ko
// function: Set_PreAuth_Proc @ 0x2b07c
// size: 184 bytes
//

undefined4 Set_PreAuth_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(*param_1 + 0x3c);
  if (*(byte *)((int)param_1 + 0x2b7242) <= uVar2) {
    return 0;
  }
  iVar1 = os_str_tol(param_2,0,10,(uint)*(byte *)((int)param_1 + 0x2b7242),param_4);
  if (iVar1 == 0) {
    *(undefined1 *)((int)param_1 + uVar2 * 0x5834 + 0x2b775a) = 0;
  }
  else {
    *(undefined1 *)((int)param_1 + uVar2 * 0x5834 + 0x2b775a) = 1;
  }
  if (2 < DebugLevel) {
    printk("I/F(%s%d) PreAuth=%d\n",&_LC49,uVar2,
           *(undefined1 *)((int)param_1 + uVar2 * 0x5834 + 0x2b775a));
    return 1;
  }
  return 1;
}


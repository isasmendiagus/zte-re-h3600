// module: mt7915.ko
// function: Set_IappPID_Proc @ 0x2af84
// size: 64 bytes
//

undefined4 Set_IappPID_Proc(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  uVar1 = os_str_tol(param_2,0,10);
  *(undefined4 *)(iVar2 + 0x30) =
       *(undefined4 *)(*(int *)(((uint)&stack0xfffffff8 & 0xffffe000) + 0xc) + 0x234);
  *(undefined4 *)(iVar2 + 0x34) = uVar1;
  return 1;
}


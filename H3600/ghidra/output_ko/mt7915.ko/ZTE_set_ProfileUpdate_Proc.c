// module: mt7915.ko
// function: ZTE_set_ProfileUpdate_Proc @ 0x2b790
// size: 156 bytes
//

undefined4 ZTE_set_ProfileUpdate_Proc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  local_c = 0;
  iVar1 = os_str_tol(param_2,0,10);
  if (iVar1 != 0) {
    os_alloc_mem(param_1,&local_c,0x8000);
    if (local_c == 0) {
      return 0;
    }
    os_zero_mem(local_c,0x8000);
    iVar1 = multi_profile_check(param_1,local_c);
    if (iVar1 == 0) {
      SetPartProfileParameters(param_1,local_c);
      uVar2 = 1;
      goto LAB_0002b7c0;
    }
  }
  uVar2 = 0;
LAB_0002b7c0:
  if (local_c != 0) {
    os_free_mem(local_c);
  }
  return uVar2;
}


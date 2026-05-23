// module: tm.ko
// function: tm_acl_fast_add @ 0x5f338
// size: 224 bytes
//

undefined4 tm_acl_fast_add(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_3 == 0 || param_1 == 0) {
    return 0xfffffff4;
  }
  switch(*(undefined4 *)(param_1 + 0xc)) {
  case 3:
  case 5:
    uVar1 = tm_acl_fast_add_v4v6(is3TupleRule != 1,1,param_1,param_2,param_3);
    return uVar1;
  case 4:
  case 6:
    if (is3TupleRule != 1) {
      uVar1 = tm_acl_fast_add_v4v6(1,0,param_1,param_2,param_3);
      return uVar1;
    }
switchD_0005f364_caseD_8:
    uVar1 = tm_acl_fast_add_v4v6(0,0,param_1,param_2,param_3);
    return uVar1;
  case 7:
    uVar1 = tm_acl_fast_add_v4v6(0,1,param_1,param_2,param_3);
    return uVar1;
  case 8:
    goto switchD_0005f364_caseD_8;
  default:
    printk("invalid ruletype for fast add %d\n",*(undefined4 *)(param_1 + 0xc),param_1,param_2);
    return 0xfffffff4;
  }
}


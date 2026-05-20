// module: mt7915.ko
// function: ecc_point_add_cmm @ 0x217358
// size: 272 bytes
//

undefined4 *
ecc_point_add_cmm(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  uVar1 = *(undefined4 *)(param_4 + 4);
  local_24 = (undefined4 *)0x0;
  local_20 = 0;
  local_1c[0] = 0;
  if (2 < DebugLevel) {
    printk("==> %s()\n","ecc_point_add_cmm");
    if (local_24 != (undefined4 *)0x0) goto LAB_002173cc;
  }
  FUN_0021705c(&local_24);
  if (local_24 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
LAB_002173cc:
  Bignum_Mod_Mul(param_3,param_3,uVar1,&local_20);
  Bignum_Mod_Add_quick(*param_1,*param_2,uVar1,local_1c);
  Bignum_Mod_Sub(local_20,local_1c[0],uVar1,local_24);
  Bignum_Mod_Sub_quick(*param_1,*local_24,uVar1,&local_20);
  Bignum_Mod_Mul(param_3,local_20,uVar1,local_1c);
  Bignum_Mod_Sub(local_1c[0],param_1[1],uVar1,local_24 + 1);
  Bignum_Free(&local_20);
  Bignum_Free(local_1c);
  return local_24;
}


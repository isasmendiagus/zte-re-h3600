// module: mt7915.ko
// function: Set_TpcReq_Proc @ 0x140184
// size: 204 bytes
//

undefined4 Set_TpcReq_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = RandomByte();
  uVar2 = os_str_tol(param_2,0,0x10);
  if (2 < DebugLevel) {
    printk("%s::wcid = %d\n","Set_TpcReq_Proc",uVar2,DebugLevel,param_4);
  }
  uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar3 <= uVar2) {
    if (-1 < DebugLevel) {
      printk("%s: unknow sta of Aid(%d)\n","Set_TpcReq_Proc",uVar2,DebugLevel,param_4);
    }
    return 1;
  }
  FUN_0013e0f8(param_1,uVar1);
  EnqueueTPCReq(param_1,uVar2 * 0x14c0 + param_1 + 0xa1e0c,uVar1);
  return 1;
}


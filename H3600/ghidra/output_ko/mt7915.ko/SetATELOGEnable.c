// module: mt7915.ko
// function: SetATELOGEnable @ 0x260e08
// size: 120 bytes
//

undefined4 SetATELOGEnable(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  uVar1 = simple_strtol(param_2,0,10,param_4,param_4);
  (**(code **)(iVar2 + 0x100))(param_1,uVar1,1,2000);
  if (0 < DebugLevel) {
    printk("%s: log_type:%u, driver:%08x\n","SetATELOGEnable",uVar1,
           *(undefined4 *)(param_1 + 0xa39ffc));
  }
  return 1;
}


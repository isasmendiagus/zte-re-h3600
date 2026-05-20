// module: mt7915.ko
// function: SetATETxPower3 @ 0x261764
// size: 184 bytes
//

bool SetATETxPower3(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 local_2c;
  int local_28;
  undefined4 uStack_24;
  uint local_20;
  undefined4 uStack_1c;
  
  iVar3 = *(int *)(param_1 + 0xa39fd4);
  if (0 < DebugLevel) {
    printk("%s: Power3 = %s\n","SetATETxPower3",param_2);
  }
  cVar1 = simple_strtol(param_2,0,10);
  *(char *)(param_1 + 0xa3ac1f) = cVar1;
  os_zero_mem(&local_2c,0x14);
  local_28 = (int)cVar1;
  iVar2 = net_ad_wrap_service(param_1);
  local_20 = (uint)*(byte *)(iVar2 + 0x4cc);
  iVar3 = (**(code **)(iVar3 + 0x38))(param_1,local_2c,local_28,uStack_24,local_20,uStack_1c);
  return iVar3 == 0;
}


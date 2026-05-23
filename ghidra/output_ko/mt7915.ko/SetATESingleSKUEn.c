// module: mt7915.ko
// function: SetATESingleSKUEn @ 0x26c78c
// size: 156 bytes
//

undefined4 SetATESingleSKUEn(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0xa39fd4);
  iVar3 = net_ad_wrap_service();
  cVar1 = *(char *)(iVar3 + 0x4cc);
  uVar2 = simple_strtol(param_2,0,10);
  if (0 < DebugLevel) {
    printk("%s: fgSKUEn: %d, control_band_idx: %d\n","SetATESingleSKUEn",uVar2,cVar1);
  }
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0xa3ba8c) = uVar2;
  }
  else if (cVar1 == '\x01') {
    *(undefined1 *)(param_1 + 0xa3abb4) = uVar2;
  }
  (**(code **)(iVar4 + 0xe4))(param_1,6,uVar2);
  return 1;
}


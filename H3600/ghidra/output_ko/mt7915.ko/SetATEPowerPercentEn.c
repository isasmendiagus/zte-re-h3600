// module: mt7915.ko
// function: SetATEPowerPercentEn @ 0x26c900
// size: 152 bytes
//

undefined4 SetATEPowerPercentEn(int param_1,undefined4 param_2)

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
    printk("%s: fgPowerPercentEn: %d\n","SetATEPowerPercentEn",uVar2);
  }
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0xa3ba8d) = uVar2;
  }
  else if (cVar1 == '\x01') {
    *(undefined1 *)(param_1 + 0xa3abb5) = uVar2;
  }
  (**(code **)(iVar4 + 0xe4))(param_1,7,uVar2);
  return 1;
}


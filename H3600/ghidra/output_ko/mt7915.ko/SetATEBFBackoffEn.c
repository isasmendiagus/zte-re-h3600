// module: mt7915.ko
// function: SetATEBFBackoffEn @ 0x26ca70
// size: 152 bytes
//

undefined4 SetATEBFBackoffEn(int param_1,undefined4 param_2)

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
    printk("%s: fgBFBackoffEn: %d\n","SetATEBFBackoffEn",uVar2);
  }
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0xa3ba8e) = uVar2;
  }
  else if (cVar1 == '\x01') {
    *(undefined1 *)(param_1 + 0xa3abb6) = uVar2;
  }
  (**(code **)(iVar4 + 0xe4))(param_1,8,uVar2);
  return 1;
}


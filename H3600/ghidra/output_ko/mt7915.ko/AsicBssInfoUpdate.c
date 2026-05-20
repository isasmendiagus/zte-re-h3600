// module: mt7915.ko
// function: AsicBssInfoUpdate @ 0x134780
// size: 176 bytes
//

undefined4 AsicBssInfoUpdate(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s(): Set Bssid=%02x:%02x:%02x:%02x:%02x:%02x, BssIndex(%d)\n","AsicBssInfoUpdate",
           *(undefined1 *)(param_2 + 0xe),*(undefined1 *)(param_2 + 0xf),
           *(undefined1 *)(param_2 + 0x10),*(undefined1 *)(param_2 + 0x11),
           *(undefined1 *)(param_2 + 0x12),*(undefined1 *)(param_2 + 0x13),
           *(undefined1 *)(param_2 + 0xd));
  }
  if (*(code **)(iVar1 + 0x28) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001347d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x28))(param_1,param_2);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicBssInfoUpdate");
  return 0;
}


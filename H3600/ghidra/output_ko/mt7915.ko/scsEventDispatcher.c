// module: mt7915.ko
// function: scsEventDispatcher @ 0x238788
// size: 244 bytes
//

void scsEventDispatcher(int param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_2;
  if (DebugLevel < 0) {
    if (iVar1 != 6) {
      return;
    }
  }
  else {
    printk("%s: u4EventId = %u, len = %u\n","scsEventDispatcher",iVar1,param_3);
    if (iVar1 != 6) {
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s: SCS_EVENT_GET_GLO_ADDR\n","scsEventDispatcher");
    }
  }
  iVar2 = *(int *)(param_1 + 0x1c);
  iVar1 = hc_get_chip_ops(*(undefined4 *)(iVar2 + 0xa797a0));
  if (-1 < DebugLevel) {
    printk("%s:SCS_EVENT_GET_GLO_ADDR\n","scs_get_glo_addr_handler");
    if (-1 < DebugLevel) {
      printk("eventId %u\n",*param_2);
    }
  }
  if (*(code **)(iVar1 + 0x2c8) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x002387fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x2c8))(iVar2,param_2 + 2);
  return;
}


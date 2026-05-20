// module: mt7915.ko
// function: ShowBcnProc @ 0xedcc0
// size: 220 bytes
//

undefined4 ShowBcnProc(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 == 0) goto LAB_000edd34;
  do {
    iVar2 = os_str_toul(param_2,0,10);
    if (iVar2 == iVar3) goto LAB_000edd34;
    while( true ) {
      if (iVar3 == 1) {
        if (0 < DebugLevel) {
          printk("===============================\n");
        }
        return 1;
      }
      iVar3 = 1;
      if (param_2 != 0) break;
LAB_000edd34:
      if (0 < DebugLevel) {
        printk("%s, Band %d\n","ShowBcnProc",iVar3,DebugLevel,param_4);
        if (0 < DebugLevel) {
          printk("===============================\n");
        }
      }
      if (*(code **)(iVar1 + 0x40) != (code *)0x0) {
        (**(code **)(iVar1 + 0x40))(*(undefined4 *)(param_1 + 0xa797a0),iVar3);
      }
    }
  } while( true );
}


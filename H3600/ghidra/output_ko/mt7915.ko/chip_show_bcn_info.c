// module: mt7915.ko
// function: chip_show_bcn_info @ 0x18dd04
// size: 572 bytes
//

void chip_show_bcn_info(int param_1,int param_2)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  undefined4 local_1c;
  
  iVar3 = *(int *)(param_1 + 0x4328);
  Show_Mib_Info_Proc(iVar3,&_LC219);
  if (0 < DebugLevel) {
    printk(&_LC12);
  }
  puVar1 = &_LC218;
  if (param_2 == 0) {
    puVar1 = &_LC217;
  }
  show_mib_proc(iVar3,puVar1);
  if (0 < DebugLevel) {
    printk(&_LC12);
  }
  show_trinfo_proc(iVar3,&_LC219);
  if (0 < DebugLevel) {
    printk(&_LC12);
  }
  ShowPLEInfo(iVar3,0);
  if (0 < DebugLevel) {
    printk(&_LC12);
  }
  ShowSerProc2(iVar3,&_LC219);
  if (0 < DebugLevel) {
    printk(&_LC12);
  }
  ShowPseInfo(iVar3,0);
  if (0 < DebugLevel) {
    printk(&_LC12);
  }
  show_tpinfo_proc(iVar3,&_LC217);
  if (0 < DebugLevel) {
    printk(&_LC12);
  }
  Show_MibBucket_Proc(iVar3,&_LC219);
  if (0 < DebugLevel) {
    printk(&_LC12);
  }
  mac_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),param_2 * 0x10000 + -0x7df1cf80,&local_1c);
  if (0 < DebugLevel) {
    printk("ARB_SCR=0x%08x\n",local_1c);
  }
  iVar2 = 0;
  do {
    mac_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),param_2 * 0x10000 + -0x7df1ce70,&local_1c);
    if (0 < DebugLevel) {
      printk("ARB_BFCR=0x%08x (loop %d)\n",local_1c,iVar2);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 10);
  if (0 < DebugLevel) {
    printk(&_LC12);
  }
  return;
}


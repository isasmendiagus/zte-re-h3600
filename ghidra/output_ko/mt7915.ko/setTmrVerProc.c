// module: mt7915.ko
// function: setTmrVerProc @ 0xbb030
// size: 164 bytes
//

undefined4 setTmrVerProc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = os_str_tol(param_2,0,10);
  if (bVar1 < 3) {
    if (DebugLevel < 1) {
      return 1;
    }
    printk("%s: ver = %d, pChipCap->TmrHwVer = %d\n","setTmrVerProc",(int)(char)bVar1,
           *(undefined1 *)(iVar2 + 0x14f),param_4);
    return 1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s: wrong setting %d, remain default %d!!\n","setTmrVerProc",(int)(char)bVar1,
         *(undefined1 *)(iVar2 + 0x14f),param_4);
  return 0;
}


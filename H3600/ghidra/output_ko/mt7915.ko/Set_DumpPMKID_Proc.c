// module: mt7915.ko
// function: Set_DumpPMKID_Proc @ 0x33fc8
// size: 188 bytes
//

undefined4 Set_DumpPMKID_Proc(int param_1,undefined4 param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  
  cVar1 = os_str_tol(param_2,0,10);
  if (cVar1 == '\x01') {
    pcVar2 = &DAT_00368858 + param_1;
    iVar3 = 0;
    do {
      if ((*pcVar2 != '\0') && (0 < DebugLevel)) {
        printk("Cacheidx = %d, Mbssidx = %d, Mac = %02x:%02x:%02x:%02x:%02x:%02x\n",iVar3,
               pcVar2[-0x5c],pcVar2[-0x5b],pcVar2[-0x5a],pcVar2[-0x59],pcVar2[-0x58],pcVar2[-0x57],
               pcVar2[-0x56]);
      }
      iVar3 = iVar3 + 1;
      pcVar2 = pcVar2 + 0x60;
    } while (iVar3 != 0x80);
  }
  return 1;
}


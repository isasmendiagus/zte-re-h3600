// module: mt7915.ko
// function: set_tx_deq_cpu @ 0xc3c28
// size: 204 bytes
//

undefined4 set_tx_deq_cpu(undefined4 param_1,char *param_2)

{
  byte bVar1;
  char *pcVar2;
  uint uVar3;
  bool bVar4;
  bool bVar5;
  char *local_c;
  
  local_c = param_2;
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    pcVar2 = strsep(&local_c,":");
    bVar1 = os_str_tol(pcVar2,0,10);
    if ((local_c != (char *)0x0) && (*local_c != '\0')) {
      uVar3 = os_str_tol(local_c,0,10);
      bVar5 = bVar1 != 0;
      bVar4 = bVar1 == 1;
      if (bVar1 < 2) {
        bVar5 = 2 < uVar3;
        bVar4 = uVar3 == 3;
      }
      if (!bVar5 || bVar4) {
        if (DebugLevel < 1) {
          return 1;
        }
        printk("band %d cpu = %u\n",bVar1,uVar3);
        return 1;
      }
    }
  }
  if (0 < DebugLevel) {
    printk("invalid input, should be band:cpu\n");
  }
  return 1;
}


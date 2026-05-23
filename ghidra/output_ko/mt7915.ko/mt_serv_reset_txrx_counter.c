// module: mt7915.ko
// function: mt_serv_reset_txrx_counter @ 0x251a6c
// size: 168 bytes
//

int mt_serv_reset_txrx_counter(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  
  piVar3 = param_1 + 0x5b;
  iVar4 = *param_1;
  do {
    sys_ad_zero_mem(piVar3,0x1ac);
    piVar1 = piVar3 + -0x5b;
    do {
      piVar1[0x78] = 0xff;
      piVar2 = piVar1 + 6;
      piVar1[0x77] = 0xff;
      piVar1[0x79] = 0xff;
      piVar1[0x7a] = 0xff;
      piVar1 = piVar2;
    } while (piVar2 != piVar3 + -0x43);
    piVar3 = piVar3 + 0x6b;
  } while (piVar3 != param_1 + 0x131);
  param_1[0x447] = 0;
  if (*(char *)(iVar4 + 0x34) != '\0') {
    param_1[0x78d] = 0;
  }
  iVar4 = (**(code **)(param_1[0x7c4] + 0x8c))(*param_1);
  if (iVar4 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_reset_txrx_counter",iVar4);
  }
  return iVar4;
}


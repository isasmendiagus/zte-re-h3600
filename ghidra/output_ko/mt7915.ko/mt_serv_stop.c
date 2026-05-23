// module: mt7915.ko
// function: mt_serv_stop @ 0x250784
// size: 140 bytes
//

int mt_serv_stop(undefined4 *param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x7d1) == '\0') {
    iVar1 = mt_engine_stop(*param_1,(int)param_1 + 0x4ce,param_1 + 0x138,param_1[0x7c4],param_1 + 1,
                           param_1 + 0x7d3);
  }
  else {
    iVar1 = (**(code **)(param_1[0x7c4] + 100))(*param_1);
  }
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_stop",iVar1);
  }
  return iVar1;
}


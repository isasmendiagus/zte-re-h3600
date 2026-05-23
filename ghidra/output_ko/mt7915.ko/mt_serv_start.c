// module: mt7915.ko
// function: mt_serv_start @ 0x2506f0
// size: 148 bytes
//

int mt_serv_start(undefined4 *param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x7d1) == '\0') {
    iVar1 = mt_engine_start(*param_1,(int)param_1 + 0x4ce,param_1 + 0x138,param_1[0x7c4],param_1 + 1
                            ,param_1 + 0x5b,param_1[0x7d2]);
  }
  else {
    iVar1 = (**(code **)(param_1[0x7c4] + 0x60))(*param_1);
  }
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_start",iVar1);
  }
  return iVar1;
}


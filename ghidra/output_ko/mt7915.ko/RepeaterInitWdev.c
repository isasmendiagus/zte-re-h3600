// module: mt7915.ko
// function: RepeaterInitWdev @ 0x8172c
// size: 212 bytes
//

char RepeaterInitWdev(undefined4 param_1,int param_2,undefined4 *param_3,int param_4)

{
  char cVar1;
  undefined1 uVar2;
  
  __memzero(param_4,0x4060);
  cVar1 = wdev_init(param_1,param_4,0x100,*param_3,(int)*(char *)(param_2 + 2),param_2,param_1);
  if (cVar1 == '\0') {
    if (-1 < DebugLevel) {
      printk(" Init repeater wdev failed!\n");
    }
    return '\0';
  }
  RepeaterSyncWdevWithMainSta(param_4,param_3);
  wdev_fsm_init(param_4);
  *(undefined1 *)(param_4 + 0x888) = 2;
  *(undefined1 *)(param_4 + 0x3c4) = 7;
  *(undefined4 *)(param_4 + 0x1b) = *(undefined4 *)(param_2 + 0x83);
  *(undefined2 *)(param_4 + 0x1f) = *(undefined2 *)(param_2 + 0x87);
  HcAddRepeaterEntry(param_4);
  uVar2 = HcGetRepeaterOmac(param_4);
  *(undefined1 *)(param_4 + 0x29) = uVar2;
  return cVar1;
}


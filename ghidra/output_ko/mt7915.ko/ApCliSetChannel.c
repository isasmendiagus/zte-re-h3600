// module: mt7915.ko
// function: ApCliSetChannel @ 0xc43a4
// size: 96 bytes
//

undefined4 ApCliSetChannel(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 4);
  uVar1 = *(undefined1 *)(iVar2 + 0x4165);
  if (2 < DebugLevel) {
    printk("cmd> channel=%d CMDTHREAD_APCLI_PBC_TIMEOUT!\n",uVar1);
  }
  rtmp_set_channel(param_1,iVar2,uVar1);
  return 0;
}


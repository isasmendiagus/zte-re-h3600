// module: mt7915.ko
// function: MT_ATESetAutoResp @ 0x27d5d8
// size: 336 bytes
//

undefined4 MT_ATESetAutoResp(int param_1,void *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  void *__dest;
  undefined4 uVar3;
  
  cVar1 = *(char *)(param_1 + 0xa3ae36);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    __dest = (void *)(param_1 + 0xa3af17);
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    __dest = (void *)(param_1 + 0xa3aeb7);
  }
  else {
    __dest = (void *)0x0;
  }
  if (2 < DebugLevel) {
    printk(&_LC65,"MT_ATESetAutoResp");
  }
  if (cVar1 == '\x01') {
    iVar2 = net_ad_wrap_service(param_1);
    uVar3 = HcGetOmacIdx(param_1,*(undefined4 *)
                                  (param_1 + (uint)*(byte *)(iVar2 + 0x1224) * 4 + 0xc));
    if (2 < DebugLevel) {
      printk("%s OwnMacIdx:%d\n","MT_ATESetAutoResp",uVar3);
    }
  }
  else {
    uVar3 = 0;
  }
  if (param_3 == 0) {
    AsicDevInfoUpdate(param_1,uVar3,param_1 + 0x794b5b,cVar1,1,1);
    return 0;
  }
  if (__dest != (void *)0x0) {
    memmove(__dest,param_2,6);
  }
  AsicDevInfoUpdate(param_1,uVar3,param_2,cVar1,1,1);
  return 0;
}


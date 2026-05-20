// module: mt7915.ko
// function: __cntl_disconnect_request @ 0x10d484
// size: 348 bytes
//

undefined4
__cntl_disconnect_request
          (int param_1,undefined4 param_2,void *param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_24;
  undefined1 auStack_20 [6];
  undefined2 local_1a;
  
  if (*(int *)(param_1 + 8) == 0) {
    printk(&_LC17,0x1ba);
    dump_stack();
  }
  if (0 < DebugLevel) {
    printk("%s, caller:%pS,type=%d,reason=%d\n","__cntl_disconnect_request");
  }
  local_24 = param_2;
  os_move_mem(auStack_20,param_3,6);
  iVar2 = *(int *)(param_1 + 8);
  local_1a = (undefined2)param_4;
  if ((param_1 == 0) || (*(int *)(param_1 + 0x14) != 2)) {
    __ZTE_STA_Assoc_Process
              (iVar2,0x11,param_3,*(undefined1 *)(param_1 + 0xe),param_4,0,0,param_5,param_6);
  }
  else {
    if (*(byte *)(param_1 + 0x1a) < 0xf) {
      uVar1 = 0xffffffff;
    }
    else {
      uVar1 = 0xfffffffb;
    }
    __ZTE_STA_Assoc_Process(iVar2,0x11,param_3,uVar1,param_4,0,0,param_5,param_6);
  }
  MlmeEnqueueWithWdev(iVar2,5,5,0xc,&local_24,0,param_1);
  RtmpOsMlmeUp(iVar2 + 0x286298);
  return 1;
}


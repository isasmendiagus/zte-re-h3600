// module: mt7915.ko
// function: RtmpOSWrielessEventSend @ 0x243f7c
// size: 136 bytes
//

undefined4
RtmpOSWrielessEventSend
          (undefined4 param_1,undefined4 param_2,int param_3,undefined4 *param_4,int param_5,
          int param_6)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined1 auStack_30 [2];
  undefined2 local_2e;
  undefined2 uStack_2c;
  undefined2 local_2a;
  
  uVar1 = FUN_00243140(param_2);
  __memzero(auStack_30,0x10);
  if (-1 < param_3) {
    local_2a = (undefined2)param_3;
  }
  if (param_4 != (undefined4 *)0x0) {
    local_2e = (undefined2)*param_4;
    local_2a = *(undefined2 *)(param_4 + 1);
  }
  if (param_5 == 0 || param_6 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (undefined2)param_6;
  }
  _local_2e = CONCAT22(uVar2,local_2e);
  wireless_send_event(param_1,uVar1,auStack_30,param_5);
  return 0;
}


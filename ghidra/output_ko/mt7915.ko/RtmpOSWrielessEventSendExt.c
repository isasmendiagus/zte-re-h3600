// module: mt7915.ko
// function: RtmpOSWrielessEventSendExt @ 0x244004
// size: 128 bytes
//

undefined4
RtmpOSWrielessEventSendExt
          (undefined4 param_1,undefined4 param_2,int param_3,undefined4 *param_4,int param_5,
          int param_6,undefined2 param_7)

{
  undefined4 uVar1;
  undefined2 local_30;
  undefined4 local_2e;
  undefined2 local_2a;
  
  uVar1 = FUN_00243140(param_2);
  __memzero(&local_30,0x10);
  if (-1 < param_3) {
    local_2a = (undefined2)param_3;
  }
  local_30 = param_7;
  if (param_4 != (undefined4 *)0x0) {
    local_2e = *param_4;
    local_2a = *(undefined2 *)(param_4 + 1);
  }
  if (param_5 != 0 && param_6 != 0) {
    local_2e = CONCAT22((short)param_6,(undefined2)local_2e);
  }
  wireless_send_event(param_1,uVar1,&local_30,param_5);
  return 0;
}


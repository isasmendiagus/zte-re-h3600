// module: mt7915.ko
// function: ap_send_broadcast_deauth @ 0x4e080
// size: 116 bytes
//

void ap_send_broadcast_deauth(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *local_14 [2];
  
  os_alloc_mem(param_1,local_14,0x930);
  if (local_14[0] != (undefined4 *)0x0) {
    local_14[0][2] = param_2;
    uVar1 = (undefined4)BROADCAST_ADDR;
    *(undefined2 *)(local_14[0] + 0x248) = 0x7fff;
    *(undefined2 *)((int)local_14[0] + 6) = 1;
    *local_14[0] = uVar1;
    *(undefined2 *)(local_14[0] + 1) = BROADCAST_ADDR._4_2_;
    ap_mlme_deauth_req_action(param_1,local_14[0]);
    os_free_mem(local_14[0]);
  }
  return;
}


// module: mt7915.ko
// function: AndesInitCmdMsg @ 0x1a4184
// size: 244 bytes
//

void AndesInitCmdMsg(undefined2 *param_1,uint param_2,uint param_3,undefined2 param_4,
                    undefined4 param_5,undefined4 param_6)

{
  undefined2 uVar1;
  undefined2 local_c;
  undefined1 uStack_a;
  undefined1 uStack_9;
  byte local_8;
  undefined2 local_6;
  
  local_c = (undefined2)param_2;
  uStack_a = (undefined1)(param_2 >> 0x10);
  uStack_9 = (undefined1)(param_2 >> 0x18);
  if (3 < DebugLevel) {
    printk("%s:: mcu_dest(%d), cmd_type(0x%x), ExtCmdType(0x%x)\n","AndesInitCmdMsg",
           param_2 & 0xffff,uStack_a,uStack_9);
  }
  uVar1 = GetRealPortQueueID(param_1,uStack_a);
  *param_1 = local_c;
  *(undefined1 *)(param_1 + 1) = uStack_a;
  *(undefined1 *)((int)param_1 + 3) = uStack_9;
  local_8 = (byte)param_3;
  param_1[10] = uVar1;
  *(byte *)(param_1 + 2) = local_8;
  param_1[4] = param_4;
  if ((param_3 & 4) != 0) {
    *(undefined4 *)(param_1 + 0x28) = 0;
    __init_waitqueue_head(param_1 + 0x2a,"&x->wait",&_LANCHOR1);
    local_8 = *(byte *)(param_1 + 2);
  }
  local_6 = (undefined2)(param_3 >> 0x10);
  if ((local_8 & 2) == 0) {
    *(byte *)((int)param_1 + 0x17) = local_8 & 2;
  }
  else {
    *(undefined1 *)((int)param_1 + 0x17) = 3;
  }
  param_1[3] = local_6;
  *(undefined4 *)(param_1 + 6) = param_5;
  *(undefined4 *)(param_1 + 8) = param_6;
  return;
}


// module: mt7915.ko
// function: mac_entry_delete @ 0x14ac20
// size: 88 bytes
//

void mac_entry_delete(undefined4 param_1,int param_2)

{
  undefined2 local_30;
  undefined4 local_2e;
  undefined2 local_2a;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_2e = *(undefined4 *)(param_2 + 0xec);
  local_30 = *(undefined2 *)(param_2 + 0xe0);
  local_2a = *(undefined2 *)(param_2 + 0xf0);
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  RTEnqueueInternalCmd(param_1,0x18,&local_30,0x20);
  return;
}


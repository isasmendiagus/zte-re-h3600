// module: mt7915.ko
// function: hqa_set_rx_path @ 0x24c2e4
// size: 244 bytes
//

undefined4 hqa_set_rx_path(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  ushort local_1a;
  uint local_18;
  int local_14;
  
  local_14 = param_2 + 0xc;
  uVar2 = (uint)*(byte *)(param_1 + 0x4cc);
  local_18 = 0;
  local_1a = 0;
  if (*(ushort *)(param_2 + 8) < 3) {
    FUN_002474f4(1,2,&local_14,&local_1a);
    printk("%s: rx_path:%d\n","hqa_set_rx_path",local_1a);
  }
  else {
    FUN_002474f4(1,4,&local_14,&local_18);
    local_1a = (ushort)local_18;
    FUN_002474f4(1,4,&local_14,&local_18);
    uVar2 = local_18 & 0xff;
    if (uVar2 != 0 && 3 < local_1a) {
      local_1a = local_1a >> 2;
    }
    printk("%s: rx_path:%d, band:%d\n","hqa_set_rx_path");
  }
  *(ushort *)(uVar2 * 0xd18 + param_1 + 0x112e) = local_1a;
  uVar1 = mt_serv_set_rx_path(param_1);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}


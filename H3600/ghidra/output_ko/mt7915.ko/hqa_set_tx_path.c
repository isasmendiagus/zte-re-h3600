// module: mt7915.ko
// function: hqa_set_tx_path @ 0x24c4b0
// size: 276 bytes
//

undefined4 hqa_set_tx_path(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint local_24;
  int local_20;
  uint local_1c [2];
  
  local_20 = param_2 + 0xc;
  uVar2 = (uint)*(byte *)(param_1 + 0x4cc);
  local_24 = 0;
  local_1c[0] = 0;
  if (*(ushort *)(param_2 + 8) < 3) {
    FUN_002474f4(1,4,&local_20,local_1c);
    printk("%s: tx_path:0x%x\n","hqa_set_tx_path",local_1c[0]);
  }
  else {
    FUN_002474f4(1,4,&local_20,&local_24);
    local_1c[0] = local_24;
    FUN_002474f4(1,4,&local_20,&local_24);
    uVar2 = local_24 & 0xff;
    if ((int)local_1c[0] < 0) {
      printk("%s: user_tx_path:0x%x, band:%d\n","hqa_set_tx_path",local_1c[0],uVar2);
    }
    else if (uVar2 != 0 && 3 < local_1c[0]) {
      local_1c[0] = local_1c[0] >> 2;
    }
    printk("%s: tx_path:0x%x, band:%d\n","hqa_set_tx_path",local_1c[0],uVar2);
  }
  *(uint *)(uVar2 * 0xd18 + param_1 + 0x1128) = local_1c[0];
  uVar1 = mt_serv_set_tx_path(param_1);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}


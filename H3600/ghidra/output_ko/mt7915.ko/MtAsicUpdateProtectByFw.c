// module: mt7915.ko
// function: MtAsicUpdateProtectByFw @ 0x1994c0
// size: 128 bytes
//

void MtAsicUpdateProtectByFw(undefined4 param_1,undefined1 *param_2)

{
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  
  os_zero_mem(&local_2c,0xc);
  local_2b = *param_2;
  local_28 = param_2[1];
  local_27 = param_2[2];
  local_26 = param_2[3];
  local_25 = param_2[5];
  local_24 = param_2[4];
  local_23 = param_2[6];
  local_22 = param_2[7];
  local_21 = (undefined1)*(undefined2 *)(param_2 + 8);
  local_2c = 2;
  MtCmdUpdateProtect(param_1,&local_2c);
  return;
}


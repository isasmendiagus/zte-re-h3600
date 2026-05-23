// module: mt7915.ko
// function: sta_set_rfeature_ltf @ 0xcea70
// size: 132 bytes
//

void sta_set_rfeature_ltf(undefined4 param_1,byte *param_2)

{
  uint uVar1;
  undefined2 local_13;
  undefined1 local_11;
  
  uVar1 = (uint)*param_2;
  local_13 = 0x5500;
  local_11 = 0xaa;
  if (uVar1 < 3) {
    if (0 < DebugLevel) {
      printk("func:%s, arg:%d ra_setting=0x%08x\n","sta_set_rfeature_ltf",uVar1,
             *(undefined1 *)((int)&local_13 + uVar1));
    }
    snd_ra_fw_cmd(7,param_1,1,(int)&local_13 + uVar1);
  }
  return;
}


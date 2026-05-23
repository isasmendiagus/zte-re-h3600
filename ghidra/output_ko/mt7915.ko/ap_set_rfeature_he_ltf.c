// module: mt7915.ko
// function: ap_set_rfeature_he_ltf @ 0xced4c
// size: 272 bytes
//

void ap_set_rfeature_he_ltf(int param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  bool bVar6;
  undefined2 local_1b;
  undefined1 local_19;
  
  uVar5 = (uint)*param_2;
  local_19 = 0xaa;
  local_1b = 0x5500;
  if (uVar5 < 3) {
    if (0 < DebugLevel) {
      printk("func:%s, arg:%d ra_setting=0x%08x\n","ap_set_rfeature_he_ltf",uVar5,
             *(undefined1 *)((int)&local_1b + uVar5));
    }
    uVar1 = HcGetMaxStaNum(param_1);
    puVar4 = (uint *)(param_1 + 0xa1d20);
    for (uVar3 = 0; (uVar2 = HcGetMaxStaNum(param_1), uVar3 < uVar2 && (uVar3 <= uVar1));
        uVar3 = uVar3 + 1) {
      uVar2 = *puVar4;
      bVar6 = puVar4 != (uint *)0x0;
      puVar4 = puVar4 + 0x530;
      if ((bVar6 && (uVar2 & 0xfffffbff) != 0) &&
         (uVar2 == 2 || (uVar2 - 0x20001 & 0xfffdffff) == 0)) {
        snd_ra_fw_cmd(7,param_1,uVar3,(int)&local_1b + uVar5);
      }
    }
  }
  return;
}


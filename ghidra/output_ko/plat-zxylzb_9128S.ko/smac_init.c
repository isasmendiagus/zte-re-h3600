// module: plat-zxylzb_9128S.ko
// function: smac_init @ 0x13278
// size: 168 bytes
//

void smac_init(int param_1)

{
  param_1 = param_1 * 0x40000;
  *(undefined4 *)(npp_base + param_1 + 0x40000) = 0xbae003;
  *(undefined4 *)(npp_base + param_1 + 0x40004) = 0xffff;
  *(undefined4 *)(npp_base + param_1 + 0x40008) = 0x80000001;
  *(undefined ***)(npp_base + param_1 + 0x400e0) = &PTR_caseD_47_00011200;
  *(uint *)(npp_base + param_1 + 0x40d00) = *(uint *)(npp_base + param_1 + 0x40d00) & 0xfffffffd;
  *(uint *)(npp_base + param_1 + 0x40d30) = *(uint *)(npp_base + param_1 + 0x40d30) & 0xffffffdf;
  return;
}


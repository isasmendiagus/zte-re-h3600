// module: plat-zxylzb_9128S.ko
// function: pon_pp_port_isolate.part.1 @ 0x164e0
// size: 52 bytes
//

void pon_pp_port_isolate_part_1(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = param_1 * 4 + 0x83c0;
  *(uint *)(pp_base + iVar1) = *(uint *)(pp_base + iVar1) | param_2;
  return;
}


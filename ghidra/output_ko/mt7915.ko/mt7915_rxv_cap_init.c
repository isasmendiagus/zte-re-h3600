// module: mt7915.ko
// function: mt7915_rxv_cap_init @ 0x178b80
// size: 120 bytes
//

undefined4 mt7915_rxv_cap_init(int param_1)

{
  char cVar1;
  int iVar2;
  undefined1 uVar3;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  cVar1 = "Get_RBIST_IQ_Data_Proc"[param_1 + 0x14];
  if (cVar1 == '\0') {
    *(undefined1 *)(iVar2 + 0x213) = 2;
  }
  else {
    *(undefined1 *)(iVar2 + 0x213) = 2;
    if (cVar1 == '\x01') {
      uVar3 = 0x1a;
      goto LAB_00178bc8;
    }
  }
  uVar3 = 0x14;
LAB_00178bc8:
  *(undefined1 *)(iVar2 + 0x214) = 2;
  *(undefined1 *)(iVar2 + 0x217) = 2;
  *(undefined1 *)(iVar2 + 0x215) = 0x12;
  *(undefined1 *)(iVar2 + 0x216) = uVar3;
  *(undefined1 *)(iVar2 + 0x218) = 4;
  return 0;
}


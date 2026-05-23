// module: tm.ko
// function: sbrg_set_indreg_wr @ 0x1c8c0
// size: 104 bytes
//

uint sbrg_set_indreg_wr(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *in_r3;
  undefined4 *puVar5;
  
  puVar5 = in_r3;
  uVar1 = sbrg_set_indreg_wr_cfg();
  uVar2 = tmOnuRegWrite(0x4e,in_r3[2],0,&sbragRegTable,puVar5);
  uVar3 = tmOnuRegWrite(0x4d,in_r3[1],0,&sbragRegTable);
  uVar4 = tmOnuRegWrite(0x4c,*in_r3,0,&sbragRegTable);
  return uVar3 | uVar2 | uVar4 | uVar1;
}


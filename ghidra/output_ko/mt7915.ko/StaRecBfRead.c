// module: mt7915.ko
// function: StaRecBfRead @ 0x884d8
// size: 520 bytes
//

void StaRecBfRead(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  uint uVar10;
  
  __memzero((undefined4 *)(param_1 + 0xa78698),0x2a);
  puVar4 = param_2;
  puVar1 = (undefined4 *)(param_1 + 0xa78698);
  do {
    puVar5 = puVar1;
    puVar3 = puVar4;
    puVar4 = puVar3 + 4;
    uVar9 = puVar3[1];
    uVar7 = puVar3[2];
    uVar2 = puVar3[3];
    *puVar5 = *puVar3;
    puVar5[1] = uVar9;
    puVar5[2] = uVar7;
    puVar5[3] = uVar2;
    puVar1 = puVar5 + 4;
  } while (puVar4 != param_2 + 8);
  uVar2 = *puVar4;
  puVar5[5] = puVar3[5];
  puVar5[4] = uVar2;
  *(undefined2 *)(puVar5 + 6) = *(undefined2 *)(puVar3 + 6);
  if (0 < DebugLevel) {
    uVar6 = (uint)*(byte *)(param_1 + 0xa786ac);
    uVar10 = *(byte *)(param_1 + 0xa786ab) & 0x3f;
    uVar8 = *(byte *)(param_1 + 0xa786ad) & 0x3f;
    printk("====================================== BF StaRec ========================================\nrStaRecBf.u2PfmuId      = %d\nrStaRecBf.fgSU_MU       = %d\nrStaRecBf.u1TxBfCap     = %d\nrStaRecBf.ucSoundingPhy = %d\nrStaRecBf.ucNdpaRate    = %d\nrStaRecBf.ucNdpRate     = %d\nrStaRecBf.ucReptPollRate= %d\nrStaRecBf.ucTxMode      = %d\nrStaRecBf.ucNc          = %d\nrStaRecBf.ucNr          = %d\nrStaRecBf.ucCBW         = %d\nrStaRecBf.ucTotMemRequire = %d\nrStaRecBf.ucMemRequire20M = %d\nrStaRecBf.ucMemRow0     = %d\nrStaRecBf.ucMemCol0     = %d\nrStaRecBf.ucMemRow1     = %d\nrStaRecBf.ucMemCol1     = %d\nrStaRecBf.ucMemRow2     = %d\nrStaRecBf.ucMemCol2     = %d\nrStaRecBf.ucMemRow3     = %d\nrStaRecBf.ucMemCol3     = %d\n"
           ,*(undefined2 *)(param_1 + 0xa78698),*(undefined1 *)(param_1 + 0xa7869a),
           *(undefined1 *)(param_1 + 0xa7869b),*(undefined1 *)(param_1 + 0xa7869c),
           *(undefined1 *)(param_1 + 0xa7869d),*(undefined1 *)(param_1 + 0xa7869e),
           *(undefined1 *)(param_1 + 0xa7869f),*(undefined1 *)(param_1 + 0xa786a0),
           *(undefined1 *)(param_1 + 0xa786a1),*(undefined1 *)(param_1 + 0xa786a2),
           *(undefined1 *)(param_1 + 0xa786a3),*(undefined1 *)(param_1 + 0xa786a4),
           *(undefined1 *)(param_1 + 0xa786a5),*(undefined1 *)(param_1 + 0xa786a6),
           *(byte *)(param_1 + 0xa786a7) & 0x3f,*(undefined1 *)(param_1 + 0xa786a8),
           *(byte *)(param_1 + 0xa786a9) & 0x3f,*(undefined1 *)(param_1 + 0xa786aa),uVar10,uVar6,
           uVar8);
    if (0 < DebugLevel) {
      printk("rStaRecBf.u2SmartAnt    = 0x%x\nrStaRecBf.ucSEIdx       = %d\nrStaRecBf.ucAutoSoundingCtrl = %d\nrStaRecBf.uciBfTimeOut  = 0x%x\nrStaRecBf.uciBfDBW      = %d\nrStaRecBf.uciBfNcol     = %d\nrStaRecBf.uciBfNrow     = %d\nrStaRecBf.nr_bw160      = %d\nrStaRecBf.nc_bw160 \t  = %d\nrStaRecBf.ru_start_idx  = %d\nrStaRecBf.ru_end_idx \t  = %d\nrStaRecBf.trigger_su \t  = %d\nrStaRecBf.trigger_mu \t  = %d\nrStaRecBf.ng16_su \t  = %d\nrStaRecBf.ng16_mu \t  = %d\nrStaRecBf.codebook42_su = %d\nrStaRecBf.codebook75_mu = %d\nrStaRecBf.he_ltf \t      = %d\n=======================================================================================\n"
             ,*(undefined2 *)(param_1 + 0xa786ae),*(undefined1 *)(param_1 + 0xa786b0),
             *(undefined1 *)(param_1 + 0xa786b1),*(undefined1 *)(param_1 + 0xa786b2),
             *(undefined1 *)(param_1 + 0xa786b3),*(undefined1 *)(param_1 + 0xa786b4),
             *(undefined1 *)(param_1 + 0xa786b5),*(undefined1 *)(param_1 + 0xa786b6),
             *(undefined1 *)(param_1 + 0xa786b7),*(undefined1 *)(param_1 + 0xa786b8),
             *(undefined1 *)(param_1 + 0xa786b9),*(undefined1 *)(param_1 + 0xa786ba),
             *(undefined1 *)(param_1 + 0xa786bb),*(undefined1 *)(param_1 + 0xa786bc),
             *(undefined1 *)(param_1 + 0xa786bd),*(undefined1 *)(param_1 + 0xa786be),
             *(undefined1 *)(param_1 + 0xa786bf),*(undefined1 *)(param_1 + 0xa786c0),uVar10,uVar6,
             uVar8);
    }
  }
  return;
}


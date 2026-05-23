// module: mt7915.ko
// function: mtf_dump_rmac_info @ 0x19c548
// size: 2292 bytes
//

void mtf_dump_rmac_info(undefined4 param_1,uint *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = *param_2;
  if (0 < DebugLevel) {
    uVar1 = rxd_pkt_type_str(uVar2 >> 0x1b);
    printk("RMAC_RXD Header Format :%s\n",uVar1);
  }
  if (uVar2 >> 0x1b != 1) {
    return;
  }
  if (DebugLevel < 1) {
    return;
  }
  printk(", TA_0_31=%d\n",*param_2);
  if (DebugLevel < 1) {
LAB_0019c610:
    if (0 < DebugLevel) {
      printk(", HtStbc=%d",(*(byte *)((int)param_2 + 9) & 1) << 1 | (byte)param_2[2] >> 7);
      if (DebugLevel < 1) {
        return;
      }
      printk(", HtAdCode=%d",((uint)*(byte *)((int)param_2 + 9) << 0x1e) >> 0x1f);
      goto LAB_0019c664;
    }
LAB_0019c6ac:
    if (0 < DebugLevel) {
      printk(", FrMode=%d\n",
             (*(byte *)((int)param_2 + 10) & 1) << 1 | *(byte *)((int)param_2 + 9) >> 7);
      if (DebugLevel < 1) {
        return;
      }
      printk(", VHTA1_B22=%d",((uint)*(byte *)((int)param_2 + 10) << 0x1e) >> 0x1f);
      goto LAB_0019c700;
    }
LAB_0019c748:
    if (0 < DebugLevel) {
      printk(", HtSmooth=%d",((uint)*(byte *)((int)param_2 + 10) << 0x1b) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk(", HtNoSound=%d",((uint)*(byte *)((int)param_2 + 10) << 0x1a) >> 0x1f);
      goto LAB_0019c790;
    }
LAB_0019c7d8:
    if (0 < DebugLevel) {
      printk(", SuVhtMcs_MuCoding=%d",((uint)*(byte *)((int)param_2 + 0xb) << 0x1b) >> 0x1c);
      if (DebugLevel < 1) {
        return;
      }
      printk(", Beamormed=%d",((uint)*(byte *)((int)param_2 + 0xb) << 0x1a) >> 0x1f);
      goto LAB_0019c820;
    }
LAB_0019c868:
    if (0 < DebugLevel) {
      printk(", Length=%d",(uint)(ushort)param_2[3] | (*(byte *)((int)param_2 + 0xe) & 0x1f) << 0x10
            );
      if (DebugLevel < 1) {
        return;
      }
      printk(", GroupId=%d",
             (*(byte *)((int)param_2 + 0xf) & 7) << 3 | *(byte *)((int)param_2 + 0xe) >> 5);
      goto LAB_0019c8cc;
    }
LAB_0019c914:
    if (0 < DebugLevel) {
      printk(", SelAnt=%d\n",*(byte *)((int)param_2 + 0xf) >> 7);
      if (DebugLevel < 1) {
        return;
      }
      printk(", VHTA1_B21_B10=%d",
             (uint)(byte)param_2[4] | (*(byte *)((int)param_2 + 0x11) & 0xf) << 8);
      goto LAB_0019c964;
    }
LAB_0019c9ac:
    if (0 < DebugLevel) {
      printk(", IBRssiRx=%d",*(undefined1 *)((int)param_2 + 0x12));
      if (DebugLevel < 1) {
        return;
      }
      printk(", WBRssiRx=%d\n",*(undefined1 *)((int)param_2 + 0x13));
      goto LAB_0019c9ec;
    }
LAB_0019ca2c:
    if (0 < DebugLevel) {
      printk(", RCPI2=%d",*(undefined1 *)((int)param_2 + 0x16));
      if (DebugLevel < 1) {
        return;
      }
      printk(", RCPI3=%d\n",*(undefined1 *)((int)param_2 + 0x17));
      goto LAB_0019ca6c;
    }
LAB_0019cab4:
    if (0 < DebugLevel) {
      printk(", MISC1=%d\n",
             (uint)*(byte *)((int)param_2 + 0x19) << 2 | (uint)(byte)((byte)param_2[6] >> 6) |
             (uint)*(byte *)((int)param_2 + 0x1a) << 10 |
             (*(byte *)((int)param_2 + 0x1b) & 0x7f) << 0x12);
      if (DebugLevel < 1) {
        return;
      }
      printk(", Nf0=%d",(char)param_2[7]);
      goto LAB_0019cb14;
    }
LAB_0019cb54:
    if (0 < DebugLevel) {
      printk(", Nf3=%d\n",*(undefined1 *)((int)param_2 + 0x1f));
      if (DebugLevel < 1) {
        return;
      }
      printk(", PrimItfrEnv=%d",(byte)param_2[8] & 1);
      goto LAB_0019cb98;
    }
LAB_0019cbe0:
    if (0 < DebugLevel) {
      printk(", Sec80ItfrEnv=%d",((uint)(byte)param_2[8] << 0x1c) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk(", RxLQ=%d",
             (uint)*(byte *)((int)param_2 + 0x21) << 4 | (uint)(byte)((byte)param_2[8] >> 4) |
             (*(byte *)((int)param_2 + 0x22) & 3) << 0xc);
      goto LAB_0019cc3c;
    }
LAB_0019cc84:
    if (0 < DebugLevel) {
      printk(", LqDataBit=%d",
             (*(byte *)((int)param_2 + 0x23) & 0xf) << 2 | *(byte *)((int)param_2 + 0x22) >> 6);
      if (DebugLevel < 1) {
        return;
      }
      printk(", RxCERmsd=%d",((uint)*(byte *)((int)param_2 + 0x23) << 0x19) >> 0x1d);
      goto LAB_0019ccd8;
    }
LAB_0019cd20:
    if (0 < DebugLevel) {
      printk(", RxBW=%d",(*(byte *)((int)param_2 + 0x25) & 1) << 1 | (byte)param_2[9] >> 7);
      if (DebugLevel < 1) {
        return;
      }
      printk(", PostBWDSecCh=%d",((uint)*(byte *)((int)param_2 + 0x25) << 0x1d) >> 0x1e);
      goto LAB_0019cd74;
    }
  }
  else {
    printk(", TA_32_47=%d",(short)param_2[1]);
    if (DebugLevel < 1) {
      return;
    }
    printk(", RxvSn=%d",*(undefined1 *)((int)param_2 + 6));
    if (0 < DebugLevel) {
      printk(", TR=%d\n",*(byte *)((int)param_2 + 7) & 1);
      if (DebugLevel < 1) {
        return;
      }
      printk(", TxRate=%d",(byte)param_2[2] & 0x7f);
      goto LAB_0019c610;
    }
LAB_0019c664:
    if (0 < DebugLevel) {
      printk(", HtExtltf=%d",((uint)*(byte *)((int)param_2 + 9) << 0x1c) >> 0x1e);
      if (DebugLevel < 1) {
        return;
      }
      printk(", TxMode=%d",((uint)*(byte *)((int)param_2 + 9) << 0x19) >> 0x1d);
      goto LAB_0019c6ac;
    }
LAB_0019c700:
    if (0 < DebugLevel) {
      printk(", HtAggregation=%d",((uint)*(byte *)((int)param_2 + 10) << 0x1d) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk(", HtShortGi=%d",((uint)*(byte *)((int)param_2 + 10) << 0x1c) >> 0x1f);
      goto LAB_0019c748;
    }
LAB_0019c790:
    if (0 < DebugLevel) {
      printk(", NumRx=%d\n",*(byte *)((int)param_2 + 10) >> 6);
      if (DebugLevel < 1) {
        return;
      }
      printk(", LdpcExtraOFDMSymbol=%d",*(byte *)((int)param_2 + 0xb) & 1);
      goto LAB_0019c7d8;
    }
LAB_0019c820:
    if (0 < DebugLevel) {
      printk(", ACID_DET_LOWER=%d",((uint)*(byte *)((int)param_2 + 0xb) << 0x19) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk(", ACID_DET_UPPER=%d\n",*(byte *)((int)param_2 + 0xb) >> 7);
      goto LAB_0019c868;
    }
LAB_0019c8cc:
    if (0 < DebugLevel) {
      printk(", NstsField=%d",((uint)*(byte *)((int)param_2 + 0xf) << 0x1a) >> 0x1d);
      if (DebugLevel < 1) {
        return;
      }
      printk(", RxValidIndicator=%d",((uint)*(byte *)((int)param_2 + 0xf) << 0x19) >> 0x1f);
      goto LAB_0019c914;
    }
LAB_0019c964:
    if (0 < DebugLevel) {
      printk(", POPEverTrig=%d",((uint)*(byte *)((int)param_2 + 0x11) << 0x1b) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk(", FgacCalLnaRx=%d",*(byte *)((int)param_2 + 0x11) >> 5);
      goto LAB_0019c9ac;
    }
LAB_0019c9ec:
    if (0 < DebugLevel) {
      printk(", RCPI0=%d",(char)param_2[5]);
      if (DebugLevel < 1) {
        return;
      }
      printk(", RCPI1=%d",*(undefined1 *)((int)param_2 + 0x15));
      goto LAB_0019ca2c;
    }
LAB_0019ca6c:
    if (0 < DebugLevel) {
      printk(", FagcLnaGainx=%d",(byte)param_2[6] & 7);
      if (DebugLevel < 1) {
        return;
      }
      printk(", FagcLpfGainx=%d",((uint)(byte)param_2[6] << 0x1a) >> 0x1d);
      goto LAB_0019cab4;
    }
LAB_0019cb14:
    if (0 < DebugLevel) {
      printk(", Nf1=%d",*(undefined1 *)((int)param_2 + 0x1d));
      if (DebugLevel < 1) {
        return;
      }
      printk(", Nf2=%d",*(undefined1 *)((int)param_2 + 0x1e));
      goto LAB_0019cb54;
    }
LAB_0019cb98:
    if (0 < DebugLevel) {
      printk(", SecItfrEnv=%d",((uint)(byte)param_2[8] << 0x1e) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk(", Sec40ItfrEnv=%d",((uint)(byte)param_2[8] << 0x1d) >> 0x1f);
      goto LAB_0019cbe0;
    }
LAB_0019cc3c:
    if (0 < DebugLevel) {
      printk(", BtEnv=%d",((uint)*(byte *)((int)param_2 + 0x22) << 0x1d) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk(", ScrambleSeed=%d\n",((uint)*(byte *)((int)param_2 + 0x22) << 0x1a) >> 0x1d);
      goto LAB_0019cc84;
    }
LAB_0019ccd8:
    if (0 < DebugLevel) {
      printk(", FCSErr=%d\n",*(byte *)((int)param_2 + 0x23) >> 7);
      if (DebugLevel < 1) {
        return;
      }
      printk(", PostTMD=%d",(byte)param_2[9] & 0x7f);
      goto LAB_0019cd20;
    }
LAB_0019cd74:
    if (DebugLevel < 1) goto LAB_0019ce00;
    printk(", PostDewSecCh=%d",((uint)*(byte *)((int)param_2 + 0x25) << 0x1c) >> 0x1f);
    if (DebugLevel < 1) {
      return;
    }
    printk(", HtSTFDet=%d",((uint)*(byte *)((int)param_2 + 0x25) << 0x1b) >> 0x1f);
  }
  if (DebugLevel < 1) {
    return;
  }
  printk(", CagcSTFDet=%d",*(byte *)((int)param_2 + 0x25) >> 5);
  if (DebugLevel < 1) {
    return;
  }
  printk(", IBRssi0=%d",*(undefined1 *)((int)param_2 + 0x26));
LAB_0019ce00:
  if (DebugLevel < 1) {
    return;
  }
  printk(", WBRssi0=%d",*(undefined1 *)((int)param_2 + 0x27));
  return;
}


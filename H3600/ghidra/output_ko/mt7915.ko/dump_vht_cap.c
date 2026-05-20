// module: mt7915.ko
// function: dump_vht_cap @ 0x201fec
// size: 968 bytes
//

void dump_vht_cap(undefined4 param_1,byte *param_2)

{
  if (0 < DebugLevel) {
    printk("Dump VHT_CAP IE\n");
  }
  hex_dump("VHT CAP IE Raw Data",param_2,0xc);
  if (DebugLevel < 1) {
    return;
  }
  printk("VHT Capabilities Info Field\n");
  if (DebugLevel < 1) {
LAB_002020bc:
    if (0 < DebugLevel) {
      printk("\tShortGI_160M=%d\n",((uint)*param_2 << 0x19) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tTxSTBC=%d\n",*param_2 >> 7);
      goto LAB_00202104;
    }
LAB_0020214c:
    if (0 < DebugLevel) {
      printk("\tSU BeamformeeCap=%d\n",((uint)param_2[1] << 0x1b) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tCompressedSteeringNumOfBeamformerAnt=%d\n",param_2[1] >> 5);
      goto LAB_00202194;
    }
LAB_002021dc:
    if (0 < DebugLevel) {
      printk("\tMU BeamformeeCap=%d\n",((uint)param_2[2] << 0x1b) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tVHT TXOP PS=%d\n",((uint)param_2[2] << 0x1a) >> 0x1f);
      goto LAB_00202224;
    }
LAB_00202278:
    if (0 < DebugLevel) {
      printk("\tVHT LinkAdaptation Capable=%d\n",((uint)param_2[3] << 0x1c) >> 0x1e);
      if (DebugLevel < 1) {
        return;
      }
      printk("VHT Supported MCS Set Field\n");
      goto LAB_002022b8;
    }
  }
  else {
    printk("\tMaximum MPDU Length=%d\n",*param_2 & 3);
    if (DebugLevel < 1) {
      return;
    }
    printk("\tSupported Channel Width=%d\n",((uint)*param_2 << 0x1c) >> 0x1e);
    if (0 < DebugLevel) {
      printk("\tRxLDPC=%d\n",((uint)*param_2 << 0x1b) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tShortGI_80M=%d\n",((uint)*param_2 << 0x1a) >> 0x1f);
      goto LAB_002020bc;
    }
LAB_00202104:
    if (0 < DebugLevel) {
      printk("\tRxSTBC=%d\n",param_2[1] & 7);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tSU BeamformerCap=%d\n",((uint)param_2[1] << 0x1c) >> 0x1f);
      goto LAB_0020214c;
    }
LAB_00202194:
    if (0 < DebugLevel) {
      printk("\tNumber of Sounding Dimensions=%d\n",param_2[2] & 7);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tMU BeamformerCap=%d\n",((uint)param_2[2] << 0x1c) >> 0x1f);
      goto LAB_002021dc;
    }
LAB_00202224:
    if (0 < DebugLevel) {
      printk("\t+HTC-VHT Capable=%d\n",((uint)param_2[2] << 0x19) >> 0x1f);
      if (DebugLevel < 1) {
        return;
      }
      printk("\tMaximum A-MPDU Length Exponent=%d\n",(param_2[3] & 3) << 1 | param_2[2] >> 7);
      goto LAB_00202278;
    }
LAB_002022b8:
    if (DebugLevel < 1) goto LAB_00202358;
    printk("\tRx Highest SupDataRate=%d\n",(uint)param_2[6] | (param_2[7] & 0x1f) << 8);
    if (DebugLevel < 1) {
      return;
    }
    printk("\tRxMCS Map_1SS=%d\n",param_2[4] & 3);
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("\tRxMCS Map_2SS=%d\n",((uint)param_2[4] << 0x1c) >> 0x1e);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tTx Highest SupDataRate=%d\n",(uint)param_2[10] | (param_2[0xb] & 0x1f) << 8);
LAB_00202358:
  if (DebugLevel < 1) {
    return;
  }
  printk("\tTxMCS Map_1SS=%d\n",param_2[8] & 3);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tTxMCS Map_2SS=%d\n",((uint)param_2[8] << 0x1c) >> 0x1e);
  return;
}


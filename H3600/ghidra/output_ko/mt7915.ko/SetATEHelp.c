// module: mt7915.ko
// function: SetATEHelp @ 0x2690b0
// size: 676 bytes
//

undefined4 SetATEHelp(void)

{
  undefined4 extraout_r2;
  undefined4 in_r3;
  
  if (DebugLevel < 1) {
    return 1;
  }
  printk("ATE=ATESTART, ATESTOP, TXCONT, TXCARR, TXCARS, TXFRAME, RXFRAME\n");
  if (DebugLevel < 1) {
LAB_0026913c:
    if (0 < DebugLevel) {
      printk("ATETXPOW0, set power level of antenna 1.\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("ATETXPOW1, set power level of antenna 2.\n");
      goto LAB_00269174;
    }
LAB_002691ac:
    if (0 < DebugLevel) {
      printk("ATETXBW, set BandWidth, 0:20MHz, 1:40MHz\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("ATETXLEN, set Frame length, range 24~%d\n",0x908,extraout_r2,DebugLevel,in_r3);
      goto LAB_002691e8;
    }
LAB_00269220:
    if (0 < DebugLevel) {
      printk(
            "ATETXMODE, set Mode 0:CCK, 1:OFDM, 2:HT-Mix, 3:GreenField, 4:VHT, reference to rate table.\n"
            );
      if (DebugLevel < 1) {
        return 1;
      }
      printk("ATETXGI, set GI interval, 0:Long, 1:Short\n");
      goto LAB_00269258;
    }
LAB_00269290:
    if (0 < DebugLevel) {
      printk("ATELDE2P, load EEPROM from .bin file.\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("ATERE2P, display all EEPROM content.\n");
      goto LAB_002692c8;
    }
  }
  else {
    printk("ATEDA\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("ATESA\n");
    if (0 < DebugLevel) {
      printk("ATEBSSID\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("ATECHANNEL, range:0~14\n");
      goto LAB_0026913c;
    }
LAB_00269174:
    if (0 < DebugLevel) {
      printk("ATETXANT, set TX antenna. 0:all, 1:antenna one, 2:antenna two.\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("ATERXANT, set RX antenna.0:all, 1:antenna one, 2:antenna two, 3:antenna three.\n");
      goto LAB_002691ac;
    }
LAB_002691e8:
    if (0 < DebugLevel) {
      printk("ATETXCNT, set how many frame going to transmit.\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("ATETXMCS, set MCS, reference to rate table.\n");
      goto LAB_00269220;
    }
LAB_00269258:
    if (0 < DebugLevel) {
      printk("ATERXFER, 0:disable Rx Frame error rate. 1:enable Rx Frame error rate.\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("ATERRF, show all RF registers.\n");
      goto LAB_00269290;
    }
LAB_002692c8:
    if (DebugLevel < 1) goto LAB_00269338;
    printk("ATEAUTOALC, enable ATE auto Tx alc (Tx auto level control).\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("ATEIPG, set ATE Tx frame IPG.\n");
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk("ATEPAYLOAD, set ATE payload pattern for TxFrame.\n");
  if (DebugLevel < 1) {
    return 1;
  }
  printk("ATESHOW, display all parameters of ATE.\n");
LAB_00269338:
  if (0 < DebugLevel) {
    printk("ATEHELP, online help.\n");
  }
  return 1;
}


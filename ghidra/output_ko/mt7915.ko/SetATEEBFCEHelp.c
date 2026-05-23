// module: mt7915.ko
// function: SetATEEBFCEHelp @ 0x2686f0
// size: 2496 bytes
//

undefined4 SetATEEBFCEHelp(void)

{
  if (DebugLevel < 1) {
    return 1;
  }
  printk(
        "=============================================================================================\n"
        );
  if (DebugLevel < 1) {
LAB_0026877c:
    if (0 < DebugLevel) {
      printk(" 1)  iwpriv ra0 set ATEEBFCE=1\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 2)  iwpriv ra0 set ATEConTxETxBfGdProc=02:00:00:036:112:1 (Use in Golden Device)\n");
      goto LAB_002687b4;
    }
LAB_002687ec:
    if (0 < DebugLevel) {
      printk(" 5)  iwpriv ra0 set ATE=TXFRAME\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 6)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if apply then nonzero)\n");
      goto LAB_00268824;
    }
LAB_0026885c:
    if (0 < DebugLevel) {
      printk(" 9)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if not apply then zero)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("10)  check Iqxel waveformn");
      goto LAB_00268894;
    }
LAB_002688cc:
    if (0 < DebugLevel) {
      printk(&_LC346);
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 1)  iwpriv ra0 set ATEEBFCE=1\n");
      goto LAB_00268904;
    }
LAB_0026893c:
    if (0 < DebugLevel) {
      printk(" 4)  iwpriv ra0 set ATETXEBF=1 (Tx packet apply BF On)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 5)  iwpriv ra0 set ATE=TXFRAMESKB\n");
      goto LAB_00268974;
    }
LAB_002689ac:
    if (0 < DebugLevel) {
      printk(" 8)  iwpriv ra0 set ATETXEBF=0 (Tx packet apply BF Off)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 9)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if not apply then zero)\n");
      goto LAB_002689e4;
    }
LAB_00268a1c:
    if (0 < DebugLevel) {
      printk("For VHT80 mode\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(&_LC74);
      goto LAB_00268a54;
    }
LAB_00268a8c:
    if (0 < DebugLevel) {
      printk(" 3)  iwpriv ra0 set ATEConTxETxBfInitProc=04:00:02:01:04:18:036:112:1:16000\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 4)  iwpriv ra0 set ATETXEBF=1 (Tx packet apply BF On)\n");
      goto LAB_00268ac4;
    }
LAB_00268afc:
    if (0 < DebugLevel) {
      printk(" 7)  check IQxel waveform\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 8)  iwpriv ra0 set ATETXEBF=0 (Tx packet apply BF Off)\n");
      goto LAB_00268b34;
    }
LAB_00268b6c:
    if (0 < DebugLevel) {
      printk(
            "---------------------------------------------------------------------------------------------\n"
            );
      if (DebugLevel < 1) {
        return 1;
      }
      printk("For VHT160C mode\n");
      goto LAB_00268ba4;
    }
LAB_00268bdc:
    if (0 < DebugLevel) {
      printk(" 2)  iwpriv ra0 set ATEConTxETxBfGdProc=04:00:03:036:112:1 (Use in Golden Device)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 3)  iwpriv ra0 set ATEConTxETxBfInitProc=04:00:03:01:04:18:036:112:1:16000\n");
      goto LAB_00268c14;
    }
LAB_00268c4c:
    if (0 < DebugLevel) {
      printk(" 6)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if apply then nonzero)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 7)  check IQxel waveform\n");
      goto LAB_00268c84;
    }
LAB_00268cbc:
    if (0 < DebugLevel) {
      printk("10)  check Iqxel waveform\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(
            "---------------------------------------------------------------------------------------------\n"
            );
      goto LAB_00268cf4;
    }
LAB_00268d2c:
    if (0 < DebugLevel) {
      printk(" 1)  iwpriv ra0 set ATEEBFCE=1\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 2)  iwpriv ra0 set ATEConTxETxBfGdProc=04:00:06:036:112:1 (Use in Golden Device)\n");
      goto LAB_00268d64;
    }
LAB_00268d9c:
    if (0 < DebugLevel) {
      printk(" 5)  iwpriv ra0 set ATE=TXFRAMESKB\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 6)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if apply then nonzero)\n");
      goto LAB_00268dd4;
    }
LAB_00268e0c:
    if (0 < DebugLevel) {
      printk(" 9)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if not apply then zero)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("10)  check Iqxel waveform\n");
      goto LAB_00268e44;
    }
LAB_00268e7c:
    if (0 < DebugLevel) {
      printk(&_LC74);
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 1)  configure DBDC mode and Reboot system\n");
      goto LAB_00268eb4;
    }
LAB_00268eec:
    if (0 < DebugLevel) {
      printk(" 4)  iwpriv ra1 set ATEConTxETxBfInitProc=02:00:00:01:02:18:36:112:1:04000\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 5)  iwpriv ra1 set ATETXEBF=1 (Tx packet apply BF On)\n");
      goto LAB_00268f24;
    }
LAB_00268f5c:
    if (0 < DebugLevel) {
      printk(" 8)  check IQxel waveform\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 9)  iwpriv ra1 set ATETXEBF=0 (Tx packet apply BF Off)\n");
      goto LAB_00268f94;
    }
LAB_00268fcc:
    if (0 < DebugLevel) {
      printk(
            "=============================================================================================\n"
            );
      if (DebugLevel < 1) {
        return 1;
      }
      printk("                           Method for Dynamical Control Tx Power\n");
      goto LAB_00269004;
    }
  }
  else {
    printk("                            ATE ETxBF Certification Procedure Guide\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk(
          "=============================================================================================\n"
          );
    if (0 < DebugLevel) {
      printk("For HT20 mode\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(&_LC346);
      goto LAB_0026877c;
    }
LAB_002687b4:
    if (0 < DebugLevel) {
      printk(" 3)  iwpriv ra0 set ATEConTxETxBfInitProc=02:00:00:01:04:18:036:112:1:04000\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 4)  iwpriv ra0 set ATETXEBF=1 (Tx packet apply BF On)\n");
      goto LAB_002687ec;
    }
LAB_00268824:
    if (0 < DebugLevel) {
      printk(" 7)  check IQxel waveform\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 8)  iwpriv ra0 set ATETXEBF=0 (Tx packet apply BF Off)\n");
      goto LAB_0026885c;
    }
LAB_00268894:
    if (0 < DebugLevel) {
      printk(
            "---------------------------------------------------------------------------------------------\n"
            );
      if (DebugLevel < 1) {
        return 1;
      }
      printk("For HT40 mode\n");
      goto LAB_002688cc;
    }
LAB_00268904:
    if (0 < DebugLevel) {
      printk(" 2)  iwpriv ra0 set ATEConTxETxBfGdProc=02:00:01:036:112:1 (Use in Golden Device)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 3)  iwpriv ra0 set ATEConTxETxBfInitProc=02:00:01:01:04:18:036:112:1:04000\n");
      goto LAB_0026893c;
    }
LAB_00268974:
    if (0 < DebugLevel) {
      printk(" 6)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if apply then nonzero)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 7)  check IQxel waveform\n");
      goto LAB_002689ac;
    }
LAB_002689e4:
    if (0 < DebugLevel) {
      printk("10)  check Iqxel waveform\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(
            "---------------------------------------------------------------------------------------------\n"
            );
      goto LAB_00268a1c;
    }
LAB_00268a54:
    if (0 < DebugLevel) {
      printk(" 1)  iwpriv ra0 set ATEEBFCE=1\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 2)  iwpriv ra0 set ATEConTxETxBfGdProc=04:00:02:036:112:1 (Use in Golden Device)\n");
      goto LAB_00268a8c;
    }
LAB_00268ac4:
    if (0 < DebugLevel) {
      printk(" 5)  iwpriv ra0 set ATE=TXFRAMESKB\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 6)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if apply then nonzero)\n");
      goto LAB_00268afc;
    }
LAB_00268b34:
    if (0 < DebugLevel) {
      printk(" 9)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if not apply then zero)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("10)  check Iqxel waveform\n");
      goto LAB_00268b6c;
    }
LAB_00268ba4:
    if (0 < DebugLevel) {
      printk(&_LC74);
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 1)  iwpriv ra0 set ATEEBFCE=1\n");
      goto LAB_00268bdc;
    }
LAB_00268c14:
    if (0 < DebugLevel) {
      printk(" 4)  iwpriv ra0 set ATETXEBF=1 (Tx packet apply BF On)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 5)  iwpriv ra0 set ATE=TXFRAMESKB\n");
      goto LAB_00268c4c;
    }
LAB_00268c84:
    if (0 < DebugLevel) {
      printk(" 8)  iwpriv ra0 set ATETXEBF=0 (Tx packet apply BF Off)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 9)  iwpriv ra0 mac 820fa09c (check [15:0] eBF counter, if not apply then zero)\n");
      goto LAB_00268cbc;
    }
LAB_00268cf4:
    if (0 < DebugLevel) {
      printk("For VHT160NC mode\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(&_LC74);
      goto LAB_00268d2c;
    }
LAB_00268d64:
    if (0 < DebugLevel) {
      printk(" 3)  iwpriv ra0 set ATEConTxETxBfInitProc=04:00:06:01:04:18:036:112:1:16000\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 4)  iwpriv ra0 set ATETXEBF=1 (Tx packet apply BF On)\n");
      goto LAB_00268d9c;
    }
LAB_00268dd4:
    if (0 < DebugLevel) {
      printk(" 7)  check IQxel waveform\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 8)  iwpriv ra0 set ATETXEBF=0 (Tx packet apply BF Off)\n");
      goto LAB_00268e0c;
    }
LAB_00268e44:
    if (0 < DebugLevel) {
      printk(
            "---------------------------------------------------------------------------------------------\n"
            );
      if (DebugLevel < 1) {
        return 1;
      }
      printk("For DBDC Band1 HT20 mode\n");
      goto LAB_00268e7c;
    }
LAB_00268eb4:
    if (0 < DebugLevel) {
      printk(" 2)  iwpriv ra1 set ATEEBFCE=1\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 3)  iwpriv ra1 set ATEConTxETxBfGdProc=02:00:00:36:112:1 (Use in Golden Device)\n");
      goto LAB_00268eec;
    }
LAB_00268f24:
    if (0 < DebugLevel) {
      printk(" 6)  iwpriv ra1 set ATE=TXFRAMESKB\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" 7)  iwpriv ra1 mac 820fa09c (check [15:0] eBF counter, if apply then nonzero)\n");
      goto LAB_00268f5c;
    }
LAB_00268f94:
    if (0 < DebugLevel) {
      printk("10)  iwpriv ra1 mac 820fa09c (check [15:0] eBF counter, if not apply then zero)\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("11)  check Iqxel waveform\n");
      goto LAB_00268fcc;
    }
LAB_00269004:
    if (DebugLevel < 1) goto LAB_00269074;
    printk(
          "=============================================================================================\n"
          );
    if (DebugLevel < 1) {
      return 1;
    }
    printk(" 1)  Follow ETxBF Certification Procedure to enable TxBf packet at first\n");
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk(" 2)  Use command \"iwpriv ra0 set ATE=TXSTOP\" to stop Tx\n");
  if (DebugLevel < 1) {
    return 1;
  }
  printk(
        " 3)  Use command \"iwpriv ra0 set ATETXPOW0=XX\" to configure Tx Power DAC value for OFDM 54M\n"
        );
LAB_00269074:
  if ((0 < DebugLevel) &&
     (printk(" 4)  USe command \"ra0 set ATE=TXFRAMESKB\" to start continuous packet Tx\n"),
     0 < DebugLevel)) {
    printk(
          "=============================================================================================\n"
          );
  }
  return 1;
}


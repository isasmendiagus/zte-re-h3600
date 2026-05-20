// module: mt7915.ko
// function: RTMPSetLED @ 0x15a57c
// size: 16 bytes
//

undefined4 RTMPSetLED(void)

{
  ZTE_WSC_LED_Status_Set();
  return 1;
}


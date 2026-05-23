// module: mt7915.ko
// function: mt_Trigger_Sounding_Packet @ 0x850e8
// size: 20 bytes
//

void mt_Trigger_Sounding_Packet(void)

{
  CmdETxBfSoundingPeriodicTriggerCtrl();
  return;
}


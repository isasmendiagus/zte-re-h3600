// module: mt7915.ko
// function: BackgroundChannelSwitchAnnouncementAction @ 0x22e6dc
// size: 76 bytes
//

void BackgroundChannelSwitchAnnouncementAction(int param_1)

{
  printk("Trigger Channel Switch Announcemnet IE\n");
  if (2 < DebugLevel) {
    printk("Trigger Channel Switch Announcemnet IE\n");
  }
  *(undefined4 *)(param_1 + 0xa79184) = 3;
  return;
}


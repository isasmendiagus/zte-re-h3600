#!/bin/sh
cd /tmp
tftp -g -r peekmem 192.168.1.50
chmod +x peekmem
/tmp/peekmem 0x92340000 > /tmp/peek.out 2>&1
/tmp/peekmem 0x923400F0 >> /tmp/peek.out 2>&1
/tmp/peekmem 0x92348014 >> /tmp/peek.out 2>&1

#pragma once
#include "file_dialog.h"
#include "pcap_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <windows.h>

class CISO {

public:
  enum { OK, FAIL };

public:
  int open_file();

private:
  PcapReader pcap_reader;
  FileDialog file_dialog;
};

#pragma once
#include "file_dialog.h"
#include "pcap_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <windows.h>

#define START_AND_DETACH_THREAD(x)                                             \
  {                                                                            \
    std::thread t([&]() { x; });                                               \
    t.detach();                                                                \
  }

class CISO {
public:
  enum { OK, FAIL };

public:
  int open_file();
  int save_file();
  int save_as_file();

private:
  PcapReader m_pcap_reader;
  FileDialog m_file_dialog;
};

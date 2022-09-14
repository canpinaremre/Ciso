#include "ciso.h"

int CISO::open_file() {
  if (m_pcap_reader.set_input_file_name(
          m_file_dialog.open_file("All Files (*.*)\0*.*\0").c_str()) ==
      PcapReader::OK) {
    if (m_pcap_reader.read_from_input_file() == PcapReader::FAIL) {
      printf("Could not read file");
    }
  } else {
    printf("Could not open file");
  }

  return 0;
}

int CISO::save_file() {
  // TODO: if file name is know, just save, do not open dialog
  printf(m_file_dialog.save_file("All Files (*.*)\0*.*\0").c_str());
  return 0;
}

int CISO::save_as_file() {
  printf(m_file_dialog.save_file("All Files (*.*)\0*.*\0").c_str());
  return 0;
}

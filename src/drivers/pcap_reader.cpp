#include "pcap_reader.h"

int PcapReader::read_from_file(std::string file_name) {

  FILE *f = fopen(input_file_name.c_str(), "rb");
  if (f == NULL) {
    // TODO: could not opened file.
    return FAIL;
  }

  uint32_t size = get_file_size(f);
  if (size <= 0) {
    // TODO: file is empty.
    return FAIL;
  }

  uint8_t *buffer = new uint8_t[size];
  fread(buffer, 1, size, f);

  return OK;
}

int PcapReader::read_from_input_file() {
  return read_from_file(input_file_name);
}

uint32_t PcapReader::get_file_size(FILE *fp) { return 0; }

int PcapReader::set_input_file_name(std::string in_file_name) {
  if (!in_file_name.empty()) {
    input_file_name = in_file_name;
  }
}

std::string PcapReader::get_input_file_name() { return input_file_name; }

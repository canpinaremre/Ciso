#pragma once

#include <list>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <windows.h>

class PcapReader {
public:
  enum { OK, FAIL };

  int read_from_file(std::string file_name);
  int read_from_input_file();
  int get_packets(uint8_t *buffer, uint32_t len);
  int get_packers_from_source(uint8_t *buffer, uint32_t len,
                              uint32_t source_ip);
  int get_packers_from_target(uint8_t *buffer, uint32_t len,
                              uint32_t target_ip);
  uint32_t get_file_size(FILE *fp);
  int set_input_file_name(std::string in_file_name);
  std::string get_input_file_name();

private:
  std::list<uint8_t *> packets;
  std::string input_file_name;

  int obj;
};
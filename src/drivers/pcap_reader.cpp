#include "pcap_reader.h"

int PcapReader::read_from_file(std::string file_name)
{
    printf("Reading from file : %s\n", file_name.c_str());
    FILE *f = fopen(file_name.c_str(), "rb");
    if (f == NULL)
    {
        // TODO: could not opened file.
        printf("Could not open (fopen) : %s\n", file_name.c_str());
        return FAIL;
    }

    uint32_t size = get_file_size(f);
    if (size <= 0)
    {
        printf("File is empty: %s\n", file_name.c_str());
        // TODO: file is empty.
        return FAIL;
    }

    uint8_t *buffer = new uint8_t[size];
    fread(buffer, 1, size, f);

    for (uint32_t i = 0; i < size; i++)
    {
        printf("%X ", buffer[i]);
    }
    delete[] buffer;
    return OK;
}

int PcapReader::read_from_input_file()
{
    return read_from_file(input_file_name);
}

uint32_t PcapReader::get_file_size(FILE *fp)
{
    uint32_t start_location = (uint32_t)ftell(fp);
    fseek(fp, 0L, SEEK_END);
    uint32_t file_size = (uint32_t)ftell(fp);
    fseek(fp, (long)start_location, SEEK_SET); // return to initial position
    return file_size;
}

int PcapReader::set_input_file_name(std::string in_file_name)
{
    if (!in_file_name.empty())
    {
        input_file_name = in_file_name;
        return OK;
    }
    return FAIL;
}

std::string PcapReader::get_input_file_name()
{
    return input_file_name;
}

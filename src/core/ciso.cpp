#include "ciso.h"

int CISO::open_file(std::string path)
{
    if (path.empty())
    {
        path = m_file_dialog.open_file("All Files (*.*)\0*.*\0").c_str();
    }
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (!result)
        return -1; // TODO

    return 0;
}

int CISO::save_file()
{
    // TODO

    CPPHeaderGen gen;

    return gen.create_header(doc);
}

int CISO::save_as_file()
{
    printf(m_file_dialog.save_file("All Files (*.*)\0*.*\0").c_str());
    return 0;
}

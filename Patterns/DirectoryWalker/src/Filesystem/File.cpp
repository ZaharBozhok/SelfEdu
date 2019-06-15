#include "File.h"

namespace fs = FileSystem;

bool fs::File::IsDirectory(const File& f)
{
    return (f.Mode() & S_IFDIR);
}

fs::File::File(const std::string& path)
{
    processPath(path);
    getFileMode();
}
fs::File::File(const std::string& path, mode_t mode)
{
    processPath(path);
    m_mode = mode;
}
mode_t fs::File::Mode() const
{
    return m_mode;
}
const std::string& fs::File::Path() const
{
    return m_path;
}
const std::string& fs::File::Name() const
{
    return m_name;
}
void fs::File::getFileMode()
{
    struct stat filestat;
    if (stat(m_path.c_str(), &filestat))
    {
        throw std::runtime_error("Can't retireve file mode");
    }
    m_mode = filestat.st_mode;
}
void fs::File::processPath(const std::string& path)
{
    if (true == path.empty())
    {
        throw std::runtime_error("Empty path");
    }
    char* realname = canonicalize_file_name(path.c_str());
    if (NULL == realname)
    {
        throw std::runtime_error("Can't get realname");
    }
    m_path = realname;
    m_name = basename(realname);
    free(realname);
}

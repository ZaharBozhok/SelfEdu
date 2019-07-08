#ifndef FILE_H
#define FILE_H

#include <sys/stat.h>
#include <string>
#include <stdexcept>
#include <libgen.h>

namespace FileSystem
{
    class File
    {
        public:
            File() = default;
            explicit File(const std::string& path);
            explicit File(const std::string& path, mode_t mode);
            mode_t Mode() const;
            const std::string& Path() const;
            const std::string& Name() const;
            void Name(const std::string& newName);
            void Commit();
        public:
            static bool IsDirectory(const File& f);
        private:
            void getFileMode();
            void processPath(const std::string& path);
        private:
            std::string m_path;
            std::string m_name;
            mode_t m_mode;
    };
};

#endif //FILE_H
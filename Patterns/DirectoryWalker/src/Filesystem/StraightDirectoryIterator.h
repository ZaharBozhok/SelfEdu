#ifndef STRAIGHTDIRECTORYITERATOR_H
#define STRAIGHTDIRECTORYITERATOR_H

#include "DirectoryIterator.h"
#include <dirent.h>
#include <sys/types.h>
#include "File.h"

namespace FileSystem
{

    class StraightDirectoryIterator : public DirectoryIterator
    {
        public:
            StraightDirectoryIterator(const File& file);
            File& operator*() override;
            File* operator->() override;
            explicit operator bool() const override;
            DirectoryIterator& operator++() override;
            bool operator==(const StraightDirectoryIterator& val) const;
            bool operator!=(const StraightDirectoryIterator& val) const;
        public:
            static StraightDirectoryIterator end();
        private:
            StraightDirectoryIterator();
            void openDir();
            void skipDots();
            void getNext();
        private:
            File m_iterableDir;
            File m_currentFile;
            DIR* m_dir;
            dirent* m_dirent;
    };
};
#endif // STRAIGHTDIRECTORYITERATOR_H
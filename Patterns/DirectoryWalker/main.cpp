#include<iostream>
#include<string>
#include <sys/stat.h>
#include <vector>
#include <dirent.h>
#include <memory>
#include <limits.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <stack>
#include <functional>

namespace FileSystem
{
    class IDataStructure;
    class ADataStructure;
    class File;
    class Directory;
    class AFileIterator;
    class DirectoryWalker;
    bool isDir(IDataStructure* dataStruct);

    struct IDataStructure
    {
        virtual ~IDataStructure() {}
        virtual const std::string& GetName() const = 0;
        virtual const std::string& GetFullPath() const = 0;
        virtual mode_t GetMode() const = 0;
        virtual void LoadData() = 0;
        virtual const std::vector<IDataStructure*>& GetChildren() const = 0;
    };

    class ADataStructure : public IDataStructure
    {
        public:
            ADataStructure(const std::string& path)
            {
                if (path.empty())
                {
                    throw std::runtime_error("Empty path passed");
                }
                char* realname = canonicalize_file_name(path.c_str());
                if (NULL == realpath)
                {
                    throw std::runtime_error("Can't resolve realpath");
                }
                m_fullPath = realname;
                char* basenamebuff = strdup(realname);
                m_name = basename(basenamebuff);
                free(basenamebuff);
                free(realname);
                struct stat fileStat;
                if (stat(m_fullPath.c_str(), &fileStat))
                {
                    throw std::runtime_error("Can't retireve file mode");
                }
                m_mode = fileStat.st_mode;
            }
            virtual const std::string& GetName() const override
            {
                return m_name;
            }
            virtual const std::string& GetFullPath() const override
            {
                return m_fullPath;
            }
            virtual mode_t GetMode() const override
            {
                return m_mode;
            }
        private:
            std::string m_fullPath;
            std::string m_name;
            mode_t m_mode;
    };

    class File : public ADataStructure
    {
        public:
            File(const std::string& fullPath) : ADataStructure(fullPath)
            {
            }
            const std::vector<IDataStructure*>& GetChildren() const
            {
                throw std::runtime_error("File has no children");
            }
            void LoadData() override
            {
                //Load additional info about file
            }
    };

    class Directory : public ADataStructure
    {
        public:
            Directory(const std::string& fullPath) : ADataStructure(fullPath)
            {
                m_dir = opendir(GetFullPath().c_str());
                if (NULL == m_dir)
                {
                    throw std::runtime_error("Can't open directory");
                }
            }
            ~Directory()
            {
                if (0 != closedir(m_dir))
                {
                    std::cerr << "Can't close directory" << std::endl;
                }
                for (size_t i = 0; i < m_files.size(); i++)
                {
                    delete m_files[i];
                }
            }
            void LoadData() override
            {
                struct dirent* dirent;
                while ((dirent = readdir(m_dir)) != NULL)
                {
                    if (dirent->d_type & DT_DIR)
                    {
                        if (strcmp(dirent->d_name, ".") == 0 || (strcmp(dirent->d_name, "..") == 0))
                        {
                            continue;
                        }
                        m_files.emplace_back(new Directory(GetFullPath() + "/" + dirent->d_name));
                    }
                    else
                    {
                        m_files.emplace_back(new File(GetFullPath() + "/" + dirent->d_name));
                    }
                }
            }
            const std::vector<IDataStructure*>& GetChildren() const
            {
                return m_files;
            }
        private:
            DIR* m_dir;
            std::vector<IDataStructure*> m_files;
    };

    template<class T>
    struct IIterator
    {
        virtual ~IIterator() {}
        virtual const IIterator& operator++() = 0;
        virtual T& operator*() = 0;
        virtual explicit operator bool() const = 0;
    };

    class AFileIterator : public IIterator<IDataStructure>
    {

    };

    class DumbFileIterator : public AFileIterator
    {
            struct IterableDataStruct
            {
                IterableDataStruct(IDataStructure* dataStruct) : current(dataStruct), currentChildIndex(0)
                {
                    if (isDir(dataStruct))
                    {
                        children = dataStruct->GetChildren();
                    }
                }
                IDataStructure* current;
                size_t currentChildIndex;
                std::vector<IDataStructure*> children;
            };
        public:
            explicit DumbFileIterator(IDataStructure* dataStruct) : m_currentDataStruct(dataStruct)
            {
                m_stack.push(IterableDataStruct(dataStruct));
            }
            explicit operator bool() const override
            {
                return !m_stack.empty();
            }
            IDataStructure& operator*() override
            {
                return *m_currentDataStruct;
            }
            const IIterator& operator++() override
            {
                m_currentDataStruct = nullptr;
                IterableDataStruct& currIt = m_stack.top();
                if (!currIt.children.empty())
                {
                    if (currIt.currentChildIndex < currIt.children.size())
                    {
                        m_currentDataStruct = currIt.children[currIt.currentChildIndex];
                        m_currentDataStruct->LoadData();
                        currIt.currentChildIndex++;
                        if (isDir(m_currentDataStruct))
                        {
                            m_stack.push(IterableDataStruct(m_currentDataStruct));
                        }
                    }
                    else
                    {
                        ChopHead();
                    }
                }
                else
                {
                    ChopHead();
                }
            }
        private:
            void ChopHead()
            {
                while(true)
                {
                    m_stack.pop();
                    if (m_stack.empty())
                    {
                        return;
                    }
                    IterableDataStruct& currIt = m_stack.top();
                    currIt.currentChildIndex++;
                    if (currIt.currentChildIndex < currIt.children.size())
                    {
                        m_currentDataStruct = currIt.children[currIt.currentChildIndex];
                        m_currentDataStruct->LoadData(); 
                        currIt.currentChildIndex++;
                        if (isDir(m_currentDataStruct))
                        {
                            m_stack.push(IterableDataStruct(m_currentDataStruct));
                        }
                        return;
                    }
                }
            }
        private:
            std::stack<IterableDataStruct> m_stack;
            IDataStructure* m_currentDataStruct;
    };

    template<class T>
    struct IWalker
    {
        virtual ~IWalker() {}
        virtual void Walk() = 0;
        virtual void SetHandler(const std::function<void(const T&)>& handler) = 0;
    };

    class DirectoryWalker : public IWalker<IDataStructure>
    {
        public:
            DirectoryWalker(AFileIterator& fileIterator) : m_fileIterator(fileIterator)
            {

            }
            void Walk() override
            {
                while (m_fileIterator)
                {
                    if (m_handler)
                    {
                        m_handler(*m_fileIterator);
                        ++m_fileIterator;
                    }
                }
            }
            void SetHandler(const std::function<void(const IDataStructure&)>& handler)
            {
                m_handler = handler;
            }
        private:
            AFileIterator& m_fileIterator;
            std::function<void(const IDataStructure&)> m_handler;
    };

    bool isDir(IDataStructure* dataStruct)
    {
        auto mode = dataStruct->GetMode();
        return (mode & S_IFDIR);
    }
    IDataStructure* DataStructureFactory(const std::string& path)
    {
        struct stat sb;
        if (stat(path.c_str(), &sb) == -1)
        {
            throw std::runtime_error("Can't resolve data struct by path");
        }
        if (sb.st_mode & S_IFDIR)
        {
            return new Directory(path);
        }
        else
        {
            return new File(path);
        }
    }
};


int main(int argc, char* argv[])
{
    std::string path;
    if (argc == 2)
    {
        path = argv[1];
    }
    else
    {
        path = argv[0];
    }


    using namespace FileSystem;
    {
        IDataStructure* file = DataStructureFactory(path);
        file->LoadData();
        DumbFileIterator iter(file);
        DirectoryWalker walker(iter);
        std::function<void(const IDataStructure&)> handler =
            [](const IDataStructure & dataStruct)->void
        {
            std::cout << dataStruct.GetFullPath() << std::endl;
        };
        walker.SetHandler(handler);
        walker.Walk();
        delete file;
    }
    return 0;
}
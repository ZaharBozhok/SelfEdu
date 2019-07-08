#ifndef FILEMUTATOR_H
#define FILEMUTATOR_H

#include "Mutator.h"

#include <File.h>

namespace FileMutation
{
    using FileMutator = Mutator<FileSystem::File>;
    using FileMutatorChain = MutatorChain<FileSystem::File, FileMutator>;

    class FileMutatorFacade : public FileMutator
    {
        public:
            void Mutate(FileSystem::File& file) override
            {
                m_mutatorChain.Mutate(file);
            }
            void AddMutator(FileMutator* mutator)
            {
                m_mutators.push_back(mutator);
                m_mutatorChain.AddMutator(mutator);
            }
            ~FileMutatorFacade()
            {
                for(size_t i=0; i<m_mutators.size(); ++i)
                {
                    delete m_mutators[i];
                }
            }
        private:
            std::vector<FileMutator*> m_mutators;
            FileMutatorChain m_mutatorChain;
    };

    struct TextToFileNameAppender : public FileMutator
    {
            TextToFileNameAppender(const std::string& text) : m_text(text)
            {}
            void Mutate(FileSystem::File& file) override
            {
                auto name = file.Name();
                auto index = name.find('.');
                if (index == std::string::npos)
                {
                    /* No file extension found, just appending to the end */
                    index = name.size() - 1;
                }
                name.insert(index, m_text);
                file.Name(name);
            }
        private:
            std::string m_text;
    };

    struct StringFromNameReplacer : public FileMutator
    {
            StringFromNameReplacer(const std::string& toFind, const std::string& toReplace) : m_toFind(toFind), m_toReplace(toReplace)
            {}
            void Mutate(FileSystem::File& file) override
            {
                auto name = file.Name();
                size_t index = 0;
                while (true)
                {
                    index = name.find(m_toFind, index);
                    if (index == std::string::npos)
                    {
                        break;
                    }
                    name.replace(index, m_toReplace.size(), m_toReplace);
                    index += m_toReplace.size();
                }
                file.Name(name);
            }
        private:
            std::string m_toFind;
            std::string m_toReplace;
    };
};

#endif //FILEMUTATOR_H
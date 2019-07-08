#ifndef FILEMUTATORFACADEFACTORY_H
#define FILEMUTATORFACADEFACTORY_H

#include "FileMutator.h"

class FileMutatorFacadeFactory
{

        static FileMutation::FileMutator* CreateFileMutator(std::vector<std::string>& str)
        {
            size_t index = 0;
            auto& type = str.at(index);
            FileMutation::FileMutator* mutator;
            if (type == "Name.Append")
            {
                mutator = new FileMutation::TextToFileNameAppender(str.at(++index));
            }
            else if (type == "Name.Replace")
            {
                mutator = new FileMutation::StringFromNameReplacer(str.at(++index), str.at(++index));
            }
            str.erase(str.begin(), str.begin() + index);
            return mutator;
        }
    public:
        static FileMutation::FileMutatorFacade CreateFileMutatorFacade(std::vector<std::string> str)
        {
            FileMutation::FileMutatorFacade fileMutatorFacade;
            while (!str.empty())
            {
                fileMutatorFacade.AddMutator(CreateFileMutator(str));
            }
            return fileMutatorFacade;
        }
};

#endif //FILEMUTATORFACADEFACTORY_H
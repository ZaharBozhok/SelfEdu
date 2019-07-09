#ifndef FILEMUTATORFACADEFACTORY_H
#define FILEMUTATORFACADEFACTORY_H

#include "FileMutator.h"
#include <stdexcept>

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
            else
            {
                throw std::runtime_error("Unknown parameter");
            }
            
            str.erase(str.begin(), str.begin() + index + 1);
            return mutator;
        }
    public:
        static void CreateFileMutatorFacade(FileMutation::FileMutatorFacade& fileMutatorFacade, std::vector<std::string> str)
        {
            try
            {
                while (!str.empty())
                {
                    fileMutatorFacade.AddMutator(CreateFileMutator(str));
                }
            }
            catch (const std::out_of_range& ex)
            {
                std::cerr << "Wrong number of parameters, error : " << ex.what() << std::endl;
            }
        }
};

#endif //FILEMUTATORFACADEFACTORY_H
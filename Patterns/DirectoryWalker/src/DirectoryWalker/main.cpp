#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

#include <File.h>
#include <RecursiveDirectoryIterator.h>
#include <StraightDirectoryIterator.h>

#include "DirectoryWalker.h"
#include "StreamWrapper.h"
#include "SocketWrapper.h"
#include "WritablesFactory.h"
#include "DirectoryIteratorFactory.h"
#include "FileMutatorFacadeFactory.h"
#include "StringToIteratorAdapter.h"
#include "StringToWritableAdapter.h"
#include "Utils.h"

namespace fs = FileSystem;

namespace
{
    auto CopyStringsToVector(char* argv[], size_t start, size_t end)
    {
        std::vector<std::string> vec;
        for (auto i = start; i < end; ++i)
        {
            vec.push_back(argv[i]);
        }
        return vec;
    }
};

int main(int argc, char* argv[])
{
    try
    {
        std::unique_ptr<fs::DirectoryIterator> dirIter(
            DirectoryIteratorFactory::CreateIterator(
                GetIterator(argc, argv), Utils::GetPath(argc, argv)
            )
        );
        std::unique_ptr<Writable> writable(
            WritablesFactory::CreateWritable(
                GetWritable(argc, argv)
            )
        );

        FileMutation::FileMutatorFacade fileMutatorFacade;
        if (argc >= 5)
        {
            std::vector<std::string> str = CopyStringsToVector(argv, 4, argc);
            FileMutatorFacadeFactory::CreateFileMutatorFacade(fileMutatorFacade, str);
        }

        DirectoryWalker directoryWalker(dirIter.get(),
                                        [&writable, &fileMutatorFacade](fs::File & file)
        {
            /* Logging old one name */
            writable->Write(file.Name());

            /* Mutating file */
            fileMutatorFacade.Mutate(file);
            writable->Write(" -> " + file.Name() + "\n");
        });
        directoryWalker.Walk();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "DirectoryWalker exited with error : " << ex.what() << std::endl;
        return -1;
    }
    return 0;
}
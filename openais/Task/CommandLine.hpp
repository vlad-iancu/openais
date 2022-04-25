#ifndef OPENAIS_TASK_COMMANDLINE_H
#define OPENAIS_TASK_COMMANDLINE_H

#include <Task/Config.hpp>

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <vector>

using namespace openais::task;

namespace openais
{
    namespace task
    {
        boost::optional<std::pair<Config, Config>> ParseCommandLineOptions(int argc, char **argv, bool &help);
    } // namespace task
    
} // namespace openais



#endif
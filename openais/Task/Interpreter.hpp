#ifndef OPENAIS_TASK_INTERPRETER_H
#define OPENAIS_TASK_INTERPRETER_H

#include <Task/Config.hpp>
#include <mutex>

namespace openais 
{
    
    namespace task
    {
        class Interpreter
        {
            public:
                Interpreter();

                /**
                 * @brief Acquires th Python GIL from the main thread, then it
                 * constructs a new interpreter,
                 * adds searchPath into sys.path
                 * and then releases the Python GIL back to main thread.
                 * It is worth noting that Interpreter::Interpreter(), Interpreter::Get(),
                 * and Interpreter::~Interpreter() are mutually thread safe, which
                 * means that all of these functions are using a scope on a unique global
                 * mutex, that is due to the fact that some Python C API functions
                 * require the current interpreter to hold the GIL while making certain
                 * operations
                 *
                 * @param searchPath The path used to search Python modules
                 * associated with this application
                 */
                Interpreter(const std::string &searchPath);

                /**
                 * Destroys the Python interpreter associated with this object
                 */
                ~Interpreter();

            public:
                /**
                 * @brief Populates the config parameter with the data from the given
                 * Python module name.
                 * Be careful, the openais::task::config is operating directly
                 * on Python objects (PyObject*) so they will be no longer valid
                 * after the interpreter associated with them is destroyed
                 */
                void Get(const std::string &mod, Config &config);

            public:
                /**
                 * @brief This function is called by the openais::task::Main
                 * with the thread state of __main__ interpreter
                 */
                static void Initialize(PyThreadState *mainThread);

            private:
                /**
                 * @brief Wheter or not the __main__ interpreter is currently holding
                 * the Python GIL
                 */
                static bool IsMainInterpreterHoldingGIL();

                /**
                 * @brief Locks the g_mainInterpreterLock mutex
                 * After this function returns the caller is responsible for
                 * taking the Python GIL from the __main__ interpreter
                 */
                static void RequestGILFromMainInterpreter();

                /**
                 * Locks the g_mainInterpreterLock mutex
                 * After this function returns the caller is responsible for
                 * taking the Python GIL from the __main__ interpreter
                 */
                static void ReleaseGILToMainInterpreter();
                static bool g_isMainInterpreterHoldingGIL;
                static PyThreadState *g_mainThreadState;
                static std::mutex g_mainInterpreterLock;

            private:
                PyThreadState *m_threadState;
                std::string m_searchPath;
                PyObject *m_configDir;
        };
    }

}

#endif

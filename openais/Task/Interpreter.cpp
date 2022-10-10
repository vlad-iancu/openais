#include <Task/Interpreter.hpp>
#include <iostream>

using namespace openais::task;

bool Interpreter::g_isMainInterpreterHoldingGIL;
std::mutex Interpreter::g_mainInterpreterLock;
PyThreadState* Interpreter::g_mainThreadState;

Interpreter::Interpreter()
    :
        Interpreter("")
{
}

Interpreter::Interpreter(const std::string &searchPath)
    : 
        m_searchPath(searchPath)
{
    RequestGILFromMainInterpreter();
    //Also acquires python GIL
    m_threadState = Py_NewInterpreter();
    PyThreadState *prevTs = PyEval_SaveThread();
    PyEval_AcquireThread(m_threadState);
    if(!searchPath.empty())
    {
        PyObject *modulePath = PySys_GetObject("path");
        PyObject *configDir = PyUnicode_FromString(m_searchPath.c_str());
        m_configDir = configDir;
        PyList_Append(modulePath, configDir);
    }
    PyEval_ReleaseThread(m_threadState);
    PyEval_RestoreThread(prevTs);
    ReleaseGILToMainInterpreter();
}

Interpreter::~Interpreter()
{
    RequestGILFromMainInterpreter();
    Py_XDECREF(m_configDir);
    Py_EndInterpreter(m_threadState);
    ReleaseGILToMainInterpreter();
}

void Interpreter::Get(const std::string &mod, Config &config)
{
    RequestGILFromMainInterpreter();
    PyThreadState *prevTs = PyEval_SaveThread();
    PyThreadState *ts = PyThreadState_New(m_threadState->interp);
    PyEval_RestoreThread(ts);

    GetPythonConfig(mod, config);

    PyThreadState_Clear(ts);
    PyThreadState_DeleteCurrent();
    PyEval_RestoreThread(prevTs);
    ReleaseGILToMainInterpreter();
}

void Interpreter::Initialize(PyThreadState *mainThreadState)
{
    g_isMainInterpreterHoldingGIL = true;
    g_mainThreadState = mainThreadState;
}

void Interpreter::RequestGILFromMainInterpreter()
{
    g_mainInterpreterLock.lock();
    g_isMainInterpreterHoldingGIL = false;
    
}

void Interpreter::ReleaseGILToMainInterpreter()
{
    g_isMainInterpreterHoldingGIL = true;
    g_mainInterpreterLock.unlock();
}

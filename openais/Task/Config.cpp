#include <Task/Config.hpp>
#include <vector>
#include <cstdint>
#include <stdexcept>

using namespace openais::task;

void Config::FromPythonObject(PyObject *obj)
{
    if (PyCallable_Check(obj))
    {
        return;
    }
    // std::unique_ptr<Config> config = std::make_unique<Config>(obj);
    m_value = obj;
    if (PyLong_Check(obj))
    {
    }
    else if (PyFloat_Check(obj))
    {
    }
    else if (PyUnicode_Check(obj))
    {
    }
    else if (PyList_Check(obj))
    {
        for (Py_ssize_t i = 0; i < PyList_Size(obj); i++)
        {
            PyObject *pItem = PyList_GetItem(obj, i);
            Config *config = new Config();
            config->FromPythonObject(pItem);
            m_children.push_back(config);
        }
    }
    else if (PyTuple_Check(obj))
    {
        for (Py_ssize_t i = 0; i < PyTuple_Size(obj); i++)
        {
            PyObject *pItem = PyTuple_GetItem(obj, i);
            Config *config = new Config();
            config->FromPythonObject(pItem);
            m_children.push_back(config);
        }
    }
    else if (PyDict_Check(obj))
    {
        PyObject *pDictItems, *pItem;
        pDictItems = PyDict_Items(obj);
        for (Py_ssize_t i = 0; i < PyList_Size(pDictItems); i++)
        {
            pItem = PyList_GetItem(pDictItems, i);
            // pItemValue = PyTuple_GetItem(pItem, 1);
            Config *config = new Config();
            config->FromPythonObject(pItem);
            m_children.push_back(config);
        }
    }
    else
    {
        PyObject *pAttrs = PyObject_Dir(obj);
        PyObject *pElement;
        PyObject *pItem;
        PyObject *pEntry;
        PyObject *pName;
        for (Py_ssize_t i = 0; i < PyList_Size(pAttrs); i++)
        {
            pElement = PyList_GetItem(pAttrs, i);
            const char *fieldName = PyUnicode_AsUTF8(pElement);
            // if field is not a "dunder"
            if (strncmp(fieldName, "__", 2) ||
                strncmp(fieldName + (strlen(fieldName) - 2), "__", 2))
            {
                pItem = PyObject_GetAttrString(obj, fieldName);
                if (PyCallable_Check(pItem))
                {
                    continue;
                }
                pEntry = PyTuple_New(2);
                pName = PyUnicode_FromString(fieldName);
                PyTuple_SetItem(pEntry, 0, pName);
                PyTuple_SetItem(pEntry, 1, pItem);
                Config *config = new Config();
                config->FromPythonObject(pEntry);
                m_children.push_back(config);
            }
        }
    }
}

template <>
long Config::Get<long>() const
{
    if (!PyLong_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a long value");
    }
    return PyLong_AsLong(m_value);
}

template <>
long Config::Get<long>(const long &defaultValue) const
{
    if (!PyLong_Check(m_value))
    {
        return defaultValue;
    }
    return PyLong_AsLong(m_value);
}

template <>
std::size_t Config::Get<std::size_t>() const
{
    if (!PyLong_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a long value");
    }
    return (std::size_t)PyLong_AsSize_t(m_value);
}

template <>
std::size_t Config::Get<std::size_t>(const std::size_t &defaultValue) const
{
    if (!PyLong_Check(m_value))
    {
        return defaultValue;
    }
    return PyLong_AsSize_t(m_value);
}

template <>
int Config::Get<int>() const
{
    if (!PyLong_Check(m_value))
    {
        throw std::runtime_error("Config does not hold an int value");
    }
    return (int)PyLong_AsLong(m_value);
}

template <>
int Config::Get<int>(const int &defaultValue) const
{
    if (!PyLong_Check(m_value))
    {
        return defaultValue;
    }
    return (int)PyLong_AsLong(m_value);
}


template <>
short Config::Get<short>(const short &defaultValue) const
{
    if (!PyLong_Check(m_value))
    {
        return defaultValue;
    }
    return (short)PyLong_AsLong(m_value);
}

template <>
short Config::Get<short>() const
{
    if (!PyLong_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a short value");
    }
    return (short)PyLong_AsLong(m_value);
}

template <>
unsigned short Config::Get<unsigned short>(const unsigned short &defaultValue) const
{
    if (!PyLong_Check(m_value))
    {
        return defaultValue;
    }
    return (unsigned short)PyLong_AsLong(m_value);
}

template <>
unsigned short Config::Get<unsigned short>() const
{
    if (!PyLong_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a short value");
    }
    return (unsigned short)PyLong_AsLong(m_value);
}

template <>
unsigned Config::Get<unsigned>(const unsigned &defaultValue) const
{
    if (!PyLong_Check(m_value))
    {
        return defaultValue;
    }
    return (unsigned)PyLong_AsLong(m_value);
}

template <>
unsigned Config::Get<unsigned>() const
{
    if (!PyLong_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a short value");
    }
    return (unsigned)PyLong_AsLong(m_value);
}

template <>
std::string Config::Get<std::string>() const
{
    if (!PyUnicode_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a string value");
    }
    std::string str(PyUnicode_AsUTF8(m_value));
    return str;
}

template <>
std::string Config::Get<std::string>(const std::string &defaultValue) const
{
    if (!PyUnicode_Check(m_value))
    {
        return defaultValue;
    }
    std::string str(PyUnicode_AsUTF8(m_value));
    return str;
}

template <>
double Config::Get<double>() const
{
    if (!PyFloat_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a double value");
    }
    return PyFloat_AsDouble(m_value);
}

template <>
double Config::Get<double>(const double &defaultValue) const
{
    if (!PyFloat_Check(m_value))
    {
        return defaultValue;
    }
    return PyFloat_AsDouble(m_value);
}
template <>
float Config::Get<float>() const
{
    if (!PyFloat_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a double value");
    }
    return (float)PyFloat_AsDouble(m_value);
}

template <>
float Config::Get<float>(const float &defaultValue) const
{
    if (!PyFloat_Check(m_value))
    {
        return defaultValue;
    }
    return (float)PyFloat_AsDouble(m_value);
}
/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-local-addr" */
template <>
const boost::ptr_vector<Config> &Config::Get<const boost::ptr_vector<Config> &>() const
{
    if (!PyList_Check(m_value) && !PyTuple_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a list value");
    }
    return m_children;
}
/* #pragma GCC diagnostic pop */

const Config &Config::operator[](const std::string &name) const
{
    if (PyDict_Check(m_value))
    {
        for (const Config &config : m_children)
        {
            PyObject *pItem = config.m_value;
            PyObject *pKey = PyTuple_GetItem(pItem, 0);
            if (PyUnicode_Check(pKey))
            {
                const char *keyName = PyUnicode_AsUTF8(pKey);
                if (!strcmp(keyName, name.c_str()))
                {
                    return config.m_children[1];
                }
            }
        }
    }
    if (PyObject_HasAttrString(m_value, name.c_str()))
    {
        for (const Config &config : m_children)
        {
            PyObject *pItem = config.m_value;
            PyObject *pKey = PyTuple_GetItem(pItem, 0);
            if (PyUnicode_Check(pKey))
            {
                const char *keyName = PyUnicode_AsUTF8(pKey);
                if (!strcmp(keyName, name.c_str()))
                {
                    return config.m_children[1];
                }
            }
        }
    }
    throw std::invalid_argument("key " + name + " not found");
}

const Config &Config::operator[](Py_ssize_t index) const
{
    if (PyList_Check(m_value))
    {
        return m_children[index];
    }
    if (PyTuple_Check(m_value))
    {
        return m_children[index];
    }
    if (PyDict_Check(m_value))
    {
        for (const Config &config : m_children)
        {
            if (PyLong_Check(config.m_value))
            {
                if (PyLong_AsLong(config.m_value) == index)
                {
                    return config;
                }
            }
        }
    }
    throw std::out_of_range("Index out of range in Config");
}

boost::ptr_vector<Config>::iterator Config::begin()
{
    return m_children.begin();
}
boost::ptr_vector<Config>::const_iterator Config::begin() const
{
    return m_children.begin();
}
boost::ptr_vector<Config>::iterator Config::end()
{
    return m_children.end();
}
boost::ptr_vector<Config>::const_iterator Config::end() const
{
    return m_children.end();
}
boost::ptr_vector<Config>::const_iterator Config::cbegin() const
{
    return m_children.cbegin();
}
boost::ptr_vector<Config>::const_iterator Config::cend() const
{
    return m_children.cend();
}
boost::ptr_vector<Config>::reverse_iterator Config::rbegin()
{
    return m_children.rbegin();
}
boost::ptr_vector<Config>::reverse_iterator Config::rend()
{
    return m_children.rend();
}
boost::ptr_vector<Config>::const_reverse_iterator Config::crbegin() const
{
    return m_children.crbegin();
}
boost::ptr_vector<Config>::const_reverse_iterator Config::crend() const
{
    return m_children.crend();
}

size_t Config::Size() const
{
    return m_children.size();
}

std::string Config::ToString() const
{
    PyObject *str = PyObject_Str(m_value); 
    const char *pyStr = PyUnicode_AsUTF8(str); 
    std::string result; 
    result = pyStr;
    Py_DECREF(str);
    return result;
}

std::string Config::PyType() const
{
    if(PyList_Check(m_value))
    {
        return "PyList";
    }
    if(PyDictItems_Check(m_value))
    {
        return "PyDict";
    }
    if(PyUnicode_Check(m_value))
    {
        return "PyUnicode";
    }
    if(PyTuple_Check(m_value))
    {
        return "PyTuple";
    }
    if(PyLong_Check(m_value))
    {
        return "PyLong";
    }
    if(PyFloat_Check(m_value))
    {
        return "PyFloat";
    }
    if(PyCallable_Check(m_value))
    {
        return "PyCallable";
    }
    return "PyObject";
}

void openais::task::GetPythonConfig(std::string module, Config &config)
{
    PyObject *pModule, *pModuleDict;
    pModule = PyImport_ImportModule(module.c_str());
    pModuleDict = PyModule_GetDict(pModule);
    config.FromPythonObject(pModuleDict);
}

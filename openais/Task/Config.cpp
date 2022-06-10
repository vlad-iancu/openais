#include <Task/Config.hpp>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <iostream>

using namespace openais::task;

void Config::FromPythonObject(PyObject *obj)
{
    // std::unique_ptr<Config> config = std::make_unique<Config>(obj);
    m_value = obj;
    if (PyLong_Check(obj))
    {
        // std::cout << "We have a long: " << PyLong_AsLong(m_value) << std::endl;
    }
    else if (PyFloat_Check(obj))
    {
        // std::cout << "We have a float: " << PyFloat_AsDouble(m_value) << std::endl;
    }
    else if (PyUnicode_Check(obj))
    {
        // std::cout << "We have a string: " << PyUnicode_AsUTF8(m_value) << std::endl;
    }
    else if (PyList_Check(obj))
    {
        // std::cout << "We have a list" << obj  << std::endl;
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
        // std::cout << "We have a tuple " << obj << std::endl;
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
        // std::cout << "We have a dict " << obj << std::endl;
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
double Config::Get<double>() const
{
    if (!PyFloat_Check(m_value))
    {
        throw std::runtime_error("Config does not hold a double value");
    }
    return PyFloat_AsDouble(m_value);
}

/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-local-addr" */
template <>
const boost::ptr_vector<Config>& Config::Get<const boost::ptr_vector<Config>&>() const
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
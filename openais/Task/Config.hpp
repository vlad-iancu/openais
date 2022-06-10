#ifndef OPENAIS_CONFIG_H
#define OPENAIS_CONFIG_H

#include <map>
#include <string>
#include <variant>
#include <iterator>
#include <cstddef>
#include <boost/property_tree/ptree.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <Python.h>

namespace openais
{
    namespace task
    {
        using string = std::string;
        using ConfigValue = std::variant<double, string, uint64_t>;
        // using Config = std::map<string, ConfigValue>;
        using JsonConfig = boost::property_tree::ptree;

        // Config ParseJsonConfig(const JsonConfig &jsonConfig);

        class Config
        {
        public:
            /* Since there are a finite amount of possible values, the template will be implemented
               in source file
            */
            template <typename T>
            T Get() const;

            const Config &operator[](const std::string &name) const;
            const Config &operator[](Py_ssize_t index) const;

            void FromPythonObject(PyObject *obj);

            typedef boost::ptr_vector<Config>::iterator iterator;

            boost::ptr_vector<Config>::iterator begin();
            boost::ptr_vector<Config>::const_iterator begin() const;
            boost::ptr_vector<Config>::iterator end();
            boost::ptr_vector<Config>::const_iterator end() const;
            boost::ptr_vector<Config>::const_iterator cbegin() const;
            boost::ptr_vector<Config>::const_iterator cend() const;
            boost::ptr_vector<Config>::reverse_iterator rbegin();
            boost::ptr_vector<Config>::reverse_iterator rend();
            boost::ptr_vector<Config>::const_reverse_iterator crbegin() const;
            boost::ptr_vector<Config>::const_reverse_iterator crend() const;

        private:
            PyObject *m_value;
            boost::ptr_vector<Config> m_children;
        };

    } // namespace task

} // namespace openais

#endif
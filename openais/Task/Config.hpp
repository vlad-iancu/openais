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
        /**
         * This class is responsible for representing Python objects which can be retrieved
         * by the application for configuration purposes
         */
        class Config
        {
        public:
            template <typename T>
            T Get() const;
            template <typename T>
            T Get(const T& defaultValue) const;

            const Config &operator[](const std::string &name) const;
            const Config &operator[](Py_ssize_t index) const;

            /**
             * @brief The number of elements in the configuration, only available in
             */
            size_t Size() const;
            std::string ToString() const;
            std::string PyType() const;
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

        void GetPythonConfig(std::string mod, Config &config);
    } // namespace task

} // namespace openais

#endif

#ifndef ATHENA_DATAMANAGERFACTORY_HPP
#define ATHENA_DATAMANAGERFACTORY_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "DataManager.hpp"
#include "CsvStorage.hpp"

namespace abstract_game {

    class DataManagerFactory {
    public:
        DataManagerFactory() = delete;

        /**
         * @brief Factory method to create a DataManager instance.
         *
         * @param type The type of DataManager to create.
         * @return A unique_ptr to the created DataManager instance.
         */
        static std::unique_ptr<DataManager> create(std::string const &type);
    };

} // abstract_game

#endif //ATHENA_DATAMANAGERFACTORY_HPP

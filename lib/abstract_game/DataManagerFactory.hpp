#pragma once

#include <memory>
#include <string>

#include "DataManager.hpp"

namespace abstract_game {
    /**
     * @brief Factory class for creating DataManager instances.
     */
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

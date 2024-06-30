#pragma once

#include <memory>
#include <string>

#include "DataManager.hpp"

namespace abstract_game {
    /**
     * @brief The DataManagerFactory class is responsible for creating DataManager instances.
     *
     * This class provides a factory method to create DataManager instances based on the specified type.
     * It returns a unique_ptr to the created DataManager instance.
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

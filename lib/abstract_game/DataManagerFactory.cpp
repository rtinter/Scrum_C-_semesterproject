#include "DataManagerFactory.hpp"

namespace abstract_game {

    std::unique_ptr<DataManager> DataManagerFactory::create(std::string const &type) {
        if (type == "CsvManager") {
            return std::make_unique<CsvStorage>();
        }
        // Add other types here if needed, e.g. SQLManager
        return nullptr;
    }

} // abstract_game
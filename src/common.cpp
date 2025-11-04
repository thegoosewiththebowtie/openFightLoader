/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */

#include "common.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
namespace v::common {
    void gxctCreatePackage(const std::unordered_map<std::string , std::vector<char>>& arg_files , const std::string& arg_package_name) {
        std::ofstream pkg(arg_package_name, std::ios::binary);
        uint32_t      file_count = arg_files.size();
        pkg.write(reinterpret_cast<char*>(&file_count), sizeof(file_count));
        for(const auto& [filename, data] : arg_files) {
            uint32_t size = data.size();
            pkg.write(reinterpret_cast<char*>(&size), sizeof(size));
            pkg.write(filename.c_str(), static_cast<long long>(filename.size() + 1));
            pkg.write(data.data(), static_cast<long long>(data.size()));
        }
    }

    std::unordered_map<std::string , std::vector<char>> gxctReadEntirePackage(const std::string& arg_package_name) {
        std::ifstream                                       pkg(arg_package_name, std::ios::binary);
        std::unordered_map<std::string , std::vector<char>> files;
        uint32_t file_count;
        pkg.read(reinterpret_cast<char*>(&file_count), sizeof(file_count));
        for(uint32_t i = 0 ; i < file_count ; ++i) {
            uint32_t size;
            pkg.read(reinterpret_cast<char*>(&size), sizeof(size));
            std::string filename;
            std::getline(pkg, filename, '\0');
            std::vector<char> data(size);
            pkg.read(data.data(), size);
            files[filename] = std::move(data);
        }
        return files;
    }
    std::vector<char> gxctLoadFile(const std::string& arg_filepath) {
        std::ifstream file(arg_filepath, std::ios::binary | std::ios::ate);
        std::vector<char> buffer(file.tellg());
        file.seekg(0);
        file.read(buffer.data(), static_cast<long long>(buffer.size()));
        return buffer;
    }
}

/* [≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡▲≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡] */

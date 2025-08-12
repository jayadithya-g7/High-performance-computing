#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <omp.h>


using namespace std;


std::size_t read_file(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    omp_set_num_threads(4);
    std::size_t size=file.tellg();
    file.seekg(0,std::ios::beg);

    std::vector<char> buffer(size);
    file.read(buffer.data(), size);

    std::cout << "Thread " << omp_get_thread_num()
              << " read " << size << " bytes from " << filename << std::endl;

    return size;
}

int main(){

std::vector<std::string> filenames = {
        "random_data_file_1024.bin",
        "random_data_file_1048576.bin",
        "random_data_file_1073741824.bin"
    };

    #pragma omp parallel for
    for (int i = 0; i < filenames.size(); ++i) {
        read_file(filenames[i]);
    }

    return 0;

}


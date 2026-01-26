#ifndef IO_HPP
#define IO_HPP

#include <fstream>
#include <string>
#include <iostream>

class IO {
    private:
        std::fstream file_stream;

    public:
        IO(const std::string &file_path);
        ~IO();
        std::fstream getFileStream();
};

#endif

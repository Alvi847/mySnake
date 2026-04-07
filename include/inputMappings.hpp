#pragma once
#include <unordered_map>
#include <string>

class InputMappings{
    public:
        InputMappings(){}

        int get(std::string name) const;

        void addMapping(std::string name, int value);

        void changeMapping(std::string name, int newValue);

    private:

    std::unordered_map<std::string, int> mappings;
};

class MappingError : public std::exception {
private:
    std::string msg;
public:
    // Constructor que recibe un mensaje
    explicit MappingError(std::string path);

    // Para devolver el mensaje
    const char* what() const noexcept override {
        return msg.c_str();
    }
};
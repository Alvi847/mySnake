#include <inputMappings.hpp>

int InputMappings::get(std::string name) const{
    if(mappings.find(name) != mappings.end()){
        return mappings.find(name)->second;
    }
    else
        throw MappingError(name);
}

void InputMappings::addMapping(std::string name, int value){
    mappings.insert_or_assign(name, value);
}

void InputMappings::changeMapping(std::string name, int newValue){
    if(mappings.find(name) != mappings.end()){
        mappings.erase(name);
        mappings.insert_or_assign(name, newValue);
    }
    else
        throw MappingError(name);
}

MappingError::MappingError(std::string str) {
	msg = std::string("Error: El mapping " + str + " no está asignado\n");
}
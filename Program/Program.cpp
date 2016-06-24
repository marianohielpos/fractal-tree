#include <iostream>
#include <fstream>
#include <string.h>
#include <boost/program_options.hpp>

#include "../Logic/FractalTree.hpp"
#include "../Common/Register.hpp"

#define PATH "./production.bin"

namespace po = boost::program_options;

int main(int argc, char *argv[]){

    std::unique_ptr<FractalTree> fractalTree(new FractalTree(PATH));

    po::options_description desc("Allowed options");

    desc.add_options()
        ("help", "Produce help message")
        ("set", "Set a register, must have id, code and description")
        ("get", "Retrive a register, id must be handled")
        ("delete", "Delete a register, id must be handled")
        ("id", po::value<uint32_t>(), "The register id")
        ("code", po::value<std::string>(), "The register code")
        ("description", po::value<std::string>(), "The register description")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
    } else if (vm.count("set") && vm.count("description") && vm.count("code") && vm.count("id")) {
        uint32_t id = vm["id"].as<uint32_t>();
        std::string code = vm["code"].as<std::string>();
        std::string description = vm["description"].as<std::string>();

        if( code.length() != 3 || description.length() > 1000 ){
            std::cout << "Error. Code must be 3 characters long and description under 1000" << std::endl;
            return 0;
        }
        Register _register = Register(id, code.c_str(), description.c_str());
        if(fractalTree->setRegister(&_register)){
            std::cout << "Ok" << std::endl;
            return 0;
        }
        std::cout << "Error" << std::endl;
    } else if(vm.count("get") && vm.count("id")){
        Register* _register = fractalTree->getRegister(vm["id"].as<uint32_t>());
        std::cout << "Id: " << _register->getId() << std::endl;
        std::cout << "Code: " << _register->getCode() << std::endl;
        std::cout << "Description: " << _register->getDescription() << std::endl;
        delete _register;
        return 0;
    } else if(vm.count("delete") && vm.count("id")){
        if( fractalTree->deleteRegister(vm["id"].as<uint32_t>()) ){
            std::cout << "Ok" << std::endl;
            return 0;
        }
        std::cout << "Not found" << std::endl;
    }  else{
        std::cout << "Invalid option" << std::endl;
    }

    return 0;
}

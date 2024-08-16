#include "../include/utils.hpp"

// Funcao que converte o formato dos endereços recebidos para uma string simples que representa o endereço da forma que ele deve 
// ser retornado ao usuário, para simplificar a classe stations e o a redabilidade do codigo em geral 
std::string addressify(std::string idend, std::string id_logrado, 
                     std::string sigla_tipo, std::string nome_logra,
                     std::string numero_imo,std::string nome_bairr,
                     std::string nome_regio,std::string cep) 
    {   
        std::string address = std::string();
        address.append(sigla_tipo);
        address.append(" ");
        address.append(nome_logra);
        address.append(", ");    
        address.append(numero_imo);
        address.append(", ");
        address.append(nome_bairr);
        address.append(", ");
        address.append(nome_regio);
        address.append(", ");
        address.append(cep);
        return address;

    }
